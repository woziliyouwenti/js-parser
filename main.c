
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "lexer.h"
#include "parser.h"
#include "parser_api.h"
#include "ast.h"

/*
 * main.c 负责将“文件 -> 解析结果”串联起来，步骤如下：
 *   1. read_file 读取 JS 源码并放入 lexer_input 缓冲。
 *   2. reset_lexer / parser_reset 初始化 ASI 状态以及语法检查标志。
 *   3. 运行 yyparse()，若无语法错误则打印“语法检查通过”，否则输出错误数。
 * 该文件不关心具体语法规则，而是提供最小可执行入口，便于命令行或测试脚本调用。
 */

// 全局变量定义
unsigned char *lexer_input = NULL;
int yylineno = 1;
int asi_enabled = 1;        // ASI是否开启，也就是是否启用自动分号插入逻辑
int asi_newline = 0;        // ASI是否遇到换行，也就是最近一次读取到的字符是否为换行符
int asi_can_insert = 0;     // ASI是否可以插入分号，也就是说当前token是否可以结束语句
int asi_pending = 0;        // ASI是否需要插入分号，也就是说需要暂存一个待插入的虚拟分号
int asi_force_insert = 0;   // ASI是否强制插入分号，也就是说即便遇到限制性token也要先插入分号
int asi_keyword_pending = 0;// ASI是否关键字待定，也就是说上一个token是否为return/break/continue/throw
int asi_report_enabled = 1;

typedef struct {
    char ch;
    int line;
    int column;
    int object_like;
    int allow_semicolon;
} Delimiter;

static int matching_open(char close) {
    switch (close) {
        case ')': return '(';
        case ']': return '[';
        case '}': return '{';
        default: return 0;
    }
}

static const char *missing_close_message(char open) {
    switch (open) {
        case '(': return "missing ')'";
        case '[': return "missing ']'";
        case '{': return "missing '}'";
        default: return "missing closing delimiter";
    }
}

static int is_top_level_starter(const char *p) {
    const char *keywords[] = {
        "function", "var", "let", "const", "class", "if", "for", "while",
        "switch", "try", "return", "throw", NULL
    };
    int i;

    while (*p == ' ' || *p == '\t' || *p == '\v' || *p == '\f') {
        p++;
    }

    for (i = 0; keywords[i] != NULL; i++) {
        size_t len = strlen(keywords[i]);
        if (strncmp(p, keywords[i], len) == 0) {
            char next = p[len];
            if (!((next >= 'a' && next <= 'z') ||
                  (next >= 'A' && next <= 'Z') ||
                  (next >= '0' && next <= '9') ||
                  next == '_')) {
                return 1;
            }
        }
    }

    return 0;
}

static int previous_significant_char(const char *input, const char *p) {
    while (p > input) {
        p--;
        if (*p != ' ' && *p != '\t' && *p != '\v' && *p != '\f' &&
            *p != '\r' && *p != '\n') {
            return (unsigned char)*p;
        }
    }
    return 0;
}

static int previous_word_is(const char *input, const char *p, const char *word) {
    const char *end;
    const char *start;
    size_t len;

    while (p > input) {
        p--;
        if (*p != ' ' && *p != '\t' && *p != '\v' && *p != '\f' &&
            *p != '\r' && *p != '\n') {
            break;
        }
    }

    end = p + 1;
    while (p >= input &&
           ((*p >= 'a' && *p <= 'z') ||
            (*p >= 'A' && *p <= 'Z') ||
            (*p >= '0' && *p <= '9') ||
            *p == '_')) {
        p--;
    }
    start = p + 1;
    len = strlen(word);

    return (size_t)(end - start) == len && strncmp(start, word, len) == 0;
}

static int report_missing_from_stack(Delimiter *stack, int *top, char open,
                                     int line, int column, const char *near) {
    int i;
    for (i = *top - 1; i >= 0; i--) {
        if (stack[i].ch == open) {
            fprintf(stderr,
                    "Syntax error (line %d, column %d): %s before %s "
                    "(opened at line %d, column %d)\n",
                    line, column, missing_close_message(open), near,
                    stack[i].line, stack[i].column);
            *top = i;
            return 1;
        }
    }
    return 0;
}

static int diagnose_delimiters(const char *input) {
    Delimiter stack[512];
    int top = 0;
    int errors = 0;
    int line = 1;
    int column = 1;
    const char *p = input;

    while (*p != '\0') {
        char c = *p;

        if (c == '/' && p[1] == '/') {
            const char *comment_start = p;
            const char *comment_end = p;
            int mentions_rbrace = 0;

            while (*comment_end != '\0' && *comment_end != '\n') {
                if (*comment_end == '}') {
                    mentions_rbrace = 1;
                }
                comment_end++;
            }

            if (top > 0 && stack[top - 1].ch == '{' && (mentions_rbrace || is_top_level_starter(p + 2))) {
                fprintf(stderr,
                        "Syntax error (line %d, column %d): missing '}' before line comment "
                        "(opened at line %d, column %d)\n",
                        line, column, stack[top - 1].line, stack[top - 1].column);
                top--;
                errors++;
            }
            p = comment_start;
            while (*p != '\0' && *p != '\n') {
                p++;
                column++;
            }
            continue;
        }

        if (c == '/' && p[1] == '*') {
            int start_line = line;
            int start_column = column;
            p += 2;
            column += 2;
            while (*p != '\0' && !(p[0] == '*' && p[1] == '/')) {
                if (*p == '\n') {
                    line++;
                    column = 1;
                } else {
                    column++;
                }
                p++;
            }
            if (*p != '\0') {
                p += 2;
                column += 2;
            } else {
                fprintf(stderr,
                        "Syntax error (line %d, column %d): unterminated block comment\n",
                        start_line, start_column);
                errors++;
            }
            continue;
        }

        if (c == '"' || c == '\'') {
            char quote = c;
            int start_line = line;
            int start_column = column;
            int closed = 0;
            p++;
            column++;
            while (*p != '\0') {
                if (*p == '\\' && p[1] != '\0') {
                    p += 2;
                    column += 2;
                    continue;
                }
                if (*p == quote) {
                    p++;
                    column++;
                    closed = 1;
                    break;
                }
                if (*p == '\n') {
                    break;
                }
                if (*p == '\r') {
                    break;
                }
                column++;
                p++;
            }
            if (!closed) {
                if (*p == '\n' || *p == '\r') {
                    fprintf(stderr,
                            "Syntax error (line %d, column %d): unterminated string literal before line break\n",
                            start_line, start_column);
                } else {
                    fprintf(stderr,
                            "Syntax error (line %d, column %d): unterminated string literal before end of file\n",
                            start_line, start_column);
                }
                errors++;
            }
            continue;
        }

        if (c == '`') {
            int start_line = line;
            int start_column = column;
            int closed = 0;
            p++;
            column++;
            while (*p != '\0') {
                if (*p == '\\' && p[1] != '\0') {
                    p += 2;
                    column += 2;
                    continue;
                }
                if (*p == '`') {
                    p++;
                    column++;
                    closed = 1;
                    break;
                }
                if (*p == '\n') {
                    line++;
                    column = 1;
                } else {
                    column++;
                }
                p++;
            }
            if (!closed) {
                fprintf(stderr,
                        "Syntax error (line %d, column %d): unterminated template literal\n",
                        start_line, start_column);
                errors++;
            }
            continue;
        }

        if (c == '(' || c == '[' || c == '{') {
            if (top < (int)(sizeof(stack) / sizeof(stack[0]))) {
                stack[top].ch = c;
                stack[top].line = line;
                stack[top].column = column;
                stack[top].object_like = (c == '{' && previous_significant_char(input, p) == '=');
                stack[top].allow_semicolon = (c == '(' && previous_word_is(input, p, "for"));
                top++;
            }
        } else if (c == ';') {
            if (top > 0 &&
                ((stack[top - 1].ch == '(' && !stack[top - 1].allow_semicolon) ||
                 stack[top - 1].object_like)) {
                fprintf(stderr,
                        "Syntax error (line %d, column %d): %s before ';' "
                        "(opened at line %d, column %d)\n",
                        line, column, missing_close_message(stack[top - 1].ch),
                        stack[top - 1].line, stack[top - 1].column);
                top--;
                errors++;
            }
        } else if (c == ')' || c == ']' || c == '}') {
            int expected = matching_open(c);
            if (top > 0 && stack[top - 1].ch == expected) {
                top--;
            } else if (top > 0 && stack[top - 1].ch != expected) {
                fprintf(stderr,
                        "Syntax error (line %d, column %d): %s before '%c' "
                        "(opened at line %d, column %d)\n",
                        line, column, missing_close_message(stack[top - 1].ch), c,
                        stack[top - 1].line, stack[top - 1].column);
                top--;
                if (top > 0 && stack[top - 1].ch == expected) {
                    top--;
                }
                errors++;
            } else if (top > 0 && report_missing_from_stack(stack, &top, expected, line, column, "closing delimiter")) {
                errors++;
            } else {
                fprintf(stderr,
                        "Syntax error (line %d, column %d): unexpected '%c'\n",
                        line, column, c);
                errors++;
            }
        }

        if (c == '\n') {
            line++;
            column = 1;
        } else {
            column++;
        }
        p++;
    }

    while (top > 0) {
        top--;
        fprintf(stderr,
                "Syntax error (line %d, column %d): %s before end of file\n",
                stack[top].line, stack[top].column, missing_close_message(stack[top].ch));
        errors++;
    }

    return errors;
}

// read_file: 将整个文件读入内存，供 lexer 直接从内存缓冲读取。
// 返回值需要由调用者负责释放；出错时返回 NULL 并打印错误信息。
char* read_file(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "Error: cannot open file %s\n", filename);
        return NULL;
    }
    
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    char *buffer = malloc(length + 1);
    if (!buffer) {
        fclose(file);
        return NULL;
    }
    
    fread(buffer, 1, length, file);
    buffer[length] = '\0';
    
    fclose(file);
    return buffer;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <javascript-file>\n", argv[0]);
        fprintf(stderr, "Example: %s test.js\n", argv[0]);
        return 1;
    }
    
    char *input = read_file(argv[1]);
    if (!input) {
        return 1;
    }
    
    // 设置词法分析器输入
    lexer_input = (unsigned char *)input;
    yylineno = 1;
    asi_enabled = 1;
    asi_newline = 0;
    asi_can_insert = 0;
    asi_pending = 0;
    asi_force_insert = 0;
    asi_keyword_pending = 0;
    parser_reset();
    reset_lexer();
    
    printf("Parsing JavaScript file: %s\n", argv[1]);
    printf("ASI (automatic semicolon insertion) enabled\n");
    printf("========================================\n\n");
    
    int result = 1;
    int valid = 0;
    int total_errors = diagnose_delimiters(input);

    if (total_errors == 0) {
        // 开始语法分析
        result = yyparse();
        valid = parser_is_valid();
        total_errors = parser_error_total();
    }
    
    printf("\n========================================\n");
    if (result == 0 && valid) {
        ASTNode *ast;
        char dot_filename[512];
        char html_filename[512];

        printf("Parse complete. Syntax check passed.\n");
        printf("\nAST:\n");
        ast = parser_get_ast();
        ast_print(ast);

        snprintf(dot_filename, sizeof(dot_filename), "%s.ast.dot", argv[1]);
        if (ast_write_dot(ast, dot_filename)) {
            printf("\nAST visualization written to: %s\n", dot_filename);
            printf("Render with: dot -Tpng \"%s\" -o ast.png\n", dot_filename);
        } else {
            fprintf(stderr, "Warning: cannot write AST visualization file %s\n", dot_filename);
        }
        snprintf(html_filename, sizeof(html_filename), "%s.ast.html", argv[1]);
        if (ast_write_html(ast, html_filename)) {
            printf("AST HTML visualization written to: %s\n", html_filename);
        } else {
            fprintf(stderr, "Warning: cannot write AST HTML file %s\n", html_filename);
        }
        ast_free(ast);
    } else {
        if (!valid) {
            printf("Syntax check failed with %d error(s).\n", total_errors);
        } else {
            printf("Parse failed. Bison returned %d.\n", result);
        }
    }
    
    free(input);
    return (result == 0 && valid) ? 0 : 1;
}


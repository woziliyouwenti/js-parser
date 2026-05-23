#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "parser.h"

#ifdef _WIN32
static char *js_strndup(const char *s, size_t n) {
    char *copy = (char *)malloc(n + 1);
    if (!copy) {
        return NULL;
    }
    memcpy(copy, s, n);
    copy[n] = '\0';
    return copy;
}
#else
#define js_strndup strndup
#endif

// 扫描器状态：re2c 通过 cursor/marker 推进输入；line/column 用于错误和 ASI 报告。
typedef struct {
    const char *start;
    const char *cursor;
    const char *marker;
    const char *ctxmarker;
    int line;
    int column;
    int last_token_line;
    int last_token_column;
    int last_token;
    int brace_stack[256];
    int brace_top;
    int last_closed_brace_was_object;
} Scanner;

static Scanner scanner;

// 初始化词法分析器状态。每次重新解析同一份输入时都要调用。
void init_scanner(const char *input) {
    scanner.start = input;
    scanner.cursor = input;
    scanner.marker = NULL;
    scanner.ctxmarker = NULL;
    scanner.line = 1;
    scanner.column = 1;
    scanner.last_token_line = 1;
    scanner.last_token_column = 1;
    scanner.last_token = 0;
    scanner.brace_top = 0;
    scanner.last_closed_brace_was_object = 0;
}

// 从输入开头重新计算当前位置。当前项目输入较小，这种写法简单可靠。
static void update_position() {
    const char *p = scanner.start;
    int line = 1;
    int column = 1;
    
    while (p < scanner.cursor) {
        if (*p == '\n') {
            line++;
            column = 1;
        } else {
            column++;
        }
        p++;
    }
    
    scanner.line = line;
    scanner.column = column;
    yylineno = line;
}

// 计算某个源码指针对应的 1-based 行号和列号。
static void pointer_position(const char *target, int *line, int *column) {
    const char *p = scanner.start;
    int current_line = 1;
    int current_column = 1;

    while (p < target) {
        if (*p == '\n') {
            current_line++;
            current_column = 1;
        } else {
            current_column++;
        }
        p++;
    }

    *line = current_line;
    *column = current_column;
}

// 打印 ASI 虚拟分号插入位置。AST 阶段复用 lexer 时会关闭该日志。
static void print_asi_insertion(const char *after_char) {
    int line;
    int column;

    if (!asi_report_enabled) {
        return;
    }
    pointer_position(after_char, &line, &column);
    printf("ASI: inserted virtual semicolon at line %d, column %d\n",
           line, column + 1);
}

// 返回当前行最后一个有效源码字符；行尾注释不参与 ASI 判断。
static const char *effective_line_end(const char *newline_start) {
    const char *line_start = newline_start;
    const char *p;

    while (line_start > scanner.start && line_start[-1] != '\n' && line_start[-1] != '\r') {
        line_start--;
    }

    for (p = line_start; p + 1 < newline_start; p++) {
        if (p[0] == '/' && p[1] == '/') {
            newline_start = p;
            break;
        }
    }

    p = newline_start;
    while (p > line_start) {
        --p;
        if (*p != ' ' && *p != '\t' && *p != '\v' && *p != '\f') {
            return p;
        }
    }

    return NULL;
}

// 返回 token 前维护少量上下文，用于区分对象字面量的 } 和普通代码块的 }。
static int token(int tok) {
    scanner.last_token_line = scanner.line;
    scanner.last_token_column = scanner.column;

    if (tok == LBRACE) {
        int is_object = 0;
        switch (scanner.last_token) {
            case ASSIGN:
            case PLUS_ASSIGN:
            case MINUS_ASSIGN:
            case MULTIPLY_ASSIGN:
            case DIVIDE_ASSIGN:
            case MODULO_ASSIGN:
            case EXPONENT_ASSIGN:
            case AND_ASSIGN:
            case OR_ASSIGN:
            case XOR_ASSIGN:
            case LEFT_SHIFT_ASSIGN:
            case RIGHT_SHIFT_ASSIGN:
            case UNSIGNED_RIGHT_SHIFT_ASSIGN:
            case LPAREN:
            case LBRACKET:
            case COMMA:
            case COLON:
            case QUESTION:
            case RETURN:
            case THROW:
            case ARROW:
                is_object = 1;
                break;
        }

        if (scanner.brace_top < (int)(sizeof(scanner.brace_stack) / sizeof(scanner.brace_stack[0]))) {
            scanner.brace_stack[scanner.brace_top++] = is_object;
        }
        scanner.last_closed_brace_was_object = 0;
    } else if (tok == RBRACE) {
        scanner.last_closed_brace_was_object = 0;
        if (scanner.brace_top > 0) {
            scanner.last_closed_brace_was_object = scanner.brace_stack[--scanner.brace_top];
        }
    } else if (tok != SEMICOLON) {
        scanner.last_closed_brace_was_object = 0;
    }

    scanner.last_token = tok;
    return tok;
}

/*!re2c
    re2c:define:YYCTYPE = "unsigned char";
    re2c:define:YYCURSOR = scanner.cursor;
    re2c:define:YYMARKER = scanner.marker;
    re2c:define:YYCTXMARKER = scanner.ctxmarker;
    re2c:yyfill:enable = 0;
    re2c:flags:8 = 1;
    // 基础字符类。
    DIGIT = [0-9];
    HEXDIGIT = [0-9a-fA-F];
    IDENT_START = [_a-zA-Z];
    IDENT_PART = [_a-zA-Z0-9];
    WHITESPACE = [ \t\v\f];
    LINE_TERMINATOR = [\r\n] | "\r\n";
    
    // ASI 统一在换行处判断，符合条件时返回一个虚拟 SEMICOLON。
    ASI_NEWLINE = LINE_TERMINATOR;
*/

int yylex(void) {
    const char *start;
    
scan:
    start = scanner.cursor;
    update_position();
    
/*!re2c
    // 空白和注释不产生 token。
    WHITESPACE+ { goto scan; }
    
    "/*" {
        while (*scanner.cursor != '\0') {
            if (scanner.cursor[0] == '*' && scanner.cursor[1] == '/') {
                scanner.cursor += 2;
                goto scan;
            }
            scanner.cursor++;
        }
        return token(ERROR_TOKEN);
    }
    
    "//" [^\r\n]* { goto scan; }
    
    // 自动分号插入：只在上一行能结束语句、下一 token 不会破坏结构时插入。
    ASI_NEWLINE {
        const char *p = effective_line_end(start);
        if (p == NULL) {
            goto scan;
        }
        if (strchr("{[(,.:;?*/%<>=!&|^~", *p) != NULL) {
            goto scan;
        }
        if ((*p == '+' || *p == '-') && (p == scanner.start || p[-1] != *p)) {
            goto scan;
        }
        if (*p == '}' && !scanner.last_closed_brace_was_object) {
            goto scan;
        }
        const char *q = scanner.cursor;
        while (*q == ' ' || *q == '\t' || *q == '\v' || *q == '\f') {
            ++q;
        }
        if (*q == ']' || *q == ')') {
            goto scan;
        }
        if (*q == '}' && scanner.brace_top > 0 && scanner.brace_stack[scanner.brace_top - 1]) {
            goto scan;
        }
        print_asi_insertion(p);
        return token(SEMICOLON);
    }
    
    // 数字字面量。
    (DIGIT+ [eE] [+-]? DIGIT+) | (DIGIT* "." DIGIT+ ([eE] [+-]? DIGIT+)?) | (DIGIT+ "." DIGIT* ([eE] [+-]? DIGIT+)?) {
        yylval.number = strtod(start, NULL);
        return token(NUMBER);
    }

    DIGIT+ {
        yylval.number = strtod(start, NULL);
        return token(NUMBER);
    }
    
    "0x" HEXDIGIT+ {
        yylval.number = strtol(start, NULL, 16);
        return token(NUMBER);
    }
    
    // 字符串字面量。
    "\"" ([^"\\\r\n\x00] | "\\" [\x01-\xFF])* "\"" {
        yylval.string = js_strndup(start + 1, (scanner.cursor - start) - 2);
        return token(STRING);
    }
    
    "'" ([^'\\\r\n\x00] | "\\" [\x01-\xFF])* "'" {
        yylval.string = js_strndup(start + 1, (scanner.cursor - start) - 2);
        return token(STRING);
    }
    
    // 关键字。当前暂未实现完整 void/await 语义，因此作为普通标识符处理。
    "break" { return token(BREAK); }
    "case" { return token(CASE); }
    "catch" { return token(CATCH); }
    "class" { return token(CLASS); }
    "const" { return token(CONST); }
    "continue" { return token(CONTINUE); }
    "debugger" { return token(DEBUGGER); }
    "default" { return token(DEFAULT); }
    "delete" { return token(DELETE); }
    "do" { return token(DO); }
    "else" { return token(ELSE); }
    "export" { return token(EXPORT); }
    "extends" { return token(EXTENDS); }
    "finally" { return token(FINALLY); }
    "for" { return token(FOR); }
    "function" { return token(FUNCTION); }
    "if" { return token(IF); }
    "import" { return token(IMPORT); }
    "in" { return token(IN); }
    "instanceof" { return token(INSTANCEOF); }
    "let" { return token(LET); }
    "new" { return token(NEW); }
    "return" { return token(RETURN); }
    "super" { return token(SUPER); }
    "switch" { return token(SWITCH); }
    "this" { return token(THIS); }
    "throw" { return token(THROW); }
    "try" { return token(TRY); }
    "typeof" { return token(TYPEOF); }
    "var" { return token(VAR); }
    "void" { yylval.string = js_strndup(start, scanner.cursor - start); return token(IDENTIFIER); }
    "while" { return token(WHILE); }
    "with" { return token(WITH); }
    "yield" { return token(YIELD); }
    "await" { yylval.string = js_strndup(start, scanner.cursor - start); return token(IDENTIFIER); }
    "null" { yylval.string = js_strndup("null", 4); return token(NULL_LITERAL); }
    "true" { return token(TRUE); }
    "false" { return token(FALSE); }
    
    // 标识符。
    IDENT_START IDENT_PART* {
        yylval.string = js_strndup(start, scanner.cursor - start);
        return token(IDENTIFIER);
    }
    
    // 多字符运算符必须写在单字符运算符之前。
    "===" { return token(STRICT_EQUAL); }
    "!==" { return token(STRICT_NOT_EQUAL); }
    "==" { return token(EQUAL); }
    "!=" { return token(NOT_EQUAL); }
    "<=" { return token(LESS_EQUAL); }
    ">=" { return token(GREATER_EQUAL); }
    "&&" { return token(LOGICAL_AND); }
    "||" { return token(LOGICAL_OR); }
    "++" { return token(INCREMENT); }
    "--" { return token(DECREMENT); }
    "<<" { return token(LEFT_SHIFT); }
    ">>" { return token(RIGHT_SHIFT); }
    ">>>" { return token(UNSIGNED_RIGHT_SHIFT); }
    "+=" { return token(PLUS_ASSIGN); }
    "-=" { return token(MINUS_ASSIGN); }
    "*=" { return token(MULTIPLY_ASSIGN); }
    "/=" { return token(DIVIDE_ASSIGN); }
    "%=" { return token(MODULO_ASSIGN); }
    "&=" { return token(AND_ASSIGN); }
    "|=" { return token(OR_ASSIGN); }
    "^=" { return token(XOR_ASSIGN); }
    "<<=" { return token(LEFT_SHIFT_ASSIGN); }
    ">>=" { return token(RIGHT_SHIFT_ASSIGN); }
    ">>>=" { return token(UNSIGNED_RIGHT_SHIFT_ASSIGN); }
    "..." { return token(SPREAD); }
    "**=" { return token(EXPONENT_ASSIGN); }
    "**" { return token(EXPONENT); }
    "??" { return token(NULLISH_COALESCING); }
    "?." { return token(OPTIONAL_CHAINING); }
    "=>" { return token(ARROW); }
    
    // 单字符标点和运算符。
    ";" { return token(SEMICOLON); }
    "," { return token(COMMA); }
    ":" { return token(COLON); }
    "." { return token(DOT); }
    "{" { return token(LBRACE); }
    "}" { return token(RBRACE); }
    "[" { return token(LBRACKET); }
    "]" { return token(RBRACKET); }
    "(" { return token(LPAREN); }
    ")" { return token(RPAREN); }
    "?" { return token(QUESTION); }
    "~" { return token(BITWISE_NOT); }
    "+" { return token(PLUS); }
    "-" { return token(MINUS); }
    "*" { return token(MULTIPLY); }
    "/" { return token(DIVIDE); }
    "%" { return token(MODULO); }
    "<" { return token(LESS); }
    ">" { return token(GREATER); }
    "=" { return token(ASSIGN); }
    "!" { return token(NOT); }
    "&" { return token(BITWISE_AND); }
    "|" { return token(BITWISE_OR); }
    "^" { return token(BITWISE_XOR); }
    
    // re2c EOF 约定：返回 0 给 bison。
    [\000] { return 0; }
    
    // 其他未知字符作为词法错误 token。
    * { return token(ERROR_TOKEN); }
*/
}

// parser/AST 构建器用它读取最近一个 token 的位置。
void get_token_position(int *line, int *column) {
    *line = scanner.last_token_line;
    *column = scanner.last_token_column;
}

// 使用当前 lexer_input 重新开始扫描。
void reset_lexer(void) {
    init_scanner((const char *)lexer_input);
}


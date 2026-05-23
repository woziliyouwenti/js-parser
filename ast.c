#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "lexer.h"
#include "parser.h"

typedef struct {
    int tok;
    char *text;
    int line;
    int column;
    int virtual_semicolon;
} TokenInfo;

struct ASTNode {
    char *kind;
    char *label;
    ASTNode **children;
    int child_count;
    int child_capacity;
};

typedef struct {
    TokenInfo *tokens;
    int count;
    int capacity;
    int pos;
} ASTParser;

static char *ast_strdup(const char *s) {
    size_t len;
    char *copy;

    if (!s) {
        s = "";
    }
    len = strlen(s);
    copy = (char *)malloc(len + 1);
    if (!copy) {
        return NULL;
    }
    memcpy(copy, s, len + 1);
    return copy;
}

ASTNode *ast_new(const char *kind, const char *label) {
    ASTNode *node = (ASTNode *)calloc(1, sizeof(ASTNode));
    if (!node) {
        return NULL;
    }
    node->kind = ast_strdup(kind);
    node->label = ast_strdup(label);
    return node;
}

void ast_add(ASTNode *parent, ASTNode *child) {
    ASTNode **new_children;
    int new_capacity;

    if (!parent || !child) {
        return;
    }
    if (parent->child_count == parent->child_capacity) {
        new_capacity = parent->child_capacity == 0 ? 4 : parent->child_capacity * 2;
        new_children = (ASTNode **)realloc(parent->children, sizeof(ASTNode *) * new_capacity);
        if (!new_children) {
            return;
        }
        parent->children = new_children;
        parent->child_capacity = new_capacity;
    }
    parent->children[parent->child_count++] = child;
}

ASTNode *ast_list(const char *kind, ASTNode *first) {
    ASTNode *node = ast_new(kind, "");
    ast_add(node, first);
    return node;
}

ASTNode *ast_leaf(const char *kind, const char *label) {
    return ast_new(kind, label);
}

ASTNode *ast_unary(const char *kind, const char *op, ASTNode *argument) {
    ASTNode *node = ast_new(kind, op);
    ast_add(node, argument);
    return node;
}

ASTNode *ast_binary(const char *kind, const char *op, ASTNode *left, ASTNode *right) {
    ASTNode *node = ast_new(kind, op);
    ast_add(node, left);
    ast_add(node, right);
    return node;
}

ASTNode *ast_wrap(const char *kind, const char *label, ASTNode *child) {
    ASTNode *node = ast_new(kind, label);
    ast_add(node, child);
    return node;
}

static const char *token_name(int tok) {
    switch (tok) {
        case NUMBER: return "NUMBER";
        case STRING: return "STRING";
        case IDENTIFIER: return "IDENTIFIER";
        case IF: return "if";
        case ELSE: return "else";
        case FOR: return "for";
        case WHILE: return "while";
        case DO: return "do";
        case SWITCH: return "switch";
        case CASE: return "case";
        case DEFAULT: return "default";
        case BREAK: return "break";
        case CONTINUE: return "continue";
        case RETURN: return "return";
        case VAR: return "var";
        case LET: return "let";
        case CONST: return "const";
        case FUNCTION: return "function";
        case CLASS: return "class";
        case THIS: return "this";
        case SUPER: return "super";
        case NEW: return "new";
        case TYPEOF: return "typeof";
        case DELETE: return "delete";
        case INSTANCEOF: return "instanceof";
        case IN: return "in";
        case TRUE: return "true";
        case FALSE: return "false";
        case NULL_LITERAL: return "null";
        case TRY: return "try";
        case CATCH: return "catch";
        case FINALLY: return "finally";
        case THROW: return "throw";
        case WITH: return "with";
        case DEBUGGER: return "debugger";
        case IMPORT: return "import";
        case EXPORT: return "export";
        case YIELD: return "yield";
        case EXTENDS: return "extends";
        case LPAREN: return "(";
        case RPAREN: return ")";
        case LBRACE: return "{";
        case RBRACE: return "}";
        case LBRACKET: return "[";
        case RBRACKET: return "]";
        case SEMICOLON: return ";";
        case COMMA: return ",";
        case DOT: return ".";
        case COLON: return ":";
        case QUESTION: return "?";
        case PLUS: return "+";
        case MINUS: return "-";
        case MULTIPLY: return "*";
        case DIVIDE: return "/";
        case MODULO: return "%";
        case ASSIGN: return "=";
        case PLUS_ASSIGN: return "+=";
        case MINUS_ASSIGN: return "-=";
        case MULTIPLY_ASSIGN: return "*=";
        case DIVIDE_ASSIGN: return "/=";
        case MODULO_ASSIGN: return "%=";
        case EQUAL: return "==";
        case NOT_EQUAL: return "!=";
        case STRICT_EQUAL: return "===";
        case STRICT_NOT_EQUAL: return "!==";
        case LESS: return "<";
        case GREATER: return ">";
        case LESS_EQUAL: return "<=";
        case GREATER_EQUAL: return ">=";
        case LOGICAL_AND: return "&&";
        case LOGICAL_OR: return "||";
        case NOT: return "!";
        case BITWISE_AND: return "&";
        case BITWISE_OR: return "|";
        case BITWISE_XOR: return "^";
        case BITWISE_NOT: return "~";
        case LEFT_SHIFT: return "<<";
        case RIGHT_SHIFT: return ">>";
        case UNSIGNED_RIGHT_SHIFT: return ">>>";
        case LEFT_SHIFT_ASSIGN: return "<<=";
        case RIGHT_SHIFT_ASSIGN: return ">>=";
        case UNSIGNED_RIGHT_SHIFT_ASSIGN: return ">>>=";
        case AND_ASSIGN: return "&=";
        case OR_ASSIGN: return "|=";
        case XOR_ASSIGN: return "^=";
        case INCREMENT: return "++";
        case DECREMENT: return "--";
        case EXPONENT: return "**";
        case EXPONENT_ASSIGN: return "**=";
        case SPREAD: return "...";
        case NULLISH_COALESCING: return "??";
        case OPTIONAL_CHAINING: return "?.";
        case ARROW: return "=>";
        default: return "TOKEN";
    }
}

static void parser_add_token(ASTParser *parser, TokenInfo token) {
    TokenInfo *new_tokens;
    int new_capacity;

    if (parser->count == parser->capacity) {
        new_capacity = parser->capacity == 0 ? 128 : parser->capacity * 2;
        new_tokens = (TokenInfo *)realloc(parser->tokens, sizeof(TokenInfo) * new_capacity);
        if (!new_tokens) {
            return;
        }
        parser->tokens = new_tokens;
        parser->capacity = new_capacity;
    }
    parser->tokens[parser->count++] = token;
}

static void append_text(char *buffer, size_t size, const char *text) {
    if (buffer[0] != '\0') {
        strncat(buffer, " ", size - strlen(buffer) - 1);
    }
    strncat(buffer, text, size - strlen(buffer) - 1);
}

static TokenInfo *peek(ASTParser *parser) {
    if (parser->pos >= parser->count) {
        return NULL;
    }
    return &parser->tokens[parser->pos];
}

static TokenInfo *advance(ASTParser *parser) {
    if (parser->pos >= parser->count) {
        return NULL;
    }
    return &parser->tokens[parser->pos++];
}

static int match(ASTParser *parser, int tok) {
    TokenInfo *token = peek(parser);
    if (token && token->tok == tok) {
        parser->pos++;
        return 1;
    }
    return 0;
}

static ASTNode *parse_statement(ASTParser *parser);

static ASTNode *parse_expression_until(ASTParser *parser, const int *stops, int stop_count) {
    ASTNode *expr = ast_new("Expression", "");
    char label[1024] = "";
    int depth = 0;
    int stop = 0;
    int prev_tok = 0;
    int i;
    TokenInfo *token;

    while ((token = peek(parser)) != NULL) {
        stop = depth == 0 ? 0 : 0;
        if (depth == 0) {
            for (i = 0; i < stop_count; i++) {
                if (token->tok == stops[i]) {
                    stop = 1;
                    break;
                }
            }
        }
        if (stop) {
            break;
        }

        if (token->tok == LBRACE) {
            if (prev_tok == 0 || prev_tok == ASSIGN || prev_tok == COMMA ||
                prev_tok == COLON || prev_tok == LPAREN || prev_tok == LBRACKET ||
                prev_tok == RETURN || prev_tok == ARROW) {
                ast_add(expr, ast_new("ObjectLiteral", "{}"));
            }
            depth++;
        } else if (token->tok == LBRACKET) {
            if (prev_tok == 0 || prev_tok == ASSIGN || prev_tok == COMMA ||
                prev_tok == COLON || prev_tok == LPAREN || prev_tok == LBRACKET ||
                prev_tok == RETURN) {
                ast_add(expr, ast_new("ArrayLiteral", "[]"));
            } else {
                ast_add(expr, ast_new("ComputedMember", "[]"));
            }
            depth++;
        } else if (token->tok == LPAREN) {
            depth++;
        } else if (token->tok == RBRACE || token->tok == RBRACKET || token->tok == RPAREN) {
            if (depth == 0) {
                break;
            }
            depth--;
        }

        append_text(label, sizeof(label), token->text);
        prev_tok = token->tok;
        advance(parser);
    }

    free(expr->label);
    expr->label = ast_strdup(label);
    return expr;
}

static ASTNode *parse_block(ASTParser *parser) {
    ASTNode *block = ast_new("BlockStatement", "");
    if (!match(parser, LBRACE)) {
        return block;
    }
    while (peek(parser) && peek(parser)->tok != RBRACE) {
        ast_add(block, parse_statement(parser));
    }
    match(parser, RBRACE);
    return block;
}

static ASTNode *parse_variable(ASTParser *parser) {
    TokenInfo *kind = advance(parser);
    ASTNode *node = ast_new("VariableDeclaration", kind ? kind->text : "");

    while (peek(parser) && peek(parser)->tok != SEMICOLON && peek(parser)->tok != RBRACE) {
        TokenInfo *id = peek(parser);
        ASTNode *declarator;
        int stops[] = { COMMA, SEMICOLON, RBRACE };

        if (id->tok != IDENTIFIER) {
            ast_add(node, parse_expression_until(parser, stops, 3));
            break;
        }
        advance(parser);
        declarator = ast_new("VariableDeclarator", id->text);
        if (match(parser, ASSIGN)) {
            ast_add(declarator, parse_expression_until(parser, stops, 3));
        }
        ast_add(node, declarator);
        if (!match(parser, COMMA)) {
            break;
        }
    }
    match(parser, SEMICOLON);
    return node;
}

static ASTNode *parse_condition_statement(ASTParser *parser, const char *kind) {
    int stops[] = { RPAREN };
    ASTNode *node = ast_new(kind, "");
    advance(parser);
    if (match(parser, LPAREN)) {
        ast_add(node, parse_expression_until(parser, stops, 1));
        match(parser, RPAREN);
    }
    ast_add(node, parse_statement(parser));
    if (strcmp(kind, "IfStatement") == 0 && match(parser, ELSE)) {
        ast_add(node, parse_statement(parser));
    }
    return node;
}

static ASTNode *parse_function(ASTParser *parser) {
    ASTNode *node = ast_new("FunctionDeclaration", "");
    TokenInfo *name;
    int stops[] = { RPAREN };

    advance(parser);
    name = peek(parser);
    if (name && name->tok == IDENTIFIER) {
        free(node->label);
        node->label = ast_strdup(name->text);
        advance(parser);
    }
    if (match(parser, LPAREN)) {
        ASTNode *params = ast_new("Parameters", "");
        ast_add(params, parse_expression_until(parser, stops, 1));
        ast_add(node, params);
        match(parser, RPAREN);
    }
    ast_add(node, parse_block(parser));
    return node;
}

static ASTNode *parse_for(ASTParser *parser) {
    int stops[] = { RPAREN };
    ASTNode *node = ast_new("ForStatement", "");
    advance(parser);
    if (match(parser, LPAREN)) {
        ast_add(node, parse_expression_until(parser, stops, 1));
        match(parser, RPAREN);
    }
    ast_add(node, parse_statement(parser));
    return node;
}

static ASTNode *parse_do(ASTParser *parser) {
    int stops[] = { RPAREN };
    ASTNode *node = ast_new("DoWhileStatement", "");
    advance(parser);
    ast_add(node, parse_statement(parser));
    if (match(parser, WHILE) && match(parser, LPAREN)) {
        ast_add(node, parse_expression_until(parser, stops, 1));
        match(parser, RPAREN);
    }
    match(parser, SEMICOLON);
    return node;
}

static ASTNode *parse_switch(ASTParser *parser) {
    int stops[] = { RPAREN };
    ASTNode *node = ast_new("SwitchStatement", "");
    advance(parser);
    if (match(parser, LPAREN)) {
        ast_add(node, parse_expression_until(parser, stops, 1));
        match(parser, RPAREN);
    }
    ast_add(node, parse_block(parser));
    return node;
}

static ASTNode *parse_try(ASTParser *parser) {
    ASTNode *node = ast_new("TryStatement", "");
    advance(parser);
    ast_add(node, parse_block(parser));
    if (match(parser, CATCH)) {
        ASTNode *catch_node = ast_new("CatchClause", "");
        if (match(parser, LPAREN)) {
            int stops[] = { RPAREN };
            ast_add(catch_node, parse_expression_until(parser, stops, 1));
            match(parser, RPAREN);
        }
        ast_add(catch_node, parse_block(parser));
        ast_add(node, catch_node);
    }
    if (match(parser, FINALLY)) {
        ASTNode *finally_node = ast_new("FinallyClause", "");
        ast_add(finally_node, parse_block(parser));
        ast_add(node, finally_node);
    }
    return node;
}

static ASTNode *parse_class(ASTParser *parser) {
    ASTNode *node = ast_new("ClassDeclaration", "");
    TokenInfo *name;
    advance(parser);
    name = peek(parser);
    if (name && name->tok == IDENTIFIER) {
        free(node->label);
        node->label = ast_strdup(name->text);
        advance(parser);
    }
    while (peek(parser) && peek(parser)->tok != LBRACE) {
        advance(parser);
    }
    ast_add(node, parse_block(parser));
    return node;
}

static ASTNode *parse_return_like(ASTParser *parser, const char *kind) {
    int stops[] = { SEMICOLON, RBRACE };
    ASTNode *node = ast_new(kind, "");
    advance(parser);
    ast_add(node, parse_expression_until(parser, stops, 2));
    match(parser, SEMICOLON);
    return node;
}

static ASTNode *parse_expression_statement(ASTParser *parser) {
    int stops[] = { SEMICOLON, RBRACE };
    ASTNode *node = ast_new("ExpressionStatement", "");
    ast_add(node, parse_expression_until(parser, stops, 2));
    match(parser, SEMICOLON);
    return node;
}

static ASTNode *parse_statement(ASTParser *parser) {
    TokenInfo *token = peek(parser);
    if (!token) {
        return ast_new("Empty", "");
    }

    switch (token->tok) {
        case LBRACE: return parse_block(parser);
        case VAR:
        case LET:
        case CONST: return parse_variable(parser);
        case FUNCTION: return parse_function(parser);
        case CLASS: return parse_class(parser);
        case IF: return parse_condition_statement(parser, "IfStatement");
        case WHILE: return parse_condition_statement(parser, "WhileStatement");
        case FOR: return parse_for(parser);
        case DO: return parse_do(parser);
        case SWITCH: return parse_switch(parser);
        case TRY: return parse_try(parser);
        case RETURN: return parse_return_like(parser, "ReturnStatement");
        case THROW: return parse_return_like(parser, "ThrowStatement");
        case BREAK:
            advance(parser);
            match(parser, SEMICOLON);
            return ast_new("BreakStatement", "");
        case CONTINUE:
            advance(parser);
            match(parser, SEMICOLON);
            return ast_new("ContinueStatement", "");
        case SEMICOLON:
            advance(parser);
            return ast_new("EmptyStatement", "");
        default:
            return parse_expression_statement(parser);
    }
}

ASTNode *ast_build_from_lexer(void) {
    ASTParser parser;
    int tok;
    int line;
    int column;

    memset(&parser, 0, sizeof(parser));
    reset_lexer();
    asi_report_enabled = 0;

    while ((tok = yylex()) != 0) {
        TokenInfo token;
        get_token_position(&line, &column);
        token.tok = tok;
        token.line = line;
        token.column = column;
        token.virtual_semicolon = tok == SEMICOLON && line != yylineno;
        if (tok == IDENTIFIER || tok == STRING || tok == NULL_LITERAL) {
            token.text = ast_strdup(yylval.string);
        } else if (tok == NUMBER) {
            char number[64];
            snprintf(number, sizeof(number), "%g", yylval.number);
            token.text = ast_strdup(number);
        } else {
            token.text = ast_strdup(token_name(tok));
        }
        parser_add_token(&parser, token);
    }

    asi_report_enabled = 1;
    parser.pos = 0;

    {
        ASTNode *program = ast_new("Program", "");
        int i;
        while (peek(&parser)) {
            ast_add(program, parse_statement(&parser));
        }
        for (i = 0; i < parser.count; i++) {
            free(parser.tokens[i].text);
        }
        free(parser.tokens);
        return program;
    }
}

static void ast_print_inner(ASTNode *node, int depth) {
    int i;
    if (!node) {
        return;
    }
    for (i = 0; i < depth; i++) {
        printf("  ");
    }
    printf("%s", node->kind);
    if (node->label && node->label[0] != '\0') {
        printf(": %s", node->label);
    }
    printf("\n");
    for (i = 0; i < node->child_count; i++) {
        ast_print_inner(node->children[i], depth + 1);
    }
}

void ast_print(ASTNode *node) {
    ast_print_inner(node, 0);
}

static void dot_escape(FILE *file, const char *text) {
    const char *p;
    for (p = text; p && *p; p++) {
        if (*p == '"' || *p == '\\') {
            fputc('\\', file);
        }
        if (*p == '\n' || *p == '\r') {
            fputc(' ', file);
        } else {
            fputc(*p, file);
        }
    }
}

static int ast_write_dot_inner(FILE *file, ASTNode *node, int *next_id) {
    int id;
    int i;
    if (!node) {
        return -1;
    }
    id = (*next_id)++;
    fprintf(file, "  n%d [label=\"", id);
    dot_escape(file, node->kind);
    if (node->label && node->label[0] != '\0') {
        fprintf(file, "\\n");
        dot_escape(file, node->label);
    }
    fprintf(file, "\"];\n");
    for (i = 0; i < node->child_count; i++) {
        int child_id = ast_write_dot_inner(file, node->children[i], next_id);
        if (child_id >= 0) {
            fprintf(file, "  n%d -> n%d;\n", id, child_id);
        }
    }
    return id;
}

int ast_write_dot(ASTNode *node, const char *filename) {
    FILE *file = fopen(filename, "w");
    int next_id = 0;
    if (!file) {
        return 0;
    }
    fprintf(file, "digraph AST {\n");
    fprintf(file, "  node [shape=box, style=\"rounded,filled\", fillcolor=\"#f8fafc\", color=\"#64748b\", fontname=\"Consolas\"];\n");
    fprintf(file, "  edge [color=\"#64748b\"];\n");
    ast_write_dot_inner(file, node, &next_id);
    fprintf(file, "}\n");
    fclose(file);
    return 1;
}

static void html_escape(FILE *file, const char *text) {
    const char *p;
    for (p = text; p && *p; p++) {
        switch (*p) {
            case '&': fputs("&amp;", file); break;
            case '<': fputs("&lt;", file); break;
            case '>': fputs("&gt;", file); break;
            case '"': fputs("&quot;", file); break;
            default: fputc(*p, file); break;
        }
    }
}

static void ast_write_html_inner(FILE *file, ASTNode *node) {
    int i;
    if (!node) {
        return;
    }
    fprintf(file, "<li><span class=\"node\"><strong>");
    html_escape(file, node->kind);
    fprintf(file, "</strong>");
    if (node->label && node->label[0] != '\0') {
        fprintf(file, "<em>");
        html_escape(file, node->label);
        fprintf(file, "</em>");
    }
    fprintf(file, "</span>");
    if (node->child_count > 0) {
        fprintf(file, "<ul>");
        for (i = 0; i < node->child_count; i++) {
            ast_write_html_inner(file, node->children[i]);
        }
        fprintf(file, "</ul>");
    }
    fprintf(file, "</li>");
}

int ast_write_html(ASTNode *node, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        return 0;
    }
    fprintf(file, "<!doctype html><html><head><meta charset=\"utf-8\">");
    fprintf(file, "<title>AST Visualization</title>");
    fprintf(file, "<style>");
    fprintf(file, "body{font-family:Segoe UI,Arial,sans-serif;margin:24px;background:#f8fafc;color:#0f172a}");
    fprintf(file, "h1{font-size:20px;margin:0 0 16px}");
    fprintf(file, "ul{list-style:none;margin:0 0 0 22px;padding:0;border-left:1px solid #cbd5e1}");
    fprintf(file, "li{margin:6px 0 6px 12px;position:relative}");
    fprintf(file, "li:before{content:'';position:absolute;left:-12px;top:14px;width:12px;border-top:1px solid #cbd5e1}");
    fprintf(file, ".node{display:inline-flex;gap:8px;align-items:center;padding:5px 8px;border:1px solid #cbd5e1;border-radius:6px;background:white;box-shadow:0 1px 2px rgba(15,23,42,.06)}");
    fprintf(file, "strong{font-size:13px}.node em{font-style:normal;color:#475569;font-family:Consolas,monospace;font-size:12px}");
    fprintf(file, "</style></head><body><h1>AST Visualization</h1><ul>");
    ast_write_html_inner(file, node);
    fprintf(file, "</ul></body></html>\n");
    fclose(file);
    return 1;
}

void ast_free(ASTNode *node) {
    int i;
    if (!node) {
        return;
    }
    for (i = 0; i < node->child_count; i++) {
        ast_free(node->children[i]);
    }
    free(node->children);
    free(node->kind);
    free(node->label);
    free(node);
}

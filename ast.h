#ifndef AST_H
#define AST_H

typedef struct ASTNode ASTNode;

ASTNode *ast_new(const char *kind, const char *label);
void ast_add(ASTNode *parent, ASTNode *child);
ASTNode *ast_list(const char *kind, ASTNode *first);
ASTNode *ast_leaf(const char *kind, const char *label);
ASTNode *ast_unary(const char *kind, const char *op, ASTNode *argument);
ASTNode *ast_binary(const char *kind, const char *op, ASTNode *left, ASTNode *right);
ASTNode *ast_wrap(const char *kind, const char *label, ASTNode *child);
ASTNode *ast_build_from_lexer(void);
void ast_print(ASTNode *node);
int ast_write_dot(ASTNode *node, const char *filename);
int ast_write_html(ASTNode *node, const char *filename);
void ast_free(ASTNode *node);

#endif

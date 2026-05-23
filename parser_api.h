#ifndef PARSER_API_H
#define PARSER_API_H

#include "ast.h"

// parser_api.h 统一对外暴露语法分析状态，便于主程序查询

// 重置语法分析状态（语法有效标记与错误计数）
void parser_reset(void);

// 当前语法是否有效（无语法错误返回非0）
int parser_is_valid(void);

// 语法错误数量
int parser_error_total(void);

// 返回最近一次成功解析得到的 AST 根节点。
ASTNode *parser_get_ast(void);

#endif


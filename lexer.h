#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>

// 词法分析器状态
extern unsigned char *lexer_input;
extern int yylineno;
extern int asi_enabled;        // ASI是否开启，也就是是否启用自动分号插入逻辑
extern int asi_newline;        // ASI是否遇到换行，也就是最近一次读取到的字符是否为换行符
extern int asi_can_insert;     // ASI是否可以插入分号，也就是说当前token是否可以结束语句
extern int asi_pending;        // ASI是否需要插入分号，也就是说需要暂存一个待插入的虚拟分号
extern int asi_force_insert;   // ASI是否强制插入分号，也就是说即便遇到限制性token也要先插入分号
extern int asi_keyword_pending;// ASI是否关键字待定，也就是说上一个token是否为return/break/continue/throw
extern int asi_report_enabled; // 是否打印 ASI 虚拟分号插入日志

// 词法分析函数
int yylex(void);

// 重置词法分析器
void reset_lexer(void);

// 获取最近一个 token 的位置
void get_token_position(int *line, int *column);

#endif


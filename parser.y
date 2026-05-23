%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "parser_api.h"
#include "ast.h"

/*
 * parser.y 设计原则
 * -----------------
 * 1. 语句层统一要求显式 SEMICOLON，所有 ASI 场景交由 lexer 虚拟插入。
 * 2. StatementList 自身不允许空产生式，通过 StatementListOpt 在需要的位置显式放宽。
 * 3. 将复杂 ECMAScript 语法拆分为“当前已实现的核心子集”，减少 LR(1) 冲突，
 *    当前版本在 bison 中仅剩 7 个 shift/reduce 与 2 个 reduce/reduce 警告。
 * 这些约束让语法文件更易维护，同时向阅读者揭示“为什么某些语法暂未支持”。
 */

// 错误处理
void yyerror(const char *s);
int yylex(void);

// 全局变量
extern unsigned char *lexer_input;
extern int yylineno;

// 语法检查结果
int syntax_valid = 1;
int error_count = 0;
ASTNode *ast_root = NULL;

static ASTNode *number_literal(double value) {
    char text[64];
    snprintf(text, sizeof(text), "%g", value);
    return ast_leaf("Literal", text);
}

%}

%union {
    double number;
    char *string;
    void *node;
}

%define parse.error verbose

// 词法标记
%token <number> NUMBER
%token <string> STRING IDENTIFIER NULL_LITERAL
%token IF ELSE FOR WHILE DO SWITCH CASE DEFAULT BREAK CONTINUE RETURN
%token VAR LET CONST FUNCTION CLASS
%token THIS SUPER NEW TYPEOF DELETE INSTANCEOF IN
%token TRUE FALSE
%token TRY CATCH FINALLY THROW
%token WITH DEBUGGER
%token IMPORT EXPORT
%token YIELD
%token INTERFACE EXTENDS
%token LPAREN RPAREN LBRACE RBRACE LBRACKET RBRACKET
%token SEMICOLON COMMA DOT COLON QUESTION
%token PLUS MINUS MULTIPLY DIVIDE MODULO
%token ASSIGN PLUS_ASSIGN MINUS_ASSIGN MULTIPLY_ASSIGN DIVIDE_ASSIGN MODULO_ASSIGN
%token EQUAL NOT_EQUAL STRICT_EQUAL STRICT_NOT_EQUAL
%token LESS GREATER LESS_EQUAL GREATER_EQUAL
%token LOGICAL_AND LOGICAL_OR NOT
%token BITWISE_AND BITWISE_OR BITWISE_XOR BITWISE_NOT
%token LEFT_SHIFT RIGHT_SHIFT UNSIGNED_RIGHT_SHIFT
%token LEFT_SHIFT_ASSIGN RIGHT_SHIFT_ASSIGN UNSIGNED_RIGHT_SHIFT_ASSIGN
%token AND_ASSIGN OR_ASSIGN XOR_ASSIGN
%token INCREMENT DECREMENT
%token EXPONENT EXPONENT_ASSIGN
%token SPREAD NULLISH_COALESCING OPTIONAL_CHAINING
%token ARROW
%token ERROR_TOKEN

%type <node> Program StatementList StatementListOpt Statement
%type <node> BlockStatement VariableStatement VariableDeclarationList VariableDeclaration
%type <node> EmptyStatement ExpressionStatement IfStatement IterationStatement
%type <node> ContinueStatement BreakStatement ReturnStatement YieldStatement
%type <node> WithStatement LabelledStatement SwitchStatement CaseBlock
%type <node> CaseClausesOpt CaseClauses CaseClause DefaultClause
%type <node> ThrowStatement TryStatement Catch Finally DebuggerStatement
%type <node> FunctionDeclaration FormalParametersOpt FormalParameters
%type <node> ClassDeclaration ClassTail ClassBodyOpt ClassBody ClassElement MethodDefinition
%type <node> Expression ExpressionOpt AssignmentExpression ArrowFunction ArrowParameters ConciseBody
%type <node> ConditionalExpression LogicalORExpression LogicalANDExpression
%type <node> BitwiseORExpression BitwiseXORExpression BitwiseANDExpression
%type <node> EqualityExpression RelationalExpression ShiftExpression
%type <node> AdditiveExpression MultiplicativeExpression UnaryExpression PostfixExpression
%type <node> LeftHandSideExpression NewExpression MemberExpression OptionalExpression
%type <node> CallExpression Arguments ArgumentList PrimaryExpression Literal
%type <node> ArrayLiteral ArrayElementsOpt ElementList ElisionOpt Elision
%type <node> ObjectLiteral PropertyDefinitionsOpt PropertyDefinitionList PropertySeparator
%type <node> SemicolonListOpt SemicolonList PropertyDefinition PropertyName
%type <node> FunctionExpression IdentifierOpt ClassExpression ForBinding

// 优先级和结合性
%right ASSIGN PLUS_ASSIGN MINUS_ASSIGN MULTIPLY_ASSIGN DIVIDE_ASSIGN MODULO_ASSIGN
%right AND_ASSIGN OR_ASSIGN XOR_ASSIGN LEFT_SHIFT_ASSIGN RIGHT_SHIFT_ASSIGN UNSIGNED_RIGHT_SHIFT_ASSIGN
%right EXPONENT_ASSIGN
%right QUESTION COLON
%left LOGICAL_OR
%left NULLISH_COALESCING
%left LOGICAL_AND
%left BITWISE_OR
%left BITWISE_XOR
%left BITWISE_AND
%left EQUAL NOT_EQUAL STRICT_EQUAL STRICT_NOT_EQUAL
%left LESS GREATER LESS_EQUAL GREATER_EQUAL INSTANCEOF IN
%left LEFT_SHIFT RIGHT_SHIFT UNSIGNED_RIGHT_SHIFT
%left PLUS MINUS
%left MULTIPLY DIVIDE MODULO
%right NOT BITWISE_NOT TYPEOF DELETE
%right INCREMENT DECREMENT
%right EXPONENT
%left DOT LBRACKET LPAREN
%right NEW

%%

// 程序入口
Program:
    StatementListOpt { ast_root = ast_wrap("Program", "", $1); $$ = ast_root; }
    ;

// 语句列表
StatementList:
    Statement { $$ = ast_list("StatementList", $1); }
    | StatementList Statement { $$ = $1; ast_add($$, $2); }
    | StatementList error SEMICOLON { $$ = $1; yyerrok; }
    ;

// 语句
Statement:
    BlockStatement { $$ = $1; }
    | VariableStatement { $$ = $1; }
    | EmptyStatement { $$ = $1; }
    | ExpressionStatement { $$ = $1; }
    | IfStatement { $$ = $1; }
    | IterationStatement { $$ = $1; }
    | ContinueStatement { $$ = $1; }
    | BreakStatement { $$ = $1; }
    | ReturnStatement { $$ = $1; }
    | YieldStatement { $$ = $1; }
    | WithStatement { $$ = $1; }
    | LabelledStatement { $$ = $1; }
    | SwitchStatement { $$ = $1; }
    | ThrowStatement { $$ = $1; }
    | TryStatement { $$ = $1; }
    | DebuggerStatement { $$ = $1; }
    | FunctionDeclaration { $$ = $1; }
    | ClassDeclaration { $$ = $1; }
    | error SEMICOLON { $$ = ast_new("ErrorStatement", ""); yyerrok; }
    ;

// 块语句
BlockStatement:
    LBRACE StatementListOpt RBRACE { $$ = ast_wrap("BlockStatement", "", $2); }
    ;

// 变量声明语句
VariableStatement:
    VariableDeclarationList SEMICOLON { $$ = ast_wrap("VariableDeclaration", "", $1); }
    ;

VariableDeclarationList:
    VAR VariableDeclaration { $$ = ast_list("VariableDeclarationList", $2); }
    | LET VariableDeclaration { $$ = ast_list("VariableDeclarationList", $2); }
    | CONST VariableDeclaration { $$ = ast_list("VariableDeclarationList", $2); }
    | VariableDeclarationList COMMA VariableDeclaration { $$ = $1; ast_add($$, $3); }
    ;

VariableDeclaration:
    IDENTIFIER { $$ = ast_new("VariableDeclarator", $1); ast_add($$, ast_leaf("Identifier", $1)); }
    | IDENTIFIER ASSIGN AssignmentExpression { $$ = ast_new("VariableDeclarator", $1); ast_add($$, ast_leaf("Identifier", $1)); ast_add($$, ast_wrap("Initializer", "", $3)); }
    ;

// 空语句
EmptyStatement:
    SEMICOLON { $$ = ast_new("EmptyStatement", ""); }
    ;

// 表达式语句
ExpressionStatement:
    Expression SEMICOLON { $$ = ast_wrap("ExpressionStatement", "", $1); }
    ;

// If语句
IfStatement:
    IF LPAREN Expression RPAREN Statement { $$ = ast_new("IfStatement", ""); ast_add($$, ast_wrap("Test", "", $3)); ast_add($$, ast_wrap("Consequent", "", $5)); }
    | IF LPAREN Expression RPAREN Statement ELSE Statement { $$ = ast_new("IfStatement", ""); ast_add($$, ast_wrap("Test", "", $3)); ast_add($$, ast_wrap("Consequent", "", $5)); ast_add($$, ast_wrap("Alternate", "", $7)); }
    ;

// 迭代语句
IterationStatement:
    WHILE LPAREN Expression RPAREN Statement { $$ = ast_new("WhileStatement", ""); ast_add($$, ast_wrap("Test", "", $3)); ast_add($$, ast_wrap("Body", "", $5)); }
    | DO Statement WHILE LPAREN Expression RPAREN SEMICOLON { $$ = ast_new("DoWhileStatement", ""); ast_add($$, ast_wrap("Body", "", $2)); ast_add($$, ast_wrap("Test", "", $5)); }
    | FOR LPAREN ExpressionOpt SEMICOLON ExpressionOpt SEMICOLON ExpressionOpt RPAREN Statement { $$ = ast_new("ForStatement", ""); ast_add($$, ast_wrap("Init", "", $3)); ast_add($$, ast_wrap("Test", "", $5)); ast_add($$, ast_wrap("Update", "", $7)); ast_add($$, ast_wrap("Body", "", $9)); }
    | FOR LPAREN VariableDeclarationList SEMICOLON ExpressionOpt SEMICOLON ExpressionOpt RPAREN Statement { $$ = ast_new("ForStatement", ""); ast_add($$, ast_wrap("Init", "", $3)); ast_add($$, ast_wrap("Test", "", $5)); ast_add($$, ast_wrap("Update", "", $7)); ast_add($$, ast_wrap("Body", "", $9)); }
    | FOR LPAREN LeftHandSideExpression IN Expression RPAREN Statement { $$ = ast_new("ForInStatement", ""); ast_add($$, ast_wrap("Left", "", $3)); ast_add($$, ast_wrap("Right", "", $5)); ast_add($$, ast_wrap("Body", "", $7)); }
    | FOR LPAREN VAR ForBinding IN Expression RPAREN Statement { $$ = ast_new("ForInStatement", "var"); ast_add($$, ast_wrap("Left", "", $4)); ast_add($$, ast_wrap("Right", "", $6)); ast_add($$, ast_wrap("Body", "", $8)); }
    | FOR LPAREN LET ForBinding IN Expression RPAREN Statement { $$ = ast_new("ForInStatement", "let"); ast_add($$, ast_wrap("Left", "", $4)); ast_add($$, ast_wrap("Right", "", $6)); ast_add($$, ast_wrap("Body", "", $8)); }
    | FOR LPAREN CONST ForBinding IN Expression RPAREN Statement { $$ = ast_new("ForInStatement", "const"); ast_add($$, ast_wrap("Left", "", $4)); ast_add($$, ast_wrap("Right", "", $6)); ast_add($$, ast_wrap("Body", "", $8)); }
    ;

ForBinding:
    IDENTIFIER { $$ = ast_leaf("Identifier", $1); }
    ;

ExpressionOpt:
    /* empty */ { $$ = ast_new("Empty", ""); }
    | Expression { $$ = $1; }
    ;

// Continue语句
ContinueStatement:
    CONTINUE SEMICOLON { $$ = ast_new("ContinueStatement", ""); }
    | CONTINUE IDENTIFIER SEMICOLON { $$ = ast_new("ContinueStatement", $2); }
    ;

// Break语句
BreakStatement:
    BREAK SEMICOLON { $$ = ast_new("BreakStatement", ""); }
    | BREAK IDENTIFIER SEMICOLON { $$ = ast_new("BreakStatement", $2); }
    ;

// Return语句
ReturnStatement:
    RETURN ExpressionOpt SEMICOLON { $$ = ast_wrap("ReturnStatement", "", $2); }
    ;

// With语句
WithStatement:
    WITH LPAREN Expression RPAREN Statement { $$ = ast_new("WithStatement", ""); ast_add($$, ast_wrap("Object", "", $3)); ast_add($$, ast_wrap("Body", "", $5)); }
    ;

// 标签语句
LabelledStatement:
    IDENTIFIER COLON Statement { $$ = ast_new("LabeledStatement", $1); ast_add($$, $3); }
    ;

// Switch语句
SwitchStatement:
    SWITCH LPAREN Expression RPAREN CaseBlock { $$ = ast_new("SwitchStatement", ""); ast_add($$, ast_wrap("Discriminant", "", $3)); ast_add($$, $5); }
    ;

CaseBlock:
    LBRACE CaseClausesOpt RBRACE { $$ = ast_wrap("CaseBlock", "", $2); }
    | LBRACE CaseClausesOpt DefaultClause CaseClausesOpt RBRACE { $$ = ast_new("CaseBlock", ""); ast_add($$, $2); ast_add($$, $3); ast_add($$, $4); }
    ;

CaseClausesOpt:
    /* empty */ { $$ = ast_new("CaseClauses", ""); }
    | CaseClauses { $$ = $1; }
    ;

CaseClauses:
    CaseClause { $$ = ast_list("CaseClauses", $1); }
    | CaseClauses CaseClause { $$ = $1; ast_add($$, $2); }
    ;

CaseClause:
    CASE Expression COLON StatementListOpt { $$ = ast_new("CaseClause", ""); ast_add($$, ast_wrap("Test", "", $2)); ast_add($$, $4); }
    ;

DefaultClause:
    DEFAULT COLON StatementListOpt { $$ = ast_wrap("DefaultClause", "", $3); }
    ;

StatementListOpt:
    /* empty */ { $$ = ast_new("StatementList", ""); }
    | StatementList { $$ = $1; }
    ;

// Throw语句
ThrowStatement:
    THROW Expression SEMICOLON { $$ = ast_wrap("ThrowStatement", "", $2); }
    ;

// Try语句
TryStatement:
    TRY BlockStatement Catch { $$ = ast_new("TryStatement", ""); ast_add($$, $2); ast_add($$, $3); }
    | TRY BlockStatement Finally { $$ = ast_new("TryStatement", ""); ast_add($$, $2); ast_add($$, $3); }
    | TRY BlockStatement Catch Finally { $$ = ast_new("TryStatement", ""); ast_add($$, $2); ast_add($$, $3); ast_add($$, $4); }
    ;

Catch:
    CATCH LPAREN IDENTIFIER RPAREN BlockStatement { $$ = ast_new("CatchClause", $3); ast_add($$, ast_leaf("Identifier", $3)); ast_add($$, $5); }
    ;

Finally:
    FINALLY BlockStatement { $$ = ast_wrap("FinallyClause", "", $2); }
    ;

// Debugger语句
DebuggerStatement:
    DEBUGGER SEMICOLON { $$ = ast_new("DebuggerStatement", ""); }
    ;

// 函数声明
FunctionDeclaration:
    FUNCTION IDENTIFIER LPAREN FormalParametersOpt RPAREN BlockStatement { $$ = ast_new("FunctionDeclaration", $2); ast_add($$, ast_leaf("Identifier", $2)); ast_add($$, $4); ast_add($$, $6); }
    ;

FormalParametersOpt:
    /* empty */ { $$ = ast_new("Parameters", ""); }
    | FormalParameters { $$ = $1; }
    ;

FormalParameters:
    IDENTIFIER { $$ = ast_list("Parameters", ast_leaf("Identifier", $1)); }
    | FormalParameters COMMA IDENTIFIER { $$ = $1; ast_add($$, ast_leaf("Identifier", $3)); }
    ;

// 类声明
ClassDeclaration:
    CLASS IDENTIFIER ClassTail { $$ = ast_new("ClassDeclaration", $2); ast_add($$, ast_leaf("Identifier", $2)); ast_add($$, $3); }
    ;

ClassTail:
    LBRACE ClassBodyOpt RBRACE { $$ = ast_wrap("ClassBody", "", $2); }
    | EXTENDS LeftHandSideExpression LBRACE ClassBodyOpt RBRACE { $$ = ast_new("ClassTail", "extends"); ast_add($$, ast_wrap("SuperClass", "", $2)); ast_add($$, $4); }
    ;

ClassBodyOpt:
    /* empty */ { $$ = ast_new("ClassElements", ""); }
    | ClassBody { $$ = $1; }
    ;

ClassBody:
    ClassElement { $$ = ast_list("ClassElements", $1); }
    | ClassBody ClassElement { $$ = $1; ast_add($$, $2); }
    ;

ClassElement:
    MethodDefinition { $$ = $1; }
    | SEMICOLON { $$ = ast_new("EmptyClassElement", ""); }
    ;

MethodDefinition:
    IDENTIFIER LPAREN FormalParametersOpt RPAREN BlockStatement { $$ = ast_new("MethodDefinition", $1); ast_add($$, ast_leaf("Identifier", $1)); ast_add($$, $3); ast_add($$, $5); }
    ;

// 表达式
Expression:
    AssignmentExpression { $$ = $1; }
    | Expression COMMA AssignmentExpression { $$ = ast_binary("SequenceExpression", ",", $1, $3); }
    ;

// 赋值表达式
AssignmentExpression:
    ArrowFunction { $$ = $1; }
    | ConditionalExpression { $$ = $1; }
    | LeftHandSideExpression ASSIGN AssignmentExpression { $$ = ast_binary("AssignmentExpression", "=", $1, $3); }
    | LeftHandSideExpression PLUS_ASSIGN AssignmentExpression { $$ = ast_binary("AssignmentExpression", "+=", $1, $3); }
    | LeftHandSideExpression MINUS_ASSIGN AssignmentExpression { $$ = ast_binary("AssignmentExpression", "-=", $1, $3); }
    | LeftHandSideExpression MULTIPLY_ASSIGN AssignmentExpression { $$ = ast_binary("AssignmentExpression", "*=", $1, $3); }
    | LeftHandSideExpression DIVIDE_ASSIGN AssignmentExpression { $$ = ast_binary("AssignmentExpression", "/=", $1, $3); }
    | LeftHandSideExpression MODULO_ASSIGN AssignmentExpression { $$ = ast_binary("AssignmentExpression", "%=", $1, $3); }
    | LeftHandSideExpression EXPONENT_ASSIGN AssignmentExpression { $$ = ast_binary("AssignmentExpression", "**=", $1, $3); }
    | LeftHandSideExpression AND_ASSIGN AssignmentExpression { $$ = ast_binary("AssignmentExpression", "&=", $1, $3); }
    | LeftHandSideExpression OR_ASSIGN AssignmentExpression { $$ = ast_binary("AssignmentExpression", "|=", $1, $3); }
    | LeftHandSideExpression XOR_ASSIGN AssignmentExpression { $$ = ast_binary("AssignmentExpression", "^=", $1, $3); }
    | LeftHandSideExpression LEFT_SHIFT_ASSIGN AssignmentExpression { $$ = ast_binary("AssignmentExpression", "<<=", $1, $3); }
    | LeftHandSideExpression RIGHT_SHIFT_ASSIGN AssignmentExpression { $$ = ast_binary("AssignmentExpression", ">>=", $1, $3); }
    | LeftHandSideExpression UNSIGNED_RIGHT_SHIFT_ASSIGN AssignmentExpression { $$ = ast_binary("AssignmentExpression", ">>>=", $1, $3); }
    ;

ArrowFunction:
    ArrowParameters ARROW ConciseBody { $$ = ast_new("ArrowFunctionExpression", ""); ast_add($$, ast_wrap("Params", "", $1)); ast_add($$, ast_wrap("Body", "", $3)); }
    ;

ArrowParameters:
    IDENTIFIER { $$ = ast_leaf("Identifier", $1); }
    | LPAREN FormalParametersOpt RPAREN { $$ = $2; }
    ;

ConciseBody:
    AssignmentExpression { $$ = $1; }
    | BlockStatement { $$ = $1; }
    ;

// 条件表达式
ConditionalExpression:
    LogicalORExpression { $$ = $1; }
    | LogicalORExpression QUESTION AssignmentExpression COLON AssignmentExpression { $$ = ast_new("ConditionalExpression", "?:"); ast_add($$, ast_wrap("Test", "", $1)); ast_add($$, ast_wrap("Consequent", "", $3)); ast_add($$, ast_wrap("Alternate", "", $5)); }
    ;

// 逻辑OR表达式
LogicalORExpression:
    LogicalANDExpression { $$ = $1; }
    | LogicalORExpression LOGICAL_OR LogicalANDExpression { $$ = ast_binary("LogicalExpression", "||", $1, $3); }
    | LogicalORExpression NULLISH_COALESCING LogicalANDExpression { $$ = ast_binary("LogicalExpression", "??", $1, $3); }
    ;

// 逻辑AND表达式
LogicalANDExpression:
    BitwiseORExpression { $$ = $1; }
    | LogicalANDExpression LOGICAL_AND BitwiseORExpression { $$ = ast_binary("LogicalExpression", "&&", $1, $3); }
    ;

// 按位OR表达式
BitwiseORExpression:
    BitwiseXORExpression { $$ = $1; }
    | BitwiseORExpression BITWISE_OR BitwiseXORExpression { $$ = ast_binary("BinaryExpression", "|", $1, $3); }
    ;

// 按位XOR表达式
BitwiseXORExpression:
    BitwiseANDExpression { $$ = $1; }
    | BitwiseXORExpression BITWISE_XOR BitwiseANDExpression { $$ = ast_binary("BinaryExpression", "^", $1, $3); }
    ;

// 按位AND表达式
BitwiseANDExpression:
    EqualityExpression { $$ = $1; }
    | BitwiseANDExpression BITWISE_AND EqualityExpression { $$ = ast_binary("BinaryExpression", "&", $1, $3); }
    ;

// 相等表达式
EqualityExpression:
    RelationalExpression { $$ = $1; }
    | EqualityExpression EQUAL RelationalExpression { $$ = ast_binary("BinaryExpression", "==", $1, $3); }
    | EqualityExpression NOT_EQUAL RelationalExpression { $$ = ast_binary("BinaryExpression", "!=", $1, $3); }
    | EqualityExpression STRICT_EQUAL RelationalExpression { $$ = ast_binary("BinaryExpression", "===", $1, $3); }
    | EqualityExpression STRICT_NOT_EQUAL RelationalExpression { $$ = ast_binary("BinaryExpression", "!==", $1, $3); }
    ;

// 关系表达式
RelationalExpression:
    ShiftExpression { $$ = $1; }
    | RelationalExpression LESS ShiftExpression { $$ = ast_binary("BinaryExpression", "<", $1, $3); }
    | RelationalExpression GREATER ShiftExpression { $$ = ast_binary("BinaryExpression", ">", $1, $3); }
    | RelationalExpression LESS_EQUAL ShiftExpression { $$ = ast_binary("BinaryExpression", "<=", $1, $3); }
    | RelationalExpression GREATER_EQUAL ShiftExpression { $$ = ast_binary("BinaryExpression", ">=", $1, $3); }
    | RelationalExpression INSTANCEOF ShiftExpression { $$ = ast_binary("BinaryExpression", "instanceof", $1, $3); }
    | RelationalExpression IN ShiftExpression { $$ = ast_binary("BinaryExpression", "in", $1, $3); }
    ;

// 位移表达式
ShiftExpression:
    AdditiveExpression { $$ = $1; }
    | ShiftExpression LEFT_SHIFT AdditiveExpression { $$ = ast_binary("BinaryExpression", "<<", $1, $3); }
    | ShiftExpression RIGHT_SHIFT AdditiveExpression { $$ = ast_binary("BinaryExpression", ">>", $1, $3); }
    | ShiftExpression UNSIGNED_RIGHT_SHIFT AdditiveExpression { $$ = ast_binary("BinaryExpression", ">>>", $1, $3); }
    ;

// 加法表达式
AdditiveExpression:
    MultiplicativeExpression { $$ = $1; }
    | AdditiveExpression PLUS MultiplicativeExpression { $$ = ast_binary("BinaryExpression", "+", $1, $3); }
    | AdditiveExpression MINUS MultiplicativeExpression { $$ = ast_binary("BinaryExpression", "-", $1, $3); }
    ;

// 乘法表达式
MultiplicativeExpression:
    UnaryExpression { $$ = $1; }
    | MultiplicativeExpression MULTIPLY UnaryExpression { $$ = ast_binary("BinaryExpression", "*", $1, $3); }
    | MultiplicativeExpression DIVIDE UnaryExpression { $$ = ast_binary("BinaryExpression", "/", $1, $3); }
    | MultiplicativeExpression MODULO UnaryExpression { $$ = ast_binary("BinaryExpression", "%", $1, $3); }
    ;

// 一元表达式
UnaryExpression:
    PostfixExpression { $$ = $1; }
    | DELETE UnaryExpression { $$ = ast_unary("UnaryExpression", "delete", $2); }
    | TYPEOF UnaryExpression { $$ = ast_unary("UnaryExpression", "typeof", $2); }
    | INCREMENT UnaryExpression { $$ = ast_unary("UpdateExpression", "prefix ++", $2); }
    | DECREMENT UnaryExpression { $$ = ast_unary("UpdateExpression", "prefix --", $2); }
    | PLUS UnaryExpression { $$ = ast_unary("UnaryExpression", "+", $2); }
    | MINUS UnaryExpression { $$ = ast_unary("UnaryExpression", "-", $2); }
    | BITWISE_NOT UnaryExpression { $$ = ast_unary("UnaryExpression", "~", $2); }
    | NOT UnaryExpression { $$ = ast_unary("UnaryExpression", "!", $2); }
    | EXPONENT UnaryExpression { $$ = ast_unary("UnaryExpression", "**", $2); }
    ;

// 后置表达式
PostfixExpression:
    LeftHandSideExpression { $$ = $1; }
    | LeftHandSideExpression INCREMENT { $$ = ast_unary("UpdateExpression", "postfix ++", $1); }
    | LeftHandSideExpression DECREMENT { $$ = ast_unary("UpdateExpression", "postfix --", $1); }
    ;

// 左值表达式
LeftHandSideExpression:
    NewExpression { $$ = $1; }
    | CallExpression { $$ = $1; }
    | OptionalExpression { $$ = $1; }
    ;

// New表达式
NewExpression:
    MemberExpression { $$ = $1; }
    | NEW NewExpression { $$ = ast_wrap("NewExpression", "", $2); }
    ;

// 成员表达式
MemberExpression:
    PrimaryExpression { $$ = $1; }
    | MemberExpression DOT IDENTIFIER { $$ = ast_new("MemberExpression", "."); ast_add($$, ast_wrap("Object", "", $1)); ast_add($$, ast_leaf("Identifier", $3)); }
    | MemberExpression LBRACKET Expression RBRACKET { $$ = ast_new("MemberExpression", "computed"); ast_add($$, ast_wrap("Object", "", $1)); ast_add($$, ast_wrap("Property", "", $3)); }
    | SUPER DOT IDENTIFIER { $$ = ast_new("MemberExpression", "."); ast_add($$, ast_leaf("Super", "super")); ast_add($$, ast_leaf("Identifier", $3)); }
    | SUPER LBRACKET Expression RBRACKET { $$ = ast_new("MemberExpression", "computed"); ast_add($$, ast_leaf("Super", "super")); ast_add($$, ast_wrap("Property", "", $3)); }
    | NEW MemberExpression Arguments { $$ = ast_new("NewExpression", ""); ast_add($$, ast_wrap("Callee", "", $2)); ast_add($$, $3); }
    ;

// 可选表达式
OptionalExpression:
    MemberExpression OPTIONAL_CHAINING IDENTIFIER { $$ = ast_new("OptionalMemberExpression", "?."); ast_add($$, $1); ast_add($$, ast_leaf("Identifier", $3)); }
    | CallExpression OPTIONAL_CHAINING IDENTIFIER { $$ = ast_new("OptionalMemberExpression", "?."); ast_add($$, $1); ast_add($$, ast_leaf("Identifier", $3)); }
    | OptionalExpression OPTIONAL_CHAINING IDENTIFIER { $$ = ast_new("OptionalMemberExpression", "?."); ast_add($$, $1); ast_add($$, ast_leaf("Identifier", $3)); }
    ;

// 调用表达式
CallExpression:
    MemberExpression Arguments { $$ = ast_new("CallExpression", ""); ast_add($$, ast_wrap("Callee", "", $1)); ast_add($$, $2); }
    | CallExpression Arguments { $$ = ast_new("CallExpression", ""); ast_add($$, ast_wrap("Callee", "", $1)); ast_add($$, $2); }
    | CallExpression LBRACKET Expression RBRACKET { $$ = ast_new("MemberExpression", "computed"); ast_add($$, ast_wrap("Object", "", $1)); ast_add($$, ast_wrap("Property", "", $3)); }
    | CallExpression DOT IDENTIFIER { $$ = ast_new("MemberExpression", "."); ast_add($$, ast_wrap("Object", "", $1)); ast_add($$, ast_leaf("Identifier", $3)); }
    | SUPER Arguments { $$ = ast_new("CallExpression", "super"); ast_add($$, $2); }
    ;

Arguments:
    LPAREN RPAREN { $$ = ast_new("Arguments", ""); }
    | LPAREN ArgumentList RPAREN { $$ = $2; }
    ;

ArgumentList:
    AssignmentExpression { $$ = ast_list("Arguments", $1); }
    | SPREAD AssignmentExpression { $$ = ast_list("Arguments", ast_wrap("SpreadElement", "", $2)); }
    | ArgumentList COMMA AssignmentExpression { $$ = $1; ast_add($$, $3); }
    | ArgumentList COMMA SPREAD AssignmentExpression { $$ = $1; ast_add($$, ast_wrap("SpreadElement", "", $4)); }
    ;

// 主表达式
PrimaryExpression:
    THIS { $$ = ast_leaf("ThisExpression", "this"); }
    | IDENTIFIER { $$ = ast_leaf("Identifier", $1); }
    | Literal { $$ = $1; }
    | ArrayLiteral { $$ = $1; }
    | ObjectLiteral { $$ = $1; }
    | FunctionExpression { $$ = $1; }
    | ClassExpression { $$ = $1; }
    | LPAREN Expression RPAREN { $$ = $2; }
    ;

// 字面量
Literal:
    NULL_LITERAL { $$ = ast_leaf("Literal", "null"); }
    | TRUE { $$ = ast_leaf("Literal", "true"); }
    | FALSE { $$ = ast_leaf("Literal", "false"); }
    | NUMBER { $$ = number_literal($1); }
    | STRING { $$ = ast_leaf("Literal", $1); }
    ;

// 数组字面量
ArrayLiteral:
    LBRACKET ArrayElementsOpt RBRACKET { $$ = ast_wrap("ArrayExpression", "", $2); }
    ;

ArrayElementsOpt:
    /* empty */ { $$ = ast_new("Elements", ""); }
    | ElementList { $$ = $1; }
    | ElementList COMMA { $$ = $1; }
    ;

ElementList:
    ElisionOpt AssignmentExpression { $$ = ast_list("Elements", $2); }
    | SPREAD AssignmentExpression { $$ = ast_list("Elements", ast_wrap("SpreadElement", "", $2)); }
    | ElementList COMMA ElisionOpt AssignmentExpression { $$ = $1; ast_add($$, $4); }
    | ElementList COMMA SPREAD AssignmentExpression { $$ = $1; ast_add($$, ast_wrap("SpreadElement", "", $4)); }
    ;

ElisionOpt:
    /* empty */ { $$ = ast_new("Elision", ""); }
    | Elision { $$ = $1; }
    ;

Elision:
    COMMA { $$ = ast_new("Elision", ","); }
    | Elision COMMA { $$ = $1; }
    ;

// 对象字面量
ObjectLiteral:
    LBRACE PropertyDefinitionsOpt RBRACE { $$ = ast_wrap("ObjectExpression", "", $2); }
    ;

PropertyDefinitionsOpt:
    /* empty */ { $$ = ast_new("Properties", ""); }
    | SemicolonList { $$ = ast_new("Properties", ""); }
    | PropertyDefinitionList SemicolonListOpt { $$ = $1; }
    | PropertyDefinitionList COMMA SemicolonListOpt { $$ = $1; }
    ;

PropertyDefinitionList:
    PropertyDefinition { $$ = ast_list("Properties", $1); }
    | PropertyDefinitionList PropertySeparator PropertyDefinition { $$ = $1; ast_add($$, $3); }
    ;

PropertySeparator:
    COMMA SemicolonListOpt { $$ = ast_new("PropertySeparator", ","); }
    | SemicolonList { $$ = ast_new("PropertySeparator", ";"); }
    ;

SemicolonListOpt:
    /* empty */ { $$ = ast_new("SemicolonList", ""); }
    | SemicolonList { $$ = $1; }
    ;

SemicolonList:
    SEMICOLON { $$ = ast_new("SemicolonList", ";"); }
    | SemicolonList SEMICOLON { $$ = $1; }
    ;

PropertyDefinition:
    IDENTIFIER { $$ = ast_new("Property", "shorthand"); ast_add($$, ast_leaf("Identifier", $1)); }
    | PropertyName COLON AssignmentExpression { $$ = ast_new("Property", "init"); ast_add($$, ast_wrap("Key", "", $1)); ast_add($$, ast_wrap("Value", "", $3)); }
    | MethodDefinition { $$ = $1; }
    | SPREAD AssignmentExpression { $$ = ast_wrap("SpreadElement", "", $2); }
    ;

PropertyName:
    IDENTIFIER { $$ = ast_leaf("Identifier", $1); }
    | STRING { $$ = ast_leaf("Literal", $1); }
    | NUMBER { $$ = number_literal($1); }
    ;

// 函数表达式
FunctionExpression:
    FUNCTION IdentifierOpt LPAREN FormalParametersOpt RPAREN BlockStatement { $$ = ast_new("FunctionExpression", ""); ast_add($$, $2); ast_add($$, $4); ast_add($$, $6); }
    ;

IdentifierOpt:
    /* empty */ { $$ = ast_new("Identifier", ""); }
    | IDENTIFIER { $$ = ast_leaf("Identifier", $1); }
    ;

// 注意：IdentifierOpt 必须在 FunctionExpression 之后定义

// 类表达式
ClassExpression:
    CLASS IdentifierOpt ClassTail { $$ = ast_new("ClassExpression", ""); ast_add($$, $2); ast_add($$, $3); }
    ;

// Yield语句
YieldStatement:
    YIELD ExpressionOpt SEMICOLON { $$ = ast_wrap("YieldStatement", "", $2); }
    ;

%%

void parser_reset(void) {
    syntax_valid = 1;
    error_count = 0;
    ast_root = NULL;
}

int parser_is_valid(void) {
    return syntax_valid;
}

int parser_error_total(void) {
    return error_count;
}

ASTNode *parser_get_ast(void) {
    return ast_root;
}

// 错误处理
void yyerror(const char *s) {
    syntax_valid = 0;
    error_count++;
    fprintf(stderr, "Syntax error (line %d): %s\n", yylineno, s);
}


/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

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


#line 110 "parser.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_NUMBER = 3,                     /* NUMBER  */
  YYSYMBOL_STRING = 4,                     /* STRING  */
  YYSYMBOL_IDENTIFIER = 5,                 /* IDENTIFIER  */
  YYSYMBOL_NULL_LITERAL = 6,               /* NULL_LITERAL  */
  YYSYMBOL_IF = 7,                         /* IF  */
  YYSYMBOL_ELSE = 8,                       /* ELSE  */
  YYSYMBOL_FOR = 9,                        /* FOR  */
  YYSYMBOL_WHILE = 10,                     /* WHILE  */
  YYSYMBOL_DO = 11,                        /* DO  */
  YYSYMBOL_SWITCH = 12,                    /* SWITCH  */
  YYSYMBOL_CASE = 13,                      /* CASE  */
  YYSYMBOL_DEFAULT = 14,                   /* DEFAULT  */
  YYSYMBOL_BREAK = 15,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 16,                  /* CONTINUE  */
  YYSYMBOL_RETURN = 17,                    /* RETURN  */
  YYSYMBOL_VAR = 18,                       /* VAR  */
  YYSYMBOL_LET = 19,                       /* LET  */
  YYSYMBOL_CONST = 20,                     /* CONST  */
  YYSYMBOL_FUNCTION = 21,                  /* FUNCTION  */
  YYSYMBOL_CLASS = 22,                     /* CLASS  */
  YYSYMBOL_THIS = 23,                      /* THIS  */
  YYSYMBOL_SUPER = 24,                     /* SUPER  */
  YYSYMBOL_NEW = 25,                       /* NEW  */
  YYSYMBOL_TYPEOF = 26,                    /* TYPEOF  */
  YYSYMBOL_DELETE = 27,                    /* DELETE  */
  YYSYMBOL_INSTANCEOF = 28,                /* INSTANCEOF  */
  YYSYMBOL_IN = 29,                        /* IN  */
  YYSYMBOL_TRUE = 30,                      /* TRUE  */
  YYSYMBOL_FALSE = 31,                     /* FALSE  */
  YYSYMBOL_TRY = 32,                       /* TRY  */
  YYSYMBOL_CATCH = 33,                     /* CATCH  */
  YYSYMBOL_FINALLY = 34,                   /* FINALLY  */
  YYSYMBOL_THROW = 35,                     /* THROW  */
  YYSYMBOL_WITH = 36,                      /* WITH  */
  YYSYMBOL_DEBUGGER = 37,                  /* DEBUGGER  */
  YYSYMBOL_IMPORT = 38,                    /* IMPORT  */
  YYSYMBOL_EXPORT = 39,                    /* EXPORT  */
  YYSYMBOL_YIELD = 40,                     /* YIELD  */
  YYSYMBOL_INTERFACE = 41,                 /* INTERFACE  */
  YYSYMBOL_EXTENDS = 42,                   /* EXTENDS  */
  YYSYMBOL_LPAREN = 43,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 44,                    /* RPAREN  */
  YYSYMBOL_LBRACE = 45,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 46,                    /* RBRACE  */
  YYSYMBOL_LBRACKET = 47,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 48,                  /* RBRACKET  */
  YYSYMBOL_SEMICOLON = 49,                 /* SEMICOLON  */
  YYSYMBOL_COMMA = 50,                     /* COMMA  */
  YYSYMBOL_DOT = 51,                       /* DOT  */
  YYSYMBOL_COLON = 52,                     /* COLON  */
  YYSYMBOL_QUESTION = 53,                  /* QUESTION  */
  YYSYMBOL_PLUS = 54,                      /* PLUS  */
  YYSYMBOL_MINUS = 55,                     /* MINUS  */
  YYSYMBOL_MULTIPLY = 56,                  /* MULTIPLY  */
  YYSYMBOL_DIVIDE = 57,                    /* DIVIDE  */
  YYSYMBOL_MODULO = 58,                    /* MODULO  */
  YYSYMBOL_ASSIGN = 59,                    /* ASSIGN  */
  YYSYMBOL_PLUS_ASSIGN = 60,               /* PLUS_ASSIGN  */
  YYSYMBOL_MINUS_ASSIGN = 61,              /* MINUS_ASSIGN  */
  YYSYMBOL_MULTIPLY_ASSIGN = 62,           /* MULTIPLY_ASSIGN  */
  YYSYMBOL_DIVIDE_ASSIGN = 63,             /* DIVIDE_ASSIGN  */
  YYSYMBOL_MODULO_ASSIGN = 64,             /* MODULO_ASSIGN  */
  YYSYMBOL_EQUAL = 65,                     /* EQUAL  */
  YYSYMBOL_NOT_EQUAL = 66,                 /* NOT_EQUAL  */
  YYSYMBOL_STRICT_EQUAL = 67,              /* STRICT_EQUAL  */
  YYSYMBOL_STRICT_NOT_EQUAL = 68,          /* STRICT_NOT_EQUAL  */
  YYSYMBOL_LESS = 69,                      /* LESS  */
  YYSYMBOL_GREATER = 70,                   /* GREATER  */
  YYSYMBOL_LESS_EQUAL = 71,                /* LESS_EQUAL  */
  YYSYMBOL_GREATER_EQUAL = 72,             /* GREATER_EQUAL  */
  YYSYMBOL_LOGICAL_AND = 73,               /* LOGICAL_AND  */
  YYSYMBOL_LOGICAL_OR = 74,                /* LOGICAL_OR  */
  YYSYMBOL_NOT = 75,                       /* NOT  */
  YYSYMBOL_BITWISE_AND = 76,               /* BITWISE_AND  */
  YYSYMBOL_BITWISE_OR = 77,                /* BITWISE_OR  */
  YYSYMBOL_BITWISE_XOR = 78,               /* BITWISE_XOR  */
  YYSYMBOL_BITWISE_NOT = 79,               /* BITWISE_NOT  */
  YYSYMBOL_LEFT_SHIFT = 80,                /* LEFT_SHIFT  */
  YYSYMBOL_RIGHT_SHIFT = 81,               /* RIGHT_SHIFT  */
  YYSYMBOL_UNSIGNED_RIGHT_SHIFT = 82,      /* UNSIGNED_RIGHT_SHIFT  */
  YYSYMBOL_LEFT_SHIFT_ASSIGN = 83,         /* LEFT_SHIFT_ASSIGN  */
  YYSYMBOL_RIGHT_SHIFT_ASSIGN = 84,        /* RIGHT_SHIFT_ASSIGN  */
  YYSYMBOL_UNSIGNED_RIGHT_SHIFT_ASSIGN = 85, /* UNSIGNED_RIGHT_SHIFT_ASSIGN  */
  YYSYMBOL_AND_ASSIGN = 86,                /* AND_ASSIGN  */
  YYSYMBOL_OR_ASSIGN = 87,                 /* OR_ASSIGN  */
  YYSYMBOL_XOR_ASSIGN = 88,                /* XOR_ASSIGN  */
  YYSYMBOL_INCREMENT = 89,                 /* INCREMENT  */
  YYSYMBOL_DECREMENT = 90,                 /* DECREMENT  */
  YYSYMBOL_EXPONENT = 91,                  /* EXPONENT  */
  YYSYMBOL_EXPONENT_ASSIGN = 92,           /* EXPONENT_ASSIGN  */
  YYSYMBOL_SPREAD = 93,                    /* SPREAD  */
  YYSYMBOL_NULLISH_COALESCING = 94,        /* NULLISH_COALESCING  */
  YYSYMBOL_OPTIONAL_CHAINING = 95,         /* OPTIONAL_CHAINING  */
  YYSYMBOL_ARROW = 96,                     /* ARROW  */
  YYSYMBOL_ERROR_TOKEN = 97,               /* ERROR_TOKEN  */
  YYSYMBOL_YYACCEPT = 98,                  /* $accept  */
  YYSYMBOL_Program = 99,                   /* Program  */
  YYSYMBOL_StatementList = 100,            /* StatementList  */
  YYSYMBOL_Statement = 101,                /* Statement  */
  YYSYMBOL_BlockStatement = 102,           /* BlockStatement  */
  YYSYMBOL_VariableStatement = 103,        /* VariableStatement  */
  YYSYMBOL_VariableDeclarationList = 104,  /* VariableDeclarationList  */
  YYSYMBOL_VariableDeclaration = 105,      /* VariableDeclaration  */
  YYSYMBOL_EmptyStatement = 106,           /* EmptyStatement  */
  YYSYMBOL_ExpressionStatement = 107,      /* ExpressionStatement  */
  YYSYMBOL_IfStatement = 108,              /* IfStatement  */
  YYSYMBOL_IterationStatement = 109,       /* IterationStatement  */
  YYSYMBOL_ForBinding = 110,               /* ForBinding  */
  YYSYMBOL_ExpressionOpt = 111,            /* ExpressionOpt  */
  YYSYMBOL_ContinueStatement = 112,        /* ContinueStatement  */
  YYSYMBOL_BreakStatement = 113,           /* BreakStatement  */
  YYSYMBOL_ReturnStatement = 114,          /* ReturnStatement  */
  YYSYMBOL_WithStatement = 115,            /* WithStatement  */
  YYSYMBOL_LabelledStatement = 116,        /* LabelledStatement  */
  YYSYMBOL_SwitchStatement = 117,          /* SwitchStatement  */
  YYSYMBOL_CaseBlock = 118,                /* CaseBlock  */
  YYSYMBOL_CaseClausesOpt = 119,           /* CaseClausesOpt  */
  YYSYMBOL_CaseClauses = 120,              /* CaseClauses  */
  YYSYMBOL_CaseClause = 121,               /* CaseClause  */
  YYSYMBOL_DefaultClause = 122,            /* DefaultClause  */
  YYSYMBOL_StatementListOpt = 123,         /* StatementListOpt  */
  YYSYMBOL_ThrowStatement = 124,           /* ThrowStatement  */
  YYSYMBOL_TryStatement = 125,             /* TryStatement  */
  YYSYMBOL_Catch = 126,                    /* Catch  */
  YYSYMBOL_Finally = 127,                  /* Finally  */
  YYSYMBOL_DebuggerStatement = 128,        /* DebuggerStatement  */
  YYSYMBOL_FunctionDeclaration = 129,      /* FunctionDeclaration  */
  YYSYMBOL_FormalParametersOpt = 130,      /* FormalParametersOpt  */
  YYSYMBOL_FormalParameters = 131,         /* FormalParameters  */
  YYSYMBOL_ClassDeclaration = 132,         /* ClassDeclaration  */
  YYSYMBOL_ClassTail = 133,                /* ClassTail  */
  YYSYMBOL_ClassBodyOpt = 134,             /* ClassBodyOpt  */
  YYSYMBOL_ClassBody = 135,                /* ClassBody  */
  YYSYMBOL_ClassElement = 136,             /* ClassElement  */
  YYSYMBOL_MethodDefinition = 137,         /* MethodDefinition  */
  YYSYMBOL_Expression = 138,               /* Expression  */
  YYSYMBOL_AssignmentExpression = 139,     /* AssignmentExpression  */
  YYSYMBOL_ArrowFunction = 140,            /* ArrowFunction  */
  YYSYMBOL_ArrowParameters = 141,          /* ArrowParameters  */
  YYSYMBOL_ConciseBody = 142,              /* ConciseBody  */
  YYSYMBOL_ConditionalExpression = 143,    /* ConditionalExpression  */
  YYSYMBOL_LogicalORExpression = 144,      /* LogicalORExpression  */
  YYSYMBOL_LogicalANDExpression = 145,     /* LogicalANDExpression  */
  YYSYMBOL_BitwiseORExpression = 146,      /* BitwiseORExpression  */
  YYSYMBOL_BitwiseXORExpression = 147,     /* BitwiseXORExpression  */
  YYSYMBOL_BitwiseANDExpression = 148,     /* BitwiseANDExpression  */
  YYSYMBOL_EqualityExpression = 149,       /* EqualityExpression  */
  YYSYMBOL_RelationalExpression = 150,     /* RelationalExpression  */
  YYSYMBOL_ShiftExpression = 151,          /* ShiftExpression  */
  YYSYMBOL_AdditiveExpression = 152,       /* AdditiveExpression  */
  YYSYMBOL_MultiplicativeExpression = 153, /* MultiplicativeExpression  */
  YYSYMBOL_UnaryExpression = 154,          /* UnaryExpression  */
  YYSYMBOL_PostfixExpression = 155,        /* PostfixExpression  */
  YYSYMBOL_LeftHandSideExpression = 156,   /* LeftHandSideExpression  */
  YYSYMBOL_NewExpression = 157,            /* NewExpression  */
  YYSYMBOL_MemberExpression = 158,         /* MemberExpression  */
  YYSYMBOL_OptionalExpression = 159,       /* OptionalExpression  */
  YYSYMBOL_CallExpression = 160,           /* CallExpression  */
  YYSYMBOL_Arguments = 161,                /* Arguments  */
  YYSYMBOL_ArgumentList = 162,             /* ArgumentList  */
  YYSYMBOL_PrimaryExpression = 163,        /* PrimaryExpression  */
  YYSYMBOL_Literal = 164,                  /* Literal  */
  YYSYMBOL_ArrayLiteral = 165,             /* ArrayLiteral  */
  YYSYMBOL_ArrayElementsOpt = 166,         /* ArrayElementsOpt  */
  YYSYMBOL_ElementList = 167,              /* ElementList  */
  YYSYMBOL_ElisionOpt = 168,               /* ElisionOpt  */
  YYSYMBOL_Elision = 169,                  /* Elision  */
  YYSYMBOL_ObjectLiteral = 170,            /* ObjectLiteral  */
  YYSYMBOL_PropertyDefinitionsOpt = 171,   /* PropertyDefinitionsOpt  */
  YYSYMBOL_PropertyDefinitionList = 172,   /* PropertyDefinitionList  */
  YYSYMBOL_PropertySeparator = 173,        /* PropertySeparator  */
  YYSYMBOL_SemicolonListOpt = 174,         /* SemicolonListOpt  */
  YYSYMBOL_SemicolonList = 175,            /* SemicolonList  */
  YYSYMBOL_PropertyDefinition = 176,       /* PropertyDefinition  */
  YYSYMBOL_PropertyName = 177,             /* PropertyName  */
  YYSYMBOL_FunctionExpression = 178,       /* FunctionExpression  */
  YYSYMBOL_IdentifierOpt = 179,            /* IdentifierOpt  */
  YYSYMBOL_ClassExpression = 180,          /* ClassExpression  */
  YYSYMBOL_YieldStatement = 181            /* YieldStatement  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  165
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1488

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  98
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  84
/* YYNRULES -- Number of rules.  */
#define YYNRULES  233
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  442

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   352


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   124,   124,   129,   130,   131,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   159,   164,   168,   169,   170,
     171,   175,   176,   181,   186,   191,   192,   197,   198,   199,
     200,   201,   202,   203,   204,   208,   212,   213,   218,   219,
     224,   225,   230,   235,   240,   245,   249,   250,   254,   255,
     259,   260,   264,   268,   272,   273,   278,   283,   284,   285,
     289,   293,   298,   303,   307,   308,   312,   313,   318,   322,
     323,   327,   328,   332,   333,   337,   338,   342,   347,   348,
     353,   354,   355,   356,   357,   358,   359,   360,   361,   362,
     363,   364,   365,   366,   367,   371,   375,   376,   380,   381,
     386,   387,   392,   393,   394,   399,   400,   405,   406,   411,
     412,   417,   418,   423,   424,   425,   426,   427,   432,   433,
     434,   435,   436,   437,   438,   443,   444,   445,   446,   451,
     452,   453,   458,   459,   460,   461,   466,   467,   468,   469,
     470,   471,   472,   473,   474,   475,   480,   481,   482,   487,
     488,   489,   494,   495,   500,   501,   502,   503,   504,   505,
     510,   511,   512,   517,   518,   519,   520,   521,   525,   526,
     530,   531,   532,   533,   538,   539,   540,   541,   542,   543,
     544,   545,   550,   551,   552,   553,   554,   559,   563,   564,
     565,   569,   570,   571,   572,   576,   577,   581,   582,   587,
     591,   592,   593,   594,   598,   599,   603,   604,   608,   609,
     613,   614,   618,   619,   620,   621,   625,   626,   627,   632,
     636,   637,   644,   649
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "NUMBER", "STRING",
  "IDENTIFIER", "NULL_LITERAL", "IF", "ELSE", "FOR", "WHILE", "DO",
  "SWITCH", "CASE", "DEFAULT", "BREAK", "CONTINUE", "RETURN", "VAR", "LET",
  "CONST", "FUNCTION", "CLASS", "THIS", "SUPER", "NEW", "TYPEOF", "DELETE",
  "INSTANCEOF", "IN", "TRUE", "FALSE", "TRY", "CATCH", "FINALLY", "THROW",
  "WITH", "DEBUGGER", "IMPORT", "EXPORT", "YIELD", "INTERFACE", "EXTENDS",
  "LPAREN", "RPAREN", "LBRACE", "RBRACE", "LBRACKET", "RBRACKET",
  "SEMICOLON", "COMMA", "DOT", "COLON", "QUESTION", "PLUS", "MINUS",
  "MULTIPLY", "DIVIDE", "MODULO", "ASSIGN", "PLUS_ASSIGN", "MINUS_ASSIGN",
  "MULTIPLY_ASSIGN", "DIVIDE_ASSIGN", "MODULO_ASSIGN", "EQUAL",
  "NOT_EQUAL", "STRICT_EQUAL", "STRICT_NOT_EQUAL", "LESS", "GREATER",
  "LESS_EQUAL", "GREATER_EQUAL", "LOGICAL_AND", "LOGICAL_OR", "NOT",
  "BITWISE_AND", "BITWISE_OR", "BITWISE_XOR", "BITWISE_NOT", "LEFT_SHIFT",
  "RIGHT_SHIFT", "UNSIGNED_RIGHT_SHIFT", "LEFT_SHIFT_ASSIGN",
  "RIGHT_SHIFT_ASSIGN", "UNSIGNED_RIGHT_SHIFT_ASSIGN", "AND_ASSIGN",
  "OR_ASSIGN", "XOR_ASSIGN", "INCREMENT", "DECREMENT", "EXPONENT",
  "EXPONENT_ASSIGN", "SPREAD", "NULLISH_COALESCING", "OPTIONAL_CHAINING",
  "ARROW", "ERROR_TOKEN", "$accept", "Program", "StatementList",
  "Statement", "BlockStatement", "VariableStatement",
  "VariableDeclarationList", "VariableDeclaration", "EmptyStatement",
  "ExpressionStatement", "IfStatement", "IterationStatement", "ForBinding",
  "ExpressionOpt", "ContinueStatement", "BreakStatement",
  "ReturnStatement", "WithStatement", "LabelledStatement",
  "SwitchStatement", "CaseBlock", "CaseClausesOpt", "CaseClauses",
  "CaseClause", "DefaultClause", "StatementListOpt", "ThrowStatement",
  "TryStatement", "Catch", "Finally", "DebuggerStatement",
  "FunctionDeclaration", "FormalParametersOpt", "FormalParameters",
  "ClassDeclaration", "ClassTail", "ClassBodyOpt", "ClassBody",
  "ClassElement", "MethodDefinition", "Expression", "AssignmentExpression",
  "ArrowFunction", "ArrowParameters", "ConciseBody",
  "ConditionalExpression", "LogicalORExpression", "LogicalANDExpression",
  "BitwiseORExpression", "BitwiseXORExpression", "BitwiseANDExpression",
  "EqualityExpression", "RelationalExpression", "ShiftExpression",
  "AdditiveExpression", "MultiplicativeExpression", "UnaryExpression",
  "PostfixExpression", "LeftHandSideExpression", "NewExpression",
  "MemberExpression", "OptionalExpression", "CallExpression", "Arguments",
  "ArgumentList", "PrimaryExpression", "Literal", "ArrayLiteral",
  "ArrayElementsOpt", "ElementList", "ElisionOpt", "Elision",
  "ObjectLiteral", "PropertyDefinitionsOpt", "PropertyDefinitionList",
  "PropertySeparator", "SemicolonListOpt", "SemicolonList",
  "PropertyDefinition", "PropertyName", "FunctionExpression",
  "IdentifierOpt", "ClassExpression", "YieldStatement", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-242)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-229)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     648,     5,  -242,  -242,   -45,  -242,    73,    89,    99,  1012,
     129,    19,    72,  1166,   161,   161,   161,   176,   181,  -242,
     102,   356,  1243,  1243,  -242,  -242,   152,  1166,   168,   166,
    1166,  1320,   462,   -30,  -242,  1243,  1243,  1243,  1243,  1243,
    1243,  1243,   227,   556,  -242,  -242,  -242,   -28,  -242,  -242,
    -242,  -242,  -242,  -242,  -242,  -242,  -242,  -242,  -242,  -242,
    -242,  -242,  -242,  -242,    97,  -242,  -242,   141,  -242,   108,
     180,   202,   147,   189,   173,   122,   149,   100,   225,  -242,
    -242,   229,  -242,    90,   150,    92,  -242,  -242,  -242,  -242,
    -242,  -242,  -242,  -242,  1012,  1166,  1089,  1166,   276,  1166,
     259,  -242,   271,  -242,   199,   306,   306,    45,   273,   280,
     284,  -242,  -242,  -242,   292,   301,   123,   123,    35,  1166,
     340,  -242,  -242,    37,  1166,  -242,   120,  -242,    80,  -242,
     921,   236,   275,  1166,  -242,   297,    31,   303,   298,   -25,
     299,   302,    21,  -242,  1166,   304,  -242,   307,   277,   300,
    -242,   305,  -242,  1166,   308,   315,  1166,   316,  -242,  -242,
    -242,  -242,  -242,  -242,  -242,  -242,   318,  -242,  -242,   161,
    -242,  1166,  1397,  1166,  1243,  1243,  1243,  1243,  1243,  1243,
    1243,  1243,  1243,  1243,  1243,  1243,  1243,  1243,  1243,  1243,
    1243,  1243,  1243,  1243,  1243,  1243,  1243,  1243,  1166,  1166,
    1166,  1166,  1166,  1166,  1166,  1166,  1166,  1166,  1166,  1166,
    -242,  -242,  1166,  1166,   350,   363,  -242,   370,  1166,   371,
     377,  -242,  -242,     3,   378,   378,   378,   279,   335,   188,
      68,   342,    86,  -242,  -242,  -242,  -242,  -242,    70,  -242,
    -242,  1166,   384,   384,  1432,    82,  -242,  -242,  -242,  1166,
    -242,   151,   246,  -242,  -242,   347,   152,   357,  -242,  -242,
     155,  -242,  -242,   388,  -242,   384,  -242,  -242,  -242,   346,
      41,  -242,   177,  -242,  1166,  -242,  -242,    26,  -242,  -242,
    -242,  -242,  -242,  -242,  -242,  -242,   352,   180,   180,   202,
     147,   189,   173,   122,   122,   122,   122,   149,   149,   149,
     149,   149,   149,   100,   100,   100,   225,   225,  -242,  -242,
    -242,  -242,  -242,  -242,  -242,  -242,  -242,  -242,  -242,  -242,
    -242,  -242,  -242,  -242,   256,  -242,  -242,  -242,   257,  -242,
    -242,  1012,   -17,   369,   373,   376,  1166,  1166,  1166,  1012,
    1166,   361,  -242,  -242,   366,   367,   368,   372,  -242,   374,
      82,  -242,  -242,  -242,  -242,   153,  -242,   407,  -242,  -242,
    1012,  -242,   375,   380,   300,  -242,  -242,  1166,  1166,  1166,
    -242,  -242,   406,  1166,  1166,  1166,   379,   381,   160,  -242,
     162,   403,  -242,   152,   152,    82,  -242,  -242,  1166,  -242,
     383,  -242,   152,  -242,  -242,  -242,  1012,   169,   172,   174,
    1166,  1166,  1012,   382,  1166,    -9,   403,  -242,  -242,  -242,
     386,  -242,   152,  -242,  -242,  1012,  1012,  1012,   385,   389,
    -242,  -242,    33,   365,  -242,   403,  -242,  -242,  -242,  -242,
    -242,  -242,  1012,  1012,   739,   830,   414,  -242,  -242,  -242,
    -242,  -242
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,   195,   196,   185,   192,     0,     0,     0,     0,
       0,     0,     0,    46,     0,     0,     0,   230,   230,   184,
       0,     0,     0,     0,   193,   194,     0,     0,     0,     0,
      46,    74,     0,   205,    33,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     3,     6,     7,     0,     8,     9,
      10,    11,    12,    13,    14,    16,    17,    18,     2,    19,
      20,    21,    22,    23,     0,    88,    90,     0,    91,   110,
     112,   115,   117,   119,   121,   123,   128,   135,   139,   142,
     146,   156,   159,   162,   161,   160,   164,   186,   187,   188,
     189,   190,    15,    24,     0,     0,    46,     0,     0,     0,
       0,    50,     0,    48,   185,   230,   230,   210,     0,    47,
      31,    27,    28,    29,     0,     0,     0,     0,     0,     0,
       0,   177,   185,     0,     0,   163,   162,   148,   156,   147,
       0,     0,     0,     0,    72,     0,   185,     0,    75,     0,
     195,   196,   185,    33,     0,     0,   224,     0,   218,   211,
     214,     0,   207,     0,     0,   199,     0,   206,   151,   152,
     154,   153,   149,   150,   155,     1,     0,     4,    26,     0,
      34,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     157,   158,     0,     0,     0,     0,   173,     0,     0,     0,
       0,   174,    54,     0,     0,     0,     0,     0,     0,   156,
       0,     0,     0,    51,    49,   231,   228,   227,   222,   220,
      52,     0,    74,    74,     0,    81,    78,   232,   178,     0,
     180,     0,     0,   167,   169,     0,     0,    67,    68,    66,
       0,   233,   107,     0,   191,    74,   225,    25,   209,   218,
       0,   212,   217,   221,     0,   202,   197,   205,   201,   208,
       5,    30,    89,   109,   108,   105,     0,   113,   114,   116,
     118,   120,   122,   124,   125,   126,   127,   133,   134,   129,
     130,   131,   132,   136,   137,   138,   140,   141,   143,   144,
     145,    92,    93,    94,    95,    96,    97,   102,   103,   104,
      99,   100,   101,    98,     0,   165,   170,   172,     0,   176,
     171,     0,    31,     0,     0,     0,    46,    46,     0,     0,
       0,     0,    32,    76,     0,     0,     0,     0,    86,     0,
      82,    83,    85,   181,   179,     0,   168,     0,    71,    69,
       0,    77,     0,   216,   219,   215,   223,     0,     0,     0,
     166,   175,    35,     0,     0,     0,     0,     0,     0,    37,
       0,    58,    55,     0,     0,    81,    79,    84,     0,   182,
       0,    53,     0,   204,   203,   111,     0,     0,     0,     0,
      46,    46,     0,     0,     0,     0,    59,    60,    73,   229,
       0,   183,     0,    87,    36,     0,     0,     0,     0,     0,
      41,    38,     0,     0,    56,    58,    61,    80,    70,    42,
      43,    44,     0,     0,     0,     0,     0,    40,    39,    62,
      63,    57
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -242,  -242,  -242,    -8,   -20,  -242,   322,    -5,  -242,  -242,
    -242,  -242,   112,   -27,  -242,  -242,  -242,  -242,  -242,  -242,
    -242,    -3,  -242,    15,  -242,     0,  -242,  -242,  -242,   204,
    -242,  -242,  -229,  -242,  -242,   345,    38,  -242,   114,  -241,
      -4,  -101,  -242,  -242,  -242,  -242,  -242,   165,   294,   313,
     317,   296,    81,    71,    43,   148,    -7,  -242,   262,   455,
     470,  -242,  -242,    77,  -242,  -242,  -242,  -242,  -242,  -242,
     219,  -242,  -242,  -242,  -242,  -242,   231,  -146,   233,  -242,
    -242,   -10,  -242,  -242
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    42,    43,    44,    45,    46,    47,   111,    48,    49,
      50,    51,   333,   108,    52,    53,    54,    55,    56,    57,
     382,   405,   406,   407,   425,   145,    59,    60,   257,   258,
      61,    62,   137,   138,    63,   246,   349,   350,   351,   146,
      64,    65,    66,    67,   285,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,   121,   251,    86,    87,    88,   154,   155,
     156,   157,    89,   147,   148,   270,   271,   149,   150,   151,
      90,   115,    91,    92
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      58,    98,   272,   135,   352,   423,   131,    94,   117,   109,
     112,   113,   -45,   344,   345,   127,   129,   250,  -198,   264,
     152,   168,   169,   132,   100,   171,   109,   139,   158,   159,
     160,   161,   162,   163,   164,   167,   362,   424,     2,     3,
     104,     5,   241,   266,   236,   237,   238,   331,   236,   237,
     238,  -106,   275,   171,    93,   278,   105,   106,    19,    20,
      21,    22,    23,   153,   265,    24,    25,  -222,   101,   228,
     282,   284,   286,    94,  -200,   -76,   152,   102,    31,   248,
     107,   -76,    33,   171,   119,   434,   222,   347,   120,    35,
      36,   223,   109,   230,   239,   232,   117,   311,   312,   313,
     314,   315,   316,   317,   318,   319,   320,   321,   322,   352,
      37,   323,   339,   265,    38,   252,    95,  -106,   171,   367,
     139,   103,  -226,   364,    39,    40,    41,  -106,   249,   260,
     341,   348,    96,   118,   144,   118,   171,   213,   144,   218,
     342,   214,    97,   219,   352,   118,   170,   171,   353,   119,
     184,   185,   283,   120,   193,   194,     2,     3,   104,     5,
     216,   173,   221,   118,   281,   244,   110,   213,   245,   210,
     211,   214,    99,   366,   105,   106,    19,    20,    21,    22,
      23,   114,   174,    24,    25,   215,   116,   220,   308,   309,
     310,   186,   187,   188,   189,   354,    31,   130,   107,   360,
      33,   355,   175,   254,   402,   171,   403,    35,    36,   324,
     171,   133,   171,   415,   328,   134,   416,   338,   417,   171,
     112,   113,   171,  -219,   171,   178,   273,   165,    37,   190,
     191,   192,    38,   303,   304,   305,   358,   172,   180,   181,
     182,   183,    39,    40,    41,   217,   388,   198,   199,   200,
     201,   202,   203,   176,   389,   297,   298,   299,   300,   301,
     302,   293,   294,   295,   296,   179,   393,   394,   395,   255,
     256,   204,   205,   206,   207,   208,   209,   210,   211,   177,
     212,   195,   196,   197,   128,   128,   231,   411,   198,   199,
     200,   201,   202,   203,   356,  -106,   171,   128,   128,   128,
     128,   128,   128,   128,   370,   371,   171,   171,   233,   376,
     377,   235,   204,   205,   206,   207,   208,   209,   210,   211,
     234,   212,   240,   372,   259,   171,   239,   269,   336,   169,
     171,   379,   109,   109,   378,   242,   380,   334,   335,   287,
     288,   306,   307,   241,   243,   253,   261,   262,   263,   273,
     267,  -228,   391,   268,  -227,   325,   276,   274,   229,     2,
       3,   122,     5,   408,   409,   277,   279,   280,   326,   397,
     398,   399,   413,   418,   419,   327,   329,   105,   106,    19,
     123,    21,   330,   332,   337,   340,    24,    25,   414,   343,
     357,   256,   428,   361,   420,   239,   109,   109,   373,   124,
     422,   107,   374,    33,   369,   375,   381,   429,   430,   431,
     383,   384,   390,   385,   396,   265,   404,   435,   227,   392,
     386,   426,   436,   410,   437,   438,  -213,   412,   400,   432,
     401,   421,   427,   433,   439,   440,   128,   128,   128,   128,
     128,   128,   128,   128,   128,   128,   128,   128,   128,   128,
     128,   128,   128,   128,   128,   128,   128,   128,   128,   128,
     441,   359,   247,     1,   387,   140,   141,   142,     5,     6,
     289,     7,     8,     9,    10,   292,   125,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
     290,   126,    24,    25,    26,   291,   368,    27,    28,    29,
     363,     0,    30,   365,     0,    31,   346,    32,   -64,    33,
       0,   143,     0,     0,     0,     0,    35,    36,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    37,     0,     0,
       0,    38,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    39,    40,    41,     0,   144,   -65,   166,     0,     2,
       3,     4,     5,     6,     0,     7,     8,     9,    10,   -65,
     -65,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,     0,     0,    24,    25,    26,     0,
       0,    27,    28,    29,     0,     0,    30,     0,     0,    31,
       0,    32,   -65,    33,     0,    34,     0,     0,     0,     0,
      35,    36,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    37,     0,     0,     0,    38,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    39,    40,    41,   -64,     1,
       0,     2,     3,     4,     5,     6,     0,     7,     8,     9,
      10,     0,     0,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,     0,     0,    24,    25,
      26,     0,     0,    27,    28,    29,     0,     0,    30,     0,
       0,    31,     0,    32,     0,    33,     0,    34,     0,     0,
       0,     0,    35,    36,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    37,     0,     0,     0,    38,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    39,    40,    41,
       1,     0,     2,     3,     4,     5,     6,     0,     7,     8,
       9,    10,   -64,   -64,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,     0,     0,    24,
      25,    26,     0,     0,    27,    28,    29,     0,     0,    30,
       0,     0,    31,     0,    32,   -64,    33,     0,    34,     0,
       0,     0,     0,    35,    36,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    37,     0,     0,     0,    38,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    39,    40,
      41,     1,     0,     2,     3,     4,     5,     6,     0,     7,
       8,     9,    10,   -64,     0,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,     0,     0,
      24,    25,    26,     0,     0,    27,    28,    29,     0,     0,
      30,     0,     0,    31,     0,    32,   -64,    33,     0,    34,
       0,     0,     0,     0,    35,    36,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    37,     0,     0,     0,    38,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    39,
      40,    41,     1,     0,     2,     3,     4,     5,     6,     0,
       7,     8,     9,    10,     0,     0,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,     0,
       0,    24,    25,    26,     0,     0,    27,    28,    29,     0,
       0,    30,     0,     0,    31,     0,    32,   -64,    33,     0,
      34,     0,     0,     0,     0,    35,    36,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    37,     0,     0,     0,
      38,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      39,    40,    41,     1,     0,     2,     3,     4,     5,     6,
       0,     7,     8,     9,    10,     0,     0,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
       0,     0,    24,    25,    26,     0,     0,    27,    28,    29,
       0,     0,    30,     0,     0,    31,     0,    32,     0,    33,
       0,    34,     0,     0,     0,     0,    35,    36,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    37,     0,     0,
       0,    38,     2,     3,   104,     5,     0,     0,     0,     0,
       0,    39,    40,    41,     0,     0,     0,   224,   225,   226,
     105,   106,    19,    20,    21,    22,    23,     0,     0,    24,
      25,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    31,     0,   107,     0,    33,     0,     0,     0,
       0,     0,     0,    35,    36,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    37,     0,     0,     0,    38,     2,
       3,   104,     5,     0,     0,     0,     0,     0,    39,    40,
      41,     0,     0,     0,     0,     0,     0,   105,   106,    19,
      20,    21,    22,    23,     0,     0,    24,    25,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    31,
       0,   107,     0,    33,     0,     0,     0,     0,     0,     0,
      35,    36,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    37,     0,     0,     0,    38,     2,     3,   122,     5,
       0,     0,     0,     0,     0,    39,    40,    41,     0,     0,
       0,     0,     0,     0,   105,   106,    19,    20,    21,    22,
      23,     0,     0,    24,    25,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   124,     0,   107,     0,
      33,     0,     0,     0,     0,     0,     0,    35,    36,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    37,     0,
       0,     0,    38,     2,     3,   136,     5,     0,     0,     0,
       0,     0,    39,    40,    41,     0,     0,     0,     0,     0,
       0,   105,   106,    19,    20,    21,    22,    23,     0,     0,
      24,    25,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    31,     0,   107,     0,    33,     0,     0,
       0,     0,     0,     0,    35,    36,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    37,     0,     0,     0,    38,
       2,     3,   104,     5,     0,     0,     0,     0,     0,    39,
      40,    41,     0,     0,     0,     0,     0,     0,   105,   106,
      19,    20,    21,    22,    23,     0,     0,    24,    25,     0,
       0,     0,     0,     0,     0,     2,     3,   122,     5,     0,
      31,     0,    32,     0,    33,     0,     0,     0,     0,     0,
       0,    35,    36,   105,   106,    19,    20,    21,     0,     0,
       0,     0,    24,    25,     0,     0,     0,     0,     0,     0,
       0,     0,    37,     0,     0,   124,    38,   107,     0,    33,
       0,     0,     0,     0,     0,     0,    39,    40,    41
};

static const yytype_int16 yycheck[] =
{
       0,     9,   148,    30,   245,    14,    26,    52,    18,    13,
      15,    16,    29,   242,   243,    22,    23,   118,    48,    44,
      50,    49,    50,    27,     5,    50,    30,    31,    35,    36,
      37,    38,    39,    40,    41,    43,   265,    46,     3,     4,
       5,     6,    59,   144,     3,     4,     5,    44,     3,     4,
       5,    96,   153,    50,    49,   156,    21,    22,    23,    24,
      25,    26,    27,    93,    43,    30,    31,    46,    49,    96,
     171,   172,   173,    52,    48,    44,    50,     5,    43,    44,
      45,    50,    47,    50,    47,    52,    94,     5,    51,    54,
      55,    95,    96,    97,    49,    99,   106,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   208,   209,   350,
      75,   212,    44,    43,    79,   119,    43,    96,    50,    93,
     124,    49,    52,   269,    89,    90,    91,    96,    93,   133,
      44,    49,    43,    43,    93,    43,    50,    47,    93,    47,
     241,    51,    43,    51,   385,    43,    49,    50,   249,    47,
      28,    29,   172,    51,    54,    55,     3,     4,     5,     6,
      83,    53,    85,    43,   169,    42,     5,    47,    45,    89,
      90,    51,    43,   274,    21,    22,    23,    24,    25,    26,
      27,     5,    74,    30,    31,    95,     5,    95,   195,   196,
     197,    69,    70,    71,    72,    44,    43,    45,    45,    44,
      47,    50,    94,   126,    44,    50,    44,    54,    55,   213,
      50,    43,    50,    44,   218,    49,    44,    29,    44,    50,
     225,   226,    50,    46,    50,    78,    49,     0,    75,    80,
      81,    82,    79,   190,   191,   192,   256,    96,    65,    66,
      67,    68,    89,    90,    91,    95,    93,    59,    60,    61,
      62,    63,    64,    73,   355,   184,   185,   186,   187,   188,
     189,   180,   181,   182,   183,    76,   367,   368,   369,    33,
      34,    83,    84,    85,    86,    87,    88,    89,    90,    77,
      92,    56,    57,    58,    22,    23,    10,   388,    59,    60,
      61,    62,    63,    64,    48,    96,    50,    35,    36,    37,
      38,    39,    40,    41,    48,    48,    50,    50,    49,   336,
     337,     5,    83,    84,    85,    86,    87,    88,    89,    90,
      49,    92,    49,   331,    49,    50,    49,    50,    49,    50,
      50,   339,   336,   337,   338,    43,   340,   225,   226,   174,
     175,   193,   194,    59,    43,     5,    49,    44,    50,    49,
      46,    52,   360,    46,    52,     5,    48,    52,    96,     3,
       4,     5,     6,   383,   384,    50,    50,    49,     5,   373,
     374,   375,   392,   400,   401,     5,     5,    21,    22,    23,
      24,    25,     5,     5,    49,    43,    30,    31,   396,     5,
      43,    34,   412,     5,   402,    49,   400,   401,    29,    43,
     404,    45,    29,    47,    52,    29,    45,   415,   416,   417,
      44,    44,     5,    45,     8,    43,    13,    52,    96,    44,
      46,   406,   425,   385,   432,   433,    46,    44,    49,    44,
      49,    49,    46,    44,   434,   435,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
      46,   257,   117,     1,   350,     3,     4,     5,     6,     7,
     176,     9,    10,    11,    12,   179,    21,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
     177,    21,    30,    31,    32,   178,   277,    35,    36,    37,
     269,    -1,    40,   270,    -1,    43,   244,    45,    46,    47,
      -1,    49,    -1,    -1,    -1,    -1,    54,    55,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,    -1,    -1,
      -1,    79,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    89,    90,    91,    -1,    93,     0,     1,    -1,     3,
       4,     5,     6,     7,    -1,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    -1,    -1,    30,    31,    32,    -1,
      -1,    35,    36,    37,    -1,    -1,    40,    -1,    -1,    43,
      -1,    45,    46,    47,    -1,    49,    -1,    -1,    -1,    -1,
      54,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    75,    -1,    -1,    -1,    79,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    89,    90,    91,     0,     1,
      -1,     3,     4,     5,     6,     7,    -1,     9,    10,    11,
      12,    -1,    -1,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    -1,    -1,    30,    31,
      32,    -1,    -1,    35,    36,    37,    -1,    -1,    40,    -1,
      -1,    43,    -1,    45,    -1,    47,    -1,    49,    -1,    -1,
      -1,    -1,    54,    55,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    75,    -1,    -1,    -1,    79,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    90,    91,
       1,    -1,     3,     4,     5,     6,     7,    -1,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    -1,    -1,    30,
      31,    32,    -1,    -1,    35,    36,    37,    -1,    -1,    40,
      -1,    -1,    43,    -1,    45,    46,    47,    -1,    49,    -1,
      -1,    -1,    -1,    54,    55,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    75,    -1,    -1,    -1,    79,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    90,
      91,     1,    -1,     3,     4,     5,     6,     7,    -1,     9,
      10,    11,    12,    13,    -1,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    -1,    -1,
      30,    31,    32,    -1,    -1,    35,    36,    37,    -1,    -1,
      40,    -1,    -1,    43,    -1,    45,    46,    47,    -1,    49,
      -1,    -1,    -1,    -1,    54,    55,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    75,    -1,    -1,    -1,    79,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,
      90,    91,     1,    -1,     3,     4,     5,     6,     7,    -1,
       9,    10,    11,    12,    -1,    -1,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    -1,
      -1,    30,    31,    32,    -1,    -1,    35,    36,    37,    -1,
      -1,    40,    -1,    -1,    43,    -1,    45,    46,    47,    -1,
      49,    -1,    -1,    -1,    -1,    54,    55,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    75,    -1,    -1,    -1,
      79,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      89,    90,    91,     1,    -1,     3,     4,     5,     6,     7,
      -1,     9,    10,    11,    12,    -1,    -1,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      -1,    -1,    30,    31,    32,    -1,    -1,    35,    36,    37,
      -1,    -1,    40,    -1,    -1,    43,    -1,    45,    -1,    47,
      -1,    49,    -1,    -1,    -1,    -1,    54,    55,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,    -1,    -1,
      -1,    79,     3,     4,     5,     6,    -1,    -1,    -1,    -1,
      -1,    89,    90,    91,    -1,    -1,    -1,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    -1,    -1,    30,
      31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    43,    -1,    45,    -1,    47,    -1,    -1,    -1,
      -1,    -1,    -1,    54,    55,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    75,    -1,    -1,    -1,    79,     3,
       4,     5,     6,    -1,    -1,    -1,    -1,    -1,    89,    90,
      91,    -1,    -1,    -1,    -1,    -1,    -1,    21,    22,    23,
      24,    25,    26,    27,    -1,    -1,    30,    31,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,
      -1,    45,    -1,    47,    -1,    -1,    -1,    -1,    -1,    -1,
      54,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    75,    -1,    -1,    -1,    79,     3,     4,     5,     6,
      -1,    -1,    -1,    -1,    -1,    89,    90,    91,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    22,    23,    24,    25,    26,
      27,    -1,    -1,    30,    31,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    43,    -1,    45,    -1,
      47,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,    -1,
      -1,    -1,    79,     3,     4,     5,     6,    -1,    -1,    -1,
      -1,    -1,    89,    90,    91,    -1,    -1,    -1,    -1,    -1,
      -1,    21,    22,    23,    24,    25,    26,    27,    -1,    -1,
      30,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    43,    -1,    45,    -1,    47,    -1,    -1,
      -1,    -1,    -1,    -1,    54,    55,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    75,    -1,    -1,    -1,    79,
       3,     4,     5,     6,    -1,    -1,    -1,    -1,    -1,    89,
      90,    91,    -1,    -1,    -1,    -1,    -1,    -1,    21,    22,
      23,    24,    25,    26,    27,    -1,    -1,    30,    31,    -1,
      -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,    -1,
      43,    -1,    45,    -1,    47,    -1,    -1,    -1,    -1,    -1,
      -1,    54,    55,    21,    22,    23,    24,    25,    -1,    -1,
      -1,    -1,    30,    31,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    75,    -1,    -1,    43,    79,    45,    -1,    47,
      -1,    -1,    -1,    -1,    -1,    -1,    89,    90,    91
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     3,     4,     5,     6,     7,     9,    10,    11,
      12,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    30,    31,    32,    35,    36,    37,
      40,    43,    45,    47,    49,    54,    55,    75,    79,    89,
      90,    91,    99,   100,   101,   102,   103,   104,   106,   107,
     108,   109,   112,   113,   114,   115,   116,   117,   123,   124,
     125,   128,   129,   132,   138,   139,   140,   141,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   163,   164,   165,   170,
     178,   180,   181,    49,    52,    43,    43,    43,   101,    43,
       5,    49,     5,    49,     5,    21,    22,    45,   111,   138,
       5,   105,   105,   105,     5,   179,     5,   179,    43,    47,
      51,   161,     5,    24,    43,   157,   158,   154,   156,   154,
      45,   102,   138,    43,    49,   111,     5,   130,   131,   138,
       3,     4,     5,    49,    93,   123,   137,   171,   172,   175,
     176,   177,    50,    93,   166,   167,   168,   169,   154,   154,
     154,   154,   154,   154,   154,     0,     1,   101,    49,    50,
      49,    50,    96,    53,    74,    94,    73,    77,    78,    76,
      65,    66,    67,    68,    28,    29,    69,    70,    71,    72,
      80,    81,    82,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    83,    84,    85,    86,    87,    88,
      89,    90,    92,    47,    51,    95,   161,    95,    47,    51,
      95,   161,   101,   138,    18,    19,    20,   104,   111,   156,
     138,    10,   138,    49,    49,     5,     3,     4,     5,    49,
      49,    59,    43,    43,    42,    45,   133,   133,    44,    93,
     139,   162,   138,     5,   161,    33,    34,   126,   127,    49,
     138,    49,    44,    50,    44,    43,   139,    46,    46,    50,
     173,   174,   175,    49,    52,   139,    48,    50,   139,    50,
      49,   105,   139,   102,   139,   142,   139,   145,   145,   146,
     147,   148,   149,   150,   150,   150,   150,   151,   151,   151,
     151,   151,   151,   152,   152,   152,   153,   153,   154,   154,
     154,   139,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   138,     5,     5,     5,   138,     5,
       5,    44,     5,   110,   110,   110,    49,    49,    29,    44,
      43,    44,   139,     5,   130,   130,   156,     5,    49,   134,
     135,   136,   137,   139,    44,    50,    48,    43,   102,   127,
      44,     5,   130,   174,   175,   176,   139,    93,   168,    52,
      48,    48,   101,    29,    29,    29,   111,   111,   138,   101,
     138,    45,   118,    44,    44,    45,    46,   136,    93,   139,
       5,   101,    44,   139,   139,   139,     8,   138,   138,   138,
      49,    49,    44,    44,    13,   119,   120,   121,   102,   102,
     134,   139,    44,   102,   101,    44,    44,    44,   111,   111,
     101,    49,   138,    14,    46,   122,   121,    46,   102,   101,
     101,   101,    44,    44,    52,    52,   119,   101,   101,   123,
     123,    46
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    98,    99,   100,   100,   100,   101,   101,   101,   101,
     101,   101,   101,   101,   101,   101,   101,   101,   101,   101,
     101,   101,   101,   101,   101,   102,   103,   104,   104,   104,
     104,   105,   105,   106,   107,   108,   108,   109,   109,   109,
     109,   109,   109,   109,   109,   110,   111,   111,   112,   112,
     113,   113,   114,   115,   116,   117,   118,   118,   119,   119,
     120,   120,   121,   122,   123,   123,   124,   125,   125,   125,
     126,   127,   128,   129,   130,   130,   131,   131,   132,   133,
     133,   134,   134,   135,   135,   136,   136,   137,   138,   138,
     139,   139,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   140,   141,   141,   142,   142,
     143,   143,   144,   144,   144,   145,   145,   146,   146,   147,
     147,   148,   148,   149,   149,   149,   149,   149,   150,   150,
     150,   150,   150,   150,   150,   151,   151,   151,   151,   152,
     152,   152,   153,   153,   153,   153,   154,   154,   154,   154,
     154,   154,   154,   154,   154,   154,   155,   155,   155,   156,
     156,   156,   157,   157,   158,   158,   158,   158,   158,   158,
     159,   159,   159,   160,   160,   160,   160,   160,   161,   161,
     162,   162,   162,   162,   163,   163,   163,   163,   163,   163,
     163,   163,   164,   164,   164,   164,   164,   165,   166,   166,
     166,   167,   167,   167,   167,   168,   168,   169,   169,   170,
     171,   171,   171,   171,   172,   172,   173,   173,   174,   174,
     175,   175,   176,   176,   176,   176,   177,   177,   177,   178,
     179,   179,   180,   181
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     3,     2,     2,     2,     2,
       3,     1,     3,     1,     2,     5,     7,     5,     7,     9,
       9,     7,     8,     8,     8,     1,     0,     1,     2,     3,
       2,     3,     3,     5,     3,     5,     3,     5,     0,     1,
       1,     2,     4,     3,     0,     1,     3,     3,     3,     4,
       5,     2,     2,     6,     0,     1,     1,     3,     3,     3,
       5,     0,     1,     1,     2,     1,     1,     5,     1,     3,
       1,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     1,     3,     1,     1,
       1,     5,     1,     3,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     3,     3,     3,     1,     3,
       3,     3,     3,     3,     3,     1,     3,     3,     3,     1,
       3,     3,     1,     3,     3,     3,     1,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     2,     1,
       1,     1,     1,     2,     1,     3,     4,     3,     4,     3,
       3,     3,     3,     2,     2,     4,     3,     2,     2,     3,
       1,     2,     3,     4,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     1,     1,     1,     1,     3,     0,     1,
       2,     2,     2,     4,     4,     0,     1,     1,     2,     3,
       0,     1,     2,     3,     1,     3,     2,     1,     0,     1,
       1,     2,     1,     3,     1,     2,     1,     1,     1,     6,
       0,     1,     3,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* Program: StatementListOpt  */
#line 124 "parser.y"
                     { ast_root = ast_wrap("Program", "", (yyvsp[0].node)); (yyval.node) = ast_root; }
#line 2097 "parser.c"
    break;

  case 3: /* StatementList: Statement  */
#line 129 "parser.y"
              { (yyval.node) = ast_list("StatementList", (yyvsp[0].node)); }
#line 2103 "parser.c"
    break;

  case 4: /* StatementList: StatementList Statement  */
#line 130 "parser.y"
                              { (yyval.node) = (yyvsp[-1].node); ast_add((yyval.node), (yyvsp[0].node)); }
#line 2109 "parser.c"
    break;

  case 5: /* StatementList: StatementList error SEMICOLON  */
#line 131 "parser.y"
                                    { (yyval.node) = (yyvsp[-2].node); yyerrok; }
#line 2115 "parser.c"
    break;

  case 6: /* Statement: BlockStatement  */
#line 136 "parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 2121 "parser.c"
    break;

  case 7: /* Statement: VariableStatement  */
#line 137 "parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 2127 "parser.c"
    break;

  case 8: /* Statement: EmptyStatement  */
#line 138 "parser.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 2133 "parser.c"
    break;

  case 9: /* Statement: ExpressionStatement  */
#line 139 "parser.y"
                          { (yyval.node) = (yyvsp[0].node); }
#line 2139 "parser.c"
    break;

  case 10: /* Statement: IfStatement  */
#line 140 "parser.y"
                  { (yyval.node) = (yyvsp[0].node); }
#line 2145 "parser.c"
    break;

  case 11: /* Statement: IterationStatement  */
#line 141 "parser.y"
                         { (yyval.node) = (yyvsp[0].node); }
#line 2151 "parser.c"
    break;

  case 12: /* Statement: ContinueStatement  */
#line 142 "parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 2157 "parser.c"
    break;

  case 13: /* Statement: BreakStatement  */
#line 143 "parser.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 2163 "parser.c"
    break;

  case 14: /* Statement: ReturnStatement  */
#line 144 "parser.y"
                      { (yyval.node) = (yyvsp[0].node); }
#line 2169 "parser.c"
    break;

  case 15: /* Statement: YieldStatement  */
#line 145 "parser.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 2175 "parser.c"
    break;

  case 16: /* Statement: WithStatement  */
#line 146 "parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 2181 "parser.c"
    break;

  case 17: /* Statement: LabelledStatement  */
#line 147 "parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 2187 "parser.c"
    break;

  case 18: /* Statement: SwitchStatement  */
#line 148 "parser.y"
                      { (yyval.node) = (yyvsp[0].node); }
#line 2193 "parser.c"
    break;

  case 19: /* Statement: ThrowStatement  */
#line 149 "parser.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 2199 "parser.c"
    break;

  case 20: /* Statement: TryStatement  */
#line 150 "parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 2205 "parser.c"
    break;

  case 21: /* Statement: DebuggerStatement  */
#line 151 "parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 2211 "parser.c"
    break;

  case 22: /* Statement: FunctionDeclaration  */
#line 152 "parser.y"
                          { (yyval.node) = (yyvsp[0].node); }
#line 2217 "parser.c"
    break;

  case 23: /* Statement: ClassDeclaration  */
#line 153 "parser.y"
                       { (yyval.node) = (yyvsp[0].node); }
#line 2223 "parser.c"
    break;

  case 24: /* Statement: error SEMICOLON  */
#line 154 "parser.y"
                      { (yyval.node) = ast_new("ErrorStatement", ""); yyerrok; }
#line 2229 "parser.c"
    break;

  case 25: /* BlockStatement: LBRACE StatementListOpt RBRACE  */
#line 159 "parser.y"
                                   { (yyval.node) = ast_wrap("BlockStatement", "", (yyvsp[-1].node)); }
#line 2235 "parser.c"
    break;

  case 26: /* VariableStatement: VariableDeclarationList SEMICOLON  */
#line 164 "parser.y"
                                      { (yyval.node) = ast_wrap("VariableDeclaration", "", (yyvsp[-1].node)); }
#line 2241 "parser.c"
    break;

  case 27: /* VariableDeclarationList: VAR VariableDeclaration  */
#line 168 "parser.y"
                            { (yyval.node) = ast_list("VariableDeclarationList", (yyvsp[0].node)); }
#line 2247 "parser.c"
    break;

  case 28: /* VariableDeclarationList: LET VariableDeclaration  */
#line 169 "parser.y"
                              { (yyval.node) = ast_list("VariableDeclarationList", (yyvsp[0].node)); }
#line 2253 "parser.c"
    break;

  case 29: /* VariableDeclarationList: CONST VariableDeclaration  */
#line 170 "parser.y"
                                { (yyval.node) = ast_list("VariableDeclarationList", (yyvsp[0].node)); }
#line 2259 "parser.c"
    break;

  case 30: /* VariableDeclarationList: VariableDeclarationList COMMA VariableDeclaration  */
#line 171 "parser.y"
                                                        { (yyval.node) = (yyvsp[-2].node); ast_add((yyval.node), (yyvsp[0].node)); }
#line 2265 "parser.c"
    break;

  case 31: /* VariableDeclaration: IDENTIFIER  */
#line 175 "parser.y"
               { (yyval.node) = ast_new("VariableDeclarator", (yyvsp[0].string)); ast_add((yyval.node), ast_leaf("Identifier", (yyvsp[0].string))); }
#line 2271 "parser.c"
    break;

  case 32: /* VariableDeclaration: IDENTIFIER ASSIGN AssignmentExpression  */
#line 176 "parser.y"
                                             { (yyval.node) = ast_new("VariableDeclarator", (yyvsp[-2].string)); ast_add((yyval.node), ast_leaf("Identifier", (yyvsp[-2].string))); ast_add((yyval.node), ast_wrap("Initializer", "", (yyvsp[0].node))); }
#line 2277 "parser.c"
    break;

  case 33: /* EmptyStatement: SEMICOLON  */
#line 181 "parser.y"
              { (yyval.node) = ast_new("EmptyStatement", ""); }
#line 2283 "parser.c"
    break;

  case 34: /* ExpressionStatement: Expression SEMICOLON  */
#line 186 "parser.y"
                         { (yyval.node) = ast_wrap("ExpressionStatement", "", (yyvsp[-1].node)); }
#line 2289 "parser.c"
    break;

  case 35: /* IfStatement: IF LPAREN Expression RPAREN Statement  */
#line 191 "parser.y"
                                          { (yyval.node) = ast_new("IfStatement", ""); ast_add((yyval.node), ast_wrap("Test", "", (yyvsp[-2].node))); ast_add((yyval.node), ast_wrap("Consequent", "", (yyvsp[0].node))); }
#line 2295 "parser.c"
    break;

  case 36: /* IfStatement: IF LPAREN Expression RPAREN Statement ELSE Statement  */
#line 192 "parser.y"
                                                           { (yyval.node) = ast_new("IfStatement", ""); ast_add((yyval.node), ast_wrap("Test", "", (yyvsp[-4].node))); ast_add((yyval.node), ast_wrap("Consequent", "", (yyvsp[-2].node))); ast_add((yyval.node), ast_wrap("Alternate", "", (yyvsp[0].node))); }
#line 2301 "parser.c"
    break;

  case 37: /* IterationStatement: WHILE LPAREN Expression RPAREN Statement  */
#line 197 "parser.y"
                                             { (yyval.node) = ast_new("WhileStatement", ""); ast_add((yyval.node), ast_wrap("Test", "", (yyvsp[-2].node))); ast_add((yyval.node), ast_wrap("Body", "", (yyvsp[0].node))); }
#line 2307 "parser.c"
    break;

  case 38: /* IterationStatement: DO Statement WHILE LPAREN Expression RPAREN SEMICOLON  */
#line 198 "parser.y"
                                                            { (yyval.node) = ast_new("DoWhileStatement", ""); ast_add((yyval.node), ast_wrap("Body", "", (yyvsp[-5].node))); ast_add((yyval.node), ast_wrap("Test", "", (yyvsp[-2].node))); }
#line 2313 "parser.c"
    break;

  case 39: /* IterationStatement: FOR LPAREN ExpressionOpt SEMICOLON ExpressionOpt SEMICOLON ExpressionOpt RPAREN Statement  */
#line 199 "parser.y"
                                                                                                { (yyval.node) = ast_new("ForStatement", ""); ast_add((yyval.node), ast_wrap("Init", "", (yyvsp[-6].node))); ast_add((yyval.node), ast_wrap("Test", "", (yyvsp[-4].node))); ast_add((yyval.node), ast_wrap("Update", "", (yyvsp[-2].node))); ast_add((yyval.node), ast_wrap("Body", "", (yyvsp[0].node))); }
#line 2319 "parser.c"
    break;

  case 40: /* IterationStatement: FOR LPAREN VariableDeclarationList SEMICOLON ExpressionOpt SEMICOLON ExpressionOpt RPAREN Statement  */
#line 200 "parser.y"
                                                                                                          { (yyval.node) = ast_new("ForStatement", ""); ast_add((yyval.node), ast_wrap("Init", "", (yyvsp[-6].node))); ast_add((yyval.node), ast_wrap("Test", "", (yyvsp[-4].node))); ast_add((yyval.node), ast_wrap("Update", "", (yyvsp[-2].node))); ast_add((yyval.node), ast_wrap("Body", "", (yyvsp[0].node))); }
#line 2325 "parser.c"
    break;

  case 41: /* IterationStatement: FOR LPAREN LeftHandSideExpression IN Expression RPAREN Statement  */
#line 201 "parser.y"
                                                                       { (yyval.node) = ast_new("ForInStatement", ""); ast_add((yyval.node), ast_wrap("Left", "", (yyvsp[-4].node))); ast_add((yyval.node), ast_wrap("Right", "", (yyvsp[-2].node))); ast_add((yyval.node), ast_wrap("Body", "", (yyvsp[0].node))); }
#line 2331 "parser.c"
    break;

  case 42: /* IterationStatement: FOR LPAREN VAR ForBinding IN Expression RPAREN Statement  */
#line 202 "parser.y"
                                                               { (yyval.node) = ast_new("ForInStatement", "var"); ast_add((yyval.node), ast_wrap("Left", "", (yyvsp[-4].node))); ast_add((yyval.node), ast_wrap("Right", "", (yyvsp[-2].node))); ast_add((yyval.node), ast_wrap("Body", "", (yyvsp[0].node))); }
#line 2337 "parser.c"
    break;

  case 43: /* IterationStatement: FOR LPAREN LET ForBinding IN Expression RPAREN Statement  */
#line 203 "parser.y"
                                                               { (yyval.node) = ast_new("ForInStatement", "let"); ast_add((yyval.node), ast_wrap("Left", "", (yyvsp[-4].node))); ast_add((yyval.node), ast_wrap("Right", "", (yyvsp[-2].node))); ast_add((yyval.node), ast_wrap("Body", "", (yyvsp[0].node))); }
#line 2343 "parser.c"
    break;

  case 44: /* IterationStatement: FOR LPAREN CONST ForBinding IN Expression RPAREN Statement  */
#line 204 "parser.y"
                                                                 { (yyval.node) = ast_new("ForInStatement", "const"); ast_add((yyval.node), ast_wrap("Left", "", (yyvsp[-4].node))); ast_add((yyval.node), ast_wrap("Right", "", (yyvsp[-2].node))); ast_add((yyval.node), ast_wrap("Body", "", (yyvsp[0].node))); }
#line 2349 "parser.c"
    break;

  case 45: /* ForBinding: IDENTIFIER  */
#line 208 "parser.y"
               { (yyval.node) = ast_leaf("Identifier", (yyvsp[0].string)); }
#line 2355 "parser.c"
    break;

  case 46: /* ExpressionOpt: %empty  */
#line 212 "parser.y"
                { (yyval.node) = ast_new("Empty", ""); }
#line 2361 "parser.c"
    break;

  case 47: /* ExpressionOpt: Expression  */
#line 213 "parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 2367 "parser.c"
    break;

  case 48: /* ContinueStatement: CONTINUE SEMICOLON  */
#line 218 "parser.y"
                       { (yyval.node) = ast_new("ContinueStatement", ""); }
#line 2373 "parser.c"
    break;

  case 49: /* ContinueStatement: CONTINUE IDENTIFIER SEMICOLON  */
#line 219 "parser.y"
                                    { (yyval.node) = ast_new("ContinueStatement", (yyvsp[-1].string)); }
#line 2379 "parser.c"
    break;

  case 50: /* BreakStatement: BREAK SEMICOLON  */
#line 224 "parser.y"
                    { (yyval.node) = ast_new("BreakStatement", ""); }
#line 2385 "parser.c"
    break;

  case 51: /* BreakStatement: BREAK IDENTIFIER SEMICOLON  */
#line 225 "parser.y"
                                 { (yyval.node) = ast_new("BreakStatement", (yyvsp[-1].string)); }
#line 2391 "parser.c"
    break;

  case 52: /* ReturnStatement: RETURN ExpressionOpt SEMICOLON  */
#line 230 "parser.y"
                                   { (yyval.node) = ast_wrap("ReturnStatement", "", (yyvsp[-1].node)); }
#line 2397 "parser.c"
    break;

  case 53: /* WithStatement: WITH LPAREN Expression RPAREN Statement  */
#line 235 "parser.y"
                                            { (yyval.node) = ast_new("WithStatement", ""); ast_add((yyval.node), ast_wrap("Object", "", (yyvsp[-2].node))); ast_add((yyval.node), ast_wrap("Body", "", (yyvsp[0].node))); }
#line 2403 "parser.c"
    break;

  case 54: /* LabelledStatement: IDENTIFIER COLON Statement  */
#line 240 "parser.y"
                               { (yyval.node) = ast_new("LabeledStatement", (yyvsp[-2].string)); ast_add((yyval.node), (yyvsp[0].node)); }
#line 2409 "parser.c"
    break;

  case 55: /* SwitchStatement: SWITCH LPAREN Expression RPAREN CaseBlock  */
#line 245 "parser.y"
                                              { (yyval.node) = ast_new("SwitchStatement", ""); ast_add((yyval.node), ast_wrap("Discriminant", "", (yyvsp[-2].node))); ast_add((yyval.node), (yyvsp[0].node)); }
#line 2415 "parser.c"
    break;

  case 56: /* CaseBlock: LBRACE CaseClausesOpt RBRACE  */
#line 249 "parser.y"
                                 { (yyval.node) = ast_wrap("CaseBlock", "", (yyvsp[-1].node)); }
#line 2421 "parser.c"
    break;

  case 57: /* CaseBlock: LBRACE CaseClausesOpt DefaultClause CaseClausesOpt RBRACE  */
#line 250 "parser.y"
                                                                { (yyval.node) = ast_new("CaseBlock", ""); ast_add((yyval.node), (yyvsp[-3].node)); ast_add((yyval.node), (yyvsp[-2].node)); ast_add((yyval.node), (yyvsp[-1].node)); }
#line 2427 "parser.c"
    break;

  case 58: /* CaseClausesOpt: %empty  */
#line 254 "parser.y"
                { (yyval.node) = ast_new("CaseClauses", ""); }
#line 2433 "parser.c"
    break;

  case 59: /* CaseClausesOpt: CaseClauses  */
#line 255 "parser.y"
                  { (yyval.node) = (yyvsp[0].node); }
#line 2439 "parser.c"
    break;

  case 60: /* CaseClauses: CaseClause  */
#line 259 "parser.y"
               { (yyval.node) = ast_list("CaseClauses", (yyvsp[0].node)); }
#line 2445 "parser.c"
    break;

  case 61: /* CaseClauses: CaseClauses CaseClause  */
#line 260 "parser.y"
                             { (yyval.node) = (yyvsp[-1].node); ast_add((yyval.node), (yyvsp[0].node)); }
#line 2451 "parser.c"
    break;

  case 62: /* CaseClause: CASE Expression COLON StatementListOpt  */
#line 264 "parser.y"
                                           { (yyval.node) = ast_new("CaseClause", ""); ast_add((yyval.node), ast_wrap("Test", "", (yyvsp[-2].node))); ast_add((yyval.node), (yyvsp[0].node)); }
#line 2457 "parser.c"
    break;

  case 63: /* DefaultClause: DEFAULT COLON StatementListOpt  */
#line 268 "parser.y"
                                   { (yyval.node) = ast_wrap("DefaultClause", "", (yyvsp[0].node)); }
#line 2463 "parser.c"
    break;

  case 64: /* StatementListOpt: %empty  */
#line 272 "parser.y"
                { (yyval.node) = ast_new("StatementList", ""); }
#line 2469 "parser.c"
    break;

  case 65: /* StatementListOpt: StatementList  */
#line 273 "parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 2475 "parser.c"
    break;

  case 66: /* ThrowStatement: THROW Expression SEMICOLON  */
#line 278 "parser.y"
                               { (yyval.node) = ast_wrap("ThrowStatement", "", (yyvsp[-1].node)); }
#line 2481 "parser.c"
    break;

  case 67: /* TryStatement: TRY BlockStatement Catch  */
#line 283 "parser.y"
                             { (yyval.node) = ast_new("TryStatement", ""); ast_add((yyval.node), (yyvsp[-1].node)); ast_add((yyval.node), (yyvsp[0].node)); }
#line 2487 "parser.c"
    break;

  case 68: /* TryStatement: TRY BlockStatement Finally  */
#line 284 "parser.y"
                                 { (yyval.node) = ast_new("TryStatement", ""); ast_add((yyval.node), (yyvsp[-1].node)); ast_add((yyval.node), (yyvsp[0].node)); }
#line 2493 "parser.c"
    break;

  case 69: /* TryStatement: TRY BlockStatement Catch Finally  */
#line 285 "parser.y"
                                       { (yyval.node) = ast_new("TryStatement", ""); ast_add((yyval.node), (yyvsp[-2].node)); ast_add((yyval.node), (yyvsp[-1].node)); ast_add((yyval.node), (yyvsp[0].node)); }
#line 2499 "parser.c"
    break;

  case 70: /* Catch: CATCH LPAREN IDENTIFIER RPAREN BlockStatement  */
#line 289 "parser.y"
                                                  { (yyval.node) = ast_new("CatchClause", (yyvsp[-2].string)); ast_add((yyval.node), ast_leaf("Identifier", (yyvsp[-2].string))); ast_add((yyval.node), (yyvsp[0].node)); }
#line 2505 "parser.c"
    break;

  case 71: /* Finally: FINALLY BlockStatement  */
#line 293 "parser.y"
                           { (yyval.node) = ast_wrap("FinallyClause", "", (yyvsp[0].node)); }
#line 2511 "parser.c"
    break;

  case 72: /* DebuggerStatement: DEBUGGER SEMICOLON  */
#line 298 "parser.y"
                       { (yyval.node) = ast_new("DebuggerStatement", ""); }
#line 2517 "parser.c"
    break;

  case 73: /* FunctionDeclaration: FUNCTION IDENTIFIER LPAREN FormalParametersOpt RPAREN BlockStatement  */
#line 303 "parser.y"
                                                                         { (yyval.node) = ast_new("FunctionDeclaration", (yyvsp[-4].string)); ast_add((yyval.node), ast_leaf("Identifier", (yyvsp[-4].string))); ast_add((yyval.node), (yyvsp[-2].node)); ast_add((yyval.node), (yyvsp[0].node)); }
#line 2523 "parser.c"
    break;

  case 74: /* FormalParametersOpt: %empty  */
#line 307 "parser.y"
                { (yyval.node) = ast_new("Parameters", ""); }
#line 2529 "parser.c"
    break;

  case 75: /* FormalParametersOpt: FormalParameters  */
#line 308 "parser.y"
                       { (yyval.node) = (yyvsp[0].node); }
#line 2535 "parser.c"
    break;

  case 76: /* FormalParameters: IDENTIFIER  */
#line 312 "parser.y"
               { (yyval.node) = ast_list("Parameters", ast_leaf("Identifier", (yyvsp[0].string))); }
#line 2541 "parser.c"
    break;

  case 77: /* FormalParameters: FormalParameters COMMA IDENTIFIER  */
#line 313 "parser.y"
                                        { (yyval.node) = (yyvsp[-2].node); ast_add((yyval.node), ast_leaf("Identifier", (yyvsp[0].string))); }
#line 2547 "parser.c"
    break;

  case 78: /* ClassDeclaration: CLASS IDENTIFIER ClassTail  */
#line 318 "parser.y"
                               { (yyval.node) = ast_new("ClassDeclaration", (yyvsp[-1].string)); ast_add((yyval.node), ast_leaf("Identifier", (yyvsp[-1].string))); ast_add((yyval.node), (yyvsp[0].node)); }
#line 2553 "parser.c"
    break;

  case 79: /* ClassTail: LBRACE ClassBodyOpt RBRACE  */
#line 322 "parser.y"
                               { (yyval.node) = ast_wrap("ClassBody", "", (yyvsp[-1].node)); }
#line 2559 "parser.c"
    break;

  case 80: /* ClassTail: EXTENDS LeftHandSideExpression LBRACE ClassBodyOpt RBRACE  */
#line 323 "parser.y"
                                                                { (yyval.node) = ast_new("ClassTail", "extends"); ast_add((yyval.node), ast_wrap("SuperClass", "", (yyvsp[-3].node))); ast_add((yyval.node), (yyvsp[-1].node)); }
#line 2565 "parser.c"
    break;

  case 81: /* ClassBodyOpt: %empty  */
#line 327 "parser.y"
                { (yyval.node) = ast_new("ClassElements", ""); }
#line 2571 "parser.c"
    break;

  case 82: /* ClassBodyOpt: ClassBody  */
#line 328 "parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 2577 "parser.c"
    break;

  case 83: /* ClassBody: ClassElement  */
#line 332 "parser.y"
                 { (yyval.node) = ast_list("ClassElements", (yyvsp[0].node)); }
#line 2583 "parser.c"
    break;

  case 84: /* ClassBody: ClassBody ClassElement  */
#line 333 "parser.y"
                             { (yyval.node) = (yyvsp[-1].node); ast_add((yyval.node), (yyvsp[0].node)); }
#line 2589 "parser.c"
    break;

  case 85: /* ClassElement: MethodDefinition  */
#line 337 "parser.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 2595 "parser.c"
    break;

  case 86: /* ClassElement: SEMICOLON  */
#line 338 "parser.y"
                { (yyval.node) = ast_new("EmptyClassElement", ""); }
#line 2601 "parser.c"
    break;

  case 87: /* MethodDefinition: IDENTIFIER LPAREN FormalParametersOpt RPAREN BlockStatement  */
#line 342 "parser.y"
                                                                { (yyval.node) = ast_new("MethodDefinition", (yyvsp[-4].string)); ast_add((yyval.node), ast_leaf("Identifier", (yyvsp[-4].string))); ast_add((yyval.node), (yyvsp[-2].node)); ast_add((yyval.node), (yyvsp[0].node)); }
#line 2607 "parser.c"
    break;

  case 88: /* Expression: AssignmentExpression  */
#line 347 "parser.y"
                         { (yyval.node) = (yyvsp[0].node); }
#line 2613 "parser.c"
    break;

  case 89: /* Expression: Expression COMMA AssignmentExpression  */
#line 348 "parser.y"
                                            { (yyval.node) = ast_binary("SequenceExpression", ",", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2619 "parser.c"
    break;

  case 90: /* AssignmentExpression: ArrowFunction  */
#line 353 "parser.y"
                  { (yyval.node) = (yyvsp[0].node); }
#line 2625 "parser.c"
    break;

  case 91: /* AssignmentExpression: ConditionalExpression  */
#line 354 "parser.y"
                            { (yyval.node) = (yyvsp[0].node); }
#line 2631 "parser.c"
    break;

  case 92: /* AssignmentExpression: LeftHandSideExpression ASSIGN AssignmentExpression  */
#line 355 "parser.y"
                                                         { (yyval.node) = ast_binary("AssignmentExpression", "=", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2637 "parser.c"
    break;

  case 93: /* AssignmentExpression: LeftHandSideExpression PLUS_ASSIGN AssignmentExpression  */
#line 356 "parser.y"
                                                              { (yyval.node) = ast_binary("AssignmentExpression", "+=", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2643 "parser.c"
    break;

  case 94: /* AssignmentExpression: LeftHandSideExpression MINUS_ASSIGN AssignmentExpression  */
#line 357 "parser.y"
                                                               { (yyval.node) = ast_binary("AssignmentExpression", "-=", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2649 "parser.c"
    break;

  case 95: /* AssignmentExpression: LeftHandSideExpression MULTIPLY_ASSIGN AssignmentExpression  */
#line 358 "parser.y"
                                                                  { (yyval.node) = ast_binary("AssignmentExpression", "*=", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2655 "parser.c"
    break;

  case 96: /* AssignmentExpression: LeftHandSideExpression DIVIDE_ASSIGN AssignmentExpression  */
#line 359 "parser.y"
                                                                { (yyval.node) = ast_binary("AssignmentExpression", "/=", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2661 "parser.c"
    break;

  case 97: /* AssignmentExpression: LeftHandSideExpression MODULO_ASSIGN AssignmentExpression  */
#line 360 "parser.y"
                                                                { (yyval.node) = ast_binary("AssignmentExpression", "%=", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2667 "parser.c"
    break;

  case 98: /* AssignmentExpression: LeftHandSideExpression EXPONENT_ASSIGN AssignmentExpression  */
#line 361 "parser.y"
                                                                  { (yyval.node) = ast_binary("AssignmentExpression", "**=", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2673 "parser.c"
    break;

  case 99: /* AssignmentExpression: LeftHandSideExpression AND_ASSIGN AssignmentExpression  */
#line 362 "parser.y"
                                                             { (yyval.node) = ast_binary("AssignmentExpression", "&=", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2679 "parser.c"
    break;

  case 100: /* AssignmentExpression: LeftHandSideExpression OR_ASSIGN AssignmentExpression  */
#line 363 "parser.y"
                                                            { (yyval.node) = ast_binary("AssignmentExpression", "|=", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2685 "parser.c"
    break;

  case 101: /* AssignmentExpression: LeftHandSideExpression XOR_ASSIGN AssignmentExpression  */
#line 364 "parser.y"
                                                             { (yyval.node) = ast_binary("AssignmentExpression", "^=", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2691 "parser.c"
    break;

  case 102: /* AssignmentExpression: LeftHandSideExpression LEFT_SHIFT_ASSIGN AssignmentExpression  */
#line 365 "parser.y"
                                                                    { (yyval.node) = ast_binary("AssignmentExpression", "<<=", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2697 "parser.c"
    break;

  case 103: /* AssignmentExpression: LeftHandSideExpression RIGHT_SHIFT_ASSIGN AssignmentExpression  */
#line 366 "parser.y"
                                                                     { (yyval.node) = ast_binary("AssignmentExpression", ">>=", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2703 "parser.c"
    break;

  case 104: /* AssignmentExpression: LeftHandSideExpression UNSIGNED_RIGHT_SHIFT_ASSIGN AssignmentExpression  */
#line 367 "parser.y"
                                                                              { (yyval.node) = ast_binary("AssignmentExpression", ">>>=", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2709 "parser.c"
    break;

  case 105: /* ArrowFunction: ArrowParameters ARROW ConciseBody  */
#line 371 "parser.y"
                                      { (yyval.node) = ast_new("ArrowFunctionExpression", ""); ast_add((yyval.node), ast_wrap("Params", "", (yyvsp[-2].node))); ast_add((yyval.node), ast_wrap("Body", "", (yyvsp[0].node))); }
#line 2715 "parser.c"
    break;

  case 106: /* ArrowParameters: IDENTIFIER  */
#line 375 "parser.y"
               { (yyval.node) = ast_leaf("Identifier", (yyvsp[0].string)); }
#line 2721 "parser.c"
    break;

  case 107: /* ArrowParameters: LPAREN FormalParametersOpt RPAREN  */
#line 376 "parser.y"
                                        { (yyval.node) = (yyvsp[-1].node); }
#line 2727 "parser.c"
    break;

  case 108: /* ConciseBody: AssignmentExpression  */
#line 380 "parser.y"
                         { (yyval.node) = (yyvsp[0].node); }
#line 2733 "parser.c"
    break;

  case 109: /* ConciseBody: BlockStatement  */
#line 381 "parser.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 2739 "parser.c"
    break;

  case 110: /* ConditionalExpression: LogicalORExpression  */
#line 386 "parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 2745 "parser.c"
    break;

  case 111: /* ConditionalExpression: LogicalORExpression QUESTION AssignmentExpression COLON AssignmentExpression  */
#line 387 "parser.y"
                                                                                   { (yyval.node) = ast_new("ConditionalExpression", "?:"); ast_add((yyval.node), ast_wrap("Test", "", (yyvsp[-4].node))); ast_add((yyval.node), ast_wrap("Consequent", "", (yyvsp[-2].node))); ast_add((yyval.node), ast_wrap("Alternate", "", (yyvsp[0].node))); }
#line 2751 "parser.c"
    break;

  case 112: /* LogicalORExpression: LogicalANDExpression  */
#line 392 "parser.y"
                         { (yyval.node) = (yyvsp[0].node); }
#line 2757 "parser.c"
    break;

  case 113: /* LogicalORExpression: LogicalORExpression LOGICAL_OR LogicalANDExpression  */
#line 393 "parser.y"
                                                          { (yyval.node) = ast_binary("LogicalExpression", "||", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2763 "parser.c"
    break;

  case 114: /* LogicalORExpression: LogicalORExpression NULLISH_COALESCING LogicalANDExpression  */
#line 394 "parser.y"
                                                                  { (yyval.node) = ast_binary("LogicalExpression", "??", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2769 "parser.c"
    break;

  case 115: /* LogicalANDExpression: BitwiseORExpression  */
#line 399 "parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 2775 "parser.c"
    break;

  case 116: /* LogicalANDExpression: LogicalANDExpression LOGICAL_AND BitwiseORExpression  */
#line 400 "parser.y"
                                                           { (yyval.node) = ast_binary("LogicalExpression", "&&", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2781 "parser.c"
    break;

  case 117: /* BitwiseORExpression: BitwiseXORExpression  */
#line 405 "parser.y"
                         { (yyval.node) = (yyvsp[0].node); }
#line 2787 "parser.c"
    break;

  case 118: /* BitwiseORExpression: BitwiseORExpression BITWISE_OR BitwiseXORExpression  */
#line 406 "parser.y"
                                                          { (yyval.node) = ast_binary("BinaryExpression", "|", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2793 "parser.c"
    break;

  case 119: /* BitwiseXORExpression: BitwiseANDExpression  */
#line 411 "parser.y"
                         { (yyval.node) = (yyvsp[0].node); }
#line 2799 "parser.c"
    break;

  case 120: /* BitwiseXORExpression: BitwiseXORExpression BITWISE_XOR BitwiseANDExpression  */
#line 412 "parser.y"
                                                            { (yyval.node) = ast_binary("BinaryExpression", "^", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2805 "parser.c"
    break;

  case 121: /* BitwiseANDExpression: EqualityExpression  */
#line 417 "parser.y"
                       { (yyval.node) = (yyvsp[0].node); }
#line 2811 "parser.c"
    break;

  case 122: /* BitwiseANDExpression: BitwiseANDExpression BITWISE_AND EqualityExpression  */
#line 418 "parser.y"
                                                          { (yyval.node) = ast_binary("BinaryExpression", "&", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2817 "parser.c"
    break;

  case 123: /* EqualityExpression: RelationalExpression  */
#line 423 "parser.y"
                         { (yyval.node) = (yyvsp[0].node); }
#line 2823 "parser.c"
    break;

  case 124: /* EqualityExpression: EqualityExpression EQUAL RelationalExpression  */
#line 424 "parser.y"
                                                    { (yyval.node) = ast_binary("BinaryExpression", "==", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2829 "parser.c"
    break;

  case 125: /* EqualityExpression: EqualityExpression NOT_EQUAL RelationalExpression  */
#line 425 "parser.y"
                                                        { (yyval.node) = ast_binary("BinaryExpression", "!=", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2835 "parser.c"
    break;

  case 126: /* EqualityExpression: EqualityExpression STRICT_EQUAL RelationalExpression  */
#line 426 "parser.y"
                                                           { (yyval.node) = ast_binary("BinaryExpression", "===", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2841 "parser.c"
    break;

  case 127: /* EqualityExpression: EqualityExpression STRICT_NOT_EQUAL RelationalExpression  */
#line 427 "parser.y"
                                                               { (yyval.node) = ast_binary("BinaryExpression", "!==", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2847 "parser.c"
    break;

  case 128: /* RelationalExpression: ShiftExpression  */
#line 432 "parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 2853 "parser.c"
    break;

  case 129: /* RelationalExpression: RelationalExpression LESS ShiftExpression  */
#line 433 "parser.y"
                                                { (yyval.node) = ast_binary("BinaryExpression", "<", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2859 "parser.c"
    break;

  case 130: /* RelationalExpression: RelationalExpression GREATER ShiftExpression  */
#line 434 "parser.y"
                                                   { (yyval.node) = ast_binary("BinaryExpression", ">", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2865 "parser.c"
    break;

  case 131: /* RelationalExpression: RelationalExpression LESS_EQUAL ShiftExpression  */
#line 435 "parser.y"
                                                      { (yyval.node) = ast_binary("BinaryExpression", "<=", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2871 "parser.c"
    break;

  case 132: /* RelationalExpression: RelationalExpression GREATER_EQUAL ShiftExpression  */
#line 436 "parser.y"
                                                         { (yyval.node) = ast_binary("BinaryExpression", ">=", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2877 "parser.c"
    break;

  case 133: /* RelationalExpression: RelationalExpression INSTANCEOF ShiftExpression  */
#line 437 "parser.y"
                                                      { (yyval.node) = ast_binary("BinaryExpression", "instanceof", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2883 "parser.c"
    break;

  case 134: /* RelationalExpression: RelationalExpression IN ShiftExpression  */
#line 438 "parser.y"
                                              { (yyval.node) = ast_binary("BinaryExpression", "in", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2889 "parser.c"
    break;

  case 135: /* ShiftExpression: AdditiveExpression  */
#line 443 "parser.y"
                       { (yyval.node) = (yyvsp[0].node); }
#line 2895 "parser.c"
    break;

  case 136: /* ShiftExpression: ShiftExpression LEFT_SHIFT AdditiveExpression  */
#line 444 "parser.y"
                                                    { (yyval.node) = ast_binary("BinaryExpression", "<<", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2901 "parser.c"
    break;

  case 137: /* ShiftExpression: ShiftExpression RIGHT_SHIFT AdditiveExpression  */
#line 445 "parser.y"
                                                     { (yyval.node) = ast_binary("BinaryExpression", ">>", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2907 "parser.c"
    break;

  case 138: /* ShiftExpression: ShiftExpression UNSIGNED_RIGHT_SHIFT AdditiveExpression  */
#line 446 "parser.y"
                                                              { (yyval.node) = ast_binary("BinaryExpression", ">>>", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2913 "parser.c"
    break;

  case 139: /* AdditiveExpression: MultiplicativeExpression  */
#line 451 "parser.y"
                             { (yyval.node) = (yyvsp[0].node); }
#line 2919 "parser.c"
    break;

  case 140: /* AdditiveExpression: AdditiveExpression PLUS MultiplicativeExpression  */
#line 452 "parser.y"
                                                       { (yyval.node) = ast_binary("BinaryExpression", "+", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2925 "parser.c"
    break;

  case 141: /* AdditiveExpression: AdditiveExpression MINUS MultiplicativeExpression  */
#line 453 "parser.y"
                                                        { (yyval.node) = ast_binary("BinaryExpression", "-", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2931 "parser.c"
    break;

  case 142: /* MultiplicativeExpression: UnaryExpression  */
#line 458 "parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 2937 "parser.c"
    break;

  case 143: /* MultiplicativeExpression: MultiplicativeExpression MULTIPLY UnaryExpression  */
#line 459 "parser.y"
                                                        { (yyval.node) = ast_binary("BinaryExpression", "*", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2943 "parser.c"
    break;

  case 144: /* MultiplicativeExpression: MultiplicativeExpression DIVIDE UnaryExpression  */
#line 460 "parser.y"
                                                      { (yyval.node) = ast_binary("BinaryExpression", "/", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2949 "parser.c"
    break;

  case 145: /* MultiplicativeExpression: MultiplicativeExpression MODULO UnaryExpression  */
#line 461 "parser.y"
                                                      { (yyval.node) = ast_binary("BinaryExpression", "%", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2955 "parser.c"
    break;

  case 146: /* UnaryExpression: PostfixExpression  */
#line 466 "parser.y"
                      { (yyval.node) = (yyvsp[0].node); }
#line 2961 "parser.c"
    break;

  case 147: /* UnaryExpression: DELETE UnaryExpression  */
#line 467 "parser.y"
                             { (yyval.node) = ast_unary("UnaryExpression", "delete", (yyvsp[0].node)); }
#line 2967 "parser.c"
    break;

  case 148: /* UnaryExpression: TYPEOF UnaryExpression  */
#line 468 "parser.y"
                             { (yyval.node) = ast_unary("UnaryExpression", "typeof", (yyvsp[0].node)); }
#line 2973 "parser.c"
    break;

  case 149: /* UnaryExpression: INCREMENT UnaryExpression  */
#line 469 "parser.y"
                                { (yyval.node) = ast_unary("UpdateExpression", "prefix ++", (yyvsp[0].node)); }
#line 2979 "parser.c"
    break;

  case 150: /* UnaryExpression: DECREMENT UnaryExpression  */
#line 470 "parser.y"
                                { (yyval.node) = ast_unary("UpdateExpression", "prefix --", (yyvsp[0].node)); }
#line 2985 "parser.c"
    break;

  case 151: /* UnaryExpression: PLUS UnaryExpression  */
#line 471 "parser.y"
                           { (yyval.node) = ast_unary("UnaryExpression", "+", (yyvsp[0].node)); }
#line 2991 "parser.c"
    break;

  case 152: /* UnaryExpression: MINUS UnaryExpression  */
#line 472 "parser.y"
                            { (yyval.node) = ast_unary("UnaryExpression", "-", (yyvsp[0].node)); }
#line 2997 "parser.c"
    break;

  case 153: /* UnaryExpression: BITWISE_NOT UnaryExpression  */
#line 473 "parser.y"
                                  { (yyval.node) = ast_unary("UnaryExpression", "~", (yyvsp[0].node)); }
#line 3003 "parser.c"
    break;

  case 154: /* UnaryExpression: NOT UnaryExpression  */
#line 474 "parser.y"
                          { (yyval.node) = ast_unary("UnaryExpression", "!", (yyvsp[0].node)); }
#line 3009 "parser.c"
    break;

  case 155: /* UnaryExpression: EXPONENT UnaryExpression  */
#line 475 "parser.y"
                               { (yyval.node) = ast_unary("UnaryExpression", "**", (yyvsp[0].node)); }
#line 3015 "parser.c"
    break;

  case 156: /* PostfixExpression: LeftHandSideExpression  */
#line 480 "parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 3021 "parser.c"
    break;

  case 157: /* PostfixExpression: LeftHandSideExpression INCREMENT  */
#line 481 "parser.y"
                                       { (yyval.node) = ast_unary("UpdateExpression", "postfix ++", (yyvsp[-1].node)); }
#line 3027 "parser.c"
    break;

  case 158: /* PostfixExpression: LeftHandSideExpression DECREMENT  */
#line 482 "parser.y"
                                       { (yyval.node) = ast_unary("UpdateExpression", "postfix --", (yyvsp[-1].node)); }
#line 3033 "parser.c"
    break;

  case 159: /* LeftHandSideExpression: NewExpression  */
#line 487 "parser.y"
                  { (yyval.node) = (yyvsp[0].node); }
#line 3039 "parser.c"
    break;

  case 160: /* LeftHandSideExpression: CallExpression  */
#line 488 "parser.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 3045 "parser.c"
    break;

  case 161: /* LeftHandSideExpression: OptionalExpression  */
#line 489 "parser.y"
                         { (yyval.node) = (yyvsp[0].node); }
#line 3051 "parser.c"
    break;

  case 162: /* NewExpression: MemberExpression  */
#line 494 "parser.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 3057 "parser.c"
    break;

  case 163: /* NewExpression: NEW NewExpression  */
#line 495 "parser.y"
                        { (yyval.node) = ast_wrap("NewExpression", "", (yyvsp[0].node)); }
#line 3063 "parser.c"
    break;

  case 164: /* MemberExpression: PrimaryExpression  */
#line 500 "parser.y"
                      { (yyval.node) = (yyvsp[0].node); }
#line 3069 "parser.c"
    break;

  case 165: /* MemberExpression: MemberExpression DOT IDENTIFIER  */
#line 501 "parser.y"
                                      { (yyval.node) = ast_new("MemberExpression", "."); ast_add((yyval.node), ast_wrap("Object", "", (yyvsp[-2].node))); ast_add((yyval.node), ast_leaf("Identifier", (yyvsp[0].string))); }
#line 3075 "parser.c"
    break;

  case 166: /* MemberExpression: MemberExpression LBRACKET Expression RBRACKET  */
#line 502 "parser.y"
                                                    { (yyval.node) = ast_new("MemberExpression", "computed"); ast_add((yyval.node), ast_wrap("Object", "", (yyvsp[-3].node))); ast_add((yyval.node), ast_wrap("Property", "", (yyvsp[-1].node))); }
#line 3081 "parser.c"
    break;

  case 167: /* MemberExpression: SUPER DOT IDENTIFIER  */
#line 503 "parser.y"
                           { (yyval.node) = ast_new("MemberExpression", "."); ast_add((yyval.node), ast_leaf("Super", "super")); ast_add((yyval.node), ast_leaf("Identifier", (yyvsp[0].string))); }
#line 3087 "parser.c"
    break;

  case 168: /* MemberExpression: SUPER LBRACKET Expression RBRACKET  */
#line 504 "parser.y"
                                         { (yyval.node) = ast_new("MemberExpression", "computed"); ast_add((yyval.node), ast_leaf("Super", "super")); ast_add((yyval.node), ast_wrap("Property", "", (yyvsp[-1].node))); }
#line 3093 "parser.c"
    break;

  case 169: /* MemberExpression: NEW MemberExpression Arguments  */
#line 505 "parser.y"
                                     { (yyval.node) = ast_new("NewExpression", ""); ast_add((yyval.node), ast_wrap("Callee", "", (yyvsp[-1].node))); ast_add((yyval.node), (yyvsp[0].node)); }
#line 3099 "parser.c"
    break;

  case 170: /* OptionalExpression: MemberExpression OPTIONAL_CHAINING IDENTIFIER  */
#line 510 "parser.y"
                                                  { (yyval.node) = ast_new("OptionalMemberExpression", "?."); ast_add((yyval.node), (yyvsp[-2].node)); ast_add((yyval.node), ast_leaf("Identifier", (yyvsp[0].string))); }
#line 3105 "parser.c"
    break;

  case 171: /* OptionalExpression: CallExpression OPTIONAL_CHAINING IDENTIFIER  */
#line 511 "parser.y"
                                                  { (yyval.node) = ast_new("OptionalMemberExpression", "?."); ast_add((yyval.node), (yyvsp[-2].node)); ast_add((yyval.node), ast_leaf("Identifier", (yyvsp[0].string))); }
#line 3111 "parser.c"
    break;

  case 172: /* OptionalExpression: OptionalExpression OPTIONAL_CHAINING IDENTIFIER  */
#line 512 "parser.y"
                                                      { (yyval.node) = ast_new("OptionalMemberExpression", "?."); ast_add((yyval.node), (yyvsp[-2].node)); ast_add((yyval.node), ast_leaf("Identifier", (yyvsp[0].string))); }
#line 3117 "parser.c"
    break;

  case 173: /* CallExpression: MemberExpression Arguments  */
#line 517 "parser.y"
                               { (yyval.node) = ast_new("CallExpression", ""); ast_add((yyval.node), ast_wrap("Callee", "", (yyvsp[-1].node))); ast_add((yyval.node), (yyvsp[0].node)); }
#line 3123 "parser.c"
    break;

  case 174: /* CallExpression: CallExpression Arguments  */
#line 518 "parser.y"
                               { (yyval.node) = ast_new("CallExpression", ""); ast_add((yyval.node), ast_wrap("Callee", "", (yyvsp[-1].node))); ast_add((yyval.node), (yyvsp[0].node)); }
#line 3129 "parser.c"
    break;

  case 175: /* CallExpression: CallExpression LBRACKET Expression RBRACKET  */
#line 519 "parser.y"
                                                  { (yyval.node) = ast_new("MemberExpression", "computed"); ast_add((yyval.node), ast_wrap("Object", "", (yyvsp[-3].node))); ast_add((yyval.node), ast_wrap("Property", "", (yyvsp[-1].node))); }
#line 3135 "parser.c"
    break;

  case 176: /* CallExpression: CallExpression DOT IDENTIFIER  */
#line 520 "parser.y"
                                    { (yyval.node) = ast_new("MemberExpression", "."); ast_add((yyval.node), ast_wrap("Object", "", (yyvsp[-2].node))); ast_add((yyval.node), ast_leaf("Identifier", (yyvsp[0].string))); }
#line 3141 "parser.c"
    break;

  case 177: /* CallExpression: SUPER Arguments  */
#line 521 "parser.y"
                      { (yyval.node) = ast_new("CallExpression", "super"); ast_add((yyval.node), (yyvsp[0].node)); }
#line 3147 "parser.c"
    break;

  case 178: /* Arguments: LPAREN RPAREN  */
#line 525 "parser.y"
                  { (yyval.node) = ast_new("Arguments", ""); }
#line 3153 "parser.c"
    break;

  case 179: /* Arguments: LPAREN ArgumentList RPAREN  */
#line 526 "parser.y"
                                 { (yyval.node) = (yyvsp[-1].node); }
#line 3159 "parser.c"
    break;

  case 180: /* ArgumentList: AssignmentExpression  */
#line 530 "parser.y"
                         { (yyval.node) = ast_list("Arguments", (yyvsp[0].node)); }
#line 3165 "parser.c"
    break;

  case 181: /* ArgumentList: SPREAD AssignmentExpression  */
#line 531 "parser.y"
                                  { (yyval.node) = ast_list("Arguments", ast_wrap("SpreadElement", "", (yyvsp[0].node))); }
#line 3171 "parser.c"
    break;

  case 182: /* ArgumentList: ArgumentList COMMA AssignmentExpression  */
#line 532 "parser.y"
                                              { (yyval.node) = (yyvsp[-2].node); ast_add((yyval.node), (yyvsp[0].node)); }
#line 3177 "parser.c"
    break;

  case 183: /* ArgumentList: ArgumentList COMMA SPREAD AssignmentExpression  */
#line 533 "parser.y"
                                                     { (yyval.node) = (yyvsp[-3].node); ast_add((yyval.node), ast_wrap("SpreadElement", "", (yyvsp[0].node))); }
#line 3183 "parser.c"
    break;

  case 184: /* PrimaryExpression: THIS  */
#line 538 "parser.y"
         { (yyval.node) = ast_leaf("ThisExpression", "this"); }
#line 3189 "parser.c"
    break;

  case 185: /* PrimaryExpression: IDENTIFIER  */
#line 539 "parser.y"
                 { (yyval.node) = ast_leaf("Identifier", (yyvsp[0].string)); }
#line 3195 "parser.c"
    break;

  case 186: /* PrimaryExpression: Literal  */
#line 540 "parser.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 3201 "parser.c"
    break;

  case 187: /* PrimaryExpression: ArrayLiteral  */
#line 541 "parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 3207 "parser.c"
    break;

  case 188: /* PrimaryExpression: ObjectLiteral  */
#line 542 "parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 3213 "parser.c"
    break;

  case 189: /* PrimaryExpression: FunctionExpression  */
#line 543 "parser.y"
                         { (yyval.node) = (yyvsp[0].node); }
#line 3219 "parser.c"
    break;

  case 190: /* PrimaryExpression: ClassExpression  */
#line 544 "parser.y"
                      { (yyval.node) = (yyvsp[0].node); }
#line 3225 "parser.c"
    break;

  case 191: /* PrimaryExpression: LPAREN Expression RPAREN  */
#line 545 "parser.y"
                               { (yyval.node) = (yyvsp[-1].node); }
#line 3231 "parser.c"
    break;

  case 192: /* Literal: NULL_LITERAL  */
#line 550 "parser.y"
                 { (yyval.node) = ast_leaf("Literal", "null"); }
#line 3237 "parser.c"
    break;

  case 193: /* Literal: TRUE  */
#line 551 "parser.y"
           { (yyval.node) = ast_leaf("Literal", "true"); }
#line 3243 "parser.c"
    break;

  case 194: /* Literal: FALSE  */
#line 552 "parser.y"
            { (yyval.node) = ast_leaf("Literal", "false"); }
#line 3249 "parser.c"
    break;

  case 195: /* Literal: NUMBER  */
#line 553 "parser.y"
             { (yyval.node) = number_literal((yyvsp[0].number)); }
#line 3255 "parser.c"
    break;

  case 196: /* Literal: STRING  */
#line 554 "parser.y"
             { (yyval.node) = ast_leaf("Literal", (yyvsp[0].string)); }
#line 3261 "parser.c"
    break;

  case 197: /* ArrayLiteral: LBRACKET ArrayElementsOpt RBRACKET  */
#line 559 "parser.y"
                                       { (yyval.node) = ast_wrap("ArrayExpression", "", (yyvsp[-1].node)); }
#line 3267 "parser.c"
    break;

  case 198: /* ArrayElementsOpt: %empty  */
#line 563 "parser.y"
                { (yyval.node) = ast_new("Elements", ""); }
#line 3273 "parser.c"
    break;

  case 199: /* ArrayElementsOpt: ElementList  */
#line 564 "parser.y"
                  { (yyval.node) = (yyvsp[0].node); }
#line 3279 "parser.c"
    break;

  case 200: /* ArrayElementsOpt: ElementList COMMA  */
#line 565 "parser.y"
                        { (yyval.node) = (yyvsp[-1].node); }
#line 3285 "parser.c"
    break;

  case 201: /* ElementList: ElisionOpt AssignmentExpression  */
#line 569 "parser.y"
                                    { (yyval.node) = ast_list("Elements", (yyvsp[0].node)); }
#line 3291 "parser.c"
    break;

  case 202: /* ElementList: SPREAD AssignmentExpression  */
#line 570 "parser.y"
                                  { (yyval.node) = ast_list("Elements", ast_wrap("SpreadElement", "", (yyvsp[0].node))); }
#line 3297 "parser.c"
    break;

  case 203: /* ElementList: ElementList COMMA ElisionOpt AssignmentExpression  */
#line 571 "parser.y"
                                                        { (yyval.node) = (yyvsp[-3].node); ast_add((yyval.node), (yyvsp[0].node)); }
#line 3303 "parser.c"
    break;

  case 204: /* ElementList: ElementList COMMA SPREAD AssignmentExpression  */
#line 572 "parser.y"
                                                    { (yyval.node) = (yyvsp[-3].node); ast_add((yyval.node), ast_wrap("SpreadElement", "", (yyvsp[0].node))); }
#line 3309 "parser.c"
    break;

  case 205: /* ElisionOpt: %empty  */
#line 576 "parser.y"
                { (yyval.node) = ast_new("Elision", ""); }
#line 3315 "parser.c"
    break;

  case 206: /* ElisionOpt: Elision  */
#line 577 "parser.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 3321 "parser.c"
    break;

  case 207: /* Elision: COMMA  */
#line 581 "parser.y"
          { (yyval.node) = ast_new("Elision", ","); }
#line 3327 "parser.c"
    break;

  case 208: /* Elision: Elision COMMA  */
#line 582 "parser.y"
                    { (yyval.node) = (yyvsp[-1].node); }
#line 3333 "parser.c"
    break;

  case 209: /* ObjectLiteral: LBRACE PropertyDefinitionsOpt RBRACE  */
#line 587 "parser.y"
                                         { (yyval.node) = ast_wrap("ObjectExpression", "", (yyvsp[-1].node)); }
#line 3339 "parser.c"
    break;

  case 210: /* PropertyDefinitionsOpt: %empty  */
#line 591 "parser.y"
                { (yyval.node) = ast_new("Properties", ""); }
#line 3345 "parser.c"
    break;

  case 211: /* PropertyDefinitionsOpt: SemicolonList  */
#line 592 "parser.y"
                    { (yyval.node) = ast_new("Properties", ""); }
#line 3351 "parser.c"
    break;

  case 212: /* PropertyDefinitionsOpt: PropertyDefinitionList SemicolonListOpt  */
#line 593 "parser.y"
                                              { (yyval.node) = (yyvsp[-1].node); }
#line 3357 "parser.c"
    break;

  case 213: /* PropertyDefinitionsOpt: PropertyDefinitionList COMMA SemicolonListOpt  */
#line 594 "parser.y"
                                                    { (yyval.node) = (yyvsp[-2].node); }
#line 3363 "parser.c"
    break;

  case 214: /* PropertyDefinitionList: PropertyDefinition  */
#line 598 "parser.y"
                       { (yyval.node) = ast_list("Properties", (yyvsp[0].node)); }
#line 3369 "parser.c"
    break;

  case 215: /* PropertyDefinitionList: PropertyDefinitionList PropertySeparator PropertyDefinition  */
#line 599 "parser.y"
                                                                  { (yyval.node) = (yyvsp[-2].node); ast_add((yyval.node), (yyvsp[0].node)); }
#line 3375 "parser.c"
    break;

  case 216: /* PropertySeparator: COMMA SemicolonListOpt  */
#line 603 "parser.y"
                           { (yyval.node) = ast_new("PropertySeparator", ","); }
#line 3381 "parser.c"
    break;

  case 217: /* PropertySeparator: SemicolonList  */
#line 604 "parser.y"
                    { (yyval.node) = ast_new("PropertySeparator", ";"); }
#line 3387 "parser.c"
    break;

  case 218: /* SemicolonListOpt: %empty  */
#line 608 "parser.y"
                { (yyval.node) = ast_new("SemicolonList", ""); }
#line 3393 "parser.c"
    break;

  case 219: /* SemicolonListOpt: SemicolonList  */
#line 609 "parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 3399 "parser.c"
    break;

  case 220: /* SemicolonList: SEMICOLON  */
#line 613 "parser.y"
              { (yyval.node) = ast_new("SemicolonList", ";"); }
#line 3405 "parser.c"
    break;

  case 221: /* SemicolonList: SemicolonList SEMICOLON  */
#line 614 "parser.y"
                              { (yyval.node) = (yyvsp[-1].node); }
#line 3411 "parser.c"
    break;

  case 222: /* PropertyDefinition: IDENTIFIER  */
#line 618 "parser.y"
               { (yyval.node) = ast_new("Property", "shorthand"); ast_add((yyval.node), ast_leaf("Identifier", (yyvsp[0].string))); }
#line 3417 "parser.c"
    break;

  case 223: /* PropertyDefinition: PropertyName COLON AssignmentExpression  */
#line 619 "parser.y"
                                              { (yyval.node) = ast_new("Property", "init"); ast_add((yyval.node), ast_wrap("Key", "", (yyvsp[-2].node))); ast_add((yyval.node), ast_wrap("Value", "", (yyvsp[0].node))); }
#line 3423 "parser.c"
    break;

  case 224: /* PropertyDefinition: MethodDefinition  */
#line 620 "parser.y"
                       { (yyval.node) = (yyvsp[0].node); }
#line 3429 "parser.c"
    break;

  case 225: /* PropertyDefinition: SPREAD AssignmentExpression  */
#line 621 "parser.y"
                                  { (yyval.node) = ast_wrap("SpreadElement", "", (yyvsp[0].node)); }
#line 3435 "parser.c"
    break;

  case 226: /* PropertyName: IDENTIFIER  */
#line 625 "parser.y"
               { (yyval.node) = ast_leaf("Identifier", (yyvsp[0].string)); }
#line 3441 "parser.c"
    break;

  case 227: /* PropertyName: STRING  */
#line 626 "parser.y"
             { (yyval.node) = ast_leaf("Literal", (yyvsp[0].string)); }
#line 3447 "parser.c"
    break;

  case 228: /* PropertyName: NUMBER  */
#line 627 "parser.y"
             { (yyval.node) = number_literal((yyvsp[0].number)); }
#line 3453 "parser.c"
    break;

  case 229: /* FunctionExpression: FUNCTION IdentifierOpt LPAREN FormalParametersOpt RPAREN BlockStatement  */
#line 632 "parser.y"
                                                                            { (yyval.node) = ast_new("FunctionExpression", ""); ast_add((yyval.node), (yyvsp[-4].node)); ast_add((yyval.node), (yyvsp[-2].node)); ast_add((yyval.node), (yyvsp[0].node)); }
#line 3459 "parser.c"
    break;

  case 230: /* IdentifierOpt: %empty  */
#line 636 "parser.y"
                { (yyval.node) = ast_new("Identifier", ""); }
#line 3465 "parser.c"
    break;

  case 231: /* IdentifierOpt: IDENTIFIER  */
#line 637 "parser.y"
                 { (yyval.node) = ast_leaf("Identifier", (yyvsp[0].string)); }
#line 3471 "parser.c"
    break;

  case 232: /* ClassExpression: CLASS IdentifierOpt ClassTail  */
#line 644 "parser.y"
                                  { (yyval.node) = ast_new("ClassExpression", ""); ast_add((yyval.node), (yyvsp[-1].node)); ast_add((yyval.node), (yyvsp[0].node)); }
#line 3477 "parser.c"
    break;

  case 233: /* YieldStatement: YIELD ExpressionOpt SEMICOLON  */
#line 649 "parser.y"
                                  { (yyval.node) = ast_wrap("YieldStatement", "", (yyvsp[-1].node)); }
#line 3483 "parser.c"
    break;


#line 3487 "parser.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 652 "parser.y"


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


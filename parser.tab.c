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

// 错误处理
void yyerror(const char *s);
int yylex(void);

// 全局变量
extern unsigned char *lexer_input;
extern int yylineno;

// 语法检查结果
int syntax_valid = 1;
int error_count = 0;


#line 92 "parser.tab.c"

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


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    NUMBER = 258,                  /* NUMBER  */
    STRING = 259,                  /* STRING  */
    IDENTIFIER = 260,              /* IDENTIFIER  */
    IF = 261,                      /* IF  */
    ELSE = 262,                    /* ELSE  */
    FOR = 263,                     /* FOR  */
    WHILE = 264,                   /* WHILE  */
    DO = 265,                      /* DO  */
    SWITCH = 266,                  /* SWITCH  */
    CASE = 267,                    /* CASE  */
    DEFAULT = 268,                 /* DEFAULT  */
    BREAK = 269,                   /* BREAK  */
    CONTINUE = 270,                /* CONTINUE  */
    RETURN = 271,                  /* RETURN  */
    VAR = 272,                     /* VAR  */
    LET = 273,                     /* LET  */
    CONST = 274,                   /* CONST  */
    FUNCTION = 275,                /* FUNCTION  */
    CLASS = 276,                   /* CLASS  */
    THIS = 277,                    /* THIS  */
    SUPER = 278,                   /* SUPER  */
    NEW = 279,                     /* NEW  */
    TYPEOF = 280,                  /* TYPEOF  */
    DELETE = 281,                  /* DELETE  */
    INSTANCEOF = 282,              /* INSTANCEOF  */
    IN = 283,                      /* IN  */
    TRUE = 284,                    /* TRUE  */
    FALSE = 285,                   /* FALSE  */
    NULL_LITERAL = 286,            /* NULL_LITERAL  */
    TRY = 287,                     /* TRY  */
    CATCH = 288,                   /* CATCH  */
    FINALLY = 289,                 /* FINALLY  */
    THROW = 290,                   /* THROW  */
    WITH = 291,                    /* WITH  */
    DEBUGGER = 292,                /* DEBUGGER  */
    IMPORT = 293,                  /* IMPORT  */
    EXPORT = 294,                  /* EXPORT  */
    YIELD = 295,                   /* YIELD  */
    INTERFACE = 296,               /* INTERFACE  */
    EXTENDS = 297,                 /* EXTENDS  */
    LPAREN = 298,                  /* LPAREN  */
    RPAREN = 299,                  /* RPAREN  */
    LBRACE = 300,                  /* LBRACE  */
    RBRACE = 301,                  /* RBRACE  */
    LBRACKET = 302,                /* LBRACKET  */
    RBRACKET = 303,                /* RBRACKET  */
    SEMICOLON = 304,               /* SEMICOLON  */
    COMMA = 305,                   /* COMMA  */
    DOT = 306,                     /* DOT  */
    COLON = 307,                   /* COLON  */
    QUESTION = 308,                /* QUESTION  */
    PLUS = 309,                    /* PLUS  */
    MINUS = 310,                   /* MINUS  */
    MULTIPLY = 311,                /* MULTIPLY  */
    DIVIDE = 312,                  /* DIVIDE  */
    MODULO = 313,                  /* MODULO  */
    ASSIGN = 314,                  /* ASSIGN  */
    PLUS_ASSIGN = 315,             /* PLUS_ASSIGN  */
    MINUS_ASSIGN = 316,            /* MINUS_ASSIGN  */
    MULTIPLY_ASSIGN = 317,         /* MULTIPLY_ASSIGN  */
    DIVIDE_ASSIGN = 318,           /* DIVIDE_ASSIGN  */
    MODULO_ASSIGN = 319,           /* MODULO_ASSIGN  */
    EQUAL = 320,                   /* EQUAL  */
    NOT_EQUAL = 321,               /* NOT_EQUAL  */
    STRICT_EQUAL = 322,            /* STRICT_EQUAL  */
    STRICT_NOT_EQUAL = 323,        /* STRICT_NOT_EQUAL  */
    LESS = 324,                    /* LESS  */
    GREATER = 325,                 /* GREATER  */
    LESS_EQUAL = 326,              /* LESS_EQUAL  */
    GREATER_EQUAL = 327,           /* GREATER_EQUAL  */
    LOGICAL_AND = 328,             /* LOGICAL_AND  */
    LOGICAL_OR = 329,              /* LOGICAL_OR  */
    NOT = 330,                     /* NOT  */
    BITWISE_AND = 331,             /* BITWISE_AND  */
    BITWISE_OR = 332,              /* BITWISE_OR  */
    BITWISE_XOR = 333,             /* BITWISE_XOR  */
    BITWISE_NOT = 334,             /* BITWISE_NOT  */
    LEFT_SHIFT = 335,              /* LEFT_SHIFT  */
    RIGHT_SHIFT = 336,             /* RIGHT_SHIFT  */
    UNSIGNED_RIGHT_SHIFT = 337,    /* UNSIGNED_RIGHT_SHIFT  */
    LEFT_SHIFT_ASSIGN = 338,       /* LEFT_SHIFT_ASSIGN  */
    RIGHT_SHIFT_ASSIGN = 339,      /* RIGHT_SHIFT_ASSIGN  */
    UNSIGNED_RIGHT_SHIFT_ASSIGN = 340, /* UNSIGNED_RIGHT_SHIFT_ASSIGN  */
    AND_ASSIGN = 341,              /* AND_ASSIGN  */
    OR_ASSIGN = 342,               /* OR_ASSIGN  */
    XOR_ASSIGN = 343,              /* XOR_ASSIGN  */
    INCREMENT = 344,               /* INCREMENT  */
    DECREMENT = 345,               /* DECREMENT  */
    EXPONENT = 346,                /* EXPONENT  */
    EXPONENT_ASSIGN = 347,         /* EXPONENT_ASSIGN  */
    ARROW = 348,                   /* ARROW  */
    SPREAD = 349,                  /* SPREAD  */
    NULLISH_COALESCING = 350,      /* NULLISH_COALESCING  */
    OPTIONAL_CHAINING = 351,       /* OPTIONAL_CHAINING  */
    ERROR_TOKEN = 352              /* ERROR_TOKEN  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 22 "parser.y"

    double number;
    char *string;
    void *node;

#line 242 "parser.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);



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
  YYSYMBOL_IF = 6,                         /* IF  */
  YYSYMBOL_ELSE = 7,                       /* ELSE  */
  YYSYMBOL_FOR = 8,                        /* FOR  */
  YYSYMBOL_WHILE = 9,                      /* WHILE  */
  YYSYMBOL_DO = 10,                        /* DO  */
  YYSYMBOL_SWITCH = 11,                    /* SWITCH  */
  YYSYMBOL_CASE = 12,                      /* CASE  */
  YYSYMBOL_DEFAULT = 13,                   /* DEFAULT  */
  YYSYMBOL_BREAK = 14,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 15,                  /* CONTINUE  */
  YYSYMBOL_RETURN = 16,                    /* RETURN  */
  YYSYMBOL_VAR = 17,                       /* VAR  */
  YYSYMBOL_LET = 18,                       /* LET  */
  YYSYMBOL_CONST = 19,                     /* CONST  */
  YYSYMBOL_FUNCTION = 20,                  /* FUNCTION  */
  YYSYMBOL_CLASS = 21,                     /* CLASS  */
  YYSYMBOL_THIS = 22,                      /* THIS  */
  YYSYMBOL_SUPER = 23,                     /* SUPER  */
  YYSYMBOL_NEW = 24,                       /* NEW  */
  YYSYMBOL_TYPEOF = 25,                    /* TYPEOF  */
  YYSYMBOL_DELETE = 26,                    /* DELETE  */
  YYSYMBOL_INSTANCEOF = 27,                /* INSTANCEOF  */
  YYSYMBOL_IN = 28,                        /* IN  */
  YYSYMBOL_TRUE = 29,                      /* TRUE  */
  YYSYMBOL_FALSE = 30,                     /* FALSE  */
  YYSYMBOL_NULL_LITERAL = 31,              /* NULL_LITERAL  */
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
  YYSYMBOL_ARROW = 93,                     /* ARROW  */
  YYSYMBOL_SPREAD = 94,                    /* SPREAD  */
  YYSYMBOL_NULLISH_COALESCING = 95,        /* NULLISH_COALESCING  */
  YYSYMBOL_OPTIONAL_CHAINING = 96,         /* OPTIONAL_CHAINING  */
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
  YYSYMBOL_FunctionBody = 138,             /* FunctionBody  */
  YYSYMBOL_Expression = 139,               /* Expression  */
  YYSYMBOL_AssignmentExpression = 140,     /* AssignmentExpression  */
  YYSYMBOL_ConditionalExpression = 141,    /* ConditionalExpression  */
  YYSYMBOL_LogicalORExpression = 142,      /* LogicalORExpression  */
  YYSYMBOL_LogicalANDExpression = 143,     /* LogicalANDExpression  */
  YYSYMBOL_BitwiseORExpression = 144,      /* BitwiseORExpression  */
  YYSYMBOL_BitwiseXORExpression = 145,     /* BitwiseXORExpression  */
  YYSYMBOL_BitwiseANDExpression = 146,     /* BitwiseANDExpression  */
  YYSYMBOL_EqualityExpression = 147,       /* EqualityExpression  */
  YYSYMBOL_RelationalExpression = 148,     /* RelationalExpression  */
  YYSYMBOL_ShiftExpression = 149,          /* ShiftExpression  */
  YYSYMBOL_AdditiveExpression = 150,       /* AdditiveExpression  */
  YYSYMBOL_MultiplicativeExpression = 151, /* MultiplicativeExpression  */
  YYSYMBOL_UnaryExpression = 152,          /* UnaryExpression  */
  YYSYMBOL_PostfixExpression = 153,        /* PostfixExpression  */
  YYSYMBOL_LeftHandSideExpression = 154,   /* LeftHandSideExpression  */
  YYSYMBOL_NewExpression = 155,            /* NewExpression  */
  YYSYMBOL_MemberExpression = 156,         /* MemberExpression  */
  YYSYMBOL_OptionalExpression = 157,       /* OptionalExpression  */
  YYSYMBOL_CallExpression = 158,           /* CallExpression  */
  YYSYMBOL_Arguments = 159,                /* Arguments  */
  YYSYMBOL_ArgumentList = 160,             /* ArgumentList  */
  YYSYMBOL_PrimaryExpression = 161,        /* PrimaryExpression  */
  YYSYMBOL_Literal = 162,                  /* Literal  */
  YYSYMBOL_ArrayLiteral = 163,             /* ArrayLiteral  */
  YYSYMBOL_ElementList = 164,              /* ElementList  */
  YYSYMBOL_ElisionOpt = 165,               /* ElisionOpt  */
  YYSYMBOL_Elision = 166,                  /* Elision  */
  YYSYMBOL_ObjectLiteral = 167,            /* ObjectLiteral  */
  YYSYMBOL_PropertyDefinitionList = 168,   /* PropertyDefinitionList  */
  YYSYMBOL_PropertyDefinition = 169,       /* PropertyDefinition  */
  YYSYMBOL_PropertyName = 170,             /* PropertyName  */
  YYSYMBOL_FunctionExpression = 171,       /* FunctionExpression  */
  YYSYMBOL_IdentifierOpt = 172,            /* IdentifierOpt  */
  YYSYMBOL_ClassExpression = 173,          /* ClassExpression  */
  YYSYMBOL_GeneratorFunction = 174,        /* GeneratorFunction  */
  YYSYMBOL_ArrowFunction = 175,            /* ArrowFunction  */
  YYSYMBOL_ArrowParameters = 176,          /* ArrowParameters  */
  YYSYMBOL_YieldExpression = 177           /* YieldExpression  */
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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1153

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  98
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  80
/* YYNRULES -- Number of rules.  */
#define YYNRULES  231
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  455

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
       0,    81,    81,    85,    87,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   113,   114,   119,   123,   124,   125,   126,   130,
     131,   136,   141,   146,   147,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   165,   168,   170,   175,   176,
     181,   182,   187,   192,   197,   202,   206,   207,   210,   212,
     216,   217,   221,   225,   228,   230,   235,   240,   241,   242,
     246,   250,   255,   260,   263,   265,   269,   270,   275,   279,
     280,   283,   285,   289,   290,   294,   295,   299,   300,   304,
     305,   310,   311,   316,   317,   318,   319,   320,   321,   322,
     323,   324,   325,   326,   327,   328,   329,   330,   331,   336,
     337,   342,   343,   344,   349,   350,   355,   356,   361,   362,
     367,   368,   373,   374,   375,   376,   377,   382,   383,   384,
     385,   386,   387,   388,   393,   394,   395,   396,   401,   402,
     403,   408,   409,   410,   411,   416,   417,   418,   419,   420,
     421,   422,   423,   424,   425,   430,   431,   432,   437,   438,
     439,   444,   445,   450,   451,   452,   453,   454,   455,   460,
     461,   462,   467,   468,   469,   470,   471,   475,   476,   480,
     481,   482,   483,   488,   489,   490,   491,   492,   493,   494,
     495,   496,   501,   502,   503,   504,   505,   510,   511,   512,
     516,   517,   518,   519,   522,   524,   528,   529,   534,   535,
     536,   540,   541,   545,   546,   547,   548,   552,   553,   554,
     559,   562,   564,   571,   576,   581,   582,   586,   587,   592,
     593,   594
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "NUMBER", "STRING",
  "IDENTIFIER", "IF", "ELSE", "FOR", "WHILE", "DO", "SWITCH", "CASE",
  "DEFAULT", "BREAK", "CONTINUE", "RETURN", "VAR", "LET", "CONST",
  "FUNCTION", "CLASS", "THIS", "SUPER", "NEW", "TYPEOF", "DELETE",
  "INSTANCEOF", "IN", "TRUE", "FALSE", "NULL_LITERAL", "TRY", "CATCH",
  "FINALLY", "THROW", "WITH", "DEBUGGER", "IMPORT", "EXPORT", "YIELD",
  "INTERFACE", "EXTENDS", "LPAREN", "RPAREN", "LBRACE", "RBRACE",
  "LBRACKET", "RBRACKET", "SEMICOLON", "COMMA", "DOT", "COLON", "QUESTION",
  "PLUS", "MINUS", "MULTIPLY", "DIVIDE", "MODULO", "ASSIGN", "PLUS_ASSIGN",
  "MINUS_ASSIGN", "MULTIPLY_ASSIGN", "DIVIDE_ASSIGN", "MODULO_ASSIGN",
  "EQUAL", "NOT_EQUAL", "STRICT_EQUAL", "STRICT_NOT_EQUAL", "LESS",
  "GREATER", "LESS_EQUAL", "GREATER_EQUAL", "LOGICAL_AND", "LOGICAL_OR",
  "NOT", "BITWISE_AND", "BITWISE_OR", "BITWISE_XOR", "BITWISE_NOT",
  "LEFT_SHIFT", "RIGHT_SHIFT", "UNSIGNED_RIGHT_SHIFT", "LEFT_SHIFT_ASSIGN",
  "RIGHT_SHIFT_ASSIGN", "UNSIGNED_RIGHT_SHIFT_ASSIGN", "AND_ASSIGN",
  "OR_ASSIGN", "XOR_ASSIGN", "INCREMENT", "DECREMENT", "EXPONENT",
  "EXPONENT_ASSIGN", "ARROW", "SPREAD", "NULLISH_COALESCING",
  "OPTIONAL_CHAINING", "ERROR_TOKEN", "$accept", "Program",
  "StatementList", "Statement", "BlockStatement", "VariableStatement",
  "VariableDeclarationList", "VariableDeclaration", "EmptyStatement",
  "ExpressionStatement", "IfStatement", "IterationStatement", "ForBinding",
  "ExpressionOpt", "ContinueStatement", "BreakStatement",
  "ReturnStatement", "WithStatement", "LabelledStatement",
  "SwitchStatement", "CaseBlock", "CaseClausesOpt", "CaseClauses",
  "CaseClause", "DefaultClause", "StatementListOpt", "ThrowStatement",
  "TryStatement", "Catch", "Finally", "DebuggerStatement",
  "FunctionDeclaration", "FormalParametersOpt", "FormalParameters",
  "ClassDeclaration", "ClassTail", "ClassBodyOpt", "ClassBody",
  "ClassElement", "MethodDefinition", "FunctionBody", "Expression",
  "AssignmentExpression", "ConditionalExpression", "LogicalORExpression",
  "LogicalANDExpression", "BitwiseORExpression", "BitwiseXORExpression",
  "BitwiseANDExpression", "EqualityExpression", "RelationalExpression",
  "ShiftExpression", "AdditiveExpression", "MultiplicativeExpression",
  "UnaryExpression", "PostfixExpression", "LeftHandSideExpression",
  "NewExpression", "MemberExpression", "OptionalExpression",
  "CallExpression", "Arguments", "ArgumentList", "PrimaryExpression",
  "Literal", "ArrayLiteral", "ElementList", "ElisionOpt", "Elision",
  "ObjectLiteral", "PropertyDefinitionList", "PropertyDefinition",
  "PropertyName", "FunctionExpression", "IdentifierOpt", "ClassExpression",
  "GeneratorFunction", "ArrowFunction", "ArrowParameters",
  "YieldExpression", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-237)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-228)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -237,     4,   647,  -237,  -237,  -237,    50,    -4,    54,    83,
     647,    88,    11,    18,   797,    17,    17,    17,     9,   129,
    -237,    86,   495,  1016,  1016,  -237,  -237,  -237,    99,   797,
     134,    90,   217,   870,    15,     1,  -237,  1016,  1016,  1016,
    1016,  1016,  1016,  1016,  -237,  -237,  -237,    -2,  -237,  -237,
    -237,  -237,  -237,  -237,  -237,  -237,  -237,  -237,  -237,  -237,
    -237,  -237,  -237,    22,  -237,  -237,    41,   176,    92,   141,
     152,   158,    77,   132,    28,   209,  -237,  -237,   697,  -237,
     -22,   159,    70,  -237,  -237,  -237,  -237,  -237,  -237,  -237,
    -237,   170,  -237,   647,   797,   724,   797,   284,   797,   248,
    -237,   251,  -237,   210,    10,   299,    65,   256,   259,   260,
    -237,  -237,  -237,   279,   299,   285,   -10,   -10,    33,   797,
     325,  -237,  -237,   -17,   797,  -237,   124,  -237,    84,  -237,
     287,   249,   195,   797,  -237,   797,  -237,    42,   291,   281,
     111,  -237,  -237,    98,  1057,   797,   558,  -237,   122,  -237,
     286,  -237,  -237,   797,   -37,   797,   289,  -237,  -237,  -237,
    -237,  -237,  -237,  -237,  -237,    17,  -237,   797,   797,  1016,
    1016,  1016,  1016,  1016,  1016,  1016,  1016,  1016,  1016,  1016,
    1016,  1016,  1016,  1016,  1016,  1016,  1016,  1016,  1016,  1016,
    1016,  1016,  1016,   797,   797,   797,   797,   797,   797,   797,
     797,   797,   797,   797,   797,  -237,  -237,   797,   797,   331,
     332,  -237,   335,   797,   336,   337,  -237,   943,  -237,   112,
     146,   146,   146,   295,   292,   126,   305,   147,  -237,  -237,
    -237,  -237,  -237,   797,   344,   315,   344,  1045,    26,  -237,
    -237,  -237,   797,  -237,   154,   110,  -237,  -237,  -237,   317,
      99,   334,  -237,  -237,   155,  -237,  -237,   366,  -237,   344,
     280,  -237,  -237,  -237,    96,   797,  -237,  -237,     2,  -237,
    -237,  -237,  -237,   320,   176,   176,    92,   141,   152,   158,
      77,    77,    77,    77,   132,   132,   132,   132,   132,   132,
      28,    28,    28,   209,   209,  -237,  -237,  -237,  -237,  -237,
    -237,  -237,  -237,  -237,  -237,  -237,  -237,  -237,  -237,  -237,
    -237,   208,  -237,  -237,  -237,   211,  -237,  -237,  -237,  -237,
     647,  -237,   235,   346,   237,   355,   239,   357,   797,   797,
     647,   797,   342,  -237,  -237,   347,   344,   348,   343,    73,
    -237,   349,    26,  -237,  -237,  -237,  -237,   466,  -237,   385,
    -237,  -237,   647,  -237,   352,   943,  -237,  -237,  -237,  -237,
     797,   797,   797,  -237,  -237,   391,   797,   797,   797,   797,
     797,   797,   350,   156,  -237,   157,   389,  -237,    99,   358,
      99,    26,  -237,  -237,   797,  -237,   359,  -237,    99,  -237,
    -237,   259,  -237,  -237,  -237,   647,   356,   165,   361,   166,
     368,   167,   797,   647,   369,   797,    72,   389,  -237,  -237,
      99,  -237,   360,  -237,    99,  -237,  -237,   797,   647,   797,
     647,   797,   647,   363,  -237,  -237,   225,   367,  -237,   389,
    -237,  -237,  -237,  -237,   364,  -237,   371,  -237,   376,  -237,
     647,  -237,  -237,   375,   647,   647,   647,  -237,   647,  -237,
    -237,  -237,  -237,  -237,  -237
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     2,     1,   195,   196,   184,     0,     0,     0,
       0,     0,     0,     0,    46,     0,     0,     0,   221,   221,
     183,     0,     0,     0,     0,   193,   194,   192,     0,     0,
       0,     0,   229,    74,     3,   204,    31,     0,     0,     0,
       0,     0,     0,     0,     4,     5,     6,     0,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,     0,    91,    93,   109,   111,   114,   116,
     118,   120,   122,   127,   134,   138,   141,   145,   155,   158,
     161,   160,   159,   163,   185,   186,   187,   188,   189,   190,
      95,     0,    94,     0,     0,    46,     0,     0,     0,     0,
      50,     0,    48,   184,   221,   221,     0,     0,    47,    29,
      25,    26,    27,     0,   221,     0,     0,     0,     0,     0,
       0,   176,   184,     0,     0,   162,   161,   147,   155,   146,
       3,     0,     0,     0,    72,     0,   230,   184,     0,    75,
       0,   219,   218,   213,    23,     0,     0,   215,     0,   211,
       0,   197,   206,     0,     0,     0,   205,   150,   151,   153,
     152,   148,   149,   154,    24,     0,    32,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   156,   157,     0,     0,     0,
       0,   172,     0,     0,     0,     0,   173,     0,    54,     0,
       0,     0,     0,     0,   155,     0,     0,     0,    51,    49,
     222,   208,    52,     0,    74,     0,    74,     0,    81,    78,
     223,   177,     0,   179,     0,     0,   166,   168,    23,     0,
       0,    67,    68,    66,     0,   231,   228,     0,   191,    74,
       0,   216,    22,   209,     0,     0,   201,   198,   204,   200,
     207,    28,    92,     0,   112,   113,   115,   117,   119,   121,
     123,   124,   125,   126,   132,   133,   128,   129,   130,   131,
     135,   136,   137,   139,   140,   142,   143,   144,    96,    97,
      98,    99,   100,   101,   106,   107,   108,   103,   104,   105,
     102,     0,   164,   169,   171,     0,   175,   170,   226,   225,
       0,    45,     0,     0,     0,     0,     0,     0,    46,     0,
       0,     0,     0,    30,    76,     0,    74,     0,     0,     0,
      86,     0,    82,    83,    85,   180,   178,     0,   167,     0,
      71,    69,     0,    77,     0,     0,   210,   212,   214,   199,
       0,     0,     0,   165,   174,    33,    46,     0,    46,     0,
      46,     0,     0,     0,    35,     0,    58,    55,     0,     0,
       0,    81,    79,    84,     0,   181,     0,    53,     0,    89,
      88,    90,   203,   202,   110,     0,     0,     0,     0,     0,
       0,     0,    46,     0,     0,     0,     0,    59,    60,    73,
       0,   220,     0,   182,     0,    87,    34,    46,     0,    46,
       0,    46,     0,     0,    41,    36,     0,     0,    56,    58,
      61,   224,    80,    70,     0,    42,     0,    43,     0,    44,
       0,     3,     3,     0,     0,     0,     0,    37,    65,    62,
      63,    57,    38,    39,    40
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -237,  -237,     0,    -9,   -21,  -237,    48,   -11,  -237,  -237,
    -237,  -237,    69,   -92,  -237,  -237,  -237,  -237,  -237,  -237,
    -237,   -25,  -237,    16,  -237,   -20,  -237,  -237,  -237,   173,
    -237,  -237,  -226,  -237,  -237,   308,    45,  -237,    85,  -236,
    -237,    -5,   -15,  -237,  -237,   125,   257,   258,   261,   255,
      76,    51,    94,   113,     3,  -237,   275,   410,   411,  -237,
    -237,    -1,  -237,  -237,  -237,  -237,  -237,   171,  -237,  -237,
    -237,   174,  -237,  -237,    -7,  -237,  -237,  -237,  -237,  -237
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,   146,    44,    45,    46,    47,   110,    48,    49,
      50,    51,   323,   107,    52,    53,    54,    55,    56,    57,
     377,   406,   407,   408,   429,   449,    58,    59,   251,   252,
      60,    61,   138,   139,    62,   239,   341,   342,   343,   147,
     390,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,   121,   244,    83,    84,    85,   154,   155,   156,    86,
     148,   149,   150,    87,   115,    88,    89,    90,    91,    92
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
       2,    97,   344,   223,     3,   111,   112,   131,   335,   108,
     337,   267,   117,   268,   113,   230,    99,   136,   141,   142,
     143,   118,   109,   101,   132,   208,   127,   129,   140,   209,
     119,   339,   237,   354,   120,   238,     4,     5,   103,    94,
     157,   158,   159,   160,   161,   162,   163,   164,   165,   151,
     359,   152,   152,   104,   105,    20,    21,    22,    23,    24,
     100,   144,    25,    26,    27,   114,   114,   102,   141,   142,
     143,   166,   167,    32,   210,   340,    33,   241,   106,   211,
      35,   216,   188,   189,   218,   427,   -76,    37,    38,   219,
     108,   225,   -76,   227,   168,   153,   360,    95,   117,   141,
     142,   143,    93,   243,   179,   180,   344,   235,    39,   145,
     379,   231,    40,   118,   245,   169,   259,   213,   428,   140,
     255,   214,    41,    42,    43,   247,    96,   242,   254,   118,
     261,    98,   260,   119,   116,  -227,   170,   120,   266,   134,
     269,   259,   356,  -227,   130,   344,   181,   182,   183,   184,
    -217,   321,   272,   273,   271,   258,   320,   260,   348,   145,
     167,   167,   167,    15,    16,    17,   215,   118,   263,   172,
     330,   208,   264,   205,   206,   209,   167,   133,   298,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   308,   309,
     145,   332,   310,   295,   296,   297,   318,   167,   346,   352,
     403,   404,   319,   311,   347,   167,   167,   167,   315,   418,
     420,   422,   185,   186,   187,   167,   167,   167,   333,   173,
       4,     5,   103,   175,   176,   177,   178,   345,   174,   350,
     284,   285,   286,   287,   288,   289,   372,   104,   105,    20,
      21,    22,    23,    24,   253,   167,    25,    26,    27,   171,
     358,   280,   281,   282,   283,   212,   363,    32,   167,   364,
      33,   167,   106,   217,    35,   190,   191,   192,   322,   324,
     326,    37,    38,   135,   396,   167,   398,   441,   400,   290,
     291,   292,   249,   250,   366,   165,   368,   165,   370,   165,
     325,   327,    39,   226,   274,   275,    40,   228,   128,   128,
     229,   293,   294,  -227,   230,   232,    41,    42,    43,   167,
     423,   365,   128,   128,   128,   128,   128,   128,   128,   233,
     329,   374,   234,   108,   373,   434,   375,   436,   236,   438,
     246,   257,   385,   248,   389,   256,   312,   313,   265,   270,
     314,   316,   317,   387,   328,   392,   393,   394,   331,   334,
     391,   193,   194,   195,   196,   197,   198,   409,   336,   411,
     349,   108,   397,   108,   399,   108,   401,   415,   250,   413,
     224,   353,   362,   355,   367,   199,   200,   201,   202,   203,
     204,   205,   206,   369,   207,   371,   416,   376,   381,   431,
     386,   378,   380,   433,   424,   382,   388,   108,   395,   402,
     426,   405,   410,   414,   443,   417,   432,   440,   444,   435,
     419,   437,   108,   439,   108,   445,   108,   421,   425,   442,
     446,   451,   450,   430,   351,   240,   412,   383,   276,   279,
     277,   447,   125,   126,   278,   452,   453,   454,   357,   361,
       0,   448,   448,     0,   128,   128,   128,   128,   128,   128,
     128,   128,   128,   128,   128,   128,   128,   128,   128,   128,
     128,   128,   128,   128,   128,   128,   128,   128,     0,     4,
       5,   103,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   104,   105,    20,    21,
      22,    23,    24,     0,     0,    25,    26,    27,     4,     5,
     122,     0,     0,     0,     0,     0,    32,     0,     0,    33,
       0,   106,   338,    35,     0,   104,   105,    20,   123,    22,
      37,    38,     0,     0,    25,    26,    27,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   124,     0,
     106,    39,    35,     0,     0,    40,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    41,    42,    43,     0,     0,
     384,     4,     5,     6,     7,     0,     8,     9,    10,    11,
       0,     0,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,     0,     0,    25,    26,    27,
      28,     0,     0,    29,    30,    31,     0,     0,    32,     0,
       0,    33,     0,    34,   262,    35,     0,    36,     0,     0,
       0,     0,    37,    38,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    39,     0,     0,     0,    40,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    41,    42,    43,
       4,     5,     6,     7,     0,     8,     9,    10,    11,     0,
       0,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,     0,     0,    25,    26,    27,    28,
       0,     0,    29,    30,    31,     0,     0,    32,     0,     0,
      33,     0,    34,     0,    35,     0,    36,     0,     0,     0,
       0,    37,    38,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    39,     0,     0,     0,    40,     4,     5,   103,
       0,     0,     0,     0,     0,     0,    41,    42,    43,     0,
       0,   220,   221,   222,   104,   105,    20,    21,    22,    23,
      24,     0,     0,    25,    26,    27,   193,   194,   195,   196,
     197,   198,     0,     0,    32,     0,     0,    33,     0,   106,
       0,    35,     0,     0,     0,     0,     0,     0,    37,    38,
     199,   200,   201,   202,   203,   204,   205,   206,     0,   207,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    39,
       4,     5,   103,    40,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    41,    42,    43,     0,   104,   105,    20,
      21,    22,    23,    24,     0,     0,    25,    26,    27,     0,
       0,     0,     0,     0,     0,     0,     0,    32,     0,     0,
      33,     0,   106,     0,    35,     0,     0,     0,     0,     0,
       0,    37,    38,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    39,     4,     5,   137,    40,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    41,    42,    43,     0,
     104,   105,    20,    21,    22,    23,    24,     0,     0,    25,
      26,    27,     0,     0,     0,     0,     0,     0,     0,     0,
      32,     0,     0,    33,     0,   106,     0,    35,     0,     0,
       0,     0,     0,     0,    37,    38,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    39,     4,     5,   103,    40,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    41,
      42,    43,     0,   104,   105,    20,    21,    22,    23,    24,
       0,     0,    25,    26,    27,     0,     0,     0,     0,     0,
       0,     0,     0,    32,     0,     0,    33,     0,    34,     0,
      35,     0,     0,     0,     0,     0,     0,    37,    38,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    39,     4,
       5,   122,    40,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    41,    42,    43,     0,   104,   105,    20,    21,
      22,    23,    24,     0,     0,    25,    26,    27,     4,     5,
     122,     0,     0,     0,     0,     0,     0,     0,     0,   124,
       0,   106,     0,    35,     0,   104,   105,    20,    21,    22,
      37,    38,     0,     0,    25,    26,    27,     0,     0,     0,
       0,     0,     0,     0,  -208,  -208,     0,     0,   124,     0,
     106,    39,    35,     0,     0,    40,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    41,    42,    43,  -208,     0,
    -208,     0,     0,  -208,  -208,  -208,  -208,  -208,  -208,  -208,
    -208,  -208,  -208,  -208,  -208,  -208,  -208,  -208,  -208,  -208,
    -208,  -208,     0,  -208,  -208,  -208,     0,  -208,  -208,  -208,
    -208,  -208,  -208,  -208,  -208,  -208,     0,     0,     0,  -208,
       0,     0,  -208,  -208
};

static const yytype_int16 yycheck[] =
{
       0,    10,   238,    95,     0,    16,    17,    28,   234,    14,
     236,    48,    19,    50,     5,     5,     5,    32,     3,     4,
       5,    43,     5,     5,    29,    47,    23,    24,    33,    51,
      47,     5,    42,   259,    51,    45,     3,     4,     5,    43,
      37,    38,    39,    40,    41,    42,    43,    49,    50,    48,
      48,    50,    50,    20,    21,    22,    23,    24,    25,    26,
      49,    46,    29,    30,    31,    56,    56,    49,     3,     4,
       5,    49,    50,    40,    96,    49,    43,    44,    45,    80,
      47,    82,    54,    55,    93,    13,    44,    54,    55,    94,
      95,    96,    50,    98,    53,    94,    94,    43,   105,     3,
       4,     5,    52,   118,    27,    28,   342,   114,    75,    94,
     336,    46,    79,    43,   119,    74,    43,    47,    46,   124,
     135,    51,    89,    90,    91,   126,    43,    94,   133,    43,
     145,    43,    59,    47,     5,    93,    95,    51,   153,    49,
     155,    43,    46,    93,    45,   381,    69,    70,    71,    72,
      52,     5,   167,   168,   165,    44,    44,    59,    48,    94,
      50,    50,    50,    17,    18,    19,    96,    43,    46,    77,
      44,    47,    50,    89,    90,    51,    50,    43,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
      94,    44,   207,   190,   191,   192,   217,    50,    44,    44,
      44,    44,   217,   208,    50,    50,    50,    50,   213,    44,
      44,    44,    80,    81,    82,    50,    50,    50,   233,    78,
       3,     4,     5,    65,    66,    67,    68,   242,    76,   250,
     179,   180,   181,   182,   183,   184,   328,    20,    21,    22,
      23,    24,    25,    26,    49,    50,    29,    30,    31,    73,
     265,   175,   176,   177,   178,    96,    48,    40,    50,    48,
      43,    50,    45,    93,    47,    56,    57,    58,   220,   221,
     222,    54,    55,    56,   366,    50,   368,    52,   370,   185,
     186,   187,    33,    34,    49,    50,    49,    50,    49,    50,
     221,   222,    75,     9,   169,   170,    79,    49,    23,    24,
      49,   188,   189,    93,     5,    49,    89,    90,    91,    50,
     402,   320,    37,    38,    39,    40,    41,    42,    43,    59,
      28,   330,    43,   328,   329,   417,   331,   419,    43,   421,
       5,    50,   347,    46,   355,    44,     5,     5,    52,    50,
       5,     5,     5,   352,    49,   360,   361,   362,    43,     5,
     355,    59,    60,    61,    62,    63,    64,   378,    43,   380,
      43,   366,   367,   368,   369,   370,   371,   388,    34,   384,
      95,     5,    52,    93,    28,    83,    84,    85,    86,    87,
      88,    89,    90,    28,    92,    28,   395,    45,    45,   410,
       5,    44,    44,   414,   403,    46,    44,   402,     7,    49,
     405,    12,    44,    44,   429,    49,    46,    44,    44,   418,
      49,   420,   417,   422,   419,    44,   421,    49,    49,    52,
      44,    46,   442,   407,   251,   117,   381,   342,   171,   174,
     172,   440,    22,    22,   173,   444,   445,   446,   264,   268,
      -1,   441,   442,    -1,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,    -1,     3,
       4,     5,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    20,    21,    22,    23,
      24,    25,    26,    -1,    -1,    29,    30,    31,     3,     4,
       5,    -1,    -1,    -1,    -1,    -1,    40,    -1,    -1,    43,
      -1,    45,   237,    47,    -1,    20,    21,    22,    23,    24,
      54,    55,    -1,    -1,    29,    30,    31,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    -1,
      45,    75,    47,    -1,    -1,    79,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    89,    90,    91,    -1,    -1,
      94,     3,     4,     5,     6,    -1,     8,     9,    10,    11,
      -1,    -1,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    -1,    -1,    29,    30,    31,
      32,    -1,    -1,    35,    36,    37,    -1,    -1,    40,    -1,
      -1,    43,    -1,    45,    46,    47,    -1,    49,    -1,    -1,
      -1,    -1,    54,    55,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    75,    -1,    -1,    -1,    79,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    90,    91,
       3,     4,     5,     6,    -1,     8,     9,    10,    11,    -1,
      -1,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    -1,    -1,    29,    30,    31,    32,
      -1,    -1,    35,    36,    37,    -1,    -1,    40,    -1,    -1,
      43,    -1,    45,    -1,    47,    -1,    49,    -1,    -1,    -1,
      -1,    54,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    75,    -1,    -1,    -1,    79,     3,     4,     5,
      -1,    -1,    -1,    -1,    -1,    -1,    89,    90,    91,    -1,
      -1,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    -1,    -1,    29,    30,    31,    59,    60,    61,    62,
      63,    64,    -1,    -1,    40,    -1,    -1,    43,    -1,    45,
      -1,    47,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,
      83,    84,    85,    86,    87,    88,    89,    90,    -1,    92,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,
       3,     4,     5,    79,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    89,    90,    91,    -1,    20,    21,    22,
      23,    24,    25,    26,    -1,    -1,    29,    30,    31,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    -1,    -1,
      43,    -1,    45,    -1,    47,    -1,    -1,    -1,    -1,    -1,
      -1,    54,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    75,     3,     4,     5,    79,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    89,    90,    91,    -1,
      20,    21,    22,    23,    24,    25,    26,    -1,    -1,    29,
      30,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      40,    -1,    -1,    43,    -1,    45,    -1,    47,    -1,    -1,
      -1,    -1,    -1,    -1,    54,    55,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    75,     3,     4,     5,    79,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,
      90,    91,    -1,    20,    21,    22,    23,    24,    25,    26,
      -1,    -1,    29,    30,    31,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    40,    -1,    -1,    43,    -1,    45,    -1,
      47,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,     3,
       4,     5,    79,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    89,    90,    91,    -1,    20,    21,    22,    23,
      24,    25,    26,    -1,    -1,    29,    30,    31,     3,     4,
       5,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,
      -1,    45,    -1,    47,    -1,    20,    21,    22,    23,    24,
      54,    55,    -1,    -1,    29,    30,    31,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    27,    28,    -1,    -1,    43,    -1,
      45,    75,    47,    -1,    -1,    79,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    89,    90,    91,    51,    -1,
      53,    -1,    -1,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    -1,    76,    77,    78,    -1,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    -1,    -1,    -1,    92,
      -1,    -1,    95,    96
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    99,   100,     0,     3,     4,     5,     6,     8,     9,
      10,    11,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    29,    30,    31,    32,    35,
      36,    37,    40,    43,    45,    47,    49,    54,    55,    75,
      79,    89,    90,    91,   101,   102,   103,   104,   106,   107,
     108,   109,   112,   113,   114,   115,   116,   117,   124,   125,
     128,   129,   132,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   161,   162,   163,   167,   171,   173,   174,
     175,   176,   177,    52,    43,    43,    43,   101,    43,     5,
      49,     5,    49,     5,    20,    21,    45,   111,   139,     5,
     105,   105,   105,     5,    56,   172,     5,   172,    43,    47,
      51,   159,     5,    23,    43,   155,   156,   152,   154,   152,
      45,   102,   139,    43,    49,    56,   140,     5,   130,   131,
     139,     3,     4,     5,    46,    94,   100,   137,   168,   169,
     170,    48,    50,    94,   164,   165,   166,   152,   152,   152,
     152,   152,   152,   152,    49,    50,    49,    50,    53,    74,
      95,    73,    77,    78,    76,    65,    66,    67,    68,    27,
      28,    69,    70,    71,    72,    80,    81,    82,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    83,
      84,    85,    86,    87,    88,    89,    90,    92,    47,    51,
      96,   159,    96,    47,    51,    96,   159,    93,   101,   139,
      17,    18,    19,   111,   154,   139,     9,   139,    49,    49,
       5,    46,    49,    59,    43,   172,    43,    42,    45,   133,
     133,    44,    94,   140,   160,   139,     5,   159,    46,    33,
      34,   126,   127,    49,   139,   140,    44,    50,    44,    43,
      59,   140,    46,    46,    50,    52,   140,    48,    50,   140,
      50,   105,   140,   140,   143,   143,   144,   145,   146,   147,
     148,   148,   148,   148,   149,   149,   149,   149,   149,   149,
     150,   150,   150,   151,   151,   152,   152,   152,   140,   140,
     140,   140,   140,   140,   140,   140,   140,   140,   140,   140,
     140,   139,     5,     5,     5,   139,     5,     5,   102,   140,
      44,     5,   104,   110,   104,   110,   104,   110,    49,    28,
      44,    43,    44,   140,     5,   130,    43,   130,   154,     5,
      49,   134,   135,   136,   137,   140,    44,    50,    48,    43,
     102,   127,    44,     5,   130,    93,    46,   169,   140,    48,
      94,   165,    52,    48,    48,   101,    49,    28,    49,    28,
      49,    28,   111,   139,   101,   139,    45,   118,    44,   130,
      44,    45,    46,   136,    94,   140,     5,   101,    44,   102,
     138,   139,   140,   140,   140,     7,   111,   139,   111,   139,
     111,   139,    49,    44,    44,    12,   119,   120,   121,   102,
      44,   102,   134,   140,    44,   102,   101,    49,    44,    49,
      44,    49,    44,   111,   101,    49,   139,    13,    46,   122,
     121,   102,    46,   102,   111,   101,   111,   101,   111,   101,
      44,    52,    52,   119,    44,    44,    44,   101,   100,   123,
     123,    46,   101,   101,   101
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    98,    99,   100,   100,   101,   101,   101,   101,   101,
     101,   101,   101,   101,   101,   101,   101,   101,   101,   101,
     101,   101,   102,   102,   103,   104,   104,   104,   104,   105,
     105,   106,   107,   108,   108,   109,   109,   109,   109,   109,
     109,   109,   109,   109,   109,   110,   111,   111,   112,   112,
     113,   113,   114,   115,   116,   117,   118,   118,   119,   119,
     120,   120,   121,   122,   123,   123,   124,   125,   125,   125,
     126,   127,   128,   129,   130,   130,   131,   131,   132,   133,
     133,   134,   134,   135,   135,   136,   136,   137,   137,   138,
     138,   139,   139,   140,   140,   140,   140,   140,   140,   140,
     140,   140,   140,   140,   140,   140,   140,   140,   140,   141,
     141,   142,   142,   142,   143,   143,   144,   144,   145,   145,
     146,   146,   147,   147,   147,   147,   147,   148,   148,   148,
     148,   148,   148,   148,   149,   149,   149,   149,   150,   150,
     150,   151,   151,   151,   151,   152,   152,   152,   152,   152,
     152,   152,   152,   152,   152,   153,   153,   153,   154,   154,
     154,   155,   155,   156,   156,   156,   156,   156,   156,   157,
     157,   157,   158,   158,   158,   158,   158,   159,   159,   160,
     160,   160,   160,   161,   161,   161,   161,   161,   161,   161,
     161,   161,   162,   162,   162,   162,   162,   163,   163,   163,
     164,   164,   164,   164,   165,   165,   166,   166,   167,   167,
     167,   168,   168,   169,   169,   169,   169,   170,   170,   170,
     171,   172,   172,   173,   174,   175,   175,   176,   176,   177,
     177,   177
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     2,     2,     2,     2,     2,     3,     1,
       3,     1,     2,     5,     7,     5,     7,     9,    10,    10,
      10,     7,     8,     8,     8,     1,     0,     1,     2,     3,
       2,     3,     3,     5,     3,     5,     3,     5,     0,     1,
       1,     2,     4,     3,     0,     1,     3,     3,     3,     4,
       5,     2,     2,     6,     0,     1,     1,     3,     3,     3,
       5,     0,     1,     1,     2,     1,     1,     5,     4,     1,
       1,     1,     3,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     1,
       5,     1,     3,     3,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     3,     3,     3,     3,     1,     3,     3,
       3,     3,     3,     3,     1,     3,     3,     3,     1,     3,
       3,     1,     3,     3,     3,     1,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     1,     2,     2,     1,     1,
       1,     1,     2,     1,     3,     4,     3,     4,     3,     3,
       3,     3,     2,     2,     4,     3,     2,     2,     3,     1,
       2,     3,     4,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     1,     1,     1,     1,     2,     3,     4,
       2,     2,     4,     4,     0,     1,     1,     2,     2,     3,
       4,     1,     3,     1,     3,     1,     2,     1,     1,     1,
       6,     0,     1,     3,     7,     3,     3,     1,     3,     1,
       2,     3
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

#line 1879 "parser.tab.c"

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
      yyerror (YY_("syntax error"));
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

  return yyresult;
}

#line 597 "parser.y"


void parser_reset(void) {
    syntax_valid = 1;
    error_count = 0;
}

int parser_is_valid(void) {
    return syntax_valid;
}

int parser_error_total(void) {
    return error_count;
}

// 错误处理
void yyerror(const char *s) {
    syntax_valid = 0;
    error_count++;
    fprintf(stderr, "语法错误 (第 %d 行): %s\n", yylineno, s);
}


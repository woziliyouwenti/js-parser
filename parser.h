/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
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
    NULL_LITERAL = 261,            /* NULL_LITERAL  */
    IF = 262,                      /* IF  */
    ELSE = 263,                    /* ELSE  */
    FOR = 264,                     /* FOR  */
    WHILE = 265,                   /* WHILE  */
    DO = 266,                      /* DO  */
    SWITCH = 267,                  /* SWITCH  */
    CASE = 268,                    /* CASE  */
    DEFAULT = 269,                 /* DEFAULT  */
    BREAK = 270,                   /* BREAK  */
    CONTINUE = 271,                /* CONTINUE  */
    RETURN = 272,                  /* RETURN  */
    VAR = 273,                     /* VAR  */
    LET = 274,                     /* LET  */
    CONST = 275,                   /* CONST  */
    FUNCTION = 276,                /* FUNCTION  */
    CLASS = 277,                   /* CLASS  */
    THIS = 278,                    /* THIS  */
    SUPER = 279,                   /* SUPER  */
    NEW = 280,                     /* NEW  */
    TYPEOF = 281,                  /* TYPEOF  */
    DELETE = 282,                  /* DELETE  */
    INSTANCEOF = 283,              /* INSTANCEOF  */
    IN = 284,                      /* IN  */
    TRUE = 285,                    /* TRUE  */
    FALSE = 286,                   /* FALSE  */
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
    SPREAD = 348,                  /* SPREAD  */
    NULLISH_COALESCING = 349,      /* NULLISH_COALESCING  */
    OPTIONAL_CHAINING = 350,       /* OPTIONAL_CHAINING  */
    ARROW = 351,                   /* ARROW  */
    ERROR_TOKEN = 352              /* ERROR_TOKEN  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define NUMBER 258
#define STRING 259
#define IDENTIFIER 260
#define NULL_LITERAL 261
#define IF 262
#define ELSE 263
#define FOR 264
#define WHILE 265
#define DO 266
#define SWITCH 267
#define CASE 268
#define DEFAULT 269
#define BREAK 270
#define CONTINUE 271
#define RETURN 272
#define VAR 273
#define LET 274
#define CONST 275
#define FUNCTION 276
#define CLASS 277
#define THIS 278
#define SUPER 279
#define NEW 280
#define TYPEOF 281
#define DELETE 282
#define INSTANCEOF 283
#define IN 284
#define TRUE 285
#define FALSE 286
#define TRY 287
#define CATCH 288
#define FINALLY 289
#define THROW 290
#define WITH 291
#define DEBUGGER 292
#define IMPORT 293
#define EXPORT 294
#define YIELD 295
#define INTERFACE 296
#define EXTENDS 297
#define LPAREN 298
#define RPAREN 299
#define LBRACE 300
#define RBRACE 301
#define LBRACKET 302
#define RBRACKET 303
#define SEMICOLON 304
#define COMMA 305
#define DOT 306
#define COLON 307
#define QUESTION 308
#define PLUS 309
#define MINUS 310
#define MULTIPLY 311
#define DIVIDE 312
#define MODULO 313
#define ASSIGN 314
#define PLUS_ASSIGN 315
#define MINUS_ASSIGN 316
#define MULTIPLY_ASSIGN 317
#define DIVIDE_ASSIGN 318
#define MODULO_ASSIGN 319
#define EQUAL 320
#define NOT_EQUAL 321
#define STRICT_EQUAL 322
#define STRICT_NOT_EQUAL 323
#define LESS 324
#define GREATER 325
#define LESS_EQUAL 326
#define GREATER_EQUAL 327
#define LOGICAL_AND 328
#define LOGICAL_OR 329
#define NOT 330
#define BITWISE_AND 331
#define BITWISE_OR 332
#define BITWISE_XOR 333
#define BITWISE_NOT 334
#define LEFT_SHIFT 335
#define RIGHT_SHIFT 336
#define UNSIGNED_RIGHT_SHIFT 337
#define LEFT_SHIFT_ASSIGN 338
#define RIGHT_SHIFT_ASSIGN 339
#define UNSIGNED_RIGHT_SHIFT_ASSIGN 340
#define AND_ASSIGN 341
#define OR_ASSIGN 342
#define XOR_ASSIGN 343
#define INCREMENT 344
#define DECREMENT 345
#define EXPONENT 346
#define EXPONENT_ASSIGN 347
#define SPREAD 348
#define NULLISH_COALESCING 349
#define OPTIONAL_CHAINING 350
#define ARROW 351
#define ERROR_TOKEN 352

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 40 "parser.y"

    double number;
    char *string;
    void *node;

#line 267 "parser.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_H_INCLUDED  */

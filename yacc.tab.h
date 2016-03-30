/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     T_CREATE = 258,
     T_DROP = 259,
     T_USE = 260,
     T_INDEX = 261,
     T_DATABASE = 262,
     T_SHOW = 263,
     T_TABLES = 264,
     T_DESC = 265,
     T_TABLE = 266,
     T_NOT = 267,
     T_NULL = 268,
     T_SET = 269,
     T_AND = 270,
     T_SELECT = 271,
     T_LIKE = 272,
     T_GROUP = 273,
     T_BY = 274,
     T_FROM = 275,
     T_WHERE = 276,
     T_INSERT = 277,
     T_UPDATE = 278,
     T_DELETE = 279,
     T_INTO = 280,
     T_VALUES = 281,
     T_EQ = 282,
     T_LT = 283,
     T_LE = 284,
     T_GT = 285,
     T_GE = 286,
     T_NE = 287,
     T_IN = 288,
     T_ISNULL = 289,
     NOTOKEN = 290,
     T_INT = 291,
     T_REAL = 292,
     T_STRING = 293,
     T_QSTRING = 294
   };
#endif
/* Tokens.  */
#define T_CREATE 258
#define T_DROP 259
#define T_USE 260
#define T_INDEX 261
#define T_DATABASE 262
#define T_SHOW 263
#define T_TABLES 264
#define T_DESC 265
#define T_TABLE 266
#define T_NOT 267
#define T_NULL 268
#define T_SET 269
#define T_AND 270
#define T_SELECT 271
#define T_LIKE 272
#define T_GROUP 273
#define T_BY 274
#define T_FROM 275
#define T_WHERE 276
#define T_INSERT 277
#define T_UPDATE 278
#define T_DELETE 279
#define T_INTO 280
#define T_VALUES 281
#define T_EQ 282
#define T_LT 283
#define T_LE 284
#define T_GT 285
#define T_GE 286
#define T_NE 287
#define T_IN 288
#define T_ISNULL 289
#define NOTOKEN 290
#define T_INT 291
#define T_REAL 292
#define T_STRING 293
#define T_QSTRING 294




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 28 "yacc.y"
{
	int ival;
	float rval;
	char *sval;
	CompOp cval;
	NODE *n;
}
/* Line 1529 of yacc.c.  */
#line 135 "yacc.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;


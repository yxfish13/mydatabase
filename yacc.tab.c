/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



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




/* Copy the first part of user declarations.  */
#line 1 "yacc.y"

/*本yacc的生成文件是yacc.tab.c和yacc.tab.h
yacc文件由3段组成，用2个%%行把这3段隔开。
第1段是声明段，包括：
1-C代码部分：include头文件、函数、类型等声明，这些声明会原样拷到生成的.c文件中。
2-记号声明，如%token
3-类型声明，如%type
第2段是规则段，是yacc文件的主体，包括每个产生式是如何匹配的，以及匹配后要执行的C代码动作。
第3段是C函数定义段，如yyerror()的定义，这些C代码会原样拷到生成的.c文件中。该段内容可以为空*/

//第1段：声明段
#include "main.h"	
#include "parser_internal.h"
#include "query.h"
using namespace std;
#define YYDEBUG 1
extern "C"			//为了能够在C++程序里面调用C函数，必须把每一个需要使用的C函数，其声明都包括在extern "C"{}块里面，这样C++链接时才能成功链接它们。extern "C"用来在C++环境下设置C链接类型。
{					//lex.l中也有类似的这段extern "C"，可以把它们合并成一段，放到共同的头文件main.h中
	void yyerror(const char *s);
	extern int yylex(void);//该函数是在lex.yy.c里定义的，yyparse()里要调用该函数，为了能编译和链接，必须用extern加以声明
}

NODE *parse_tree;

QL_manager *pQlm;


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

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
/* Line 193 of yacc.c.  */
#line 209 "yacc.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 222 "yacc.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  46
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   152

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  40
/* YYNRULES -- Number of rules.  */
#define YYNRULES  86
/* YYNRULES -- Number of states.  */
#define YYNSTATES  164

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   294

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      41,    42,    46,    44,    43,    45,    48,    47,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    40,
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
      35,    36,    37,    38,    39
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,    30,    32,    34,    36,    38,
      40,    44,    48,    51,    58,    62,    65,    68,    75,    82,
      88,    97,   103,   108,   114,   118,   120,   126,   132,   138,
     144,   148,   154,   158,   162,   164,   168,   170,   176,   181,
     184,   190,   198,   204,   209,   211,   213,   217,   219,   224,
     228,   230,   234,   236,   238,   241,   243,   247,   249,   253,
     255,   257,   261,   263,   265,   267,   270,   272,   274,   276,
     278,   280,   282,   284,   286,   288,   290
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      50,     0,    -1,    51,    40,    -1,    52,    -1,    53,    -1,
      54,    -1,    55,    -1,    56,    -1,    57,    -1,    64,    -1,
      66,    -1,    67,    -1,    68,    -1,    65,    -1,    58,    -1,
      59,    -1,    60,    -1,    61,    -1,    62,    -1,    63,    -1,
       3,     7,    38,    -1,     4,     7,    38,    -1,     5,    38,
      -1,     3,    11,    38,    41,    72,    42,    -1,     4,    11,
      38,    -1,     8,     9,    -1,    10,    38,    -1,     3,     6,
      80,    41,    78,    42,    -1,     4,     6,    80,    41,    78,
      42,    -1,    16,    76,    20,    79,    81,    -1,    16,    76,
      20,    80,    18,    19,    76,    81,    -1,    22,    25,    38,
      26,    71,    -1,    24,    20,    38,    81,    -1,    23,    38,
      14,    69,    81,    -1,    70,    43,    69,    -1,    70,    -1,
      78,    27,    84,    44,    84,    -1,    78,    27,    84,    45,
      84,    -1,    78,    27,    84,    46,    84,    -1,    78,    27,
      84,    47,    84,    -1,    78,    27,    84,    -1,    71,    43,
      41,    85,    42,    -1,    41,    85,    42,    -1,    75,    43,
      72,    -1,    75,    -1,    74,    15,    73,    -1,    74,    -1,
      38,    33,    41,    85,    42,    -1,    38,    38,    12,    13,
      -1,    38,    38,    -1,    38,    38,    41,    36,    42,    -1,
      38,    38,    41,    36,    42,    12,    13,    -1,    38,    38,
      41,    38,    42,    -1,    38,    41,    73,    42,    -1,    77,
      -1,    46,    -1,    78,    43,    77,    -1,    78,    -1,    38,
      41,    38,    42,    -1,    38,    48,    38,    -1,    38,    -1,
      80,    43,    79,    -1,    80,    -1,    38,    -1,    21,    82,
      -1,    88,    -1,    83,    15,    82,    -1,    83,    -1,    78,
      87,    84,    -1,    78,    -1,    86,    -1,    85,    43,    86,
      -1,    86,    -1,    39,    -1,    36,    -1,    45,    36,    -1,
      37,    -1,    13,    -1,    28,    -1,    29,    -1,    30,    -1,
      31,    -1,    27,    -1,    32,    -1,    17,    -1,    34,    -1,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   126,   126,   134,   135,   136,   140,   141,   142,   146,
     147,   148,   149,   150,   154,   155,   156,   157,   158,   159,
     163,   170,   177,   184,   191,   198,   205,   212,   219,   226,
     234,   241,   248,   255,   262,   266,   273,   277,   281,   285,
     289,   296,   300,   307,   311,   318,   322,   329,   335,   339,
     343,   347,   351,   355,   362,   363,   370,   374,   381,   385,
     389,   396,   400,   407,   414,   418,   425,   429,   436,   443,
     447,   454,   458,   465,   469,   473,   477,   481,   488,   492,
     496,   500,   504,   508,   512,   516,   521
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_CREATE", "T_DROP", "T_USE", "T_INDEX",
  "T_DATABASE", "T_SHOW", "T_TABLES", "T_DESC", "T_TABLE", "T_NOT",
  "T_NULL", "T_SET", "T_AND", "T_SELECT", "T_LIKE", "T_GROUP", "T_BY",
  "T_FROM", "T_WHERE", "T_INSERT", "T_UPDATE", "T_DELETE", "T_INTO",
  "T_VALUES", "T_EQ", "T_LT", "T_LE", "T_GT", "T_GE", "T_NE", "T_IN",
  "T_ISNULL", "NOTOKEN", "T_INT", "T_REAL", "T_STRING", "T_QSTRING", "';'",
  "'('", "')'", "','", "'+'", "'-'", "'*'", "'/'", "'.'", "$accept",
  "start", "command", "db", "dml", "ddl", "createdb", "dropdb", "usedb",
  "createtable", "droptable", "showtables", "desc", "createindex",
  "dropindex", "query", "querygroupsum", "insert", "delete", "update",
  "expr_list", "expr", "list_non_mt_value_list", "non_mt_attrtype_list",
  "check_list", "check", "attrtype", "non_mt_select_clause",
  "non_mt_relattr_list", "relattr", "non_mt_relation_list", "relation",
  "opt_where_clause", "non_mt_cond_list", "condition", "relattr_or_value",
  "non_mt_value_list", "value", "op", "nothing", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
      59,    40,    41,    44,    43,    45,    42,    47,    46
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    49,    50,    51,    51,    51,    52,    52,    52,    53,
      53,    53,    53,    53,    54,    54,    54,    54,    54,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    69,    70,    70,    70,    70,
      70,    71,    71,    72,    72,    73,    73,    74,    75,    75,
      75,    75,    75,    75,    76,    76,    77,    77,    78,    78,
      78,    79,    79,    80,    81,    81,    82,    82,    83,    84,
      84,    85,    85,    86,    86,    86,    86,    86,    87,    87,
      87,    87,    87,    87,    87,    87,    88
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     3,     2,     6,     3,     2,     2,     6,     6,     5,
       8,     5,     4,     5,     3,     1,     5,     5,     5,     5,
       3,     5,     3,     3,     1,     3,     1,     5,     4,     2,
       5,     7,     5,     4,     1,     1,     3,     1,     4,     3,
       1,     3,     1,     1,     2,     1,     3,     1,     3,     1,
       1,     3,     1,     1,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     3,     4,     5,     6,     7,     8,    14,    15,
      16,    17,    18,    19,     9,    13,    10,    11,    12,     0,
       0,     0,     0,     0,     0,    22,    25,    26,    60,    55,
       0,    54,    57,     0,     0,     0,     1,     2,    63,     0,
      20,     0,     0,    21,    24,     0,     0,     0,     0,     0,
       0,    86,     0,     0,     0,     0,    59,    86,    62,    56,
       0,    86,    35,     0,     0,    32,    65,     0,     0,     0,
      44,     0,    58,    29,     0,     0,     0,    31,    33,     0,
       0,     0,    64,    67,    27,    49,     0,    23,     0,    28,
       0,    61,    62,    77,    74,    76,    73,     0,     0,    72,
       0,    34,    69,    40,    70,    84,    82,    78,    79,    80,
      81,    83,    85,     0,     0,     0,     0,     0,     0,    46,
      43,    86,    75,    42,     0,     0,     0,     0,     0,     0,
      68,    66,    48,     0,     0,     0,    53,     0,    30,    71,
       0,    36,    37,    38,    39,    50,    52,     0,    45,    41,
       0,     0,    51,    47
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      71,    72,    87,    79,   128,   129,    80,    40,    41,   112,
      67,    49,    75,    92,    93,   113,   108,   114,   123,    76
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -131
static const yytype_int16 yypact[] =
{
      57,    19,    35,   -25,    28,    13,   -23,    34,    15,    58,
      55,    42,  -131,  -131,  -131,  -131,  -131,  -131,  -131,  -131,
    -131,  -131,  -131,  -131,  -131,  -131,  -131,  -131,  -131,    50,
      51,    52,    50,    53,    54,  -131,  -131,  -131,   -32,  -131,
      73,  -131,    56,    59,    81,    60,  -131,  -131,  -131,    61,
    -131,    62,    63,  -131,  -131,    67,    68,    50,    69,    70,
      69,    79,    69,    71,    69,    66,  -131,    79,   -15,  -131,
      72,    79,    74,    83,    69,  -131,  -131,    77,   -27,    78,
      80,    82,  -131,  -131,    92,    50,    -1,    84,  -131,    69,
      -5,   -10,  -131,    86,  -131,    -2,    76,  -131,    71,  -131,
     -23,  -131,    85,  -131,  -131,  -131,  -131,    89,     5,  -131,
      75,  -131,  -131,    30,  -131,  -131,  -131,  -131,  -131,  -131,
    -131,  -131,  -131,    -5,    69,    99,     7,    88,    87,   100,
    -131,    79,  -131,  -131,    -1,    -1,    -5,    -5,    -5,    -5,
    -131,  -131,  -131,    90,    91,    93,  -131,    76,  -131,  -131,
      21,  -131,  -131,  -131,  -131,   110,  -131,    -1,  -131,  -131,
     113,    27,  -131,  -131
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -131,  -131,  -131,  -131,  -131,  -131,  -131,  -131,  -131,  -131,
    -131,  -131,  -131,  -131,  -131,  -131,  -131,  -131,  -131,  -131,
      41,  -131,  -131,    33,   -12,  -131,  -131,    36,    94,    -6,
      64,   -28,   -65,    14,  -131,   -52,  -130,   -85,  -131,  -131
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      42,   109,    83,    84,    52,   150,    88,   115,   103,    55,
     125,    95,   103,    35,    96,    38,    56,   116,   117,   118,
     119,   120,   121,    39,   122,    29,    30,   161,    85,    68,
      31,   104,   105,    38,   106,   104,   105,    36,   106,   126,
     107,    32,    33,   143,   107,   144,    34,   133,   134,   149,
     109,    37,    42,    44,    73,    46,    77,   102,    81,    43,
       1,     2,     3,   159,   134,     4,   148,     5,    91,   163,
     134,   140,   109,     6,   136,   137,   138,   139,    45,     7,
       8,     9,    47,    73,   151,   152,   153,   154,    48,    50,
      51,    53,    54,    57,    42,    60,    70,    59,    61,    58,
      74,   124,    62,    63,    64,    65,    66,    38,    82,    78,
      90,   100,   142,    86,   127,   147,   135,    89,    91,    94,
      97,   145,   160,    98,    99,   132,   162,   110,    85,   146,
     111,   130,   155,   156,   157,   158,   131,     0,   141,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   101,
       0,     0,    69
};

static const yytype_int16 yycheck[] =
{
       6,    86,    67,    18,    32,   135,    71,    17,    13,    41,
      12,    38,    13,    38,    41,    38,    48,    27,    28,    29,
      30,    31,    32,    46,    34,     6,     7,   157,    43,    57,
      11,    36,    37,    38,    39,    36,    37,     9,    39,    41,
      45,     6,     7,    36,    45,    38,    11,    42,    43,   134,
     135,    38,    58,    38,    60,     0,    62,    85,    64,    25,
       3,     4,     5,    42,    43,     8,   131,    10,    74,    42,
      43,   123,   157,    16,    44,    45,    46,    47,    20,    22,
      23,    24,    40,    89,   136,   137,   138,   139,    38,    38,
      38,    38,    38,    20,   100,    14,    26,    38,    38,    43,
      21,    15,    41,    41,    41,    38,    38,    38,    42,    38,
      27,    19,    13,    41,    38,    15,    41,    43,   124,    42,
      42,    33,    12,    43,    42,    36,    13,    43,    43,    42,
      89,    98,    42,    42,    41,   147,   100,    -1,   124,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    85,
      -1,    -1,    58
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     8,    10,    16,    22,    23,    24,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,     6,
       7,    11,     6,     7,    11,    38,     9,    38,    38,    46,
      76,    77,    78,    25,    38,    20,     0,    40,    38,    80,
      38,    38,    80,    38,    38,    41,    48,    20,    43,    38,
      14,    38,    41,    41,    41,    38,    38,    79,    80,    77,
      26,    69,    70,    78,    21,    81,    88,    78,    38,    72,
      75,    78,    42,    81,    18,    43,    41,    71,    81,    43,
      27,    78,    82,    83,    42,    38,    41,    42,    43,    42,
      19,    79,    80,    13,    36,    37,    39,    45,    85,    86,
      43,    69,    78,    84,    86,    17,    27,    28,    29,    30,
      31,    32,    34,    87,    15,    12,    41,    38,    73,    74,
      72,    76,    36,    42,    43,    41,    44,    45,    46,    47,
      84,    82,    13,    36,    38,    33,    42,    15,    81,    86,
      85,    84,    84,    84,    84,    42,    42,    41,    73,    42,
      12,    85,    13,    42
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
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



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
	    /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 127 "yacc.y"
    {
		parse_tree = (yyvsp[(1) - (2)].n);
		YYACCEPT;
	;}
    break;

  case 20:
#line 164 "yacc.y"
    {
		(yyval.n) = create_db_node((yyvsp[(3) - (3)].sval));
	;}
    break;

  case 21:
#line 171 "yacc.y"
    {
		(yyval.n) = drop_db_node((yyvsp[(3) - (3)].sval));
	;}
    break;

  case 22:
#line 178 "yacc.y"
    {
		(yyval.n) = use_db_node((yyvsp[(2) - (2)].sval));
	;}
    break;

  case 23:
#line 185 "yacc.y"
    {
		(yyval.n) = create_table_node((yyvsp[(3) - (6)].sval),(yyvsp[(5) - (6)].n));
	;}
    break;

  case 24:
#line 192 "yacc.y"
    {
		(yyval.n) = drop_table_node((yyvsp[(3) - (3)].sval));
	;}
    break;

  case 25:
#line 199 "yacc.y"
    {
		(yyval.n) = show_tables_node();
	;}
    break;

  case 26:
#line 206 "yacc.y"
    {
		(yyval.n) = desc_node((yyvsp[(2) - (2)].sval));
	;}
    break;

  case 27:
#line 213 "yacc.y"
    {
		(yyval.n) = create_index_node((yyvsp[(3) - (6)].n), (yyvsp[(5) - (6)].n));
	;}
    break;

  case 28:
#line 220 "yacc.y"
    {
		(yyval.n) = drop_index_node((yyvsp[(3) - (6)].n),(yyvsp[(5) - (6)].n));
	;}
    break;

  case 29:
#line 228 "yacc.y"
    {
		(yyval.n) = query_node((yyvsp[(2) - (5)].n), (yyvsp[(4) - (5)].n), (yyvsp[(5) - (5)].n));
	;}
    break;

  case 30:
#line 235 "yacc.y"
    {
		(yyval.n) = query_group_node((yyvsp[(2) - (8)].n),(yyvsp[(4) - (8)].n),(yyvsp[(8) - (8)].n),(yyvsp[(7) - (8)].n));
	;}
    break;

  case 31:
#line 242 "yacc.y"
    {
		(yyval.n) = insert_node((yyvsp[(3) - (5)].sval),(yyvsp[(5) - (5)].n));
	;}
    break;

  case 32:
#line 249 "yacc.y"
    {
		(yyval.n) = delete_node((yyvsp[(3) - (4)].sval),(yyvsp[(4) - (4)].n));
	;}
    break;

  case 33:
#line 256 "yacc.y"
    {
		(yyval.n) = update_node((yyvsp[(2) - (5)].sval),(yyvsp[(4) - (5)].n),(yyvsp[(5) - (5)].n));
	;}
    break;

  case 34:
#line 263 "yacc.y"
    {
		(yyval.n) = prepend((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
	;}
    break;

  case 35:
#line 267 "yacc.y"
    {
		(yyval.n) = list_node((yyvsp[(1) - (1)].n));
	;}
    break;

  case 36:
#line 274 "yacc.y"
    {
		(yyval.n) = expr_node((yyvsp[(1) - (5)].n), (yyvsp[(3) - (5)].n), (yyvsp[(5) - (5)].n), 1);
	;}
    break;

  case 37:
#line 278 "yacc.y"
    {
		(yyval.n) = expr_node((yyvsp[(1) - (5)].n), (yyvsp[(3) - (5)].n), (yyvsp[(5) - (5)].n), 2);
	;}
    break;

  case 38:
#line 282 "yacc.y"
    {
		(yyval.n) = expr_node((yyvsp[(1) - (5)].n), (yyvsp[(3) - (5)].n), (yyvsp[(5) - (5)].n), 3);
	;}
    break;

  case 39:
#line 286 "yacc.y"
    {
		(yyval.n) = expr_node((yyvsp[(1) - (5)].n), (yyvsp[(3) - (5)].n), (yyvsp[(5) - (5)].n), 4);
	;}
    break;

  case 40:
#line 290 "yacc.y"
    {
		(yyval.n) = expr_node((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n), NULL, 0);
	;}
    break;

  case 41:
#line 297 "yacc.y"
    {
		(yyval.n) = combine((yyvsp[(4) - (5)].n),(yyvsp[(1) - (5)].n));
	;}
    break;

  case 42:
#line 301 "yacc.y"
    {
		(yyval.n) = (yyvsp[(2) - (3)].n);
	;}
    break;

  case 43:
#line 308 "yacc.y"
    {
		(yyval.n) = prepend((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
	;}
    break;

  case 44:
#line 312 "yacc.y"
    {
		(yyval.n) = list_node((yyvsp[(1) - (1)].n));
	;}
    break;

  case 45:
#line 319 "yacc.y"
    {
		(yyval.n) = prepend((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
	;}
    break;

  case 46:
#line 323 "yacc.y"
    {
		(yyval.n) = list_node((yyvsp[(1) - (1)].n));
	;}
    break;

  case 47:
#line 330 "yacc.y"
    {
		(yyval.n) = check_node((yyvsp[(1) - (5)].sval),(yyvsp[(4) - (5)].n));
	;}
    break;

  case 48:
#line 336 "yacc.y"
    {
		(yyval.n) = attrtype_node((yyvsp[(1) - (4)].sval),(yyvsp[(2) - (4)].sval), 0, 1);
	;}
    break;

  case 49:
#line 340 "yacc.y"
    {
		(yyval.n) = attrtype_node((yyvsp[(1) - (2)].sval),(yyvsp[(2) - (2)].sval), 0, 0);
	;}
    break;

  case 50:
#line 344 "yacc.y"
    {
		(yyval.n) = attrtype_node((yyvsp[(1) - (5)].sval), (yyvsp[(2) - (5)].sval), (yyvsp[(4) - (5)].ival), 0);
	;}
    break;

  case 51:
#line 348 "yacc.y"
    {
		(yyval.n) = attrtype_node((yyvsp[(1) - (7)].sval), (yyvsp[(2) - (7)].sval), (yyvsp[(4) - (7)].ival), 1);
	;}
    break;

  case 52:
#line 352 "yacc.y"
    {
		(yyval.n) = primary_key_node((yyvsp[(4) - (5)].sval));
	;}
    break;

  case 53:
#line 356 "yacc.y"
    {
		(yyval.n) = attr_check_node((yyvsp[(3) - (4)].n));
	;}
    break;

  case 55:
#line 364 "yacc.y"
    {
		(yyval.n) = list_node(relattr_node(NULL,(char*)"*"));
	;}
    break;

  case 56:
#line 371 "yacc.y"
    {
		(yyval.n) = prepend((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
	;}
    break;

  case 57:
#line 375 "yacc.y"
    {
		(yyval.n) = list_node((yyvsp[(1) - (1)].n));
	;}
    break;

  case 58:
#line 382 "yacc.y"
    {
		(yyval.n) = relattr_node((yyvsp[(1) - (4)].sval), (yyvsp[(3) - (4)].sval));
	;}
    break;

  case 59:
#line 386 "yacc.y"
    {
		(yyval.n) = relattr_node((yyvsp[(1) - (3)].sval), (yyvsp[(3) - (3)].sval));
	;}
    break;

  case 60:
#line 390 "yacc.y"
    {
		(yyval.n) = relattr_node(NULL,(yyvsp[(1) - (1)].sval));
	;}
    break;

  case 61:
#line 397 "yacc.y"
    {
		(yyval.n) = prepend((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
	;}
    break;

  case 62:
#line 401 "yacc.y"
    {
		(yyval.n) = list_node((yyvsp[(1) - (1)].n));
	;}
    break;

  case 63:
#line 408 "yacc.y"
    {
		(yyval.n) = relation_node((yyvsp[(1) - (1)].sval));
	;}
    break;

  case 64:
#line 415 "yacc.y"
    {
		(yyval.n) = (yyvsp[(2) - (2)].n);
	;}
    break;

  case 65:
#line 419 "yacc.y"
    {
		(yyval.n) = NULL;
	;}
    break;

  case 66:
#line 426 "yacc.y"
    {
		(yyval.n) = prepend((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n));
	;}
    break;

  case 67:
#line 430 "yacc.y"
    {
		(yyval.n) = list_node((yyvsp[(1) - (1)].n));
	;}
    break;

  case 68:
#line 437 "yacc.y"
    {
		(yyval.n) = condition_node((yyvsp[(1) - (3)].n),(yyvsp[(2) - (3)].cval),(yyvsp[(3) - (3)].n));
	;}
    break;

  case 69:
#line 444 "yacc.y"
    {
		(yyval.n) = relattr_or_value_node((yyvsp[(1) - (1)].n),NULL);
	;}
    break;

  case 70:
#line 448 "yacc.y"
    {
		(yyval.n) = relattr_or_value_node(NULL,(yyvsp[(1) - (1)].n));
	;}
    break;

  case 71:
#line 455 "yacc.y"
    {
		(yyval.n) = prepend((yyvsp[(3) - (3)].n), (yyvsp[(1) - (3)].n));
	;}
    break;

  case 72:
#line 459 "yacc.y"
    {
		(yyval.n) = list_node((yyvsp[(1) - (1)].n));
	;}
    break;

  case 73:
#line 466 "yacc.y"
    {
		(yyval.n) = value_node(STRING,0,(void *) (yyvsp[(1) - (1)].sval));
	;}
    break;

  case 74:
#line 470 "yacc.y"
    {
		(yyval.n) = value_node(INT,0,(void *)&(yyvsp[(1) - (1)].ival));
	;}
    break;

  case 75:
#line 474 "yacc.y"
    {
		(yyval.n) = value_node(INT,1,(void *)&(yyvsp[(2) - (2)].ival));
	;}
    break;

  case 76:
#line 478 "yacc.y"
    {
		(yyval.n) = value_node(FLOAT,0, (void *)& (yyvsp[(1) - (1)].rval));
	;}
    break;

  case 77:
#line 482 "yacc.y"
    {
		(yyval.n) = value_node(NUL,0,NULL);
	;}
    break;

  case 78:
#line 489 "yacc.y"
    {
		(yyval.cval) = LT_OP;
	;}
    break;

  case 79:
#line 493 "yacc.y"
    {
		(yyval.cval) = LE_OP;
	;}
    break;

  case 80:
#line 497 "yacc.y"
    {
		(yyval.cval) = GT_OP;
	;}
    break;

  case 81:
#line 501 "yacc.y"
    {
		(yyval.cval) = GE_OP;
	;}
    break;

  case 82:
#line 505 "yacc.y"
    {
		(yyval.cval) = EQ_OP;
	;}
    break;

  case 83:
#line 509 "yacc.y"
    {
		(yyval.cval) = NE_OP;
	;}
    break;

  case 84:
#line 513 "yacc.y"
    {
		(yyval.cval) = LIKE_OP;
	;}
    break;

  case 85:
#line 517 "yacc.y"
    {
		(yyval.cval) = ISNULL_OP;
	;}
    break;


/* Line 1267 of yacc.c.  */
#line 2030 "yacc.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 524 "yacc.y"


void yyerror(const char *s)			//当yacc遇到语法错误时，会回调yyerror函数，并且把错误信息放在参数s中
{
	cerr<<s<<endl;					//直接输出错误信息
}

void runParser(QL_manager &qlm)
{
	pQlm = &qlm;

	while(true){
		new_query();

		cout << PROMPT;
		cout.flush();

		if(yyparse() == 0 && parse_tree != NULL)
			interp(parse_tree);
	}	
}

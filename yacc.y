%{
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
%}

%union{
	int ival;
	float rval;
	char *sval;
	CompOp cval;
	NODE *n;
}

/*lex里要return的记号的声明
用token后加一对<member>来定义记号，旨在用于简化书写方式。
假定某个产生式中第1个终结符是记号OPERATOR，则引用OPERATOR属性的方式：
1-如果记号OPERATOR是以普通方式定义的，如%token OPERATOR，则在动作中要写$1.m_cOp，以指明使用YYSTYPE的哪个成员
2-用%token<m_cOp>OPERATOR方式定义后，只需要写$1，yacc会自动替换为$1.m_cOp
另外用<>定义记号后，非终结符如file, tokenlist，必须用%type<member>来定义(否则会报错)，以指明它们的属性对应YYSTYPE中哪个成员，这时对该非终结符的引用，如$$，会自动替换为$$.member*/
%token    
	T_CREATE
	T_DROP
	T_USE
	T_INDEX
	T_DATABASE
	T_SHOW
	T_TABLES
	T_DESC
	T_TABLE
	T_NOT
	T_NULL
      	T_SET
      	T_AND
	T_SELECT
	T_LIKE
	T_GROUP
	T_BY
	T_FROM
	T_WHERE
	T_INSERT
	T_UPDATE
	T_DELETE
	T_INTO
	T_VALUES
	T_EQ
	T_LT
	T_LE
	T_GT
	T_GE
	T_NE
	T_IN
	T_ISNULL
	NOTOKEN

%token <ival> T_INT

%token <rval> T_REAL

%token <sval> T_STRING
	T_QSTRING

%type <cval> op

%type <n> command
	db
	dml
	ddl
	createdb
	dropdb
	usedb
	createtable
	droptable
	showtables
	createindex
	dropindex
	desc
	non_mt_attrtype_list
	attrtype
	query
	querygroupsum
	insert
	delete
	update
	expr_list
	expr
	non_mt_select_clause
	non_mt_relattr_list
	non_mt_relation_list
	list_non_mt_value_list
	non_mt_value_list
	opt_where_clause
	relattr
	relation
	non_mt_cond_list
	condition
	relattr_or_value
	value
	check_list
	check

%%

start
	:command ';'
	{
		parse_tree = $1;
		YYACCEPT;
	}
	;

command
	: db
	|dml
	|ddl
	;

db
	: createdb
	| dropdb
	| usedb
	;

dml
	: query
	| insert
	| delete
	| update
	| querygroupsum
	;

ddl
	:createtable
	|droptable
	|showtables
	|desc
	|createindex
	|dropindex
	;

createdb
	: T_CREATE T_DATABASE T_STRING
	{
		$$ = create_db_node($3);
	}
	;

dropdb
	: T_DROP T_DATABASE T_STRING
	{
		$$ = drop_db_node($3);
	}
	;

usedb	
	: T_USE T_STRING
	{
		$$ = use_db_node($2);
	}	
	;

createtable
	: T_CREATE T_TABLE T_STRING '(' non_mt_attrtype_list ')'
	{
		$$ = create_table_node($3,$5);
	}
	;

droptable
	: T_DROP T_TABLE T_STRING
	{
		$$ = drop_table_node($3);
	}
	;

showtables
	: T_SHOW T_TABLES
	{
		$$ = show_tables_node();
	}
	;

desc
	: T_DESC T_STRING
	{
		$$ = desc_node($2);
	}
	;

createindex
	: T_CREATE T_INDEX  relation '(' relattr ')'
	{
		$$ = create_index_node($3, $5);
	}
	;

dropindex
	: T_DROP T_INDEX relation '(' relattr ')'
	{
		$$ = drop_index_node($3,$5);
	}
	;
	
query
	:T_SELECT non_mt_select_clause T_FROM non_mt_relation_list
	opt_where_clause
	{
		$$ = query_node($2, $4, $5);
	}
	;

querygroupsum
	:T_SELECT non_mt_select_clause  T_FROM relation T_GROUP T_BY non_mt_select_clause opt_where_clause
	{
		$$ = query_group_node($2,$4,$8,$7);
	}
	;

insert
	:T_INSERT T_INTO T_STRING T_VALUES list_non_mt_value_list
	{
		$$ = insert_node($3,$5);
	}
	;

delete
	:T_DELETE T_FROM T_STRING opt_where_clause
	{
		$$ = delete_node($3,$4);
	}
	;

update
	:T_UPDATE T_STRING T_SET expr_list opt_where_clause
	{
		$$ = update_node($2,$4,$5);
	}
	;

expr_list
	:expr ',' expr_list
	{
		$$ = prepend($1, $3);
	}
	| expr
	{
		$$ = list_node($1);
	}
	;

expr
	: relattr T_EQ relattr_or_value '+' relattr_or_value
	{
		$$ = expr_node($1, $3, $5, 1);
	}
	|relattr T_EQ relattr_or_value '-' relattr_or_value
	{
		$$ = expr_node($1, $3, $5, 2);
	}
	|relattr T_EQ relattr_or_value '*' relattr_or_value
	{
		$$ = expr_node($1, $3, $5, 3);
	}
	| relattr T_EQ relattr_or_value '/' relattr_or_value
	{
		$$ = expr_node($1, $3, $5, 4);
	}
	| relattr T_EQ relattr_or_value
	{
		$$ = expr_node($1, $3, NULL, 0);
	}
	;

list_non_mt_value_list
	: list_non_mt_value_list ',' '(' non_mt_value_list ')' 
	{
		$$ = combine($4,$1);
	}
	| '(' non_mt_value_list ')'
	{
		$$ = $2;
	}
	;

non_mt_attrtype_list
	: attrtype ',' non_mt_attrtype_list
	{
		$$ = prepend($1, $3);
	}
	| attrtype
	{
		$$ = list_node($1);
	}
	;

check_list
	: check T_AND check_list
	{
		$$ = prepend($1, $3);
	}
	| check
	{
		$$ = list_node($1);
	}
	;

check
	: T_STRING T_IN '(' non_mt_value_list ')'
	{
		$$ = check_node($1,$4);
	}

attrtype
	:T_STRING T_STRING T_NOT T_NULL
	{
		$$ = attrtype_node($1,$2, 0, 1);
	}
	| T_STRING T_STRING
	{
		$$ = attrtype_node($1,$2, 0, 0);
	}
	|T_STRING T_STRING'(' T_INT ')'
	{
		$$ = attrtype_node($1, $2, $4, 0);
	}
	|T_STRING T_STRING'(' T_INT ')' T_NOT T_NULL
	{
		$$ = attrtype_node($1, $2, $4, 1);
	}
	|T_STRING T_STRING'(' T_STRING ')'
	{
		$$ = primary_key_node($4);
	}
	|T_STRING '(' check_list ')'
	{
		$$ = attr_check_node($3);
	}
	;

non_mt_select_clause
	: non_mt_relattr_list
	| '*'
	{
		$$ = list_node(relattr_node(NULL,(char*)"*"));
	}
	;

non_mt_relattr_list
	: relattr ',' non_mt_relattr_list
	{
		$$ = prepend($1, $3);
	}
	| relattr
	{
		$$ = list_node($1);
	}
	;

relattr 
	: T_STRING '(' T_STRING ')'
	{
		$$ = relattr_node($1, $3);
	}
	|T_STRING '.' T_STRING
	{
		$$ = relattr_node($1, $3);
	}
	| T_STRING
	{
		$$ = relattr_node(NULL,$1);
	}
	;

non_mt_relation_list
	: relation ',' non_mt_relation_list
	{
		$$ = prepend($1, $3);
	}
	| relation
	{
		$$ = list_node($1);
	}
	;

relation
	: T_STRING
	{
		$$ = relation_node($1);
	}
	;

opt_where_clause
	: T_WHERE non_mt_cond_list
	{
		$$ = $2;
	}
	| nothing
	{
		$$ = NULL;
	}
	;

non_mt_cond_list
	: condition T_AND non_mt_cond_list
	{
		$$ = prepend($1, $3);
	}
	| condition
	{
		$$ = list_node($1);
	}
	;

condition
	: relattr op relattr_or_value
	{
		$$ = condition_node($1,$2,$3);
	}
	;

relattr_or_value
	: relattr
	{
		$$ = relattr_or_value_node($1,NULL);
	}
	| value
	{
		$$ = relattr_or_value_node(NULL,$1);
	}
	;

non_mt_value_list
	: non_mt_value_list ',' value
	{
		$$ = prepend($3, $1);
	}
	| value
	{
		$$ = list_node($1);
	}
	;

value
	:T_QSTRING
	{
		$$ = value_node(STRING,0,(void *) $1);
	}
	| T_INT
	{
		$$ = value_node(INT,0,(void *)&$1);
	}
	| '-' T_INT
	{
		$$ = value_node(INT,1,(void *)&$2);
	}
	| T_REAL
	{
		$$ = value_node(FLOAT,0, (void *)& $1);
	}
	| T_NULL
	{
		$$ = value_node(NUL,0,NULL);
	}
	;

op
	: T_LT
	{
		$$ = LT_OP;
	}
	| T_LE
	{
		$$ = LE_OP;
	}
	|T_GT
	{
		$$ = GT_OP;
	}
	| T_GE
	{
		$$ = GE_OP;
	}
	| T_EQ
	{
		$$ = EQ_OP;
	}
	| T_NE
	{
		$$ = NE_OP;
	}
	| T_LIKE
	{
		$$ = LIKE_OP;
	}
	| T_ISNULL
	{
		$$ = ISNULL_OP;
	}
	;
nothing
   	: 
   	;
%%

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
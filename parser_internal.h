/*
 * parser_internal.h: internal declarations for the REDBASE parser
 *
 * Authors: Dallan Quass
 *          Jan Jannink
 *
 * originally by: Mark McAuliffe, University of Wisconsin - Madison, 1991
 */

#ifndef PARSER_INTERNAL_H
#define PARSER_INTERNAL_H

#include "parser.h"

/*
 * use double for real
 */
typedef float real;

/*
 * the prompt
 */
#define PROMPT  "\n >> "

/*
 * all the available kinds of nodes
 */
typedef enum{
    N_CREATEDB,
    N_DROPDB,
    N_USEDB,
    N_CREATETABLE,
    N_DROPTABLE,
    N_SHOWTABLES,
    N_DESC,
    N_LOAD,
    N_SET,
    N_HELP,
    N_PRINT,
    N_QUERY,
    N_QUERYGATHER,
    N_QUERYGROUP,
    N_INSERT,
    N_DELETE,
    N_UPDATE,
    N_RELATTR,
    N_CONDITION,
    N_RELATTR_OR_VALUE,
    N_ATTRTYPE,
    N_VALUE,
    N_RELATION,
    N_STATISTICS,
    N_LIST,
    N_PRIMARYKEY,
    N_CHECK,
    N_EXPR,
    N_CREATEINDEX,
    N_DROPINDEX
} NODEKIND;

/*
 * structure of parse tree nodes
 */
typedef struct node{
   NODEKIND kind;

   union{
      /* SM component nodes */
      struct{
          char *dbname;
      } CREATEDB;
      struct {
          char *dbname;
      } DROPDB;
      struct{
          char *dbname;
      } USEDB;
      /* create table node */
      struct{
         char *relname;
         struct node *attrlist;
         char *primaryKey;
      } CREATETABLE;

      /* drop table node */
      struct{
         char *relname;
      } DROPTABLE;

      /* load node */
      struct{
         char *relname;
         char *filename;
      } LOAD;

      /* set node */
      struct{
         char *paramName;
         char *string;
      } SET;

      /* help node */
      struct{
         char *relname;
      } HELP;

      /* print node */
      struct{
         char *relname;
      } PRINT;

      /* QL component nodes */
      /* query node */
      struct{
         struct node *relattrlist;
         struct node *rellist;
         struct node *conditionlist;
      } QUERY;
      
      struct{
          int kind;
          struct node *relattr;
          struct node *relation;
          struct node *conditionlist;
      } QUERYGATHER;

      struct{
          struct node *relattrlist1;
          struct node *relation;
          struct node *relattrlist2;
          struct node *conditionlist;
      } QUERYGROUP;

      /* insert node */
      struct{
         char *relname;
         struct node *valuelist;
      } INSERT;

      /* delete node */
      struct{
         char *relname;
         struct node *conditionlist;
      } DELETE;

      /* update node */
      struct{
         char *relname;
         struct node *exprlist;
         struct node *conditionlist;
      } UPDATE;

      /* command support nodes */
      /* relation attribute node */
      struct{
         char *relname;
         char *attrname;
      } RELATTR;

      /* condition node */
      struct{
         struct node *lhsRelattr;
         CompOp op;
         struct node *rhsRelattr;
         struct node *rhsValue;
      } CONDITION;

      /* relation-attribute or value */
      struct{
         struct node *relattr;
         struct node *value;
      } RELATTR_OR_VALUE;

      /* <attribute, type> pair */
      struct{
         char *attrname;
         char *type;
         int value;
         int empty;
         struct node *checklist;
      } ATTRTYPE;

      /* <value, type> pair */
      struct{
         AttrType type;
         int  ival;
         real rval;
         char *sval;
      } VALUE;

      /* relation node */
      struct{
         char *relname;
      } RELATION;

      struct{
          char *relname;
      } DESC;

      /* list node */
      struct{
         struct node *curr;
         struct node *next;
      } LIST;
      struct{
          char *attrname;
          struct node *valuelist;
      } CHECK;
      struct{
          struct node *relattr;
          struct node *op1;
          struct node *op2;
          int op;
      } EXPR;
      struct{
          struct node *relation;
          struct node *relattr;
      } CREATEINDEX;
      struct{
          struct node *relation;
          struct node *relattr;
      } DROPINDEX;
   } u;
} NODE;


/*
 * function prototypes
 */
NODE *newnode(NODEKIND kind);
NODE *create_db_node(char *dbname);
NODE *drop_db_node(char *dbname);
NODE *use_db_node(char *dbname);
NODE *create_table_node(char *relname, NODE *attrlist);
NODE *drop_table_node(char *relname);
NODE *show_tables_node();
NODE *desc_node(char *relname);
NODE *query_node(NODE *relattrlist, NODE *rellist, NODE *conditionlist);
NODE *query_group_node(NODE *relattrlist1, NODE *relation, NODE *conditionlist, NODE *relattrlist2);
NODE *query_gather_node(int kind, NODE *relattr, NODE *relation,NODE *conditionlist);
NODE *insert_node(char *relname, NODE *valuelist);
NODE *delete_node(char *relname, NODE *conditionlist);
NODE *update_node(char *relname, NODE *exprlist, NODE *conditionlist);
NODE *primary_key_node(char *primaryKey);
NODE *attrtype_node(char *attrname, char *type, int value, int empty);
NODE *relattr_node(char *relname, char *attrname);
NODE *condition_node(NODE *lhsRelattr, CompOp op, NODE *rhsRelattrOrValue);
NODE *value_node(AttrType type, int sign, void *value);
NODE *relattr_or_value_node(NODE *relattr, NODE *value);
NODE *relation_node(char *relname);
NODE *list_node(NODE *n);
NODE *prepend(NODE *n, NODE *list);
NODE *combine(NODE *list1, NODE *list2);
NODE *check_node(char *relattr, NODE *valuelist);
NODE *attr_check_node(NODE *checklist);
NODE *expr_node(NODE *relattr, NODE *relorvalue1, NODE *relorvalue2,  int op);
NODE *create_index_node(NODE *relation, NODE *relattr);
NODE *drop_index_node(NODE *relation, NODE *relattr);
NODE *condition_node1(NODE *lhsRelattr, CompOp op);
int interp(NODE *n);
void reset_charptr();
void new_query();

#endif




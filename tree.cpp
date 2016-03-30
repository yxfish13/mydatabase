#include "parser_internal.h"
#include "main.h"
#include "stdlib.h"

#define MAXNODE	10000000

static NODE nodepool[MAXNODE];
static int nodeptr = 0;

void new_query(void)
{
    	nodeptr = 0;
    	reset_charptr();
}

NODE *create_db_node(char *dbname)
{
	NODE *n = newnode(N_CREATEDB);

	n->u.CREATEDB.dbname = dbname;

	return n;
}

NODE *drop_db_node(char *dbname)
{
	NODE *n = newnode(N_DROPDB);

	n->u.DROPDB.dbname = dbname;

	return n;
}

NODE *use_db_node(char *dbname)
{
	NODE *n = newnode(N_USEDB);

	n->u.USEDB.dbname = dbname;

	return n;
}

NODE *create_table_node(char *relname, NODE *attrlist)
{
	NODE *n = newnode(N_CREATETABLE);

	n->u.CREATETABLE.relname = relname;
	n->u.CREATETABLE.attrlist = attrlist;

	return n;
}

NODE *drop_table_node(char *relname)
{
	NODE *n = newnode(N_DROPTABLE);

	n->u.DROPTABLE.relname = relname;

	return n;
}

NODE *show_tables_node()
{
	NODE *n = newnode(N_SHOWTABLES);

	return n;
}

NODE *desc_node(char *relname)
{
	NODE *n = newnode(N_DESC);

	n->u.DESC.relname = relname;

	return n;
}

NODE *newnode(NODEKIND kind)
{
	NODE *n;

    	if(nodeptr == MAXNODE){
		exit(1);
    	}

    	n = nodepool + nodeptr;
    	++nodeptr;

    	n -> kind = kind;
    	return n;
}

NODE *query_node(NODE *relattrlist, NODE *rellist, NODE *conditionlist)
{
	NODE *n = newnode(N_QUERY);

	n->u.QUERY.relattrlist = relattrlist;
	n->u.QUERY.rellist = rellist;
	n->u.QUERY.conditionlist = conditionlist;

	return n;
}

NODE *query_gather_node(int kind, NODE *relattr, NODE *relation,NODE *conditionlist)
{
	NODE *n = newnode(N_QUERYGATHER);

	n->u.QUERYGATHER.kind = kind;
	n->u.QUERYGATHER.relattr = relattr;
	n->u.QUERYGATHER.relation = relation;
	n->u.QUERYGATHER.conditionlist = conditionlist;

	return n;
}

NODE *query_group_node(NODE *relattrlist1,NODE *relation, NODE *conditionlist, NODE *relattrlist2)
{
	NODE *n = newnode(N_QUERYGROUP);

	n->u.QUERYGROUP.relattrlist1 = relattrlist1;
	n->u.QUERYGROUP.relation = relation;
	n->u.QUERYGROUP.relattrlist2 = relattrlist2;
	n->u.QUERYGROUP.conditionlist = conditionlist;

	return n;
}

NODE *insert_node(char *relname, NODE *valuelist)
{
	NODE *n = newnode(N_INSERT);

	n->u.INSERT.relname = relname;
	n->u.INSERT.valuelist = valuelist;

	return n;
}

NODE *delete_node(char *relname, NODE *conditionlist)
{
	NODE *n = newnode(N_DELETE);

	n->u.DELETE.relname = relname;
	n->u.DELETE.conditionlist = conditionlist;

	return n;
}

NODE *update_node(char *relname, NODE *exprlist, NODE *conditionlist)
{
	NODE *n = newnode(N_UPDATE);

	n->u.UPDATE.relname = relname;
	n->u.UPDATE.exprlist = exprlist;
	n->u.UPDATE.conditionlist = conditionlist;

	return n;
}

NODE *attrtype_node(char *attrname, char *type, int value, int empty)
{
	NODE *n = newnode(N_ATTRTYPE);

	n->u.ATTRTYPE.attrname = attrname;
	n->u.ATTRTYPE.type = type;
	n->u.ATTRTYPE.value = value;
	n->u.ATTRTYPE.empty = empty;

	return n;
}

NODE *primary_key_node(char *primaryKey)
{
	NODE *n = newnode(N_ATTRTYPE);

	n->u.ATTRTYPE.attrname = primaryKey;
	n->u.ATTRTYPE.value = -1; 

	return n;
}

NODE *relattr_node(char *relname, char *attrname)
{
	NODE *n = newnode(N_RELATTR);

	n->u.RELATTR.relname = relname;
	n->u.RELATTR.attrname = attrname;
	return n;
}

NODE *condition_node(NODE *lhsRelattr, CompOp op, NODE *rhsRelattrOrValue)
{
	NODE *n = newnode(N_CONDITION);

	n->u.CONDITION.lhsRelattr = lhsRelattr;
	n->u.CONDITION.op = op;
	n->u.CONDITION.rhsRelattr = rhsRelattrOrValue->u.RELATTR_OR_VALUE.relattr;
	n->u.CONDITION.rhsValue = rhsRelattrOrValue->u.RELATTR_OR_VALUE.value;

	return n;
}

NODE *condition_node1(NODE *lhsRelattr, CompOp op)
{
	NODE *n = newnode(N_CONDITION);

	n->u.CONDITION.lhsRelattr = lhsRelattr;
	n->u.CONDITION.op = op;
//	n->u.CONDITION.rhsRelattr = rhsRelattrOrValue->u.RELATTR_OR_VALUE.relattr;
//	n->u.CONDITION.rhsValue = rhsRelattrOrValue->u.RELATTR_OR_VALUE.value;

	return n;
}

NODE *value_node(AttrType type, int sign, void *value)
{
	NODE *n = newnode(N_VALUE);

	n->u.VALUE.type = type;
	switch(type){
		case INT:
			n->u.VALUE.ival = *(int *)value;
			if(sign)
				n->u.VALUE.ival = -n->u.VALUE.ival;
			break;
		case FLOAT:
			n->u.VALUE.rval = *(float *)value;
			break;
		case STRING:
			n->u.VALUE.sval = (char *)value;
			break;
	}

	return n;
}

NODE *relattr_or_value_node(NODE *relattr, NODE *value)
{
	NODE *n = newnode(N_RELATTR_OR_VALUE);

	n->u.RELATTR_OR_VALUE.relattr = relattr;
	n->u.RELATTR_OR_VALUE.value = value;

	return n;
}

NODE *relation_node(char *relname)
{
	NODE *n = newnode(N_RELATION);

	n->u.RELATION.relname = relname;
	return n;
}

NODE *list_node(NODE *n)
{
	NODE *list = newnode(N_LIST);

	list->u.LIST.curr = n;
	list->u.LIST.next = NULL;

	return  list;
}

NODE *prepend(NODE *n, NODE *list)
{
	NODE *newlist = newnode(N_LIST);

	newlist->u.LIST.curr = n;
	newlist->u.LIST.next = list;

	return newlist;
}

NODE *combine(NODE *list1, NODE *list2)
{
	NODE *tmp = list1;

	 while(list1->u.LIST.next != NULL)
	 	list1 = list1->u.LIST.next;
	 list1->u.LIST.next = list2;

	 return tmp;
}


NODE *check_node(char *relattr, NODE *valuelist)
{
	NODE *n = newnode(N_CHECK);

	n->u.CHECK.attrname = relattr;
	n->u.CHECK.valuelist = valuelist;

	return n;
}

NODE *attr_check_node(NODE *checklist)
{
	NODE *n = newnode(N_ATTRTYPE);

	n->u.ATTRTYPE.checklist = checklist;
	n->u.ATTRTYPE.value = -2;

	return n;
}

NODE *expr_node(NODE *relattr, NODE *relorvalue1, NODE *relorvalue2, int op)
{
	NODE *n = newnode(N_EXPR);

	n->u.EXPR.relattr = relattr;
	n->u.EXPR.op = op;
	n->u.EXPR.op1 = relorvalue1;
	n->u.EXPR.op2 = relorvalue2;

	return n;
}

NODE *create_index_node(NODE *relation, NODE *relattr)
{
	NODE *n = newnode(N_CREATEINDEX);

	n->u.CREATEINDEX.relation = relation;
	n->u.CREATEINDEX.relattr = relattr;

	return n;
}

NODE *drop_index_node(NODE *relation, NODE *relattr)
{
	NODE *n = newnode(N_DROPINDEX);

	n->u.DROPINDEX.relation = relation;
	n->u.DROPINDEX.relattr = relattr;

	return n;
}
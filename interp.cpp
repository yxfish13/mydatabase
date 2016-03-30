#include "parser_internal.h"
#include "string.h"
#include <string>

Value values[1000000];
Value valuelist[10][10];

int mk_attr_infos(NODE *list, int max, AttrInfo attrInfos[], char *primaryKey, int &nchecks, int valuenum[], char *attrnames[]);
void mk_rel_attr(NODE *node, RelAttr &relAttr);
void parse_type(char *type_string, AttrType *type);
int mk_rel_attrs(NODE *node, int max, RelAttr relattrs[]);
int mk_relations(NODE *list, int max, char *relations[]);
int mk_conditions(NODE *list, int max, Condition conditons[]);
int mk_exprs(NODE *list, int max, Expr exprs[]);
void mk_value(NODE *node, Value &value);
int mk_values(NODE *list, int max, Value valus[]);

#include "query.h"

extern QL_manager *pQlm;

int interp(NODE *n)
{
	switch(n -> kind){
               case N_CREATEDB:
               {
                      pQlm->CreateDB(n->u.CREATEDB.dbname);
                      break;
               }
               case N_DROPDB:
               {
                      pQlm->DropDB(n->u.DROPDB.dbname);
                      break;
               }
               case N_USEDB:
               {
                      pQlm->Use(n->u.USEDB.dbname);
                      break;
               }
               case N_CREATETABLE:
               {
                      int nattrs;
                      AttrInfo attrInfos[10];
                      char primaryKey[30];

                      int nchecks = 0;
                      char *attrnames[10];
                      int valuenum[10];

                      nattrs = mk_attr_infos(n->u.CREATETABLE.attrlist,10,attrInfos,primaryKey,nchecks, valuenum, attrnames);

                      pQlm->CreateTable(n->u.CREATETABLE.relname,nattrs,attrInfos,primaryKey,nchecks,attrnames,valuenum,valuelist);

                      break;
               }
               case N_CREATEINDEX:
               {
                      RelAttr relAttr;

                      mk_rel_attr(n->u.CREATEINDEX.relattr,relAttr);
                      pQlm->CreateIndex(n->u.CREATEINDEX.relation->u.RELATION.relname,relAttr);

                      break;
               }
               case N_DROPTABLE:
               {
                      pQlm->DropTable(n->u.DROPTABLE.relname);
                      break;
               }
               case N_DROPINDEX:
               {
                      RelAttr relAttr;

                      mk_rel_attr(n->u.CREATEINDEX.relattr,relAttr);
                      pQlm->DropIndex(n->u.CREATEINDEX.relation->u.RELATION.relname,relAttr);

                      break;
               }
               case N_SHOWTABLES:
               {
                      pQlm->Showtb();
                      break;
               }
               case N_DESC:
               {
                      pQlm->Desc(n->u.DESC.relname);
                      break;
               }
		case  N_QUERY:
		{
			int nRelAttrs = 0;
			RelAttr relAttrs[10];
			int nRelations = 0;
			char *relations[10];
			int nConditions = 0;
			Condition conditions[10];

			nRelAttrs = mk_rel_attrs(n->u.QUERY.relattrlist, 10, relAttrs);
			nRelations = mk_relations(n->u.QUERY.rellist, 10, relations);
			nConditions = mk_conditions(n->u.QUERY.conditionlist, 10, conditions);
                        if(relAttrs[0].relName)
                        {
                          if(!strcmp(relAttrs[0].relName ,"sum"))
                                pQlm->SelectGather(0,relAttrs[0],relations[0],nConditions, conditions);
                          else if(!strcmp(relAttrs[0].relName ,"avg"))
                                pQlm->SelectGather(1,relAttrs[0],relations[0],nConditions, conditions);
                          else if(!strcmp(relAttrs[0].relName ,"max"))
                                pQlm->SelectGather(2,relAttrs[0],relations[0],nConditions, conditions);
                          else if(!strcmp(relAttrs[0].relName ,"min"))
                                pQlm->SelectGather(3,relAttrs[0],relations[0],nConditions, conditions);
			  else pQlm->Select(nRelAttrs, relAttrs, nRelations, relations, nConditions, conditions);
                        } else pQlm->Select(nRelAttrs, relAttrs, nRelations, relations, nConditions, conditions);
			break;
		}
              case N_QUERYGROUP:
              {
                      int nRelAttrs1 = 0;
                      RelAttr relAttrs1[10];
                      int nRelAttrs2 = 0;
                      RelAttr relAttrs2[10];
                      char *relation;
                      int nConditions = 0;
                      Condition conditions[10];

                      nConditions = mk_conditions(n->u.QUERYGROUP.conditionlist, 10, conditions);

                      nRelAttrs1 = mk_rel_attrs(n->u.QUERYGROUP.relattrlist1, 10, relAttrs1);
                      nRelAttrs2 = mk_rel_attrs(n->u.QUERYGROUP.relattrlist2, 10, relAttrs2);
                      relation = n->u.QUERYGROUP.relation->u.RELATION.relname;


                      pQlm->SelectGroup(nRelAttrs1,relAttrs1,relation,nRelAttrs2,relAttrs2,nConditions, conditions);

                      break;
              }
              case N_INSERT:
              {
                        int nValues = 0;

                        nValues = mk_values(n->u.INSERT.valuelist, 10, values);

                        pQlm->Insert(n->u.INSERT.relname, nValues, values);
                        break;
              }
              case N_DELETE:
              {
                        int nConditions = 0;
                        Condition conditions[10];

                        nConditions = mk_conditions(n->u.DELETE.conditionlist,10,conditions);

                        pQlm->Delete(n->u.DELETE.relname,nConditions,conditions);
                        break;
              }
             case N_UPDATE:
              {
                        int nConditions = 0;
                        Condition conditions[10];

                        int nExprs = 0;
                        Expr exprs[10];

                        nExprs = mk_exprs(n->u.UPDATE.exprlist,10,exprs);

                        nConditions = mk_conditions(n->u.UPDATE.conditionlist,10,conditions);
                        pQlm->Update(n->u.UPDATE.relname,nExprs, exprs, nConditions, conditions);
                        break;
              }
	}
} 

int mk_attr_infos(NODE *list, int max, AttrInfo attrInfos[], char *primaryKey, int &nchecks, int valuenum[], char *attrnames[])
{
        int i;
        AttrType type;
        NODE *attr;
        NODE *check;

        for(i = 0; list != NULL; ++i, list = list -> u.LIST.next) {

            if(list->u.LIST.next == NULL)
            {
                    attr = list->u.LIST.curr;
                    if(attr->u.ATTRTYPE.value == -1){
                            memcpy(primaryKey , attr->u.ATTRTYPE.attrname, 30);
                            break;
                    }
                    else strcpy(primaryKey,"NoPrimaryKey");
            }

            attr = list->u.LIST.curr;
            if(attr->u.ATTRTYPE.value == -2)
            {
                    NODE *checklist = attr->u.ATTRTYPE.checklist;
                    i--;
                    for(nchecks = 0;checklist != NULL; ++nchecks, checklist = checklist->u.LIST.next){
                            check = checklist->u.LIST.curr;
                            attrnames[nchecks] = check->u.CHECK.attrname;
                            valuenum[nchecks] = mk_values(check->u.CHECK.valuelist, 10, valuelist[nchecks]);
                    }
                    continue;
            }
            parse_type(attr -> u.ATTRTYPE.type, &type);

            attrInfos[i].attrName = string(attr -> u.ATTRTYPE.attrname);
            attrInfos[i].attrType = type;
            attrInfos[i].notNull = attr->u.ATTRTYPE.empty;

            if(attr->u.ATTRTYPE.value == 0)
            {
                    switch(type){
                            case INT:
                                    attrInfos[i].attrLength = sizeof(int);
                                    break;
                            case FLOAT:
                                    attrInfos[i].attrLength = sizeof(float);
                                    break;
                    }
            }
            else 
                    attrInfos[i].attrLength = attr->u.ATTRTYPE.value;
        }

        return i;
}

void parse_type(char *type_string, AttrType *type)
{
        char c;

        sscanf(type_string, "%c", &c);

        switch(c){
                case 'i':
                        *type = INT;
                        break;
                case 'f':
                case 'r':
                        *type = FLOAT;
                        break;
                case 'v':
                        *type = STRING;
                        return;
                default:
                        return;
        }
}

int mk_rel_attrs(NODE *list, int max, RelAttr relAttrs[])
{
	int i;

   	for(i = 0; list != NULL; ++i, list = list -> u.LIST.next){
		mk_rel_attr(list->u.LIST.curr, relAttrs[i]);
   	}

   	return i;
}

void mk_rel_attr(NODE *node, RelAttr &relAttr)
{
	relAttr.relName = node->u.RELATTR.relname;
	relAttr.attrName = node->u.RELATTR.attrname;
}

int mk_relations(NODE *list, int max, char *relations[])
{
   	int i;
   	NODE *current;

  	 for(i = 0; list != NULL; ++i, list = list -> u.LIST.next){
		current = list -> u.LIST.curr;
      		relations[i] = current->u.RELATION.relname;
   	}

   	return i;
}

int mk_conditions(NODE *list, int max, Condition conditions[])
{
   	int i;
   	NODE *current;

   	for(i = 0; list != NULL; ++i, list = list -> u.LIST.next){
		current = list -> u.LIST.curr;
      		conditions[i].lhsAttr.relName = current->u.CONDITION.lhsRelattr->u.RELATTR.relname;
      		conditions[i].lhsAttr.attrName = current->u.CONDITION.lhsRelattr->u.RELATTR.attrname;
      		conditions[i].op = current->u.CONDITION.op;
      		if (current->u.CONDITION.rhsRelattr) {
         			conditions[i].bRhsIsAttr = 1;
         			conditions[i].rhsAttr.relName = current->u.CONDITION.rhsRelattr->u.RELATTR.relname;
        			conditions[i].rhsAttr.attrName =  current->u.CONDITION.rhsRelattr->u.RELATTR.attrname;
      		}
      		else {
        			conditions[i].bRhsIsAttr = 0;
         			mk_value(current->u.CONDITION.rhsValue, conditions[i].rhsValue);
     		 }
   	}

   	return i;
}

void mk_value(NODE *node, Value &value)
{
   	value.type = node->u.VALUE.type;
   	switch (value.type) {
      	case INT:
         		value.data = (void *)&node->u.VALUE.ival;
         		break;
      	case FLOAT:
         		value.data = (void *)&node->u.VALUE.rval;
         		break;
      	case STRING:
         		value.data = (void *)node->u.VALUE.sval;
        		break;
   	}
}

int mk_values(NODE *list, int max, Value values[])
{
        int i;
        for(i = 0;list != NULL;++i,list = list->u.LIST.next){
                mk_value(list->u.LIST.curr, values[i]);
        }

        return i;
}

int mk_exprs(NODE *list, int max, Expr exprs[])
{
        int i;
        NODE *current;

        for(i = 0; list != NULL; ++i, list = list -> u.LIST.next){
                current = list->u.LIST.curr;
                struct node *op1 = current->u.EXPR.op1;
                exprs[i].op = current->u.EXPR.op;
                if(op1->u.RELATTR_OR_VALUE.relattr) {
                      mk_rel_attr(op1->u.RELATTR_OR_VALUE.relattr,exprs[i].op1Attr);
                      exprs[i].op1IsAttr = 1;
                }
                else{
                      mk_value(op1->u.RELATTR_OR_VALUE.value, exprs[i].op1Value);
                      exprs[i].op1IsAttr = 0;
                }
                if(exprs[i].op > 0)
                {
                        struct node *op2 = current->u.EXPR.op2;
                          if(op2->u.RELATTR_OR_VALUE.relattr) {
                                mk_rel_attr(op2->u.RELATTR_OR_VALUE.relattr,exprs[i].op2Attr);
                                exprs[i].op2IsAttr = 1;
                            }
                        else{
                                mk_value(op2->u.RELATTR_OR_VALUE.value, exprs[i].op2Value);
                                exprs[i].op2IsAttr = 0;
                          }
              }
              mk_rel_attr(current->u.EXPR.relattr,exprs[i].attr);
        }

        return i;
}
#ifndef QUERY_H
#define QUERY_H
#include "parser.h"
#include "system_manage.h"
#include "record_manager.h"
#include <regex>
#include <iostream>
#include <string>
#include <map>
using namespace std;
class QL_manager
{
	Byte *pdata[10];
	RM_Manager &rmm;
	SM_Manager &smm;

	map<string,int> Mtotal;
	map<string,float> Msum;
	map<string,float> Mmax;
	map<string,float> Mmin;
	map<string,string> Mprinto;
	map<string,bool> hasIndex;
	map<string,map<int,bool>> Index_Int;
	int buffered[10];
	Byte *bufferdata[10][2000000];
	int checkValuekind;
	RC GetValue(int   nRelations, const char * const relations[],int offset,int length,AttrType attribute,const char *relName,Byte *&data);
	string GenString(char *a, int n){
	  int i=0; 
	  for(; i<n; i++)
	    if (a[i]==0)
	      break;
	  return string(a,i);
	}
	bool _Validate(const int op1, const int op2,CompOp comp_op)const;
 	bool _Validate(const float op1, const float op2,CompOp comp_op)const;
  	bool _Validate(const std::string &op1, const std::string &op2,CompOp comp_op)const;
  	bool _Validate(Byte* data1,Byte* data2,AttrType attrType1,AttrType attrType2,CompOp comp_op,int l1,int l2,bool notnull,bool notnull2);
  	bool checkValue(const char *relName,const char *attrName,Byte *data,int length,AttrType attrtype);
  	void load_index(const char *relName,const char *attrName);
  	void release_index(const char *relName,const char *attrName){
  		string Name=string(relName)+string(attrName);
		hasIndex[Name]=false;
	}
	bool flag;

	void SelectDFS(int nSelAttrs, const RelAttr selAttrs[], int   nRelations, const char * const relations[], int   nConditions, const Condition conditions[],int deep,int *offset,int *length,AttrType *attrType,bool *isnotnull); 
public:
	QL_manager(RM_Manager& rmm1,SM_Manager &smm1);
	~QL_manager();
	void CreateDB(const char *dbName);
	void DropDB(const char *dbName);
	void Use(const char *dbName);
	void Showtb();
	void CreateTable(const char *relName, int attrCount, AttrInfo *attributes, const char *primaryKey,int nchecks, const char *const attrnames[], const int valuenum[], Value valuelist[][10]);
	void DropTable(const char *relName);
	void Desc(const char *relName);
	void CreateIndex(const char *relName, const RelAttr &attr);
	void DropIndex(const char *relName, const RelAttr &attr);


	void Delete (const char *relName, int nConditions, const Condition conditions[]);
	void Select (int nSelAttrs, const RelAttr selAttrs[], int   nRelations, const char * const relations[], int   nConditions, const Condition conditions[]);   
	void Insert (const char *relName, int nValues, const Value values[]);
	void Update(const char *relname, int nExprs, const Expr exprs[], int nConditions, const Condition conditions[]);
	void SelectLike(int nSelAttrs, const RelAttr selAttrs[], int nRelations, const char * const relations[], const RelAttr &selAttr, const char *cond);
	void SelectGather(int kind, const RelAttr &selAttr, const char *relation, int   nConditions=0, const Condition conditions[]=NULL);
	void SelectGroup(int nSelAttrs, const RelAttr selAttrs[],const char*  relation, int nCondAttrs, const RelAttr condAttrs[], int   nConditions=0, const Condition conditions[]=NULL);
};
#endif
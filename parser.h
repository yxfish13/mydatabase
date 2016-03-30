#ifndef PARSER_H
#define PARSER_H

#include "system_manage.h"
#include "record_manager.h"
#include <iostream>
#include <sstream>
//#include  "main.h"

//struct AttrInfo{
//                char     *attrName;   /* attribute name       */
//               AttrType attrType;    /* type of attribute    */
//                int      attrLength;  /* length of attribute  */
//                int     empty; 
//};

struct RelAttr{
	char *relName;
	char *attrName;
};



struct Condition{
	RelAttr lhsAttr;
	CompOp op;
	int      bRhsIsAttr; 
    	RelAttr  rhsAttr;    
    	Value    rhsValue;
};

struct Expr{
                RelAttr attr;
                int op;
                int op1IsAttr;
                RelAttr op1Attr;
                Value op1Value;
                int op2IsAttr;
                RelAttr op2Attr;
                Value op2Value;
};

class QL_manager;

void runParser(QL_manager &qlm);
void MyParse(std::istream &Input, SM_Manager &smm);

#endif

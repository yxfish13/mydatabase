#include "query.h"
#include <iostream>
#include <cstring>
//using namespace std;
const char *Nullstring="null";
const char *TestforNorelName="TestforNorelName";
#define check_relName(relName) { int of1,len1;AttrType attrtype1;smm.GetAttrInfo((char*)relName,TestforNorelName,of1,len1,attrtype1);\
	if(of1==-2){\
		cout<<(char*)relName<<" NOT relName"<<endl;return;\
	}\
}
#define check_relattr(relName,attrName){ int of1,len1;AttrType attrtype1;smm.GetAttrInfo((char*)relName,(char *)attrName,of1,len1,attrtype1);\
	if(of1==-2){\
		cout<<(char*)relName<<" NOT relName"<<endl;return;\
	}\
	if(of1==-1){\
		cout<<(char*)relName<<"."<<(char*)attrName<<" NOT attrName"<<endl;return;\
	}\
}
QL_manager::QL_manager(RM_Manager& rmm1,SM_Manager &smm1):rmm(rmm1),smm(smm1){
	flag=false;
}
void QL_manager::CreateDB(const char *dbName){
	smm.CreateDB(string(dbName));
}

void QL_manager::DropDB (const char *dbName){
	smm.DropDB(string (dbName));
}
void QL_manager::Use (const char *dbName){
	if (flag){
		smm.CloseDb();
	}
	smm.OpenDb( dbName);
	flag=true;
}
void QL_manager::Showtb(){
	if (!flag){
		cout<<"please open a database first!"<<endl;
		return;
	}
	smm.ShowTable();
}
void QL_manager::CreateTable(const char *relName, int attrCount, AttrInfo *attributes, const char *primaryKey,int nchecks, const char *const attrnames[], const int valuenum[], Value valuelist[][10]){
	if (!flag){
		cout<<"please open a database first!"<<endl;
		return;
	}
	//cout<<"adf"<<endl;
	//cout<<key<<endl;
	//cout<<attrCount<<endl;
	//for (int i=0;i<attrCount;i++) cout<<attributes[i].notNull<<endl;
	smm.CreateTable (relName,                // Create relation
		  attrCount,
		  attributes,
		  nchecks,attrnames,valuenum,valuelist,primaryKey);
}
void QL_manager::DropTable(const char *relName){
	if (!flag){
		cout<<"please open a database first!"<<endl;
		return;
	}
	smm.DropTable(relName);
}
void QL_manager::Desc(const char *relName){
	if (!flag){
		cout<<"please open a database first!"<<endl;
		return;
	}
	smm.Print(relName);
}
void QL_manager::Delete (const char *relName, int nConditions, const Condition conditions[]){
	if (!flag){
		cout<<"please open a database first!"<<endl;
		return;
	}
	RM_FileHandle delete1_fh;
	smm.GetFh(relName,delete1_fh);
	int offset[100],length[100];
	AttrType attrType[100];
	for (int i=0;i<nConditions;i++)
		smm.GetAttrInfo(relName,conditions[i].lhsAttr.attrName,offset[i],length[i],attrType[i]);
	RM_FileScan delete_scanner(delete1_fh, attrType[0], length[0], offset[0], EQ_OP, 
                                (void*)conditions[0].rhsValue.data, length[0]);
	bool isnotnull[100];
	for (int i=0;i<nConditions;i++){
		isnotnull[i]=smm.checkNotNull(relName,conditions[i].lhsAttr.attrName);
	}
  	RC ret;
  	RM_Record record;
  	RID rid;
  	while( (ret=delete_scanner.GetNextRec_NoComp(record)) != NOT_FOUND ){
  		Byte* mem;
	  	record.GetData(mem);
	  	record.GetRid(rid);
	  	for (int i=0;i<nConditions;i++){
	 	 			Byte *data1=mem+offset[i];
					Byte *data2=(Byte*)conditions[i].rhsValue.data;
					flag = flag && _Validate(data1,data2,attrType[i],conditions[i].rhsValue.type,conditions[i].op,length[i],strlen((char*)conditions[i].rhsValue.data),isnotnull[i],true);
		}
  		bool flag=true;
  		if (flag){
    		record.GetRid(rid);
   	 		delete1_fh.DeleteRec(rid);
   	 	}
  	}
	rmm.CloseFile(delete1_fh);
}
void QL_manager::Select (int nSelAttrs, const RelAttr selAttrs1[], int   nRelations, const char * const relations[], int   nConditions, const Condition conditions[]){
//return;
	//cout<<selAttrs1[0].relName<<endl;
	//cout<<selAttrs1[0].attrName<<endl;
	//cout<<"fuck"<<endl;
	//return;
	if (!flag){
		cout<<"please open a database first!"<<endl;
		return;
	}
	const RelAttr * selAttrs=selAttrs1;
	RelAttr sel_Temp[1000];
	if (selAttrs[0].attrName[0]=='*') nSelAttrs=0;
    for (int i=0;i<nRelations;i++){
			check_relName(relations[i]);
	}
	if (nSelAttrs==0){
		for (int i=0;i<nRelations;i++){
			check_relName(relations[i]);
			RM_FileHandle * attributefh_addr;
			smm.GetattributeHandle(attributefh_addr);
			RM_FileScan attribute_scanner(*attributefh_addr, STRING, RELNAME_LENGTH, 0, EQ_OP, 
                                (void*)relations[i], strlen(relations[i]));
			  RC ret;
			  RM_Record record;
			  Byte *mem;
			  while( (ret=attribute_scanner.GetNextRec(record)) != NOT_FOUND ){
			  //  record.GetRid(rid);
			  //  attribute_fh.DeleteRec(rid);
			    record.GetData(mem);
			    sel_Temp[nSelAttrs].relName=(char*)relations[i];
			    sel_Temp[nSelAttrs].attrName=(char *)(mem+RELNAME_LENGTH);
			    nSelAttrs++;
			    //cout<<GenString((char *)(mem+RELNAME_LENGTH),ATTRNAME_LENGTH)<<"("<<*(int*)(mem+RELNAME_LENGTH+ATTRNAME_LENGTH+8)<<")"<<*(int*)(mem+RELNAME_LENGTH+ATTRNAME_LENGTH+4)<<endl;
			  }
		}
		selAttrs=sel_Temp;
	}
	//const RelAttr * selAttrs=selAttrs1;
	if(nRelations==1){
			int offset[100],length[100];
			AttrType attrType[100];
			bool isnotnull[100];
			for (int i=0;i<nConditions;i++){
				smm.GetAttrInfo(relations[0],conditions[i].lhsAttr.attrName,offset[i*2+0],length[i*2],attrType[i*2+0]);
				check_relattr(relations[0],conditions[i].lhsAttr.attrName);
				isnotnull[i*2]=smm.checkNotNull(relations[0],conditions[i].lhsAttr.attrName);
				if (conditions[i].bRhsIsAttr){
					smm.GetAttrInfo(relations[0],conditions[i].rhsAttr.attrName,offset[i*2+1],length[i*2+1],attrType[i*2+1]);
					isnotnull[i*2+1]=smm.checkNotNull(relations[0],conditions[i].rhsAttr.attrName);
				}
			}
			for (int i = nConditions*2 ; i < nConditions*2 + nSelAttrs ; i++ ){
				smm.GetAttrInfo(relations[0],selAttrs[i-nConditions*2].attrName,offset[i],length[i],attrType[i]);
				check_relattr(relations[0],selAttrs[i-nConditions*2].attrName);
				isnotnull[i]=smm.checkNotNull(relations[0],selAttrs[i-nConditions*2].attrName);
				//cout<<isnotnull[i]<<" "<<relations[0]<<" "<<selAttrs[i-nConditions*2].attrName<<endl;
			}
			RM_FileHandle S1_fh;
			smm.GetFh(relations[0],S1_fh);
			RM_FileScan S1_scanner(S1_fh, attrType[nConditions], length[nConditions], offset[nConditions], EQ_OP, 
		                                NULL, 0);
		  	RC ret;
  			RM_Record record;
  			while( (ret=S1_scanner.GetNextRec_NoComp(record)) != NOT_FOUND ){
  				//cout<<"123"<<endl;
	  			record.GetData(pdata[0]);
	   	 		bool flag=true;
	   	 		for (int i=0;i<nConditions;i++){
	   	 			Byte pdata1[500];
					Byte pdata2[500];
					Byte *data1=pdata1;
					Byte *data2=pdata2;
					GetValue(nRelations,relations,offset[i*2+0],length[i*2],attrType[i*2+0],relations[0],data1);
					if (conditions[i].bRhsIsAttr)
						GetValue(nRelations,relations,offset[i*2+1],length[i*2+1],attrType[i*2+1],relations[0],data2);
					else
					{
						attrType[i*2+1]=conditions[i].rhsValue.type;
						length[i*2+1]=length[i*2];
						isnotnull[i*2+1]=true;
						data2=(Byte*) conditions[i].rhsValue.data;
					}
					flag = flag && _Validate(data1,data2,attrType[i*2],attrType[i*2+1],conditions[i].op,length[i*2],length[i*2+1],isnotnull[i*2],isnotnull[i*2+1]);
	   	 		}
	   	 		if (flag){
	   	 			Byte *data;
	   	 			for (int i=0;i<nSelAttrs;i++){
	   	 				GetValue(nRelations,relations,offset[i+nConditions*2],length[i+nConditions*2],attrType[i+nConditions*2],relations[0],data);
	   	 				if (i) cout<<",";
	   	 				else cout<<"(";
	   	 				if (!isnotnull[i+nConditions*2]&&data[length[i+nConditions*2]]){
	   	 					cout<<Nullstring;
	   	 				}
	   	 				else{
		   	 				if (attrType[i+nConditions*2]==INT) cout<<*(int *)data;
		   	 				if (attrType[i+nConditions*2]==FLOAT) cout<<*(float *)data;
		   	 				if (attrType[i+nConditions*2]==STRING) for (int j=0;j<length[i+nConditions*2];j++) cout<<(char)data[j];
	   	 				}
	   	 			}
	   	 			cout<<")"<<endl;
	   	 		}
		  	}
			rmm.CloseFile(S1_fh);
	}else{
			int offset[100],length[100];
			AttrType attrType[100];
			bool isnotnull[100];
			for (int i=0;i<nConditions;i++){
				check_relattr(conditions[i].lhsAttr.relName,conditions[i].lhsAttr.attrName);
				smm.GetAttrInfo(conditions[i].lhsAttr.relName,conditions[i].lhsAttr.attrName,offset[i*2+0],length[i*2],attrType[i*2+0]);
				isnotnull[2*i]=smm.checkNotNull(conditions[i].lhsAttr.relName,conditions[i].lhsAttr.attrName);
				if (conditions[i].bRhsIsAttr){
					smm.GetAttrInfo(conditions[i].rhsAttr.relName,conditions[i].rhsAttr.attrName,offset[i*2+1],length[i*2+1],attrType[i*2+1]);
					isnotnull[2*i+1]=smm.checkNotNull(conditions[i].lhsAttr.relName,conditions[i].rhsAttr.attrName);
				}
			}
			for (int i = nConditions*2 ; i < nConditions*2 + nSelAttrs ; i++ ){
				check_relattr(selAttrs[i-nConditions*2].relName,selAttrs[i-nConditions*2].attrName);
				smm.GetAttrInfo(selAttrs[i-nConditions*2].relName,selAttrs[i-nConditions*2].attrName,offset[i],length[i],attrType[i]);
				isnotnull[i]=smm.checkNotNull(selAttrs[i-nConditions*2].relName,selAttrs[i-nConditions*2].attrName);
			}
			memset(buffered,0,sizeof(buffered));
			SelectDFS(nSelAttrs, selAttrs, nRelations, relations, nConditions,conditions,0,offset,length,attrType,isnotnull);
	}
}
RC QL_manager::GetValue(int   nRelations, const char * const relations[],int offset,int length,AttrType attribute,const char *relName,Byte *&data){
	for (int i=0;i<nRelations;i++){
		if (string(relations[i])==string(relName)){
			data = pdata[i]+offset;
		//	if (attribute==0)
		//	cout<<"in get value :"<<*(int*)data<<" "<<*(int*)pdata[i]<<endl;
		}
	}
	return OK;
}
void QL_manager::Insert (const char *relName, int nkValues, const Value kvalues[]){
	if (!flag){
		cout<<"please open a database first!"<<endl;
		return;
	}
	//return;
	//cout<<"in"<<endl;
	RM_FileHandle Insert_fh;
	smm.GetFh(relName,Insert_fh);
	int offset[100],length[100];
	AttrType attrType[100];
	int nValues=smm.Getoffset(relName,offset,length);
	Byte pData[500];
  	Byte *nowp=pData;
  	char attrNames[100][100];
  	memset(attrNames,0,sizeof(attrNames));
  	bool ischecked[100];
  	bool isnotnull[100];
  	smm.GetAttrName(relName,attrNames,ischecked,isnotnull,attrType);
  	check_relName(relName);
	int offset_key,length_key;
	AttrType attrType_key;
  	bool haskey=smm.hasKey(relName,offset_key,length_key,attrType_key);
	map<int,bool>  key_int;
	map<string,bool>  key_string;
	if (haskey){
		if(attrType_key==STRING){
			key_string.clear();

			RM_FileScan delete_scanner(Insert_fh, attrType_key, length[0], offset[0], EQ_OP, 
	                                NULL, length[0]);
		  	RC ret;
		  	RM_Record record,rec;
		  	while( (ret=delete_scanner.GetNextRec_NoComp(record)) != NOT_FOUND ){
		  		bool flag=true;
		  		Byte* mem;
		  		RID rid;
		  		record.GetData(mem);
		  		key_string[GenString((char*)mem+offset_key,length_key)]=true;
		  	}
		} else{
			key_int.clear();
			RM_FileScan delete_scanner(Insert_fh, attrType_key, length[0], offset[0], EQ_OP, 
	                                NULL, length[0]);
		  	RC ret;
		  	RM_Record record,rec;
		  	while( (ret=delete_scanner.GetNextRec_NoComp(record)) != NOT_FOUND ){
		  		bool flag=true;
		  		Byte* mem;
		  		RID rid;
		  		record.GetData(mem);
		  		key_int[*((int*)(mem+offset_key))]=true;
		  	}
		}
	}


  	//cout<<nValues<<endl;
  	//cout<<nkValues<<endl;
  	hasIndex.clear();
	for(int i=0;i<nValues;i++)
		for (int j=0,ls=strlen(attrNames[i]);j<ls;j++)
			if(attrNames[i][j]=='_'){
				string A=string(attrNames[i],j);
				string B=string(attrNames[i]+j+1,ls-j-1);
				int offset_idx,length_idx;
				AttrType attrType_idx;
				//cout<<A<<'_'<<B<<endl;
				if(smm.hasIndex(A.c_str(),B.c_str(),offset_idx,length_idx,attrType_idx)){
					if(attrType_idx!=STRING)
					load_index(A.c_str(),B.c_str());
				}
		}
  	for (int t=0;t<nkValues/nValues;t++){
		for (int i=0;i<nValues;i++){
			nowp=pData;
			if (attrType[i]!=kvalues[nkValues-(t*nValues+i)-1].type&&kvalues[nkValues-(t*nValues+i)-1].type!=NUL){
				cout<<attrNames[i]<<" 类型错误 : ";
				if (attrType[i]==INT)cout<<"INT"<<endl;
				if (attrType[i]==STRING)cout<<"STRING"<<endl;
				rmm.CloseFile(Insert_fh);
				return;
			}
			if (kvalues[nkValues-(t*nValues+i)-1].type==INT){
				memcpy(nowp+offset[i], kvalues[nkValues-(t*nValues+i)-1].data , 4);
				if (ischecked[i]){
					if (!checkValue(relName,attrNames[i],(Byte *)kvalues[nkValues-(t*nValues+i)-1].data,4,kvalues[nkValues-(t*nValues+i)-1].type)){
						cout<<attrNames[i]<<" "<<*(int *)kvalues[nkValues-(t*nValues+i)-1].data;
						if(checkValuekind)cout<<"外键约束缺失"<<endl;else cout<<"枚举约束失败"<<endl;
						rmm.CloseFile(Insert_fh);
						return;
					}
				}
			}
			if (kvalues[nkValues-(t*nValues+i)-1].type==FLOAT){
				memcpy(nowp+offset[i], kvalues[nkValues-(t*nValues+i)-1].data , 4);
				if (ischecked[i]){
					if (!checkValue(relName,attrNames[i],(Byte *)kvalues[nkValues-(t*nValues+i)-1].data,4,kvalues[nkValues-(t*nValues+i)-1].type)){
						cout<<attrNames[i]<<" "<<*(float *)kvalues[nkValues-(t*nValues+i)-1].data;
						if(checkValuekind)cout<<"外键约束缺失"<<endl;else cout<<"枚举约束失败"<<endl;
						rmm.CloseFile(Insert_fh);
						return;
					}
				}
			}
			if (kvalues[nkValues-(t*nValues+i)-1].type==STRING){
				if (ischecked[i]){
					if (!checkValue(relName,attrNames[i],(Byte *)kvalues[nkValues-(t*nValues+i)-1].data,strlen((char*)kvalues[nkValues-(t*nValues+i)-1].data),kvalues[nkValues-(t*nValues+i)-1].type)){
						cout<<attrNames[i]<<" "<<(char *)kvalues[nkValues-(t*nValues+i)-1].data;
						if(checkValuekind)cout<<"外键约束缺失"<<endl;else cout<<"枚举约束失败"<<endl;
						rmm.CloseFile(Insert_fh);
						return;
					}
				}
				for (int j=0,ls=strlen((char*)kvalues[nkValues-(t*nValues+i)-1].data);j<length[i];j++){
					//memcpy(pData+offset[i], values[i].data , length[i]);
					if (j<ls)
						nowp[offset[i]+j]=((char*)kvalues[nkValues-(t*nValues+i)-1].data)[j];
					else
						nowp[offset[i]+j]=0;
				}
			}
			if (kvalues[nkValues-(t*nValues+i)-1].type==NUL){
				if(isnotnull[i]){
					cout<<"can not set null:"<<attrNames[i]<<endl;
					rmm.CloseFile(Insert_fh);
					return;
				}
				nowp[offset[i]+length[i]]=1;
			}else{
				if(!isnotnull[i])nowp[offset[i]+length[i]]=0;
			}
		}
		//cout<<"insert "<<endl;
		RID rid;
		//cout<<*(int*)pData<<endl;
		if (haskey){
		  						Byte * now=pData+offset_key;
		  						if(attrType_key==STRING){
		  							if(key_string[GenString((char*)now,length_key)]){
		  								cout<<"主键重复"<<endl;
										rmm.CloseFile(Insert_fh);
										return;
		  							}
		  							key_string[GenString((char*)now,length_key)]=true;
		  						}
		  						else{
									if(key_int[*((int*)now)]){
		  								cout<<"主键重复"<<endl;
										rmm.CloseFile(Insert_fh);
										return;
		  							}	
									key_int[*((int*)now)]=true;
								}
		}
		Insert_fh.InsertRec(pData, rid);
		//cout<<"now "<<t<<endl;
	}
	rmm.CloseFile(Insert_fh);
}
void QL_manager::Update(const char *relName, int nExprs, const Expr exprs[], int nConditions, const Condition conditions[]){
						//const char *relName, const RelAttr &updAttr, const int isValue, const RelAttr &rhsRelAttr, const Value &rhsValue, int nConditions, const Condition conditions[]){
	if (!flag){
		cout<<"please open a database first!"<<endl;
		return;
	}
	check_relName(relName);
	RM_FileHandle delete1_fh;
	smm.GetFh(relName,delete1_fh);
	int offset[100],length[100];
	AttrType attrType[100];
	bool isnotnull_c[100];
	for (int i=0;i<nConditions;i++){
		check_relattr(relName,conditions[i].lhsAttr.attrName);
		smm.GetAttrInfo(relName,conditions[i].lhsAttr.attrName,offset[i],length[i],attrType[i]);
		isnotnull_c[i]=smm.checkNotNull(relName,conditions[i].lhsAttr.attrName);
	}
	int offset_key,length_key;
	AttrType attrType_key;
	bool haskey=smm.hasKey(relName,offset_key,length_key,attrType_key);
	map<int,bool>  key_int;
	map<string,bool>  key_string;
	if (haskey){
		if(attrType_key==STRING){
			key_string.clear();

			RM_FileScan delete_scanner(delete1_fh, attrType[0], length[0], offset[0], EQ_OP, 
	                                (void*)conditions[0].rhsValue.data, length[0]);
		  	RC ret;
		  	RM_Record record,rec;
		  	while( (ret=delete_scanner.GetNextRec_NoComp(record)) != NOT_FOUND ){
		  		bool flag=true;
		  		Byte* mem;
		  		RID rid;
		  		record.GetData(mem);
		  		key_string[GenString((char*)mem+offset_key,length_key)]=true;
		  	}
		} else{
			key_int.clear();
			RM_FileScan delete_scanner(delete1_fh, attrType[0], length[0], offset[0], EQ_OP, 
	                                (void*)conditions[0].rhsValue.data, length[0]);
		  	RC ret;
		  	RM_Record record,rec;
		  	while( (ret=delete_scanner.GetNextRec_NoComp(record)) != NOT_FOUND ){
		  		bool flag=true;
		  		Byte* mem;
		  		RID rid;
		  		record.GetData(mem);
		  		key_int[*((int*)(mem+offset_key))]=true;
		  	}
		}
	}


	hasIndex.clear();
	for(int i=0;i<nExprs;i++)
		for (int j=0,ls=strlen(exprs[i].attr.attrName);j<ls;j++)
			if(exprs[i].attr.attrName[j]=='_'){
				string A=string(exprs[i].attr.attrName,j);
				string B=string(exprs[i].attr.attrName+j+1,ls-j-1);
				int offset_idx,length_idx;
				AttrType attrType_idx;
				if(smm.hasIndex(A.c_str(),B.c_str(),offset_idx,length_idx,attrType_idx)){
					if(attrType_idx!=STRING)
					load_index(A.c_str(),B.c_str());
				}
		}



	//for(int t=0,t<nExprs;t++){
	//	const RelAttr &updAttr=exprs[t].attr;
		RM_FileScan delete_scanner(delete1_fh, attrType[0], length[0], offset[0], EQ_OP, 
	                                (void*)conditions[0].rhsValue.data, length[0]);
	  	RC        ret;
	  	RM_Record record,rec;

				  	int offset_up[100],length_up[100];
					AttrType attrType_up[100];  	bool ischecked[100];bool isnotnull[100];
					for(int t=0;t<nExprs;t++) {
						check_relattr(relName,exprs[t].attr.attrName);
				  		smm.GetAttrInfo(relName,exprs[t].attr.attrName,offset_up[t],length_up[t],attrType_up[t]);
				  		ischecked[t]=smm.isChecked(relName,exprs[t].attr.attrName);
				  		isnotnull[t]=smm.checkNotNull(relName,exprs[t].attr.attrName);
				  	}
	  	while( (ret=delete_scanner.GetNextRec_NoComp(record)) != NOT_FOUND ){
	  		bool flag=true;
	  		Byte* mem;
	  		RID rid;
	  		record.GetData(mem);
	  		record.GetRid(rid);
	  		for (int i=0;i<nConditions;i++){
		   	 			Byte *data1=mem+offset[i];
						Byte *data2=(Byte*)conditions[i].rhsValue.data;
						flag = flag && _Validate(data1,data2,attrType[i],conditions[i].rhsValue.type,conditions[i].op,length[i],strlen((char*)conditions[i].rhsValue.data),isnotnull_c[i],true);
			//			cout<<*(int*)data1<<" "<<*(int*)data2<<" "<<attrType[i]<<" "<<conditions[i].rhsValue.type<<" "<<conditions[i].op<<" "<<length[i]<<" "<<strlen((char*)conditions[i].rhsValue.data)<<endl;
		   	}
		   	//cout<<"now "<<flag<<endl;
	  		if (flag){
	  			for(int t=0;t<nExprs;t++){
	  				if (haskey&&offset_key==offset_up[t]){
		  						Byte * pre=mem+offset_key;
		  						if(attrType_key==STRING){
		  							key_string[GenString((char*)pre,length_key)]=false;
		  						}
		  						else{
									key_int[*((int*)pre)]=false;
								}
					}
		  			if (attrType_up[t]==INT){
		  				if (exprs[t].op==0){
		  					if (exprs[t].op1Value.type!=INT){
		  						cout<<"update must be INT"<<endl;
		  						rmm.CloseFile(delete1_fh);
									return;
		  					}
		  					//if (exprs[t])
							memcpy(mem+offset_up[t], exprs[t].op1Value.data , 4);
							if (ischecked[t]){
								if (!checkValue(relName,exprs[t].attr.attrName,(Byte *)exprs[t].op1Value.data,4,attrType_up[t])){
									if(checkValuekind)cout<<"外键约束缺失"<<endl;else cout<<"枚举约束失败"<<endl;
									rmm.CloseFile(delete1_fh);
									return;
								}
							}

						}
						else{
							int x=*(int*)(mem+offset_up[t]);
							if (exprs[t].op==1) x=x+(*(int*)(exprs[t].op2Value.data));
							if (exprs[t].op==2) x=x-(*(int*)(exprs[t].op2Value.data));
							if (exprs[t].op==3) x=x*(*(int*)(exprs[t].op2Value.data));
							if (exprs[t].op==4) x=x/(*(int*)(exprs[t].op2Value.data));
							memcpy(mem+offset_up[t], &x , 4);
							if (ischecked[t]){
								if (!checkValue(relName,exprs[t].attr.attrName,(Byte *)&x,4,attrType_up[t])){
									if(checkValuekind)cout<<"外键约束缺失"<<endl;else cout<<"枚举约束失败"<<endl;
									rmm.CloseFile(delete1_fh);
									return;
								}
							}
						}
					}
					if (attrType_up[t]==FLOAT){
						if (exprs[t].op==0){
							memcpy(mem+offset_up[t], exprs[t].op1Value.data , 4);
							if (ischecked[t]){
								if (!checkValue(relName,exprs[t].attr.attrName,(Byte *)exprs[t].op1Value.data,4,attrType_up[t])){
									if(checkValuekind)cout<<"外键约束缺失"<<endl;else cout<<"枚举约束失败"<<endl;
									rmm.CloseFile(delete1_fh);
									return;
								}
							}
						}
						else{
							float x=*(float*)mem+offset_up[t];
							if (exprs[t].op==1) x=x+(*(float*)(exprs[t].op2Value.data));
							if (exprs[t].op==2) x=x-(*(float*)(exprs[t].op2Value.data));
							if (exprs[t].op==3) x=x*(*(float*)(exprs[t].op2Value.data));
							if (exprs[t].op==4) x=x/(*(float*)(exprs[t].op2Value.data));
							memcpy(mem+offset_up[t], &x , 4);
							if (ischecked[t]){
								if (!checkValue(relName,exprs[t].attr.attrName,(Byte *)&x,4,attrType_up[t])){
									if(checkValuekind)cout<<"外键约束缺失"<<endl;else cout<<"枚举约束失败"<<endl;
									rmm.CloseFile(delete1_fh);
									return;
								}
							}
						}
					}
					if (attrType_up[t]==STRING){
						if (exprs[t].op) {cout<<"string can not be calced"<<endl; rmm.CloseFile(delete1_fh);return ;}
						if (exprs[t].op1Value.type!=STRING){
		  						cout<<"update must be string"<<endl;
		  						rmm.CloseFile(delete1_fh);
									return;
		  					}
						if (ischecked[t]){
								if (!checkValue(relName,exprs[t].attr.attrName,(Byte *)exprs[t].op1Value.data,strlen((char*)exprs[t].op1Value.data),attrType_up[t])){
									if(checkValuekind)cout<<"外键约束缺失"<<endl;else cout<<"枚举约束失败"<<endl;
									rmm.CloseFile(delete1_fh);
									return;
								}
						}
						for (int j=0,ls=strlen((char*)exprs[t].op1Value.data);j<length_up[t];j++){
							//memcpy(pData+offset[i], values[i].data , length[i]);
							if (j<ls)
								mem[offset_up[t]+j]=((char*)exprs[t].op1Value.data)[j];
							else
								mem[offset_up[t]+j]=0;
						}
					}
					if (!isnotnull[t])mem[offset_up[t]+length_up[t]]=0;
					if (exprs[t].op1Value.type==NUL){
						if(isnotnull[t]){
							cout<<"can not set null:"<<exprs[t].attr.attrName<<endl;
							rmm.CloseFile(delete1_fh);
							return;
						}
						mem[offset_up[t]+length_up[t]]=1;
					}
					if (haskey&&offset_key==offset_up[t]){
		  						Byte * now=mem+offset_key;
		  						if(attrType_key==STRING){
		  							if(key_string[GenString((char*)now,length_key)]){
		  								cout<<"主键重复"<<endl;
										rmm.CloseFile(delete1_fh);
										return;
		  							}
		  							key_string[GenString((char*)now,length_key)]=true;
		  						}
		  						else{
									if(key_int[*((int*)now)]){
		  								cout<<"主键重复"<<endl;
										rmm.CloseFile(delete1_fh);
										return;
		  							}	
									key_int[*((int*)now)]=true;
								}
					}
				}
	  			rec=RM_Record(mem, delete1_fh.GetRecordSize(), rid);
	   	 		delete1_fh.UpdateRec(rec);
	   	 	}
	  	}
  	//}
	rmm.CloseFile(delete1_fh);
}
QL_manager::~QL_manager(){
	if (flag){
		smm.CloseDb();
	}
}


void QL_manager::SelectDFS(int nSelAttrs, const RelAttr selAttrs[], int   nRelations, const char * const relations[], int   nConditions, const Condition conditions[],int deep,int *offset,int *length,AttrType *attrType,bool *isnotnull){
	if (deep==nRelations){
		bool flag=true;
		   	 		for (int i=0;i<nConditions;i++){
		   	 			Byte pdata1[500];
						Byte pdata2[500];
						Byte *data1=pdata1;
						Byte *data2=pdata2;
						GetValue(nRelations,relations,offset[i*2+0],length[i*2],attrType[i*2+0],conditions[i].lhsAttr.relName,data1);
						if (conditions[i].bRhsIsAttr)
							GetValue(nRelations,relations,offset[i*2+1],length[i*2+1],attrType[i*2+1],conditions[i].rhsAttr.relName,data2);
						else
						{
							attrType[i*2+1]=conditions[i].rhsValue.type;
							length[i*2+1]=length[i*2];
							isnotnull[i*2+1]=true;
							data2=(Byte*) conditions[i].rhsValue.data;
						}
						flag = flag && _Validate(data1,data2,attrType[i*2],attrType[i*2+1],conditions[i].op,length[i*2],length[i*2+1],isnotnull[i*2],isnotnull[i*2+1]);
		   	 		}
		   	 		if (flag){
		   	 			Byte *data;
		   	 			for (int i=0;i<nSelAttrs;i++){
		   	 				GetValue(nRelations,relations,offset[i+nConditions*2],length[i+nConditions*2],attrType[i+nConditions*2],selAttrs[i].relName,data);
		   	 				if (i) cout<<",";
		   	 				else cout<<"(";
		   	 				if (!isnotnull[i+nConditions*2]&&data[length[i+nConditions*2]]){
		   	 					cout<<Nullstring;
		   	 				}
		   	 				else{
			   	 				if (attrType[i+nConditions*2]==INT) cout<<*(int *)data;
			   	 				if (attrType[i+nConditions*2]==FLOAT) cout<<*(float *)data;
			   	 				if (attrType[i+nConditions*2]==STRING) for (int j=0;j<length[i+nConditions*2];j++) cout<<(char)data[j];
		   	 				}
		   	 			}
		   	 			cout<<")"<<endl;
		   	 		}
		return;
	}
	if (buffered[deep]==0){
		RM_FileHandle S1_fh;
		smm.GetFh(relations[deep],S1_fh);
		RM_FileScan S1_scanner(S1_fh, attrType[nConditions], length[nConditions], offset[nConditions], EQ_OP, 
			                                NULL, 0);
		RC ret;
	  	RM_Record record;
	  	while( (ret=S1_scanner.GetNextRec_NoComp(record)) != NOT_FOUND ){
		  	record.GetData(pdata[deep]);
		  	bufferdata[deep][buffered[deep]]=pdata[deep];
		  	SelectDFS(nSelAttrs, selAttrs, nRelations, relations, nConditions,conditions,deep+1,offset,length,attrType,isnotnull);
		  	buffered[deep]++;
		}
		rmm.CloseFile(S1_fh);
	}else{
		for (int i=0;i<buffered[deep];i++){
			pdata[deep]=bufferdata[deep][i];
			SelectDFS(nSelAttrs, selAttrs, nRelations, relations, nConditions,conditions,deep+1,offset,length,attrType,isnotnull);
		}
	}
}


bool QL_manager::_Validate(const int op1, const int op2,CompOp comp_op)const{
  switch(comp_op){
  case EQ_OP:
    return op1 == op2;
    break;
  case LT_OP:
    return op1 < op2;
    break;
  case GT_OP:
    return op1>op2;
    break;
  case LE_OP:
    return op1<=op2;
    break;
  case GE_OP:
    return op1>=op2;
    break;
  case NE_OP:
    return op1!=op2;
    break;
  default:
    ;
  }
  return 0;
}

bool QL_manager::_Validate(const std::string &op1, const std::string &op2,CompOp comp_op)const{
  switch(comp_op){
  case EQ_OP:
    return op1 == op2;
    break;
  case LT_OP:
    return op1 < op2;
    break;
  case GT_OP:
    return op1>op2;
    break;
  case LE_OP:
    return op1<=op2;
    break;
  case GE_OP:
    return op1>=op2;
    break;
  case NE_OP:
    return op1!=op2;
    break;
  default:
    ;
  }
  return 0;
}

bool QL_manager::_Validate(const float op1, const float op2,CompOp comp_op)const{
  float d=op1-op2;
  switch(comp_op){
  case EQ_OP:
    return d<EPS && d>-EPS;
    break;
  case LT_OP:
    return d<-EPS;
    break;
  case GT_OP:
    return d>EPS;
    break;
  case LE_OP:
    return d<EPS;
    break;
  case GE_OP:
    return d>-EPS;
    break;
  case NE_OP:
    return d>EPS || d<-EPS;
    break;
  default:
    ;
  }
  return 0;
}

bool QL_manager::_Validate(Byte* data1,Byte* data2,AttrType attrType1,AttrType attrType2,CompOp comp_op,int l1,int l2,bool notnull,bool notnull2){
		if (comp_op==ISNULL_OP){
			if (notnull) return false;
			return (data1[l1]==1);
		}
		if (!notnull&&data1[l1]==1) return false;
		if (!notnull2&&data2[l2]==1) return false;

  		if(comp_op==LIKE_OP){
  			char *A=(char*)data2;
  			char B[500];int lb=0;
  			for (int i=0;i<l2;i++){
  				if (A[i]==0) break;
  				B[lb]=A[i];lb++;
  				if (A[i]=='%'){
  					//B[lb]='\\';lb++;
  					lb--;
  					B[lb]='.';lb++;
  					B[lb]='*';lb++;
  				}
  				if (A[i]=='_'){
  					lb--;
  					//B[lb]='\\';lb++;
  					B[lb]='.';lb++;
  				}
  			}
  			B[lb]=0;
  			//cout<<"Test"<<endl;
  			//cout<<B<<endl;
  			//cout<<GenString((char*)data1,l1)<<endl;
  			std::regex pieces_regex(B);
    		std::smatch pieces_match; 
  			regex_match(GenString((char*)data1,l1), pieces_match, pieces_regex);
  			return pieces_match.size()!=0;
  		}
  		if (attrType1!=attrType2){
						return false;
					}else{
						if (attrType1==INT){
							return _Validate((*(int*)data1),(*(int*)data2),comp_op);
						}
						if (attrType1==FLOAT){
							return _Validate((*(float*)data1),(*(float*)data2),comp_op);
						}
						if (attrType1==STRING){
							return _Validate(GenString((char*)data1,l1),GenString((char*)data2,l2),comp_op);
						}
					}
		return false;
  	}


void QL_manager::SelectLike(int nSelAttrs, const RelAttr selAttrs[], int nRelations, const char * const relations[], const RelAttr &selAttr, const char *cond)
{
	for (int i = 0;i < nSelAttrs;i++)
		cout << selAttrs[i].attrName << ' ';
	cout << endl;

	for (int i = 0;i < nRelations;i++)
		cout << relations[i] << ' ';
	cout << endl;

	cout << selAttr.attrName << endl;

	cout << cond << endl;
}

void QL_manager::SelectGather(int kind, const RelAttr &selAttr, const char *relation, int   nConditions, const Condition conditions[])
{
	//cout<<"in"<<endl;
	if (!flag){
		cout<<"please open a database first!"<<endl;
		return;
	}
	check_relName(relation);
	int offset[100],length[100];
			AttrType attrType[100];
	bool isnotnull[100];
	double sum=0,max=-1E20,min=1E20;int total=0;
			for (int i=0;i<nConditions;i++){
				check_relattr(relation,conditions[i].lhsAttr.attrName);
				smm.GetAttrInfo(relation,conditions[i].lhsAttr.attrName,offset[i*2+0],length[i*2],attrType[i*2+0]);
				isnotnull[i*2]=smm.checkNotNull(relation,conditions[i].lhsAttr.attrName);
				if (conditions[i].bRhsIsAttr){
					smm.GetAttrInfo(relation,conditions[i].rhsAttr.attrName,offset[i*2+1],length[i*2+1],attrType[i*2+1]);
					isnotnull[i*2+1]=smm.checkNotNull(relation,conditions[i].rhsAttr.attrName);
				}else isnotnull[i*2+1]=true;
			}
			check_relattr(relation,selAttr.attrName);
			for (int i = nConditions*2 ; i < nConditions*2 + 1 ; i++ )
				smm.GetAttrInfo(relation,selAttr.attrName,offset[i],length[i],attrType[i]);
			RM_FileHandle S1_fh;
			smm.GetFh(relation,S1_fh);
			RM_FileScan S1_scanner(S1_fh, attrType[nConditions], length[nConditions], offset[nConditions], EQ_OP, 
		                                NULL, 0);
		  	RC ret;
  			RM_Record record;
  			while( (ret=S1_scanner.GetNextRec_NoComp(record)) != NOT_FOUND ){
	  			record.GetData(pdata[0]);
	   	 		bool flag=true;
	   	 		//continue;
	   	 		for (int i=0;i<nConditions;i++){
	   	 			Byte pdata1[100];
					Byte pdata2[100];
					Byte *data1=pdata1;
					Byte *data2=pdata2;
					data1=pdata[0]+offset[i*2+0];
					//GetValue(nRelations,relations,offset[i*2+0],length[i*2],attrType[i*2+0],relations[0],data1);
					if (conditions[i].bRhsIsAttr)
						data2=pdata[0]+offset[i*2+1];
						//GetValue(nRelations,relations,offset[i*2+1],length[i*2+1],attrType[i*2+1],relations[0],data2);
					else
					{
						attrType[i*2+1]=conditions[i].rhsValue.type;
						length[i*2+1]=length[i*2];
						data2=(Byte*) conditions[i].rhsValue.data;
					}
					flag = flag && _Validate(data1,data2,attrType[i*2],attrType[i*2+1],conditions[i].op,length[i*2],length[i*2+1],isnotnull[i*2],isnotnull[i*2+1]);
	   	 		}
	   	 		if (flag){
	   	 			Byte *data;
	   	 				data=pdata[0]+offset[nConditions*2];
	   	 				//GetValue(nRelations,relations,offset[nConditions*2],length[i+nConditions*2],attrType[i+nConditions*2],relations[0],data);
	   	 				//if (i) cout<<",";
	   	 				//else cout<<"(";
	   	 				if (attrType[nConditions*2]==INT){
	   	 					int tmp=*(int *)data;
	   	 					sum+=tmp;
	   	 					if (max<tmp) max=tmp;
	   	 					if(min>tmp)min=tmp;
	   	 				}
	   	 				if (attrType[nConditions*2]==FLOAT){
	   	 					float tmp=*(float *)data;
	   	 					sum+=tmp;
	   	 					if (max<tmp) max=tmp;
	   	 					if(min>tmp)min=tmp;
	   	 				}
	   	 				total++;
	   	 				//if (attrType[i+nConditions*2]==STRING) for (int j=0;j<length[i+nConditions*2];j++) cout<<(char)data[j];
	   	 		}
	   	 		//cout<<"Now "<< sum<<endl;
		  	}
		  //	return;
		  //	cout<<kind<<endl;
		  	//cout<<sum<<endl;
			rmm.CloseFile(S1_fh);
			double ans=sum;
			if (kind==1) ans=sum/total;
			if (kind==2)ans=max;
			if (kind==3) ans=min;
			//if (attrType[nConditions*2]==INT) //printf("%d\n",int(ans));
			//else 
			printf("%.6lf\n",ans);
}

void QL_manager::SelectGroup(int nSelAttrs, const RelAttr selAttrs[], const char *relation, int nCondAttrs, const RelAttr condAttrs[], int   nConditions, const Condition conditions[])
{

	if (!flag){
		cout<<"please open a database first!"<<endl;
		return;
	}
	check_relName(relation);
	int offset_g[100],length_g[100];
	AttrType attrType_g[100];
	Mtotal.clear();
	Msum.clear();
	Mmax.clear();
	Mmin.clear();
	Mprinto.clear();
	for (int i=0;i<nCondAttrs;i++){
		check_relattr(relation,condAttrs[i].attrName);
		smm.GetAttrInfo(relation,condAttrs[i].attrName,offset_g[i],length_g[i],attrType_g[i]);
	}
			int offset[100],length[100];
			AttrType attrType[100];
			bool isnotnull[100];
			for (int i=0;i<nConditions;i++){
				check_relattr(relation,conditions[i].lhsAttr.attrName);
				smm.GetAttrInfo(relation,conditions[i].lhsAttr.attrName,offset[i*2+0],length[i*2],attrType[i*2+0]);
				isnotnull[i*2]=smm.checkNotNull(relation,conditions[i].lhsAttr.attrName);
				if (conditions[i].bRhsIsAttr){
					smm.GetAttrInfo(relation,conditions[i].rhsAttr.attrName,offset[i*2+1],length[i*2+1],attrType[i*2+1]);
					isnotnull[i*2+1]=smm.checkNotNull(relation,conditions[i].rhsAttr.attrName);
				}else isnotnull[i*2+1]=true;
			}
			for (int i = nConditions*2 ; i < nConditions*2 + nSelAttrs ; i++ ){
				check_relattr(relation,selAttrs[i-nConditions*2].attrName);
				smm.GetAttrInfo(relation,selAttrs[i-nConditions*2].attrName,offset[i],length[i],attrType[i]);
				isnotnull[i]=smm.checkNotNull(relation,selAttrs[i-nConditions*2].attrName);
			}
			RM_FileHandle S1_fh;
			smm.GetFh(relation,S1_fh);
			RM_FileScan S1_scanner(S1_fh, attrType[nConditions], length[nConditions], offset[nConditions], EQ_OP, 
		                                NULL, 0);
		  	RC ret;
  			RM_Record record;
  			while( (ret=S1_scanner.GetNextRec_NoComp(record)) != NOT_FOUND ){
	  			record.GetData(pdata[0]);
	   	 		bool flag=true;
	   	 		for (int i=0;i<nConditions;i++){
	   	 			Byte pdata1[100];
					Byte pdata2[100];
					Byte *data1=pdata1;
					Byte *data2=pdata2;
					data1=pdata[0]+offset[i*2+0];
					//GetValue(nRelations,relations,offset[i*2+0],length[i*2],attrType[i*2+0],relations[0],data1);
					if (conditions[i].bRhsIsAttr)
						data2=pdata[0]+offset[i*2+1];//	GetValue(nRelations,relations,offset[i*2+1],length[i*2+1],attrType[i*2+1],relation,data2);
					else
					{
						attrType[i*2+1]=conditions[i].rhsValue.type;
						length[i*2+1]=length[i*2];
						data2=(Byte*) conditions[i].rhsValue.data;
					}
					flag = flag && _Validate(data1,data2,attrType[i*2],attrType[i*2+1],conditions[i].op,length[i*2],length[i*2+1],isnotnull[i*2],isnotnull[i*2+1]);
	   	 		}
	   	 		if (flag){
	   	 			Byte *data;
	   	 			string index="";
	   	 			for(int i=0;i<nCondAttrs;i++){
	   	 				data=pdata[0]+offset_g[i];
	   	 				if (attrType_g[i]==INT||attrType_g[i]==FLOAT) {
	   	 					index+=GenString((char*)data,4);
	   	 				}else
	   	 					index+=GenString((char*)data,length_g[i]);
	   	 			}
	   	 			if (Mprinto.find(index)==Mprinto.end()){
	   	 				string prt="";
	   	 				char value[20];
	   	 				for (int i=0;i<nSelAttrs-1;i++){
	   	 					data=pdata[0]+offset[i+nConditions*2];
	   	 					if (i) prt+="";
		   	 				else prt+="(";
		   	 				if (!isnotnull[i+nConditions*2]&&data[length[i+nConditions*2]]){
		   	 					prt=prt+Nullstring+",";
		   	 				}else{
			   	 				if (attrType[i+nConditions*2]==INT) {
			   	 					sprintf(value,"%d",*(int *)data);
			   	 					prt+=value;
			   	 				}
			   	 				if (attrType[i+nConditions*2]==FLOAT){
			   	 					sprintf(value,"%.6lf",*(float *)data);
			   	 					prt+=value;
			   	 				} 
			   	 				if (attrType[i+nConditions*2]==STRING) for (int j=0;j<length[i+nConditions*2];j++)prt.push_back((char)data[j]);
			   	 				prt.push_back(',');
		   	 				}
	   	 				}
	   	 				//cout<<prt<<"asdf"<<endl;
	   	 				Mprinto[index]=prt;
	   	 				Mtotal[index]=0;
	   	 				Msum[index]=0;
	   	 				Mmax[index]=-1E20;
	   	 				Mmin[index]=1E20;
	   	 			}
	   	 			for (int i=nSelAttrs-1;i<nSelAttrs;i++){
	   	 				Byte *data;
	   	 				data=pdata[0]+offset[i+nConditions*2];
	   	 				//GetValue(nRelations,relations,offset[nConditions*2],length[i+nConditions*2],attrType[i+nConditions*2],relations[0],data);
	   	 				//if (i) cout<<",";
	   	 				//else cout<<"(";
	   	 				if (attrType[i+nConditions*2]==INT){
	   	 					int tmp=*(int *)data;
	   	 					Msum[index]+=tmp;
	   	 					if (Mmax[index]<tmp) Mmax[index]=tmp;
	   	 					if(Mmin[index]>tmp)Mmin[index]=tmp;
	   	 				}
	   	 				if (attrType[i+nConditions*2]==FLOAT){
	   	 					float tmp=*(float *)data;
	   	 					Msum[index]+=tmp;
	   	 					if (Mmax[index]<tmp) Mmax[index]=tmp;
	   	 					if(Mmin[index]>tmp)Mmin[index]=tmp;
	   	 				}
	   	 				Mtotal[index]++;
	   	 			}
	   	 			//cout<<")"<<endl;
	   	 		}
		  	}
		  	int kkind=0;
		  	if (strcmp(selAttrs[nSelAttrs-1].relName, "avg")==0) kkind=1;
		  	if (strcmp(selAttrs[nSelAttrs-1].relName, "max")==0) kkind=2;
		  	if (strcmp(selAttrs[nSelAttrs-1].relName, "min")==0) kkind=3;

			rmm.CloseFile(S1_fh);
			for(map<string,string>::iterator it=Mprinto.begin();it!=Mprinto.end();++it){
				//cout<<"(";
				cout<<it->second;
				double ans=Msum[it->first];
				if (kkind==1) ans=Msum[it->first]/Mtotal[it->first];
				if (kkind==2)ans=Mmax[it->first];
				if (kkind==3) ans=Mmin[it->first];
				cout<<ans<<")"<<endl;
			}
}

bool QL_manager::checkValue(const char *relName,const char *attrName,Byte *data,int length,AttrType attrtype){
	
	checkValuekind=1;
	for (int i=0,ls=strlen(attrName);i<ls;i++)
	if (attrName[i]=='_'){
		char A[20],B[20];
		for (int j=0;j<i;j++)
			A[j]=attrName[j];
		A[i]=0;
		for (int j=i+1;j<ls;j++)
			B[j-i-1]=attrName[j];
		B[ls-i-1]=0;
		int offset_out,length_out;
		AttrType attr_out;
		string AAS(A),BBS(B);
		string ind=AAS+BBS;
		//return true;
		if(hasIndex[ind]){
			map<int,bool> &M_int=Index_Int[ind];
			//return true;
			return M_int[*(int*)data];
		}
		//cout<<ind<<": fuck"<<endl;
		//cout<<A<<B;
		smm.GetAttrInfo(A,B,offset_out,length_out,attr_out);
		RM_FileHandle S1_fh;
		smm.GetFh(A,S1_fh);
		RM_FileScan S1_scanner(S1_fh, attrtype, length, offset_out, EQ_OP, 
		                                (void*)data, length);
		RC ret;
  		RM_Record record;
  		if (S1_scanner.GetNextRec(record) != NOT_FOUND) {
			rmm.CloseFile(S1_fh);
			//cout<<"done"<<endl;
			return true;
		}
		rmm.CloseFile(S1_fh);
		//cout<<"done"<<endl;
		return false;
	}

	if (!smm.isChecked(relName,attrName)) return true;
	checkValuekind=0;
	RM_FileHandle checkdata_fh;
	string CheckData=string("__checkdata__")+relName+attrName;
	smm.GetFh(CheckData.c_str(),checkdata_fh);
	RM_FileScan checkdata_scanner(checkdata_fh, attrtype, length, 0, EQ_OP, 
                                (void*)data, length);
	RM_Record record;
	if (checkdata_scanner.GetNextRec(record) != NOT_FOUND) {
		rmm.CloseFile(checkdata_fh);
		return true;
	}
	rmm.CloseFile(checkdata_fh);
	return false;
}
void QL_manager::CreateIndex(const char *relName, const RelAttr &attr)
{
	if (!flag){
		cout<<"please open a database first!"<<endl;
		return;
	}
	smm.CreateIndex(relName,attr.attrName);
}

void QL_manager::DropIndex(const char *relName, const RelAttr &attr)
{
	if (!flag){
		cout<<"please open a database first!"<<endl;
		return;
	}
	smm.DropIndex(relName,attr.attrName);
}
void QL_manager::load_index(const char *relName,const char *attrName){
	string Name=string(relName)+string(attrName);
	hasIndex[Name]=true;
	//cout<<Name<<endl;
	map<int,bool> M_int;
	Index_Int[Name]=map<int,bool>();
	int offset,length;
	AttrType attrType;
	smm.GetAttrInfo(relName,attrName,offset,length,attrType);
	RM_FileHandle Load_fh;
	smm.GetFh(relName,Load_fh);
	RM_FileScan delete_scanner(Load_fh, attrType, length, offset, EQ_OP, 
	                                NULL, length);
		  	RC ret;
		  	RM_Record record,rec;
		  	while( (ret=delete_scanner.GetNextRec_NoComp(record)) != NOT_FOUND ){
		  		bool flag=true;
		  		Byte* mem;
		  		RID rid;
		  		record.GetData(mem);
		  		M_int[*((int*)(mem+offset))]=true;
		  	}
	Index_Int[Name]=M_int;
}
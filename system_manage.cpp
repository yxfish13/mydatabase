#include "system_manage.h"
#include <iostream>
//using namespace std;


void SM_PrintError(RC rc){

}

void PutIntData(Byte *& pData, const int x){
  memcpy(pData, &x, 4);
  pData+=4;
}

void PutFloatData(Byte *& pData, const float x){
  memcpy(pData, &x, 4);
  pData+=4;
}

void PutStringData(Byte *& pData, const char *s, const int len){
  int s_len=strlen(s);
  for(int i=0; i<len; i++){
    if (i>=s_len)
      *pData=0;
    else
      *pData=s[i];
    pData++;
  }
}

//----------------------------SM_MANAGER----------------------------------

SM_Manager::SM_Manager(RM_Manager &rmm2)
  :rmm(rmm2){
  
}

SM_Manager::~SM_Manager(){

}

RC SM_Manager::CreateDB(const string &db_name){
  string db_dir(db_name+SYS_SEP);
  system((string("mkdir ")+db_name).c_str());
  system((string("mkdir ")+db_name+"/dust").c_str());
  rmm.CreateFile( (db_dir+SYSTEM_CATALOG_NAME).c_str(),  SYSTEM_TUPLE_LENGTH);
  rmm.CreateFile( (db_dir+ATTRIBUTE_CATALOG_NAME).c_str(), ATTRIBUTE_TUPLE_LENGTH);
  rmm.CreateFile( (db_dir+CHECK_CATALOG_NAME).c_str(), CHECK_TUPLE_LENGTH);
  return OK;
}

RC SM_Manager::OpenDb(const char *db_name){
  //cout <<"iin"<<endl;
  db_dir=string(db_name)+SYS_SEP;

  RC ret=rmm.OpenFile((db_dir+SYSTEM_CATALOG_NAME).c_str(), system_fh);
  if (ret!=OK){
    SM_PrintError(ret);
    return SYSTEM_CATALOG_OPEN_ERROR;
  }

  ret=rmm.OpenFile((db_dir+ATTRIBUTE_CATALOG_NAME).c_str(), attribute_fh);
  if (ret!=OK){
    SM_PrintError(ret);
    return ATTRIBUTE_CATALOG_OPEN_ERROR;
  }

  ret=rmm.OpenFile((db_dir+CHECK_CATALOG_NAME).c_str(), check_fh);
  
  return OK;
}

RC SM_Manager::CloseDb(){
  
  RC ret=rmm.CloseFile(system_fh);
  if (ret!=OK){
    SM_PrintError(ret);
    return SYSTEM_CATALOG_CLOSE_ERROR;
  }

  ret=rmm.CloseFile(attribute_fh);
  if (ret!=OK){
    SM_PrintError(ret);
    return ATTRIBUTE_CATALOG_CLOSE_ERROR;
  }
  ret=rmm.CloseFile(check_fh);
  return OK;
}
RC SM_Manager::DropDB       (const std::string &s){
  char suffix=rand()%255;
  cout<<(string("mv -f ")+s+string(" dust/")+s+suffix)<<endl;
  system((string("mv -f ")+s+string(" dust/")+s+suffix).c_str());
  return OK;
}

RC SM_Manager::CreateTable(const char *rel_name, int attr_count, AttrInfo *attr_info,int nchecks, const char *const attrnames[], const int valuenum[], Value valuelist[][10],const char *primaryKey){
  
  //for system catalog
  int tuple_length=0;
  int index_count=0;
  for(int i=0; i<attr_count; i++){
    tuple_length += attr_info[i].attrLength;
    if (!attr_info[i].notNull)
      tuple_length++;
  }

  Byte pData[500];
  Byte *nowp=pData;
  PutStringData(nowp, rel_name, RELNAME_LENGTH);
  PutIntData(nowp, tuple_length);
  PutIntData(nowp, attr_count);
  PutIntData(nowp, index_count);

  RID rid;
  system_fh.InsertRec(pData, rid);
  //------------------- 


  //for attribute catalog
  for(int i=0, now_offset=0; i<attr_count; i++){
    RID rid;
    nowp=pData;
    PutStringData(nowp, rel_name, RELNAME_LENGTH);
    PutStringData(nowp, attr_info[i].attrName.c_str(), ATTRNAME_LENGTH);

    PutIntData(nowp, now_offset);
    now_offset+=attr_info[i].attrLength;
    if (!attr_info[i].notNull)
      now_offset++;

    PutIntData(nowp, (int)attr_info[i].attrType);
    PutIntData(nowp, attr_info[i].attrLength);
    if (strcmp(attr_info[i].attrName.c_str(),primaryKey)==0)
      PutIntData(nowp, 3);
      else 
    PutIntData(nowp, 0); //for index
    PutIntData(nowp, attr_info[i].notNull);
    attribute_fh.InsertRec(pData, rid);
  }
  for (int i=0;i<nchecks;i++){
     RID rid;
     nowp=pData;
     PutStringData(nowp, rel_name, RELNAME_LENGTH);
     PutStringData(nowp, attrnames[i], ATTRNAME_LENGTH);
     check_fh.InsertRec(pData,rid);
     string CheckData=string("__checkdata__")+rel_name+attrnames[i];
     int length=0;
     AttrType attrtype; 
     for (int j=0;j<attr_count;j++)
        if (strcmp(attrnames[i],attr_info[j].attrName.c_str())==0)
          length=attr_info[j].attrLength,attrtype=attr_info[j].attrType;
     RC ret=rmm.CreateFile((db_dir+CheckData).c_str(), length);
     RM_FileHandle checkattr_fh;
     rmm.OpenFile((db_dir+CheckData).c_str(), checkattr_fh);
     for(int j=0;j<valuenum[i];j++){
        checkattr_fh.InsertRec((Byte*)valuelist[i][j].data,rid);
     }
     rmm.CloseFile(checkattr_fh);
  }

  attribute_fh.ForcePages();
  system_fh.ForcePages();
  check_fh.ForcePages();
  //-------------------

  //for table file
  RC ret=rmm.CreateFile((db_dir+string(rel_name)).c_str(), tuple_length);
  if (ret!=OK){
    return TABLE_CREATE_ERROR;
  }
  //------------------

  return OK;
}

RC SM_Manager::DropTable(const char *relName){
  string rel_name(relName);
  
  //drop in system catalog
  RM_FileScan system_scanner(system_fh, STRING, RELNAME_LENGTH, 0, EQ_OP, 
                             (void*)relName, strlen(relName));
  RC ret;
  RM_Record record;
  ret=system_scanner.GetNextRec(record);
  if (ret==NOT_FOUND){
    return NOT_FOUND;
  }
  RID rid;
  record.GetRid(rid);
  system_fh.DeleteRec(rid);
  //------------------------

  //drop in attribute catalog
  RM_FileScan attribute_scanner(attribute_fh, STRING, RELNAME_LENGTH, 0, EQ_OP, 
                                (void*)relName, strlen(relName));
  while( (ret=attribute_scanner.GetNextRec(record)) != NOT_FOUND ){
    record.GetRid(rid);
    attribute_fh.DeleteRec(rid);
  }
  system((string("mv -f ")+db_dir+string(relName)+" "+db_dir+"dust/"+string(relName)).c_str());
  
  RM_FileScan check_scanner(check_fh, STRING, RELNAME_LENGTH, 0, EQ_OP, 
                                (void*)relName, strlen(relName));
  while( (ret=attribute_scanner.GetNextRec(record)) != NOT_FOUND ){
    Byte *mem;
    record.GetRid(rid);
    record.GetData(mem);
    attribute_fh.DeleteRec(rid);
    string CheckData=string("__checkdata__")+rel_name+(char*)(mem+RELNAME_LENGTH);
    system((string("mv -f ")+db_dir+CheckData+" "+db_dir+"dust/"+CheckData).c_str());
  }

  attribute_fh.ForcePages();
  system_fh.ForcePages();
  check_fh.ForcePages();
  
  //-----------------------
  
  return OK;
}

RC SM_Manager::Help(){
  return OK;
}

RC SM_Manager::Help(const char *rel_name){
  return OK;
}

RC SM_Manager::Print(const char *relName){
  RM_FileScan attribute_scanner(attribute_fh, STRING, RELNAME_LENGTH, 0, EQ_OP, 
                                (void*)relName, strlen(relName));
  RC ret;
  RM_Record record;
  Byte *mem;
  while( (ret=attribute_scanner.GetNextRec(record)) != NOT_FOUND ){
  //  record.GetRid(rid);
  //  attribute_fh.DeleteRec(rid);
    record.GetData(mem);
    cout<<GenString((char *)(mem+RELNAME_LENGTH),ATTRNAME_LENGTH)<<"("<<*(int*)(mem+RELNAME_LENGTH+ATTRNAME_LENGTH+8)<<")"<<*(int*)(mem+RELNAME_LENGTH+ATTRNAME_LENGTH+4)<<endl;
  }
  return OK;
}

RC SM_Manager::ShowTable   (){
  RM_FileScan system_scanner(system_fh, STRING, RELNAME_LENGTH, 0, EQ_OP, 
                                NULL, 0);
  //cout<<"1"<<endl;
  RC ret;
  RM_Record record;
  Byte *mem;
  //cout<<"1.1"<<endl;
  while( (ret=system_scanner.GetNextRec_NoComp(record)) != NOT_FOUND ){
  //  record.GetRid(rid);
  //  attribute_fh.DeleteRec(rid);
   // cout<<"2"<<endl;
    record.GetData(mem);
   // cout<<"3"<<endl;
    cout<<GenString((char *)(mem),RELNAME_LENGTH)<<"("<<*(int*)(mem+RELNAME_LENGTH)<<")"<<endl;
    //cout<<"4"<<endl;
  }
  return OK;
}               // Print table
RC SM_Manager::GetFh(const char *relName,RM_FileHandle& fh){
  RC ret=rmm.OpenFile((db_dir+string(relName)).c_str(), fh);
  return ret;
}
RC SM_Manager::GetAttrInfo(const char *relName,const char *AttrName,int &offset,int &length,AttrType &attrtype){
  RM_FileScan attribute_scanner(attribute_fh, STRING, RELNAME_LENGTH, 0, EQ_OP, 
                                (void*)relName, strlen(relName));
  RC ret;
  RM_Record record;
  Byte *mem;
  offset=-2;
  while( (ret=attribute_scanner.GetNextRec(record)) != NOT_FOUND ){
    offset=-1;
  //  record.GetRid(rid);
  //  attribute_fh.DeleteRec(rid);
    record.GetData(mem);
    if (GenString((char *)(mem+RELNAME_LENGTH),ATTRNAME_LENGTH)==GenString((char *)AttrName,strlen(AttrName))){
      offset=*(int*)(mem+RELNAME_LENGTH+ATTRNAME_LENGTH);
      length=*(int*)(mem+RELNAME_LENGTH+ATTRNAME_LENGTH+8);
      attrtype=(AttrType)*(int*)(mem+RELNAME_LENGTH+ATTRNAME_LENGTH+4);
      break;
    }
  }
  return OK;
}
int SM_Manager::Getoffset(const char *relName,int *offset,int *length){
  RM_FileScan attribute_scanner(attribute_fh, STRING, RELNAME_LENGTH, 0, EQ_OP, 
                                (void*)relName, strlen(relName));
  RC ret;
  RM_Record record;
  Byte *mem;
  int cnt=0;
  while( (ret=attribute_scanner.GetNextRec(record)) != NOT_FOUND ){
  //  record.GetRid(rid);
  //  attribute_fh.DeleteRec(rid);
    record.GetData(mem);
    //if (genString((char *)(mem+RELNAME_LENGTH),ATTRNAME_LENGTH)==genString(AttrName,strlen(AttrName))){
      offset[cnt]=*(int*)(mem+RELNAME_LENGTH+ATTRNAME_LENGTH);
      length[cnt]=*(int*)(mem+RELNAME_LENGTH+ATTRNAME_LENGTH+8);
      cnt++;
    //  attrtype=*(int*)(mem+RELNAME_LENGTH+ATTRNAME_LENGTH+4);
    //}
  }
  return cnt;
}
bool SM_Manager::isChecked(const char*relName,const char *AttrName){
  if (strchr(AttrName,'_')) return true;
  RM_FileScan check_scanner(check_fh, STRING, RELNAME_LENGTH, 0, EQ_OP, 
                                (void*)relName, strlen(relName));
  RC ret;
  RM_Record record;
  Byte *mem;
  while( (ret=check_scanner.GetNextRec(record)) != NOT_FOUND ){
    record.GetData(mem);
    if (strcmp((char*)mem+RELNAME_LENGTH,AttrName)==0){
      return true;
    }
  }
  return false;
}
bool SM_Manager::checkNotNull(const char*relName,const char *AttrName){
   RM_FileScan attribute_scanner(attribute_fh, STRING, RELNAME_LENGTH, 0, EQ_OP, 
                                (void*)relName, strlen(relName));
  RC ret;
  RM_Record record;
  Byte *mem;
  int cnt=0;
  while( (ret=attribute_scanner.GetNextRec(record)) != NOT_FOUND ){
  //  record.GetRid(rid);
  //  attribute_fh.DeleteRec(rid);
    record.GetData(mem);
    if (strcmp((char*)mem+RELNAME_LENGTH,AttrName)==0){
     // cout<<"get "<< AttrName<<" "<<*(int*)(mem+RELNAME_LENGTH+ATTRNAME_LENGTH+16)<<endl;
      return *(int*)(mem+RELNAME_LENGTH+ATTRNAME_LENGTH+16);
    }
  }
  return false;
}
void SM_Manager::GetAttrName(const char *relName,char attrNames[100][100],bool *ischecked,bool *isnotnull,AttrType* attrType){
  RM_FileScan attribute_scanner(attribute_fh, STRING, RELNAME_LENGTH, 0, EQ_OP, 
                                (void*)relName, strlen(relName));
  RC ret;
  RM_Record record;
  Byte *mem;
  int cnt=0;
  while( (ret=attribute_scanner.GetNextRec(record)) != NOT_FOUND ){
  //  record.GetRid(rid);
  //  attribute_fh.DeleteRec(rid);
    record.GetData(mem);
    //if (genString((char *)(mem+RELNAME_LENGTH),ATTRNAME_LENGTH)==genString(AttrName,strlen(AttrName))){
      memcpy(attrNames[cnt],(mem+RELNAME_LENGTH),ATTRNAME_LENGTH-1);
      ischecked[cnt]=isChecked(relName,attrNames[cnt]);
      isnotnull[cnt]=checkNotNull(relName,attrNames[cnt]);
      attrType[cnt]=(AttrType)*(int*)(mem+RELNAME_LENGTH+ATTRNAME_LENGTH+4);
      cnt++;
    //  attrtype=*(int*)(mem+RELNAME_LENGTH+ATTRNAME_LENGTH+4);
    //}
  }
}
bool SM_Manager::hasKey(const char *relName,int &offset,int &length,AttrType &attrtype){
  RM_FileScan attribute_scanner(attribute_fh, STRING, RELNAME_LENGTH, 0, EQ_OP, 
                                (void*)relName, strlen(relName));
  RC ret;
  RM_Record record;
  Byte *mem;
  while( (ret=attribute_scanner.GetNextRec(record)) != NOT_FOUND ){
  //  record.GetRid(rid);
  //  attribute_fh.DeleteRec(rid);
    record.GetData(mem);
    if ((*(int*)(mem+RELNAME_LENGTH+ATTRNAME_LENGTH+12)/2)==1){
      offset=*(int*)(mem+RELNAME_LENGTH+ATTRNAME_LENGTH);
      length=*(int*)(mem+RELNAME_LENGTH+ATTRNAME_LENGTH+8);
      attrtype=(AttrType)*(int*)(mem+RELNAME_LENGTH+ATTRNAME_LENGTH+4);
      return true;
    }
  }
  return false;
}

bool SM_Manager::hasIndex(const char *relName,const char *AttrName,int &offset,int &length,AttrType &attrtype){
  RM_FileScan attribute_scanner(attribute_fh, STRING, RELNAME_LENGTH, 0, EQ_OP, 
                                (void*)relName, strlen(relName));
  RC ret;
  RM_Record record;
  Byte *mem;
  while( (ret=attribute_scanner.GetNextRec(record)) != NOT_FOUND ){
  //  record.GetRid(rid);
  //  attribute_fh.DeleteRec(rid);
    record.GetData(mem);
    if (GenString((char *)(mem+RELNAME_LENGTH),ATTRNAME_LENGTH)==GenString((char *)AttrName,strlen(AttrName))){
      offset=*(int*)(mem+RELNAME_LENGTH+ATTRNAME_LENGTH);
      length=*(int*)(mem+RELNAME_LENGTH+ATTRNAME_LENGTH+8);
      attrtype=(AttrType)*(int*)(mem+RELNAME_LENGTH+ATTRNAME_LENGTH+4);
      //cout<<(*(int*)(mem+RELNAME_LENGTH+ATTRNAME_LENGTH+12))<<endl;
      return ((*(int*)(mem+RELNAME_LENGTH+ATTRNAME_LENGTH+12))%2)!=0;
    }
  }
  return OK;
}

void SM_Manager::CreateIndex(const char *relName, const char* AttrName)
{
  RM_FileScan attribute_scanner(attribute_fh, STRING, RELNAME_LENGTH, 0, EQ_OP, 
                                (void*)relName, strlen(relName));
  RC ret;
  RM_Record record;
  Byte *mem;
  RID rid;
  int mark=1;
  while( (ret=attribute_scanner.GetNextRec(record)) != NOT_FOUND ){
    record.GetRid(rid);
  //  attribute_fh.DeleteRec(rid);
    record.GetData(mem);
    if (GenString((char *)(mem+RELNAME_LENGTH),ATTRNAME_LENGTH)==GenString((char *)AttrName,strlen(AttrName))){
      mark=*(int*)(mem+RELNAME_LENGTH+ATTRNAME_LENGTH+12);
      mark=(mark|1);
      memcpy((mem+RELNAME_LENGTH+ATTRNAME_LENGTH+12), &mark , 4);
      RM_Record rec=RM_Record(mem, attribute_fh.GetRecordSize(), rid);
      attribute_fh.UpdateRec(rec);
    }
  }
   attribute_fh.ForcePages();
}

void SM_Manager::DropIndex(const char *relName, const char* AttrName)
{
  RM_FileScan attribute_scanner(attribute_fh, STRING, RELNAME_LENGTH, 0, EQ_OP, 
                                (void*)relName, strlen(relName));
  RC ret;
  RM_Record record;
  Byte *mem;
  RID rid;
  int mark=0;
  while( (ret=attribute_scanner.GetNextRec(record)) != NOT_FOUND ){
    record.GetRid(rid);
  //  attribute_fh.DeleteRec(rid);
    record.GetData(mem);
    if (GenString((char *)(mem+RELNAME_LENGTH),ATTRNAME_LENGTH)==GenString((char *)AttrName,strlen(AttrName))){
      mark=*(int*)(mem+RELNAME_LENGTH+ATTRNAME_LENGTH+12);
      if(mark&1) mark=mark-1;
      memcpy((mem+RELNAME_LENGTH+ATTRNAME_LENGTH+12), &mark , 4);
      RM_Record rec=RM_Record(mem, attribute_fh.GetRecordSize(), rid);
      attribute_fh.UpdateRec(rec);
    }
  }
  attribute_fh.ForcePages();
}

//----------------------------SM_MANAGER----------------------------------

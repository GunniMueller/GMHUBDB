#include <global.h>
#include <fstream>

typedef struct{
  int key;
  char name[NAME_LENGTH];
  PageNo foo;
} entry;

int getTuple(istream & stream,char * buffer)
{
  int * tCnt=(int*)buffer;
  *tCnt=0;

  entry * list=(entry*)(buffer+3*sizeof(int));
  string name;

  for(int cnt=0;cnt<MAX_ENTRY;++cnt){
    if(stream.eof()==true) break;
    stream >> list[cnt].key;
    if(stream.eof()==true) break;
    stream >> name;
    size_t len = name.size();
    if(len>=28){
      len=27;
    }
    strncpy(list[cnt].name,name.c_str(),len);
    list[cnt].name[len]='\0';
    ++(*tCnt);
  }
  return *tCnt;
}

int main()
{
  int rc;
  uint pageCnt = 1;
  int tupleCnt = 0;
  string name;
  int id;
  FILE * outFile=fopen("out.tab","wb");
  char page[BLOCKSIZE];
  if(outFile==NULL) return -1;
  memset(page,0,BLOCKSIZE);
  fwrite(page,BLOCKSIZE,1,outFile);
  do{
    rc=getTuple(cin,page);
    fwrite(page,BLOCKSIZE,1,outFile);
  }while(rc==MAX_ENTRY);
  fclose(outFile);
  return 0;
}

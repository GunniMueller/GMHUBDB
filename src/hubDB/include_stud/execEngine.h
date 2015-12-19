#ifndef _EXECENGINE_H_
#define _EXECENGINE_H_

#include <map>
#include <list>

#include <global.h>
#include <bufferMgr.h>
#include <indexMgr.h>
#include <errorObj.h>
#include <syscat.h>

typedef map<string,FileNo> Str2FileNoType;

class ExecEngine {

 public:

  ExecEngine();
  ~ExecEngine();

  void disconnect();

 protected:

  BufferMgr * bufferMgr;
  IndexMgr * indexMgr;
  SysCat sysCat;

  string _directory;
  bool _isConnected;

  Str2FileNoType fileNoList;
};

#endif /* _EXECENGINE_H_ */



  

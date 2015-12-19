#ifndef _INDEXMGR_H_
#define _INDEXMGR_H_

#include <global.h>
#include <bufferMgr.h> 
#include <tuple.h>
#include <btree.h>

class IndexMgr
{
 public:        

  IndexMgr(BufferMgr & buf, const int max = MAXOPENINDEXES);
  ~IndexMgr();

  friend ostream & operator<<(ostream & stream,IndexMgr & indexMgr);
 
  /*
   * Folgende Methoden setzen direkt auf die entsprechenden 
   * BufferMgr-Methoden auf.
   */ 
  void createIndex(const string &indexName, FileNo &fileNo);  
  
  void dropIndex (const string &indexName);
  
  void openIndex (const string &indexName, FileNo &fileNo);
  
  void closeIndex (FileNo fileNo);

  void disconnect();
  
  /*
   * Durchsucht die gegebene Indexdatei nach dem gegebenen key (= Tupel.id).
   * Falls key == NULL wird das Tupel mit der kleinsten id gesucht.
   * 
   * Rueckgabewert: das gefundene Tupel oder NULL
   */
  Tuple* find(FileNo fileNo, int *key = NULL);
  
  /*
   * Fuegt das gegebene Tupel in die gegebene Indexdatei ein.
   *
   * Rueckgabewert: true, falls insert erfolgreich war
   * false, falls ein Tupel mit der gegebenen id existiert
   */
  bool insert(FileNo fileNo, Tuple &tuple);

  /*
   * Entfernt das Tupel mit dem gegebenen key (= Tupel.id) 
   * aus der gegebenen Indexdatei. 
   * 
   * Rueckgabewert: true, falls Entfernen erfolgreich war
   * false, falls kein Tupel mit der gegebenen id existiert
   */
  bool remove(FileNo fileNo, int *key);
  
  /*
   * Statische Methode zum Testen des Index-Managers. Die Testroutine soll
   * saemtliche Funktionalitaeten des Index-Managers in geeigneter Weise
   * demonstrieren und testen. Die Implementierung dieser Methode ist in 
   * einer separaten Datei mit dem Namen indexMgr_test.cpp abzugeben. 
   * 
   * Wenn 
   * das Flag details den Wert true hat, sollen neben den Statusmeldungen 
   * der einzelnen Testschritte (OKAY, FAILED) weitere Details ueber den 
   * internen Zustand der wichtigsten Variablen des Filemanagers ausgegeben
   * werden.
   */
  static void test(bool details);  

 private:
  /* der Buffer-Manager */
  BufferMgr & bufferMgr;
  const int maxOpenIdx;
  int lastUnUsed;
};

#endif /* _INDEXMGR_H_ */


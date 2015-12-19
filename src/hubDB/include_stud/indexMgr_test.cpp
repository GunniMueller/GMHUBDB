#include "indexMgr.h"

void IndexMgr::test(bool details)
{
  BufferMgr *bmgr = new BufferMgr(64);
  IndexMgr indexMgr = IndexMgr(*bmgr);
  FileNo fileNo1, fileNo2, fileNo3;
  int key;
  
  // Kreieren zweier Indexe
  cout << endl << "Kreieren zweier Indexe: index1.dat, index2.dat" << endl;
  indexMgr.createIndex("index1.dat", fileNo1);
  indexMgr.createIndex("index2.dat", fileNo2);
  if (details)
    cout << indexMgr;

  // Oeffnen eines Index
  cout << endl << "Oeffnen von Index index1.dat" << endl;
  indexMgr.openIndex("index1.dat", fileNo3);
  if (details)
    cout << indexMgr;

  // Einfuegen einiger Werte
  cout << endl << "Einfuegen von 10, 20, 30, 40, 50 in index1.dat" << endl;
  for (int i=10; i<60; i+=10) 
  {
    Tuple tuple = Tuple(i, "foo");
    indexMgr.insert(fileNo3, tuple);
  }
  if (details)
    cout << indexMgr;
  
  // Suche eines Wertes
  cout << endl << "Suche von 30... ";
  key = 30;
  Tuple *tuple = indexMgr.find(fileNo3, &key);
  if ( tuple->getId() == 30 )
    OKAY(cout);
  else
  {
    cout << "got tuple " << *tuple << " instead of key == 30";
    FAILED(cout);
  }
  delete tuple;
  
  cout << endl << "Suche des kleinsten Schluessels... ";
  tuple = indexMgr.find(fileNo3);
  if ( tuple->getId() == 10 )
    OKAY(cout);
  else
  {
    cout << endl << "got tuple " << tuple << " instead of key == 10";
    FAILED(cout);
  }    
  delete tuple;
 
  // Loeschen einiger Werte
  cout << endl << "Loeschen von 30... ";
  bool deleted;
  key = 30;
  deleted = indexMgr.remove(fileNo3, &key);
  if ( deleted ) OKAY(cout);
  else FAILED(cout);
  
  cout << endl << "Loeschen von (nicht vorhandener) 70... ";
  key = 70;
  deleted = indexMgr.remove(fileNo3, &key);
  if ( !deleted ) OKAY(cout);
  else FAILED(cout);    
  if (details)
    cout << indexMgr;
 
  // Schliessen des Index
  cout << endl << "Schliessen von index1.dat" << endl;
  indexMgr.closeIndex(fileNo3);
  if (details)
    cout << indexMgr;

  // disconnect (== close fileNo1, fileNo2)
  cout << endl << "disconnect" << endl;
  indexMgr.disconnect();
  if (details)
    cout << indexMgr;
 
  // Loeschen der Indexe
  cout << endl << "Loeschen der Indexe index1.dat, index2.dat" << endl;
  indexMgr.dropIndex("index1.dat");
  indexMgr.dropIndex("index2.dat");
  if (details)
    cout << indexMgr;

}

#include "btree.h"
#include "vector"
#include "iterator"

void insertTuples(BTree *btree, vector<Tuple> tuples, bool details)
{ 
  try
  {
    cout << endl << "Einfuegen von ";
	  for (vector<Tuple>::iterator it = tuples.begin(); 
          it != tuples.end(); it++) 
	  {
	    cout << (*it).getId() << ", ";
      btree->insert(*it);
	  } 
    
    if (details) cout << endl << *btree;
  }
  catch (ErrorObj e)
  {
    cout << e;
    FAILED(cout);
    exit(-1);
  }  
}

void removeKeys(BTree *btree, vector<int> keys, bool details)
{ 
  try
  {
    cout << endl << "Loeschen von ";
    for (vector<int>::iterator it = keys.begin(); 
          it != keys.end(); it++) 
    {
      cout << *it << ", ";
      btree->remove(*it);
    } 
    
    if (details) cout << endl << *btree;
  }
  catch (ErrorObj e)
  {
    cout << e;
    FAILED(cout);
    exit(-1);
  }  
}

void BTree::test(bool details)
{
  BufferMgr *bmgr = new BufferMgr(64);
  FileNo fileNo; 
  
  try {
    bmgr->createFile("btreeTestFile.tab" , fileNo);  
  }
  catch(ErrorObj e ) 
  {
    bmgr->dropFile("btreeTestFile.tab");
    bmgr->createFile("btreeTestFile.tab" , fileNo);
  }

  BTree *btree = new BTree(fileNo, *bmgr); 
  vector<Tuple> tupleVector;
  vector<int> keyVector;
  
  // Einfuegen von 10, 20, 30 ,40
  tupleVector.push_back(Tuple(10, "zehn"));
  tupleVector.push_back(Tuple(20, "zwanzig"));
  tupleVector.push_back(Tuple(30, "dreissig"));
  tupleVector.push_back(Tuple(40, "vierzig"));
  insertTuples(btree, tupleVector, details);
  tupleVector.clear();
   
  // Einfuegen von 50
  tupleVector.push_back(Tuple(50, "fuenfzig"));
  insertTuples(btree, tupleVector, details);
  tupleVector.clear();
  
  // Einfuegen von 15, 25, 45 55
  tupleVector.push_back(Tuple(15, "fuenfzehn"));
  tupleVector.push_back(Tuple(25, "fuenfundzwanzig"));
  tupleVector.push_back(Tuple(45, "fuenfundvierzig"));
  tupleVector.push_back(Tuple(55, "fuenfundfuenfzig"));
  insertTuples(btree, tupleVector, details);
  tupleVector.clear();  
 
  // Einfuegen von 17
  tupleVector.push_back(Tuple(17, "siebzehn"));
  insertTuples(btree, tupleVector, details);
  tupleVector.clear();
  
  // Einfuegen von 12, 16, 22, 27
  tupleVector.push_back(Tuple(12, "zwölf"));
  tupleVector.push_back(Tuple(16, "sechzehn"));
  tupleVector.push_back(Tuple(22, "zweiundzwanzig"));
  tupleVector.push_back(Tuple(27, "siebenundzwanzig"));
  insertTuples(btree, tupleVector, details);
  tupleVector.clear();  
  
  // Einfuegen von 47
  tupleVector.push_back(Tuple(47, "siebenundvierzig"));
  insertTuples(btree, tupleVector, details);
  tupleVector.clear();  
  
  // Einfuegen von 42, 46, 52, 57
  tupleVector.push_back(Tuple(42, "zweiundvierzig"));
  tupleVector.push_back(Tuple(46, "sechsundvierzig"));
  tupleVector.push_back(Tuple(52, "zweiundfuenfig"));
  tupleVector.push_back(Tuple(57, "siebenundfuenfzig"));
  insertTuples(btree, tupleVector, details);
  tupleVector.clear();    
  
  // Einfuegen von 35
  tupleVector.push_back(Tuple(35, "fuenfunddreissig"));
  insertTuples(btree, tupleVector, details);
  tupleVector.clear();    
  
  // Einfuegen von 33, 34, 43, 44
  tupleVector.push_back(Tuple(33, "dreiunddreissig"));
  tupleVector.push_back(Tuple(34, "vierunddreissig"));
  tupleVector.push_back(Tuple(43, "dreiundvierzig"));
  tupleVector.push_back(Tuple(44, "vierundvierzig"));
  insertTuples(btree, tupleVector, details);
  tupleVector.clear();    

  // Einfuegen von 36
  tupleVector.push_back(Tuple(36, "sechsunddreissig"));
  insertTuples(btree, tupleVector, details);
  tupleVector.clear();      
  
  // Finde (nicht vorhandenen) Schluessel 100
  // Finde Schluessel 34, kleinsten Schluessel
  try 
  {
    int key;
    Tuple *foundTuple; 
    
    cout << "Finde (nicht vorhandenen) Schluessel 100... ";
    key = 100;
    foundTuple = btree->find(&key);
    if (foundTuple == NULL) OKAY(cout);
    else FAILED(cout);
    
    cout << "Finde Schluessel 34... ";
    key = 34;
    foundTuple = btree->find(&key);
    if (foundTuple->getId() == 34) OKAY(cout);
    else FAILED(cout);
    
    cout << "Finde kleinsten Schluessel (10)... ";
    foundTuple = btree->find(NULL);
    if (foundTuple->getId() == 10) OKAY(cout);
    else FAILED(cout);
  }
  catch (ErrorObj e) 
  {
    cout << e;
    FAILED(cout);
  }
  
  // Einfuegen von 18
  tupleVector.push_back(Tuple(18, "achtzehn"));
  insertTuples(btree, tupleVector, details);
  tupleVector.clear(); 
  
  // Loeschen von 12, 15
  keyVector.push_back(12);
  keyVector.push_back(15);
  removeKeys(btree, keyVector, details);
  keyVector.clear();       
 
  // Loeschen von 16
  keyVector.push_back(16);
  removeKeys(btree, keyVector, details);
  keyVector.clear();        

  // Loeschen von 20, 46
  keyVector.push_back(20);
  keyVector.push_back(46);
  removeKeys(btree, keyVector, details);
  keyVector.clear();  
  
  // Loeschen von 17, 44, 52,57
  keyVector.push_back(17);
  keyVector.push_back(44);
  keyVector.push_back(52);
  keyVector.push_back(57);
  removeKeys(btree, keyVector, details);
  keyVector.clear();    
  
  // Loeschen von 50
  keyVector.push_back(50);
  removeKeys(btree, keyVector, details);
  keyVector.clear();
  
  // Loeschen von 42
  keyVector.push_back(42);
  removeKeys(btree, keyVector, details);
  keyVector.clear();        
  
  // Loeschen von 40
  keyVector.push_back(40);
  removeKeys(btree, keyVector, details);
  keyVector.clear();    
  
  // Loeschen von 43
  keyVector.push_back(43);
  removeKeys(btree, keyVector, details);
  keyVector.clear();    
  
  // Einfuegen von 11, 12
  tupleVector.push_back(Tuple(11, "elf"));  
  tupleVector.push_back(Tuple(12, "zwölf"));
  insertTuples(btree, tupleVector, details);
  tupleVector.clear();            
  
  // Loeschen von 18
  keyVector.push_back(18);
  removeKeys(btree, keyVector, details);
  keyVector.clear();    
  
  // Einfuegen von 29
  tupleVector.push_back(Tuple(29, "neunundzwanzig"));  
  insertTuples(btree, tupleVector, details);
  tupleVector.clear();    
  
  // Einfuegen von 13
  tupleVector.push_back(Tuple(13, "dreizehn"));  
  insertTuples(btree, tupleVector, details);
  tupleVector.clear();      
  
  // Einfuegen von 14
  tupleVector.push_back(Tuple(14, "vierzehn"));  
  insertTuples(btree, tupleVector, details);
  tupleVector.clear();    

  // Einfuegen von 56, 57, 58
  tupleVector.push_back(Tuple(56, "sechsundfuenfzig"));  
  tupleVector.push_back(Tuple(57, "siebenundfuenfzig"));  
  tupleVector.push_back(Tuple(58, "achtundfuenfzig"));      
  insertTuples(btree, tupleVector, details);
  tupleVector.clear();  

  // Einfuegen von 59  
  tupleVector.push_back(Tuple(59, "neunundfuenfzig"));    
  insertTuples(btree, tupleVector, details);
  tupleVector.clear();
  
  // Einfuegen von 53, 54, 60, 61
  tupleVector.push_back(Tuple(53, "dreiundfuenfzig"));  
  tupleVector.push_back(Tuple(54, "vierundfuenfzig"));  
  tupleVector.push_back(Tuple(60, "sechzig"));      
  tupleVector.push_back(Tuple(61, "einundsechzig"));        
  insertTuples(btree, tupleVector, details);
  tupleVector.clear();    
  
  // Einfuegen von 65
  tupleVector.push_back(Tuple(65, "fuenfundsechzig"));        
  insertTuples(btree, tupleVector, details);
  tupleVector.clear();    
  
  try 
  {
    cout << "Nochmaliges Einfuegen von 65... ";
    Tuple tuple = Tuple(65, "fuenfundsechzig");
    bool inserted = btree->insert(tuple);        
    if (inserted) FAILED(cout);
    else OKAY(cout);
  }
  catch (ErrorObj e)
  {
    cout << e;
    exit(-1);
  }
  
  // Oeffnen eines existierenden B-Baums
  bmgr->closeFile(fileNo);
  delete btree;
  
  bmgr->openFile("btreeTestFile.tab", fileNo);
  btree = new BTree(fileNo, *bmgr);   
  cout << "Neu eingelesener B-Baum" << endl << *btree;        
  
  bmgr->closeFile(fileNo);
  bmgr->dropFile("btreeTestFile.tab");
  delete btree;
  
}




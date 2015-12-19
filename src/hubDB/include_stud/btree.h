#ifndef _BTREE_H_
#define _BTREE_H_

#include <global.h>
#include <bufferMgr.h>


class BTree
{ 
  
  public: 
  
   
    friend ostream & operator<<(ostream & stream,BTree & btree); 
   
    /*
     * Durchsucht den B-Baum nach dem gegebenen key.
     * 
     * Rueckgabewert: gefundenes Tupel oder NULL
     */
    Tuple* find(int *key);
   
    /*
     * Einfuegen des gegebenen Tupels in den B-Baum.
     * 
     * Rueckgabewert: true, falls insert erfolgreich war
     * false, falls ein Tupel mit der gegebenen id existiert
     */
    bool insert(Tuple &tuple);
    
    /*
     * Entfernt das Tupel mit dem gegebenen Key aus dem B-Baum. 
     * 
     * Rueckgabewert: true, falls Entfernen erfolgreich war
     * false, falls kein Tupel mit der gegebenen id existiert
     */
    bool remove(int &key);

    /*
     * Statische Methode zum Testen des B-Baums. Die Testroutine soll
     * saemtliche Funktionalitaeten des B-Baums in geeigneter Weise
     * demonstrieren und testen. Die Implementierung dieser Methode ist in 
     * einer separaten Datei mit dem Namen btree_test.cpp abzugeben. 
     * 
     * Wenn 
     * das Flag details den Wert true hat, sollen neben den Statusmeldungen 
     * der einzelnen Testschritte (OKAY, FAILED) weitere Details ueber den 
     * internen Zustand der wichtigsten Variablen des Filemanagers ausgegeben
     * werden.
     */
    static void test(bool details);

};

typedef BTree * BTreePtr;


#endif /* _BTREE_H_ */


//
// Die globalen Definitionen umfassen eine Reihe einfacher Typdefinitionen und
// Konstanten, die von den einzelnen Modulen des Datenbanksystems hubdb
// verwendet werden.
//
// ------------------------------------------------------------------------
//

#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>

#ifdef __cplusplus
#include <iostream>
#include <string>
using namespace std;
#include <errorObj.h>
#endif

#if (__SUNPRO_CC == 0x410)
typedef enum { true=1, false=0 } bool;
#endif

//
// Allg. Typdefinitionen (Synonyme)
//
typedef unsigned long ulong;
typedef unsigned int uint;
typedef ulong FileNo;
typedef ulong PageNo;
typedef ulong BlockNo;
typedef char * PagePtr;

//
// FileManager
//

// Maximale Anzahl an gleichzeitig geöffneten Dateien im Filemanager
const int MAXOPENFILES = 64;

//Fester SUFFIX der Dateien, die Tabellen der Datenbank repraesentieren
const string TABLEFILESUFFIX = ".tab";

//
// Buffermanager
//

// maximale Groesse des Bufferpools
const int MAXPOOLSIZE = 64;

// Definition der einzelnen Modi, mit denen eine Seite im Buffermanager
// angelegt wird. Bestimmen die Methoden, mit denen auf die Inhalte der
// Seite zugegriffen werden kann.
enum Lock {
  LOCK_FREE,       // no lock
  LOCK_S,          // shared lock
  LOCK_X           // exclusive lock
};

//
// Indexmanager
//

// Maximale und Minimale Anzahl von Tupeln in einem Knoten des B-Baums
const int MAX_ENTRY = 4;
const int MIN_ENTRY = 2;

//Maximale Anzahl gleichzeitig geoeffneter B-Baeume
const int MAXOPENINDEXES = 3;

//
// Div. Konstanten bezueglich der Groesse von Tupeln, B-Baum-Knoten, Seiten
// und Bloecken.
//

// Laenge eines Namens im Tupel
const int NAME_LENGTH = 28;

const int TUPLESIZE = sizeof(int) + NAME_LENGTH*sizeof(char);
const int ENTRYSIZE = TUPLESIZE + sizeof(PageNo);
const int PAGESIZE = 2*sizeof(int) + (MAX_ENTRY+1)*ENTRYSIZE;
const int BLOCKSIZE = PAGESIZE;

#endif // _GLOBAL_H_

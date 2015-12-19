//
// Die Klassendefinition enthaelt nur die zu implementierende
// Schnittstelle (public) ! Implementationsspezifische Details sind
// in geeigneter Weise zu ergaenzen.
//
// ------------------------------------------------------------------------
//
//
// TableInfo kapselt die (Meta-)Informationen einer Tabelle, die vom
// Systemkatalog zurueckgegeben werden. Dies sind (i) der Tabellenname,
// (ii) die Groeﬂe der Tabellendatei in (Datenbank-)Bloecken und
// (iii) das Datum der letzten Modifikation der Datei.
//

#ifndef _TABLEINFO_H_
#define _TABLEINFO_H_

#include <global.h>

#include <sys/types.h>

class TableInfo
{

 public:

  //
  // Erzeugt ein TableInfo-Objekt mit den entsprechenden Informationen
  //
  TableInfo(string& tableName, ulong blockCount, time_t& modificationTime);
  ~TableInfo();

  //
  // Methoden zum Abfragen der Informationen einer Tabellendatei
  //
  const string& getTableName();

  ulong getBlockCount();

  const time_t& getModificationTime();

 private:

  string tableName;
  ulong blockCount;
  time_t modificationTime;
};
#endif // _TABLEINFO_H_

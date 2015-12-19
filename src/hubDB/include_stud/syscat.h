//
// Die Klassendefinition enthaelt nur die zu implementierende
// Schnittstelle (public) ! Implementationsspezifische Details sind
// in geeigneter Weise zu ergaenzen.
//
// ------------------------------------------------------------------------
//
//
// Der Systemkatalog ermöglicht ein Auflisten der Tabellen im aktuellen
// Datenbankverzeichnis. Für jede dieser Tabellen werden eine Reihe von
// Metainformationen zuruckgegeben.
//

#ifndef _SYSCAT_H_
#define _SYSCAT_H_

#include <global.h>
#include <tableInfo.h>

#include <sys/stat.h>
#include <dirent.h>

#include <list>

class SysCat
{

 public:

  //
  // Hier sollten keine speziellen Aktionen notwendig sein. 
  //
  SysCat();
  ~SysCat();

  //
  // listTables() listet saemtliche Dateien mit der Endung .tab im
  // angegebenen Verzeichnis auf. Die Rueckgabe erfolgt ueber das
  // angegebene Listenelement, welches pro Tabelle ein Objekt der
  // Klasse TableInfo enthaelt.
  // Zu jeder Datei werden folgende Informationen ausgegeben:
  //
  // - der Dateiname (ohne die Endung .tab). Dies entspricht dem Namen
  //   der Tabelle, die durch die Datei repraesentiert wird.
  // - die Groesse der Datei in (Datenbank-)Bloecken
  // - das Datum der letzten Modifikation der Datei
  // 
  void listTables(const string& directory, list<TableInfo>& tableInfoList);

};

#endif // _SYSCAT_H_

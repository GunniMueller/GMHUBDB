//
// Die Klassendefinition enthaelt nur die zu implementierende
// Schnittstelle (public) ! Implementationsspezifische Details sind
// in geeigneter Weise zu ergaenzen.
//
// ------------------------------------------------------------------------
//
//
// Der File Manager erlaubt das Anlegen, Loeschen, Oeffnen, Schliessen,
// Schreiben und Lesen von Dateien auf dem Sekundaerspeichermedium
// (UNIX-Filesystem).
//
// Der Dateiname wird durch das aufrufende Modul festgelegt.
//
// Der File Manager verwaltet alle Dateien des Datenbank-Management-Systems
// (DBMS), demzufolge gibt es auch nur eine Instanz von ihm.
//
// Die Lese- und Schreiboperationen ermoeglichen in der Datei einen 
// Speicherbereich (Block) zu lesen bzw. zu schreiben. Bloecke werden mit 
// 0 .. N-1 nummeriert.
//

#ifndef _FILEMGR_H_
#define _FILEMGR_H_

#include <global.h>
#include <blockBuffer.h>

class FileMgr
{

 public:

  //
  // Der FileManager erhaelt als Parameter die maximale Anzahl gleichzeitig
  // geoeffneter Dateien. Per Default ist dies MAXOPENFILES.
  //
  FileMgr(uint max = MAXOPENFILES);

  //
  // Der Filemanager wird beendet, wenn das gesammte Programm beendet wird.
  // In diesem Fall sind keine speziellen "Aufraeumarbeiten" notwendig.
  //
  ~FileMgr();

  //
  // Statische Methode zum Testen des Filemanagers. Die Testroutine soll
  // saemtliche Funktionalitaeten des Filemanagers in geeigneter Weise
  // demonstrieren und testen. Die Implementierung dieser Methode ist in
  // einer separaten Datei mit dem Namen fileMgrTest.cpp abzugeben. Wenn
  // das Flag details den Wert true hat, sollen neben den Statusmeldungen
  // der einzelnen Testschritte (OK, ERROR) weitere Details ueber den
  // internen Zustand der wichtigsten Variablen des Filemanagers ausgegeben
  // werden.
  //
  static int test(bool details);

  //
  // Der Operator << wird für Objekte der Klasse fileMgr definiert und soll
  // der Ausgabe des aktuellen Zustands des Filemanagers dienen. Dabei sollen
  // u.a. die Namen der momentan geoeffneten Dateien sowie deren Groesse (in
  // Anzahl an Bloecken) ausgegeben werden, sowie alle weiteren Informationen,
  // die intern zur Verwaltung offener Dateien verwendet werden.
  //
  friend ostream& operator<<(ostream& stream, FileMgr& fMgr);

  //
  // create() erzeugt eine Datei mit dem Namen fileName. Dies entspricht
  // einem CREATE TABLE. Die erzeugte Datei wird als geoeffnete Datei im
  // Filemanager gehalten. Als Ergebnis wird in der Variable fileNo der
  // interne Identifikator der geoeffneten Datei zurueckgegeben. Ueber diesen
  // kann dann u.a. die Datei geschrieben und gelesen werden.
  //
  // Fuer folgende Situationen sind u.a. geeignete Ausnahmen zu erzeugen:
  // 
  // - die zu erzeugende Datei existiert bereits und darf deshalb nicht
  //   mit einer leeren Datei ueberschrieben werden.
  //
  void create(const string& fileName, FileNo& fileNo);

  //
  // drop() loescht die Datei mit dem Namen fileName. Dies entspricht
  // einem DROP TABLE. Es ist sicherzustellen, dass die Datei nicht
  // geoeffnet ist.
  //
  // Fuer folgende Situationen sind u.a. geeignete Ausnahmen zu erzeugen:
  // 
  // - die zu loeschende Datei existiert nicht.
  // - die zu loeschende Datei ist noch geoeffnet
  //
  void drop(const string& fileName);

  //
  // open() oeffnet die Datei mit dem Namen fileName. Alle Dateien werden
  // im READ/WRITE-Modus geoeffnet. Als Ergebnis wird in der Variable fileNo
  // der interne Identifikator der geoeffneten Datei zurueckgegeben. Sollte
  // die Datei bereits geoeffnet sein, so wird die dafuer existierende
  // FileNo im Ergebnis geliefert. Intern ist deshalb ein Zaehler fuer jede
  // geoeffnete Datei zu verwalten, der bei open() inkrementiert und bei
  // close() dekrementiert wird.
  //
  // Fuer folgende Situationen sind u.a. geeignete Ausnahmen zu erzeugen:
  // 
  // - die zu oeffnende Datei existiert nicht.
  //
  void open(const string& fileName, FileNo& fileNo);

  //
  // close() schliesst die Datei mit dem Identifikator fileNo und gibt die
  // internen Ressourcen frei.
  //
  // Fuer folgende Situationen sind u.a. geeignete Ausnahmen zu erzeugen:
  // 
  // - die zu schliessende Datei ist nicht geoeffnet.
  //
  void close(FileNo fileNo);

  //
  // read() liest den ueber blockBuffer spezifizierten Block aus der Datei
  // mit dem Identifikator fileNo in den Speicher. Dies erfolgt durch
  // Aufruf der entsprechenden Routine des BlockIOBuffer, ueber den dann auch
  // der Inhalt des Blocks im Hauptspeicher referenziert werden kann.
  //
  // Fuer folgende Situationen sind u.a. geeignete Ausnahmen zu erzeugen:
  // 
  // - es soll ein Block gelesen werden, der in der Datei nicht existiert
  // - die Datei ist nicht geoeffnet, d.h. die fileNo ist nicht zugeordnet
  //
  void read(FileNo fileNo, BlockBuffer& blockBuffer);

  //
  // write() schreibt den Inhalt des blockBuffer in die Datei mit dem
  // Identifikator fileNo. Falls der betreffende Block noch nicht in
  // der Datei vorhanden ist, muss die Datei zuvor erweitert werden.
  //
  // Fuer folgende Situationen sind u.a. geeignete Ausnahmen zu erzeugen:
  // 
  // - die Datei ist nicht geoeffnet, d.h. die fileNo ist nicht zugeordnet
  // - die Blocknummer des blockBuffer ist ungueltig, d.h.< 0
  //
  void write(FileNo fileNo, BlockBuffer& blockBuffer);

  //
  // getBlockCount() gibt die Groesse der Datei in Anzahl an Bloecken
  // zurueck.
  //
  // Fuer folgende Situationen sind u.a. geeignete Ausnahmen zu erzeugen:
  // 
  // - die Datei ist nicht geoeffnet, d.h. die fileNo ist nicht zugeordnet
  //
  ulong getBlockCount(FileNo fileNo);

  //
  // disconnect() schliesst saemtliche geoeffneten Dateien, gibt die Ressourcen
  // frei und versetzt den Filemanager in einen initialen Zustand.
  //
  void disconnect();

};

#endif /* _FILEMGR_H_ */

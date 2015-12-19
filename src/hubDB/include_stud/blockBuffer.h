//
// Die Klassendefinition enthaelt nur die zu implementierende
// Schnittstelle (public) ! Implementationsspezifische Details sind
// in geeigneter Weise zu ergaenzen.
//
// ------------------------------------------------------------------------
//
//
// Der BlockBuffer repraesentiert einen Block fester Nummer im Hauptspeicher.
// Es kann direkt auf die aktuellen Inhalte des Blocks zugegriffen werden.
// Zwei zusaetzliche Methoden ermoeglichen es, den Inhalt des Blocks vom
// Sekundaerspeichermedium zu lesen bzw. dorthin zu schreiben.
//

#ifndef _BLOCKBUFFER_H_
#define _BLOCKBUFFER_H_

#include <fstream>
#include <global.h>

//
// Testet, ob ein STREAM verwendbar ist oder nicht. Im Fehlerfall (bad()=true)
// sind nicht behebbare Fehler aufgetreten.
//
#define CHECK_STREAM(s)   if(s.bad()==true){ THROW_SYS_ERROR;}

class BlockBuffer
{

 public:

  //
  // Bei der Instanziierung von Objekten der Klasse BlockBuffer wird
  // die Nummer des Blocks angegeben, den das Objekt repraesentiert.
  // Der Default-Wert ist 0.
  //
  BlockBuffer(ulong blockNum=0);
  ~BlockBuffer();

  //
  // Gibt die Groesse des Blocks in Bytes zurueck (konstanter Wert)
  //
  size_t getBlockSize();

  //
  // Liefert einen Zeiger auf den Speicherbereich, in dem der Inhalt des
  // Blocks abgelegt ist. Die Gueltigkeit des Inhaltes dieses Speicherbereichs
  // ist von dem aufrufenden Modul sicherzustellen. So muss z.B. der
  // BufferManager sicherstellen, dass der Inhalt des Blocks gelesen wurde,
  // bevor andere Module darauf zugreifen. Diese Ueberpruefung findet nicht
  // im BlockBuffer selber statt.
  //
  char * getBlockPtr();

  //
  // Liefert die Nummer des Blocks, der durch dieses Objekt repraesentiert
  // wird.
  //
  ulong getBlockNum();

 protected:

  //
  // Diese Methoden sind nur vom FileManager oder einer anderen, von ihm
  // zur Verwaltung offener Dateien verwendeten Klasse aufzurufen.
  //
  // Bsp. friend FileMgr;
  //

  //
  // Schreibt den Inhalt des repraesentierten Blocks auf den angegebenen
  // Stream.
  //
  void writeToStream(fstream &stream);

  //
  // Liest den Inhalt des repraesentierten Blocks von dem angegebenen
  // Stream.
  //
  void readFromStream(fstream &stream);

 private:

  //
  // Speicherbereich fuer den Blockinhalt
  //
  char data[BLOCKSIZE];

  //
  // Blocknummer, die bei der Initialisierung uebergeben wurde
  //
  const ulong blockNum;
};


#endif // _BLOCKBUFFER_H_

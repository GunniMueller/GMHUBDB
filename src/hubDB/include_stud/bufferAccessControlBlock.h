//
// Die Klassendefinition enthaelt nur Basismethoden der zu implementierenden 
// Schnittstelle (public) ! Implementationsspezifische Details sind 
// in geeigneter Weise zu ergaenzen.
//
// ------------------------------------------------------------------------
//
// Der Buffer Access Control Block ist die Datenstruktur, ueber die die
// ueberliegenden Module auf die von Buffermanager verwalteten Seiten im
// Hauptspeicher zugreifen können. Der BACB stellt eine Kapselung eines
// BCB fuer die aufrufenden Module dar.
//

#ifndef _BufferAccessControlBlock_H_
#define _BufferAccessControlBlock_H_

#include <global.h>
#include <bufferControlBlock.h>

class BufferAccessControlBlock
{
 public:
  friend class BufferMgr;
  
  BufferAccessControlBlock(BCB & refBCB);
  
  ~BufferAccessControlBlock();

  friend ostream & operator<<(ostream & stream, BufferAccessControlBlock & bacb);

  //
  // Liefert einen Zeiger auf den Hauptspeicherbereich, in dem die
  // Daten der durch den BCB verwalteten Seite stehn. Sollte diese
  // nicht initialisiert sein, so ist der Zeiger NULL.
  //
  char * getDataPtr();

  //
  // Liefert die Nummer der Seite, auf die durch den BACB zugegriffen
  // werden kann.
  //
  PageNo getPageNo();
  
  //
  // Setzt das Modified-Flag im gekapselten BCB. Muss von den ueberliegenden
  // Modulen aufgerufen werden, sobald sie den Inhalt der verwalteten Seite
  // veraendert haben.
  void setModified();

  /* ... */

 private:
  BCB & refBCB;
};

typedef BufferAccessControlBlock BACB;

#endif // _BufferAccessControlBlock_H_

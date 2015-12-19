//
// Die Klassendefinition enthaelt nur Basismethoden der zu implementierenden
// Schnittstelle (public) ! Implementationsspezifische Details sind 
// in geeigneter Weise zu ergaenzen.
//
// ------------------------------------------------------------------------
//
// Der Buffer Control Block (BCB) stellt ein Frame des Bufferpools dar.
// Er verwaltet eine Page-Objekt, welches wiederum die logische Sicht
// auf eine Datei in Form von Seiten realisiert.
//

#ifndef _BufferControlBlock_H_
#define _BufferControlBlock_H_

#include <global.h>
#include <page.h>

class BufferControlBlock
{
  public:
    friend class BufferMgr;

    BufferControlBlock(Lock lock=Lock(0));
    ~BufferControlBlock();

    //
    // Liefert das ueber den BCB verwaltete Page-Objekt
    //
    Page & getPage();
    
    //
    // Liefert einen Zeiger auf den Hauptspeicherbereich, in dem die
    // Daten der durch den BCB verwalteten Seite stehn. Sollte diese
    // nicht initialisiert sein, so ist der Zeiger NULL.
    //
    char * getDataPtr();
    
    //
    // Setzt das Modified-Flag. Muss gesetzt werden, wenn das ueberliegende
    // Modul ueber das BACB-Objekt mitteilt, dass der Inhalt der Seite
    // veraendert worden ist.
    //
    void setModified();

    friend ostream & operator<<(ostream & stream, BufferControlBlock & bcb);

    /* ... */


  private:
    Page page;     // identifiziert die Seite, die durch den Kontrollblock referenziert wird
    Lock lock;     // Sperre mit der die Seite geladen wurde
    bool init;     // 'true', sobald die erste Seite in den BCB geladen, sonst 'false'
    bool modified; // 'true', wenn die Seite modifiziert wurde, sonst 'false'
    int fixcount;  // Anzahl der Zugriffe auf die betrachtete Seite

    /* ... */

};

typedef BufferControlBlock BCB;

#endif // _BufferControlBlock_H_

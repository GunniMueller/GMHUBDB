//
// Die Klassendefinition enthaelt nur die zu implementierende
// Schnittstelle (public) ! Implementationsspezifische Details sind
// in geeigneter Weise zu ergaenzen.
//
// ------------------------------------------------------------------------
//
// Der Buffermanager fungiert als Vermittler zwischen dem Dateisystem und
// den Zugriffsmodulen (z.B. Tupelmanager, Recoverymanager, Indexmanager etc).
// Alle diese Module arbeiten auf Seitenbasis, d.h., jedes Datentupel in
// einer Seite wird durch die Adresse der Seite und dem relativen Offset des
// Tupels innerhalb der Seite identifiziert.
// Der Buffermanager garantiert eine logische Sicht in Form von Seiten auf
// die Datei. Er uebersetzt dazu eine Seitenadresse in eine Blockadresse
// des Filemangers in der physischen Datei. Im Praktikum ist das eine triviale
// Uebersetzung - eine Seite entspricht einem Block. Es gibt also eine
// statische 1:1 Uebersetzung zwischen Seiten und Bloecken.
// Die Hauptaufgabe des Buffermanager besteht darin, die benoetigten Seiten
// bzw. Bloecke vom Dateisystem in den Hauptspeicherbereich des
// Datenbanksystems zu transferieren. Dieser Hauptspeicherbereich besteht
// aus einer Liste von so genannten Frames, die vom Buffermanager verwaltet
// werden - dabei kann jeder Frame genau eine Seite aufnehmen. Die Liste wird
// als Bufferpool bezeichnet. Es gibt nur eine Instanz eines Buffermanagers
// in hubdb.
//

#ifndef _BUFFERMGR_H_
#define _BUFFERMGR_H_

#include <global.h>
#include <fileMgr.h>
#include <bufferControlBlock.h>
#include <bufferAccessControlBlock.h>

class BufferMgr
{

  public:
    BufferMgr(int frameCount=MAXPOOLSIZE);
    ~BufferMgr();

    friend ostream & operator<<(ostream & stream, BufferMgr & bMgr);

    //
    // createFile() legt eine neue Datei im Filemanager an und öffnet diese
    //
    void createFile(const string & fileName, FileNo & fileNo);

    //
    // openFile() öffnet eine existierende Datei im Filemanager
    //
    void openFile(const string & fileName, FileNo & fileNo);

    //
    // closeFile() schliesst eine existierende und geöffnete Datei
    // im Filemanager
    //
    void closeFile(FileNo fileNo);

    //
    // dropFile() löscht eine existierende Datei im Filemanager
    //
    void dropFile(const string & fileName);

    //
    // fixNewPage() fordert eine leere Seite im Bufferpool an.
    // Die pageID muss vom Aufrufer mitgeteilt werden. Analog zu
    // fix() kann ueber die Seitenadresse in BACB auf die Seite
    // zugegriffen werden.
    //
    // @return BACB-Objekt der angeforderten Seite
    //
    BACB * fixNewPage(PageID & pageID, Lock mode);

    //
    // fixPage() fordert eine existierende Seite im Bufferpool an.
    // War der Aufruf erfolgreich, kann ueber die Seitenadresse in BACB
    // auf die Seite zugegriffen werden. Der Fix Counter wird um 1 erhoeht.
    // Das schuetzende Lock wird im angegebenen Modus angefordert
    // (shared bzw. exclusive).
    //
    // @return BACB-Objekt der angeforderten Seite
    //
    BACB * fixPage(PageID & pageID, Lock mode);

    //
    // unfixPage() erniedrigt falls möglich den Fix Counter der Seite um 1.
    // Wenn die Anzahl der Fixierungen einer Seite gleich null ist (nach
    // fixcount-1), darf die entsprechende Seite verdraengt werden.
    // Der Buffer Manager gibt den BACB frei und setzt den Zeiger auf NULL.
    //
    void unfixPage(BACB * access);

    //
    // flushPage() schreibt die Seite in ihrem zugehoerigen Block in die
    // Datei. Das Modified Flag im BufferControlBlock wird zurueckgesetzt
    // (false), die Seite bleibt im Puffer. Diese Methode kann von jedem
    // Client gerufen werden.
    //
    void flushPage(BACB * access);

    //
    // Statische Methode zum Testen des Buffermanagers. Die Testroutine soll
    // saemtliche Funktionalitaeten des Buffermanagers in geeigneter Weise
    // demonstrieren und testen. Die Implementierung dieser Methode ist in
    // einer separaten Datei mit dem Namen test_bufferMgr.cpp abzugeben. Wenn
    // das Flag details den Wert true hat, sollen neben den Statusmeldungen
    // der einzelnen Testschritte (OKAY, FAILED) weitere Details ueber den
    // internen Zustand der wichtigsten Variablen des Filemanagers ausgegeben
    // werden.
    //
    static void test(bool details);

    //
    // Fuehrt saemtliche benoetigten Aktionen aus, um den Buffermanager in
    // einen initialen Zustand zu versetzen. Ruft dann die entsprechende
    // Methode des Filemanagers auf.
    //
    void disconnect();

    //
    // Gibt die Groesse der Datei in Anzahl an Seiten zuruck.
    //
    ulong getPageCount(FileNo fileNo);

  private:
  	FileMgr * fileMgr;

};

#endif // _BUFFERMGR_H_


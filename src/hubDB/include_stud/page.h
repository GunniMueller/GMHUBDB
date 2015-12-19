// Die Klassendefinition enthaelt nur Basismethoden der zu implementierenden
// Schnittstelle (public) ! Implementationsspezifische Details sind
// in geeigneter Weise zu ergaenzen.
//
// ------------------------------------------------------------------------
//
// Reprasentiert eine logische Seite einer Datei, die wiederum einem
// Block in dieser Datei entspricht. Der Zugriff auf den Inhalt der
// Seite bzw. des Blocks erfolgt ueber die Klasse BlockBuffer
//

#ifndef _PAGE_H_
#define _PAGE_H_

#include <fstream>
#include <blockBuffer.h>
#include <global.h>

//
// Identifyer einer Seite, bestehend aus Seitennummer und Dateinummer. Die
// Seitennummer wird 1:1 in die Nummer des zugehoerigen Blocks der Datei
// uebersetzt.
//
class PageID
{

  public:
    PageID(FileNo fileNo=0,PageNo pageNo=0):
      fileNo(fileNo),
      pageNo(pageNo){};
    ~PageID(){};

    //
    // Methoden zum Lesen und Setzen der Dateinummer
    //
    void   setFileNo(FileNo fileNo) { this->fileNo=fileNo; };
    FileNo getFileNo() { return fileNo; };

    //
    // Methoden zum Lesen und Setzen der Seitennummer
    //
    void   setPageNo(PageNo pageNo) { this->pageNo=pageNo; };
    PageNo getPageNo() { return pageNo; };

    //
    // Vergeleichsoperator
    //
    bool operator==(PageID & ref)
    {
      return ( (ref.getFileNo() == getFileNo()) &&
               (ref.getPageNo() == getPageNo()) );
    };

    friend ostream & operator<<(ostream & stream,PageID & pageId);

  private:
    FileNo  fileNo;  // file to which the page belongs
    PageNo  pageNo;  // page number in the file

};

inline ostream & operator<<(ostream & stream,PageID & pageId)
{
  stream << "(FNo: " << pageId.getFileNo() << ","
    	 << " PNo: " << pageId.getPageNo()<< ")";
  return stream;
}


class Page
{
 public:
  Page();
  ~Page();

  //
  // Der Bezeichner der repraesentierten Seite
  //
  PageID & getPageID();

  //
  // Zugriff auf das BlockBuffer-Objekt, ueber welches die Daten des
  // zugehoerigen Blockes und somit der repraesentierten Seite verwaltet
  // und zugegriffen werden.
  //
  BlockBuffer * getBlockObj();
  void setNewBlockObj(BlockBuffer *);

  //
  // Liefert einen Zeiger auf den Hauptspeicherbereich, in dem die
  // Daten der verwalteten Seite stehn.
  //
  char * getDataPtr();

  //
  // Ausgabeoperator
  //
  friend ostream & operator<<(ostream & stream,Page & page);

 private:
  PageID pageID;
  BlockBuffer * blockObj;
};

inline ostream & operator<<(ostream & stream,Page & page)
{
  stream << page.getPageID() << " | "
    	 << hex << "0x" << (void*)page.getDataPtr() << dec;
  return stream;
}

#endif // _PAGE_H_

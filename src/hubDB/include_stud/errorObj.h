//
//
// Die Klassendefinition enthaelt nur die zu implementierende
// Schnittstelle (public) ! Implementationsspezifische Details sind
// in geeigneter Weise zu ergaenzen.
//
// ------------------------------------------------------------------------
//
// Das Fehlerobjekt errorObj dient der Fehlerbehandlung im Datenbanksystem
// hubdb. In saemtlichen Fehlersituationen ist ein solches Objekt zu erzeugen.
// Die Fehlerobjekte werden von der Execution Engine abgefangen, die dann
// die zugehoerige Fehlermeldung ausgibt. Jeder Fehler besteht aus einer
// Major- und einer Minor-Error-Number. Erstere sind vorgegeben und
// spezifizieren die Komponente, in der der Fehler auftrat. Dabei ist zu
// beachten, dass Laufzeitfehler des UNIX-Systems als eingene "Major"-
// Fehlerklasse definiert sind, d.h. Systemfehler wie z.B. beim Oeffnen
// von Dateien werden hierueber gekapselt bzw. zurueckgegeben. Fuer interne
// Fehler der Module von hubdb (z.B. schreiben auf eine Datei, die nicht
// geoffnet worden ist) sind geeignete Minor-Fehler zu definieren, zusammen
// mit ihren zugehoerigen Fehlermeldungen, die dann von der Execution Engine
// ausgegeben werden.
//

#ifndef _ERROROBJ_H_
#define _ERROROBJ_H_

#include <global.h>

typedef uint MinorErrorCode;

class ErrorObj
{

 public:

  //
  // Liste der "Major-Error-Codes".
  //
  enum MajorErrorCode{
    UNKNOWN_ERROR = -1,
    SYSTEM_ERROR = 0,
    FILE_MGR_ERROR = 1,
    BUFFER_MGR_ERROR = 2,
    IDX_MGR_ERROR = 3,
    SYSCAT_ERROR = 4,
    EXEC_ENGINE_ERROR = 5
  };

  //
  // Konstruktoren und Destruktoren zum Erzeugen und "Durchreichen" von
  // Fehlerobjekten (inklusive Implementierung)
  //
  ErrorObj(MajorErrorCode majorError = UNKNOWN_ERROR, MinorErrorCode minorError = 0):
    majorError(majorError),
    minorError(minorError)
      {};
  ~ErrorObj(){};

  ErrorObj(ErrorObj & ref):
    majorError(ref.majorError),
    minorError(ref.minorError)
      {};

  ErrorObj(const ErrorObj & ref):
    majorError(ref.majorError),
    minorError(ref.minorError)
      {};

  //
  // Operator zur Ausgabe von Fehlerobjekten. Implementierung siehe unten.
  //
  friend ostream & operator << ( ostream & stream, ErrorObj e);

  //
  // Liefert die Nummer des Minor-Error
  //
  MinorErrorCode getMinorError();

  //
  // Liefert die Nummer des Major-Error
  //
  MajorErrorCode getMajorError();

  //
  // Zugehoerige Fehlermeldung des Minor-Error (abhaenig vom
  // aktuellen Major-Error).
  //
  string getMinorErrorMsg();

 protected:

  MajorErrorCode majorError;
  MinorErrorCode minorError;
};

//
// Implementierung des Ausgabeoperators
//
inline ostream & operator << ( ostream & stream, ErrorObj e)
{
  switch(e.majorError){
  case ErrorObj::SYSTEM_ERROR:
    stream << "SYSTEM_ERROR: " << strerror(e.minorError) << endl;
    break;
  case ErrorObj::FILE_MGR_ERROR:
    stream << "FILE_MGR_ERROR " << e.getMinorErrorMsg() << endl;
    break;
  case ErrorObj::BUFFER_MGR_ERROR:
    stream << "BUFFER_MGR_ERROR " << e.getMinorErrorMsg() << endl;
    break;
  case ErrorObj::IDX_MGR_ERROR:
    stream << "IDX_MGR_ERROR " << e.getMinorErrorMsg() << endl;
    break;
  case ErrorObj::SYSCAT_ERROR:
    stream << "SYSCAT_ERROR " << e.getMinorErrorMsg() << endl;
    break;
  case ErrorObj::EXEC_ENGINE_ERROR:
    stream << "EXEC_ENGINE_ERROR " << e.getMinorErrorMsg() << endl;
    break;
  case ErrorObj::UNKNOWN_ERROR:
    stream << "UNKNOWN_ERROR " << e.getMinorErrorMsg() << endl;
    break;
  default:
    stream << "UNKNOWN_ERROR-"<<e.majorError << " " << e.getMinorErrorMsg() << endl;
  }
  return stream;
};

//
// Makros zum "Werfen" von Fehlerobjekten
//
#define THROW_SYS_ERROR throw ErrorObj(ErrorObj::SYSTEM_ERROR,errno)
#define THROW_ERROR(major,minor) throw ErrorObj(ErrorObj::major,minor)

//
// Makros zur Ausgabe einfacher Statusmeldungen
//
#define OKAY(stream) stream << "OKAY" << endl
#define FAILED(stream) stream << "FAILED" << endl


#endif // _ERROROBJ_H_

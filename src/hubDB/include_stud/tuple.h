#ifndef _TUPLE_H_
#define _TUPLE_H_

#include <global.h>

class Tuple{
 public:
 
  Tuple( char * buffer);
  
  Tuple(int id,char *name);    

  Tuple (const Tuple &tuple);
   
  ~Tuple();
  
  friend ostream & operator << (ostream & stream,Tuple & t);
  friend istream & operator >> (istream & stream,Tuple & t);
 
  /*
   * get and set id
   */
  int getId();
  void setId(int id);

  /*
   * get and set name
   */
  char * getName();
  void setName(const char * name);
  
  /*
   * interpretiere ptr als Zeiger auf int, char* und 
   * kopiere Inhalt nach id und name 
   */
  void readFromBuffer(char * ptr);

  /*
   * kopiere Inhalt von id und name 
   * nach ptr als Zeiger auf int, char*
   */
  void writeToBuffer(char * ptr);

  /*
   * Rueckgabewert: maximale Groesse eines Tupels
   */
  size_t getSize(){ return sizeof(int)+sizeof(char )*NAME_LENGTH;};
  
 protected:
};

#endif

#ifndef LANGUAGE_HH
#define LANGUAGE_HH

#include<vector>
#include<iostream>
#include<ncurses.h>
#include<fstream>
#include<string>

/*
 *File describes Language class
 */

enum Status{DEAD=0, ALIVE=1}; //status of a language

class Language{
private:
  std::string name;
  Status status;
  Language* parent; //language's parent
public:

  std::string& getName(){return name;}
  Status& getStatus(){return status;}
  Language* getParent(){return parent;}
  void setParent(Language* p){parent = p;}

  /*
   *this method gets all ancestors of a language and puts them in genLine
   */
  void getAllAncestors(std::vector<Language>* genLine);

  /*
   * this method writes a language on the screen using ncurses
   */
  void write(int r, int c);

  
  Language(){parent = nullptr;} //setting parent to nullptr for safety
};

/*
 * this method reads information about a language from a file
 */
std::fstream& operator>>(std::fstream& file, Language& l);


#endif

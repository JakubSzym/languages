#include "language.hh"

using namespace std;

void Language::getAllAncestors(vector<Language>* genLine){
  //checking if the Proto-Lamguage is reached
  if(parent != nullptr){
    genLine->push_back(*parent); //adding another ancestor to the genetic line
    parent->getAllAncestors(genLine); //using recursion to find the next ancestor
  }
}

void Language::write(int r, int c){
  if(status == ALIVE){
    attron(A_REVERSE);
    mvprintw(r, c, "%s", name.c_str());
    attroff(A_REVERSE);
  }else if(status == DEAD)
    mvprintw(r, c, "%s", name.c_str());
}

fstream& operator>>(fstream& file, Language& l){
  int help;
  file >> l.getName() >> help;
  if(help==0){
    l.getStatus() = DEAD;
  }else if(help==1){
    l.getStatus() = ALIVE;
  }
  return file;
}

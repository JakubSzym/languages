#ifndef FAMILY_HH
#define FAMILY_HH

#include "language.hh"

#include<string.h>

/*
 *This file describes Family class
 */

class Family{
private:
  std::string familyName;
  Language protoLanguage;
  std::vector<Family> subfamilies;
  std::vector<Language> members;
public:

  std::string& getFamilyName(){return familyName;}
  Language& getProtoLanguage(){return protoLanguage;}
  std::vector<Family>& getSubfamilies(){return subfamilies;}
  std::vector<Language>& getMembers(){return members;}

  /*
   * this method shows a family on a screen - it's simplified
   * It prints family members and names of subfamilies
   */
  void showFamily();

  /*
   *It finds a branch of a family and return a pointer
   *so you can easily use the result with showFamily()
   */
  Family* findBranch(std::string famName);

  /*
   * It finds the genetic line of a language
   * Then the path from the protolanguage to the searched language
   * is written to genLine
   */
  bool findGenLine(std::string langName, std::vector<Language>* genLine);

  /*
   * It receives genetic line of a language and puts it on the screen
   */
  void showGenLine(std::vector<Language>* genLine);

  /*
   * It show the shortest path to a common ancestor of two languages
   */
  void showConnection(std::string lang1, std::string lang2);

  /*
   * Constructor - it reads data from file and builds family tree
   * Language *father - in main.cpp it needs to be nullptr because Proto-Language doesn't have a parent
   * It uses a lot of recursion
   */
  Family(std::string data, Language* father);

  /*
   * Simple constructor in case you need to create a blank family
   */
  Family(){}
};

#endif

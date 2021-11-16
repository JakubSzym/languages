#include "family.hh"

#include<stdexcept>
using namespace std;

Family::Family(string data, Language* father){
  string help=" ";
  vector<string> links;  //vector of file names where you find information about subfamilies
  Language tmp;
  fstream file;
  file.open(data, ios::in);
  if(!file.good())
    throw invalid_argument("File does not exist");  //in case of a wrong path
  
  file>>familyName;   //first line of a file is the family name
  file>>protoLanguage; //seconf line is the protolanguage
  protoLanguage.setParent(father);  //setting parent of the protolanguage in order to connect everything
  while(true){
    file >> help;
    if(help == "!" || help == ".")
      break;   //'!' it means end of file, '.' means that there are paths to subfamilies
    else{
      //reading languages and setting status
      tmp.getName() = help;
      file >> help;
      switch(help[0]){
      case '0':
	tmp.getStatus() = DEAD;
	break;
      case '1':
	tmp.getStatus() = ALIVE;
	break;
      default:
	break;
      }
      members.push_back(tmp); //adding languages to the members of the family
    }
  }

  
  for(unsigned int i=0; i<members.size(); i++)
    members[i].setParent(&protoLanguage);  //setting protoLanguage as parent

  //reading paths to subfamilies
  if(help == "."){
    while(true){
      file >> help;
      if(help == ".")
	break;
      else{
	links.push_back(help);
      }
    }
    //reading information about subfamilies
    //using recursion - subfamilies can also have their own subfamilies
    for(unsigned int i = 0; i<links.size(); i++){
      Family* fam = new Family(links[i], &protoLanguage);
      subfamilies.push_back(*fam);
    }
  }
}


bool Family::findGenLine(string langName, vector<Language>* genLine){

  //searching in the family
  for(unsigned int i=0; i<members.size(); i++){
    if(members[i].getName() == langName){
      //when found add to genLine and find all ancestors
      genLine->push_back(members[i]);
      members[i].getAllAncestors(genLine);
      return true;
    }
  }
  //searching in subfamilies using recursion
  for(unsigned int i=0; i<subfamilies.size(); i++){
    if(subfamilies[i].findGenLine(langName, genLine)){
      return true;
    }
  }
  return false;  //language not found
}

void Family::showGenLine(vector<Language>* genLine){
  int len = genLine->size();
  for(int i = len-1; i>=0; i--)
    (*genLine)[i].write(len-(i+1), len-(i+1)); //printing on the screen
}

Family* Family::findBranch(string famName){
  for(unsigned int i=0; i<subfamilies.size(); i++){
    if(subfamilies[i].getFamilyName() == famName){
      return &(subfamilies[i]);
    }else{
      Family *help = subfamilies[i].findBranch(famName);
      if(help) return help; //when found - return
    }
  }
  return nullptr; //if not found
}

void Family::showFamily(){
  mvprintw(1, 1, "%s family", familyName.c_str());
  protoLanguage.write(2,1);
  for(unsigned int i=0; i<members.size(); i++)
    members[i].write(3+i, 3);
  
  for(unsigned int i=0; i<subfamilies.size(); i++)
    mvprintw(members.size()+4+i, 0, subfamilies[i].getFamilyName().c_str());
}

void Family::showConnection(string lang1, string lang2){
  unsigned int index_1=0, index_2=0;
  bool found = false;
  vector<Language> *genLine_1 = new vector<Language>;
  vector<Language> *genLine_2 = new vector<Language>;

  //finding genetic lines of languages and looking where their common ancestor is
  if(findGenLine(lang1, genLine_1) == false)
    printw("\nLanguage 1 not found");
  else if(findGenLine(lang2, genLine_2) == false)
    printw("\nLanguage 2 not found");
  else{
    for(unsigned int i=0; i<genLine_1->size(); i++){
      for(unsigned int j=0; j<genLine_2->size();j++){
	if((*genLine_1)[i].getName() == (*genLine_2)[j].getName()){
	  index_1 = i;
	  index_2 = j;
	  found = true;
	  break;
	}
      }
      if(found) break;
    }
  }

  
  vector<Language> *commonLine_1 = new vector<Language>;
  vector<Language> *commonLine_2 = new vector<Language>;


  //creating paths to the common ancestor
  for(unsigned int i=0; i<=index_1; i++)
    commonLine_1->push_back((*genLine_1)[i]);

  
  for(unsigned int i=0; i<=index_2; i++)
    commonLine_2->push_back((*genLine_2)[i]);

  
  delete genLine_1;
  delete genLine_2;

  //printing the diagram of connection on the screen
  for(unsigned int i=0; i<commonLine_1->size(); i++){
    (*commonLine_1)[commonLine_1->size()-1-i].write(10+i, 2*i+2);
  }
  for(unsigned int i=0; i<commonLine_2->size(); i++){
    (*commonLine_2)[commonLine_2->size()-1-i].write(10-i, 2*i+2); 
  }
  delete commonLine_1;
  delete commonLine_2;
}

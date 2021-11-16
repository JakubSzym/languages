#include "family.hh"
#include<stdexcept>


#define SHOW_GEN_LINE 0
#define SHOW_BRANCH 1
#define SHOW_CONNECTION 2
#define END 3

#define OPTIONS 5

#define ENTER 10

using namespace std;

int main(int argc, char** argv){
  if(argc < 2)
    throw invalid_argument("Too few arguments"); //if there's no information about language family

  string name = argv[1];
  Family *familyTree;

  //reading files depending on argument
  if(name == "indeur" || name == "INDEUR")
    familyTree  = new Family("data/indeur/indoeuropean.txt", nullptr);
  else if(name == "uralic" || name == "URALIC")
    familyTree = new Family("data/uralic/uralic.txt", nullptr);
  else
    throw invalid_argument("Family not found");
  
  initscr(); //initializes ncurses
  cbreak();  //you can quit by Ctrl+C
  start_color(); //initializes using color - doesn't work sometimes

  //windows is 10 rows high and 50 columns wide, start at top left corner
  WINDOW* win = newwin(10,50, 0, 0);
  box(win, 0, 0);
  refresh();
  wrefresh(win);

  keypad(win, true); //allowing read arrow keys etc.

  string menu[OPTIONS] = {"1. Show genetic line of a language", "2.Show a branch of the family",
			  "4. Show connection between two languages","5. Quit"};

  //focus - it is the currently highlightes option
  //choice - it sets after pushing Enter
  int focus=0, choice;

  while(true){
    noecho(); //blocking printing input
    //menu management
    while(true){
      for(int i=0; i<OPTIONS; i++){
	if(i==focus)
	  wattron(win, A_REVERSE);
	mvwprintw(win, i+1, 1, menu[i].c_str());
	wattroff(win, A_REVERSE);
      }
      choice = wgetch(win);
      switch(choice){
      case KEY_UP:
	focus--;
	if(focus == -1)
	  focus = 0;
	break;
      case KEY_DOWN:
	focus++;
	if(focus == OPTIONS)
	  focus = OPTIONS-1;
	break;
      default:
	break;
      }
      if(choice == ENTER) break;
    }
    echo(); //now you can print input
    clear();
    char* help = new char;
    string demand, lang1, lang2;
    switch(focus){
    case SHOW_GEN_LINE:
      {
      vector<Language>* genLine = new vector<Language>;
      printw("Enter the language: \n");
      scanw("%s", help);
      demand = help;
      if(familyTree->findGenLine(demand, genLine)){
	clear();
	familyTree->showGenLine(genLine);
      }else
	printw("Language not found\n");
      delete genLine;
      getch();
      clear();
      printw("Press any button in order to return to the menu");
      break;
      }
    case SHOW_BRANCH:
      {
      printw("Enter the branch: \n");
      scanw("%s", help);
      demand = help;
      Family* result = new Family;
      result = familyTree->findBranch(demand);
      clear();
      if(result)
	result->showFamily();
      else
	printw("Branch not found\n");
      result = nullptr;
      delete result;
      break;
      }
    case SHOW_CONNECTION:
      printw("Enter the first language: ");
      scanw("%s", help);
      lang1 = help;
      printw("\nEnter the second language: ");
      scanw("%s", help);
      lang2 = help;
      clear();
      familyTree->showConnection(lang1, lang2);
      break;
    default:
      break;
    }
    delete help;
    if(focus == END) break;
    getch();
    clear();
    box(win, 0, 0);
    refresh();
    wrefresh(win);
  }
  endwin();
  delete familyTree;
}

#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <windows.h>

#include "BSTNode.h"
#include "CMDGraphics.h"

using namespace std;

string toLower(string s) {
   string ret;
   for (char c : s) {
      ret += tolower(c);
   }
   return ret;
};

int main() {
   string *citation = new string();
   string word, parsedWord, input;
   ifstream readFile("text.txt");

   // Only needed for graphics
   HWND window = GetConsoleWindow();
   HDC DC = GetDC(window);
   graphics graph = graphics(DC, RGB(255,255,255));

   // Middle of the road starting node, Cuts the tree in half. Extra logic
   // can be put in to use the first word instead.
   BSTNode *headNode = new BSTNode("mmmmm", new string(), -1);

   if (readFile.is_open()) {
      while (readFile >> word) {
         // split on chapter:verse citation
         if (regex_match(word, regex("[0-9]+:[0-9]+"))) {
            //cout << word << endl << *citation << endl;
            citation = new string();
            *citation = word;
            continue;
         }
         else
            *citation += " " + word;

         // remove any punctuation from the word, and make it lower case
         parsedWord = "";

         for (char c : word)
            if (!ispunct(c))
               parsedWord += tolower(c);

         // add word and current citation to tree
         headNode->add(parsedWord, citation, 0);
      }
   }

   cout << "Read Complete, total words: " << headNode->getTotal() << endl;

   for (int i = 0; i < headNode->getNumInLvls().size(); i++)
      cout << "level " << i << ": " << headNode->getNumInLvls().at(i) << " nodes" << endl;
   cout <<"enter Word: ";

   // only needed for graphics
   graph.line(100, 100, 500, 120);

   // get input from user to search for word
   while (cin >> input) {

      BSTNode * node = headNode->get(toLower(input));

      if (!node) {
         cout << "No such word." << endl;
         continue;
      }

      vector<string *> sentances = node->getCitations();
      cout << "Ocurrences: " << node->getCount() << endl
         << "level: " << node->getLvl()
           << endl << endl << "Citations:" << endl;
      
      /* print all citations with word */
      for (int x = 0; x < sentances.size(); x++) {
         cout << *(sentances.at(x)) << endl;
      }

      cout << "Enter Another Word: ";
   }

   //not needed
   ReleaseDC(window, DC);
   return 0;
};
// BookBST.cpp : Defines the entry point for the console application.
//


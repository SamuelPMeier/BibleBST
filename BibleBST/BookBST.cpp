#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <windows.h>

#include "BSTNode.h"
#include "CMDGraphics.h"
#include "utility.h"
#include "DrawBST.h"

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
   DrawBST draw;

   bool printAll = false;

   MoveWindow(GetConsoleWindow(), 0, 0, WIN_WIDTH, WIN_HEIGHT, true);

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

   for (int i = 1; i < headNode->getNumInLvls().size(); i++)
      cout << "level " << i-1 << ": " << headNode->getNumInLvls().at(i) << " nodes" << endl;
   cout <<"enter Word: ";

   // get input from user to search for word
   while (cin >> input) {
      if (input.at(0) == '@') {
         if (!toLower(input).compare("@all")) {
            printAll = true;
            cin >> input;
         }

         if (!toLower(input).compare("@print")) {
            draw.drawTree(headNode);
            cin.get();
            continue;
         }
      }

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
      if (printAll)
         for (int x = 0; x < sentances.size(); x++) {
            cout << *(sentances.at(x)) << endl;
         }

      printAll = false;

      cout << "Enter Another Word: ";
   }

   return 0;
};
// BookBST.cpp : Defines the entry point for the console application.
//


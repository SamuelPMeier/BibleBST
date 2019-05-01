#pragma once

#include <vector>

class BSTNode 
{
private:
   BSTNode *lesser;
   BSTNode *greater;
   int number; // times word has occured.
   int level;
   std::string word;
   std::vector<std::string *> citations;

   static std::vector<int> numInLvls;
   static int total;
   static int maxLvl;

public:
   BSTNode(std::string, std::string *, int);
   void add(std::string, std::string*, int);
   BSTNode * get(std::string);

   // individual aspects
   int getCount();
   std::string getWord();
   std::vector<std::string *> getCitations();

   int getTotal() { return total; }
   int getLvl() { return level; }
   int getMaxLvl() { return maxLvl; }
   std::vector<int> getNumInLvls() { return numInLvls; }
   BSTNode* getLeft() { return lesser; }
   BSTNode* getRight() { return greater; }
};
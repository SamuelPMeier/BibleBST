#include "BSTNode.h"

int BSTNode::total = 0;
int BSTNode::maxLvl = 0;
std::vector<int> BSTNode::numInLvls;

BSTNode::BSTNode(std::string w, std::string *citation, int l) {
   word = w;
   number = 1;
   level = ++l;
   total++;
   citations.push_back(citation);
   lesser = nullptr;
   greater = nullptr;

   if (numInLvls.size() > level)
      numInLvls.at(level)++;
   else
      numInLvls.push_back(1);

   if (level > maxLvl)
      maxLvl = level;
}

void BSTNode::add(std::string w, std::string *citation, int l) {
   int val = word.compare(w);

   // standard BST logic Greater/Lesser/Equal
   if (!val) {
      
      // only add citation if it is new, prevents duplicates from citations
      // with two of the same word.
      if (citations.at(citations.size()-1) != citation)
         citations.push_back(citation);

      number++;
   }
   else if (val > 0) {
      if (lesser) {
         lesser->add(w, citation, level);
      }
      else {
         lesser = new BSTNode(w, citation, level);
      }
   }
   else {
      if (greater) {
         greater->add(w, citation, level);
      }
      else {
         greater = new BSTNode(w, citation, level);
      }
   }
}

BSTNode * BSTNode::get(std::string w) 
{
   int val = word.compare(w);

   // standard BST logic
   if (!val)
      return this;
   else if (val > 0) {
      if (lesser)
         return lesser->get(w);
      else
         return nullptr;
   }
   else {
      if (greater)
         return greater->get(w);
      else
         return nullptr;
   }
}

int BSTNode::getCount() {
   return number;
}

std::string BSTNode::getWord() {
   return word;
}

std::vector<std::string *> BSTNode::getCitations() {
   return citations;
}
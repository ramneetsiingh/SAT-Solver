#pragma once

#include <vector>
#include <map>
#include <string>
#include "ASTree.h"

class Tseitin
{
  private:
    std::vector<std::vector<int> > CNF; // represent CNF in vector of vector
    std::map<PASTree, int> numTable;
    int numCounter = 1;
    int numLiterals;
    void transform(PASTree node); // recursive function called on each subformula
    int getNumForNode(PASTree node);
    
  public:
    Tseitin(PASTree root);
    std::vector<std::vector<int> > getCNF(){
        return CNF;
    }
    int getNumLiterals(){
        return numLiterals;
    }
};

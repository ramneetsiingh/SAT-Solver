#include "Tseitin.h"

void Tseitin::transform(PASTree node){
    int a = getNumForNode(node);

    if(node == NULL or node->isID()) return;

    PASTree left = node->getLeft();
    PASTree right = node->getRight();
    int b = getNumForNode(left);
    int c = getNumForNode(right);

    transform(left);
    transform(right);

    char op = node->getContent()[0];
    switch(op){
        case '+':
            CNF.push_back({-a, b, c});
            CNF.push_back({-b, a});
            CNF.push_back({-c, a});
            break;
        case '*':
            CNF.push_back({-a, b});
            CNF.push_back({-a, c});
            CNF.push_back({-b, -c, a});
            break;
        case '-':
            CNF.push_back({-a, -b});
            CNF.push_back({a, b});
            break;
    }
}

int Tseitin::getNumForNode(PASTree node){
    int retVal;
    if(node == NULL) return 0;
    if(numTable.find(node) != numTable.end()){
        retVal = numTable[node];
    } else{
        retVal = numCounter++;
        numTable[node] = retVal;
    }
    return retVal;
}

Tseitin::Tseitin(PASTree root){
    transform(root);
    CNF.push_back({1});
    numLiterals = numCounter - 1;
}
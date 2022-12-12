#pragma once

#include <string>

class ASTree {
    std::string content;
    ASTree *left;
    ASTree *right;
    bool ID;
  public:
    ASTree(std::string content, ASTree * left, ASTree * right, bool isID):
                        content(content),
                        left(left),
                        right(right),
                        ID(isID){};

    ASTree(std::string content, ASTree * left, ASTree * right):
                        content(content),
                        left(left),
                        right(right),
                        ID(false){};

    std::string getContent(){
        return content;
    }
    ASTree* getLeft(){
        return left;
    }
    ASTree* getRight(){
        return right;
    }
    bool isID(){
        return ID;
    }
};

/*
Pointer to Abstract Syntax Tree
*/
typedef ASTree* PASTree;
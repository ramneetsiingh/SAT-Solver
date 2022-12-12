#pragma once

#include <string>

class ASTree {
    std::string content;
    ASTree *left;
    ASTree *right;
  public:
    ASTree(std::string content, ASTree * left, ASTree * right):
                        content(content),
                        left(left),
                        right(right){};

    std::string getContent(){
        return content;
    }
    ASTree* getleft(){
        return left;
    }
    ASTree* getRight(){
        return right;
    }
};

/*
Pointer to Abstract Syntax Tree
*/
typedef ASTree* PASTree;
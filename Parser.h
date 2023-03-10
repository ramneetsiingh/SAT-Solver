#pragma once

#include "Lexer.h"
#include "ASTree.h"
#include <iostream>
#include <map>

// Grammer, First's, and Follow's
/*
Grammer converted to LL(1) parsable form.

####################################################################

Formula         --> ConjTerm ConjTermPrime
ConjTermPrime   --> + Formula | E
ConjTerm        --> Term TermPrime
TermPrime       --> * ConjTerm | E
Term            --> VarName | - Term | ( Formula )


E is epsilon

####################################################################

X                   |   FIRST(X)
--------------------|--------------------
Formula             |   VarName - ( 
ConjTermPrime       |   + E
ConjTerm            |   VarName - (
TermPrime           |   * E
Term                |   VarName - (

####################################################################

X                   |   FOLLOW(X)
--------------------|--------------------
Formula             |   ) EOF
ConjTermPrime       |   ) EOF
ConjTerm            |   ) + EOF
TermPrime           |   ) + EOF
Term                |   ) + * EOF

####################################################################
*/

class Parser{
    Lexer lex;
    WORD currWord;
    PASTree ASTRoot;
    std::map<std::string, PASTree> IDNode;   //Identifier AST node

    PASTree parseFormula();
    PASTree parseConjTerm();
    PASTree parseTerm();
public:
    Parser(const std::string& s);
    PASTree getASTRoot(){
        return ASTRoot;
    }
};
#pragma once

#include "Lexer.h"
#include <iostream>

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

    /*
    Suffix _NT means non-terminal.
    */
    void Formula_NT();
    void ConjTerm_NT();
    void ConjTermPrime_NT();
    void Term_NT();
    void TermPrime_NT();
public:
    Parser(const std::string& s);
};
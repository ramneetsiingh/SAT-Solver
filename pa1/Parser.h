#pragma once

#include "Lexer.h"
#include <iostream>

/*
Grammer converted to LL(1) parsable form.

####################################################################

S               --> Formula ; Assignments
Formula         --> ConjTerm ConjTermPrime
ConjTermPrime   --> + Formula | E
ConjTerm        --> Term TermPrime
TermPrime       --> * ConjTerm | E
Term            --> 0 | 1 | Identifier | - Term | ( Formula )

Assignments         --> Assignment AssignmentsPrime | E
AssignmentsPrime    --> , Assignments | E
Assignment          --> Identifier : Constant
Constant            --> 0 | 1

E is epsilon

####################################################################

X                   |   FIRST(X)
--------------------|--------------------
S                   |   0 1 Identifier - ( 
Formula             |   0 1 Identifier - ( 
ConjTermPrime       |   + E
ConjTerm            |   0 1 Identifier - (
TermPrime           |   * E
Term                |   0 1 Identifier - (
                    |
Assignments         |   Identifier E
AssignmentsPrime    |   , E
Assignment          |   Identifier
Constant            |   0 1 

####################################################################

X                   |   FOLLOW(X)
--------------------|--------------------
S                   |   eof
Formula             |   ; )
ConjTermPrime       |   ; )
ConjTerm            |   ; ) +
TermPrime           |   ; ) +
Term                |   ; ) + *
                    |
Assignments         |   eof
AssignmentsPrime    |   eof
Assignment          |   , eof
Constant            |   , eof

eof is ";" in our code for the boolen expression

####################################################################
*/

typedef enum{
    SYNTAX_CHECK,
    EVALUATE
}ParserMode;

typedef enum{
    FALSE = 0,
    TRUE = 1,
    UNKNOWN = 2
}IdentifierValue;

typedef std::map<std::string, IdentifierValue> SYM_TAB;     // Maps Identifier name to its value

class Parser{
    Lexer lex;
    bool result;
    WORD currWord;
    SYM_TAB symbolTable;
    ParserMode mode;

    /*
    Suffix _NT means non-terminal.
    */
    bool S_NT();
    bool Formula_NT();
    bool ConjTerm_NT();
    bool ConjTermPrime_NT();
    bool Term_NT();
    bool TermPrime_NT();
    void Assignments_NT();
    void AssignmentsPrime_NT();
    void Assignment_NT();
public:
    Parser(const std::string& s);
    friend std::ostream& operator<<(std::ostream& os, const Parser& p);
    IdentifierValue get_ID_val(const std::string& id);
    void set_ID_val(const std::string& id, const IdentifierValue& val = IdentifierValue::UNKNOWN);
};
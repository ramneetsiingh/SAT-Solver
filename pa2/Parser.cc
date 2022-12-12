#include "Parser.h"
#include "Error.h"

void Parser::Term_NT(){
    if(currWord.first == Token::Identifier){
        currWord = lex.get_next_token();
        // Do Something
    } else if(currWord.first == Token::NOT){
        currWord = lex.get_next_token();
        Term_NT();
    } else if(currWord.first == Token::openB){
        currWord = lex.get_next_token();
        Formula_NT();
        if(currWord.first == Token::closeB){
            currWord = lex.get_next_token();
        } else{
            throw INVALID_INPUT;
        }
    } else {
        throw INVALID_INPUT;
    }
}

void Parser::TermPrime_NT(){
    if(currWord.first == Token::AND){
        currWord = lex.get_next_token();
        ConjTerm_NT();
    } else if(currWord.first == Token::OR or 
                currWord.first == Token::closeB or 
                currWord.first == Token::EOT){
        // Do nothing
    } else{
        throw INVALID_INPUT;
    }
}

void Parser::ConjTerm_NT(){
    Term_NT();
    TermPrime_NT();
}

void Parser::ConjTermPrime_NT(){
    if(currWord.first == Token::OR){
        currWord = lex.get_next_token();
        Formula_NT();
    } else if(currWord.first == Token::closeB or
                currWord.first == Token::EOT){
        // Do nothing
    } else{
        throw INVALID_INPUT;
    }
}

void Parser::Formula_NT(){
    ConjTerm_NT();
    ConjTermPrime_NT();
}

Parser::Parser(const std::string& s): lex(s){
    currWord = lex.get_next_token();
    Formula_NT();
    lex.reset_token_index();
}

#include "Parser.h"
#include "Error.h"

void Parser::parseTerm(){
    if(currWord.first == Token::Identifier){
        currWord = lex.get_next_token();
        // Do Something
    } else if(currWord.first == Token::NOT){
        currWord = lex.get_next_token();
        parseTerm();
    } else if(currWord.first == Token::openB){
        currWord = lex.get_next_token();
        parseFormula();
        if(currWord.first == Token::closeB){
            currWord = lex.get_next_token();
        } else{
            throw INVALID_INPUT;
        }
    } else {
        throw INVALID_INPUT;
    }
}

void Parser::parseConjTerm(){
    parseTerm();

    /*
    TermPrime
    */
    if(currWord.first == Token::AND){
        currWord = lex.get_next_token();
        parseConjTerm();
    } else if(currWord.first == Token::OR or 
                currWord.first == Token::closeB or 
                currWord.first == Token::EOT){
        // Do nothing
    } else{
        throw INVALID_INPUT;
    }
}

void Parser::parseFormula(){
    parseConjTerm();
    
    /*
    ConjTermPrime
    */
    if(currWord.first == Token::OR){
        currWord = lex.get_next_token();
        parseFormula();
    } else if(currWord.first == Token::closeB or
                currWord.first == Token::EOT){
        // Do nothing
    } else{
        throw INVALID_INPUT;
    }
}

Parser::Parser(const std::string& s): lex(s){
    currWord = lex.get_next_token();
    parseFormula();
    lex.reset_token_index();
}

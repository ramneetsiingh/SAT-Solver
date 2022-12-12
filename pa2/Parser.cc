#include "Parser.h"
#include "Error.h"

PASTree Parser::parseTerm(){
    PASTree ret = NULL;
    if(currWord.first == Token::Identifier){
        if(IDNode.find(currWord.second) == IDNode.end()){
            ret = new ASTree(currWord.second, NULL, NULL);
            IDNode[currWord.second] = ret;
        } else{
            ret = IDNode[currWord.second];
        }
        currWord = lex.get_next_token();
    } else if(currWord.first == Token::NOT){
        currWord = lex.get_next_token();
        PASTree left = parseTerm();
        ret = new ASTree("-", left, NULL);
    } else if(currWord.first == Token::openB){
        currWord = lex.get_next_token();
        ret = parseFormula();
        if(currWord.first == Token::closeB){
            currWord = lex.get_next_token();
        } else{
            throw INVALID_INPUT;
        }
    } else {
        throw INVALID_INPUT;
    }

    return ret;
}

PASTree Parser::parseConjTerm(){
    PASTree ret = parseTerm();

    /*
    TermPrime
    */
    if(currWord.first == Token::AND){
        currWord = lex.get_next_token();
        PASTree right =  parseConjTerm();
        ret = new ASTree("*", ret, right);
    } else if(currWord.first == Token::OR or 
                currWord.first == Token::closeB or 
                currWord.first == Token::EOT){
        // Do nothing
    } else{
        throw INVALID_INPUT;
    }

    return ret;
}

PASTree Parser::parseFormula(){
    PASTree ret = parseConjTerm();
    
    /*
    ConjTermPrime
    */
    if(currWord.first == Token::OR){
        currWord = lex.get_next_token();
        PASTree right =  parseFormula();
        ret = new ASTree("+", ret, right);
    } else if(currWord.first == Token::closeB or
                currWord.first == Token::EOT){
        // Do nothing
    } else{
        throw INVALID_INPUT;
    }
    
    return ret;
}

Parser::Parser(const std::string& s): lex(s){
    currWord = lex.get_next_token();
    ASTRoot = parseFormula();
    lex.reset_token_index();
}

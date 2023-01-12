#include "Lexer.h"
#include "Error.h"
#include "Helper.h"
#include <iostream>

void Lexer::tokenize(){
    std::string wordStr;
    std::string binExp = s + '\n';
    for(char c: binExp){
        if(Helper::isAlphaNum(c)){
            if(wordStr.size() == 0 and Helper::isNum(c)){
                throw INVALID_INPUT;
            }
            wordStr += c;
        } else {
            if(wordStr.size() > 0 and wordStr.size() <= 10){
                tokenVector.push_back(std::make_pair(Token::Identifier, wordStr));
                wordStr.clear();
            } else if (wordStr.size() > 10){
                throw INVALID_INPUT;
            }

            switch(c){
                case '+':
                    this->tokenVector.push_back(std::make_pair(Token::OR, "+"));
                    break;
                case '-':
                    this->tokenVector.push_back(std::make_pair(Token::NOT, "-"));
                    break;
                case '*':
                    this->tokenVector.push_back(std::make_pair(Token::AND, "*"));
                    break;
                case '(':
                    this->tokenVector.push_back(std::make_pair(Token::openB, "("));
                    break;
                case ')':
                    this->tokenVector.push_back(std::make_pair(Token::closeB, ")"));
                    break;
                case ' ':
                    break;
                case '\n':
                    this->tokenVector.push_back(std::make_pair(Token::EOT, ""));
                    break;
                default:
                    throw INVALID_INPUT;
            }
        }
    }
}

Lexer::Lexer(const std::string& s): s(s), curTokenIndex(0){
    tokenize();
}

WORD Lexer::get_next_token(){
    if(curTokenIndex < tokenVector.size()){
        return tokenVector[curTokenIndex++];
    }
    return std::make_pair(Token::EOT, "");
}

void Lexer::set_token_index(const size_t& i){
    curTokenIndex = i;
}

void Lexer::reset_token_index(){
    curTokenIndex = 0;
}
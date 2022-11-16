#pragma once
#include<string>
#include<map>
#include<vector>
#include<utility>

typedef enum{
    OR = '+',
    NOT = '-',
    AND = '*',
    openB = '(',
    closeB = ')',
    semiColon = ';',
    True = '0',
    False = '1',
    Comma = ',',
    Identifier = 'I',
    Colon = ':',
    EOT = '\n'     //End of tokens
}Token;

/*
Pair of token and its value
Example <Token::OR, "+">
*/
typedef std::pair<Token, std::string> WORD;                 // 

class Lexer{
    std::string s;
    std::vector<WORD> tokenVector;
    int curTokenIndex;
    void tokenize();
public:
    Lexer(const std::string& s);
    WORD get_next_token();
    void set_token_index(const int& i);
    void reset_token_index();
};

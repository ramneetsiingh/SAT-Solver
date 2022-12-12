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
    Identifier = 'I',
    EOT = '\n'     //End of tokens
}Token;

/*
Pair of token and its string
Example <Token::OR, "+">
*/
typedef std::pair<Token, std::string> WORD;

class Lexer{
    std::string s;
    std::vector<WORD> tokenVector;
    size_t curTokenIndex;
    void tokenize();
public:
    Lexer(const std::string& s);
    WORD get_next_token();
    void set_token_index(const size_t& i);
    void reset_token_index();
};

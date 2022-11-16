#include "Parser.h"
#include "Error.h"

bool Parser::Term_NT(){
    bool retVal = false;
    if(currWord.first == Token::True){
        currWord = lex.get_next_token();
        retVal = true;
    } else if(currWord.first == Token::False){
        currWord = lex.get_next_token();
        retVal = false;
    } else if(currWord.first == Token::Identifier){
        if(mode == ParserMode::SYNTAX_CHECK){
            /*
                In syntax check mode, set value of identifier to UNKNOWN
            */
            set_ID_val(std::string(currWord.second));
        } else if(mode == ParserMode::EVALUATE){
            retVal = get_ID_val(std::string(currWord.second)) == IdentifierValue::TRUE ? 1:0;
        }
        currWord = lex.get_next_token();
    } else if(currWord.first == Token::NOT){
        currWord = lex.get_next_token();
        retVal = !(Term_NT());
    } else if(currWord.first == Token::openB){
        currWord = lex.get_next_token();
        retVal = Formula_NT();
        if(currWord.first == Token::closeB){
            currWord = lex.get_next_token();
        } else{
            throw INVALID_INPUT;
        }
    } else {
        throw INVALID_INPUT;
    }
    return retVal;
}

bool Parser::TermPrime_NT(){
    bool retVal = true;
    if(currWord.first == Token::AND){
        currWord = lex.get_next_token();
        retVal = ConjTerm_NT();
    } else if(currWord.first == Token::OR or 
                currWord.first == Token::closeB or 
                currWord.first == Token::semiColon){
        // Do nothing
    } else{
        throw INVALID_INPUT;
    }
    return retVal;
}

bool Parser::ConjTerm_NT(){
    bool retVal1= Term_NT();
    bool retVal2 = TermPrime_NT();
    return retVal1 and retVal2;

}

bool Parser::ConjTermPrime_NT(){
    bool retVal = false;
    if(currWord.first == Token::OR){
        currWord = lex.get_next_token();
        retVal = Formula_NT();
    } else if(currWord.first == Token::closeB or
                currWord.first == Token::semiColon){
        // Do nothing
    } else{
        throw INVALID_INPUT;
    }
    return retVal;
}

bool Parser::Formula_NT(){
    bool retVal1= ConjTerm_NT();
    bool retVal2 = ConjTermPrime_NT();
    return retVal1 or retVal2;
}

bool Parser::S_NT(){
    bool retVal;
    currWord = lex.get_next_token();
    retVal = Formula_NT();
    if(currWord.first == Token::semiColon){
        /*
        No need to iterate past semicolon, if parser is in evaluate mode.
        */
        if(mode == ParserMode::SYNTAX_CHECK){
            currWord = lex.get_next_token();
            Assignments_NT();

            /*
            Check for Incomplete Assignment
            */
            for(auto id: symbolTable){
                if(id.second == IdentifierValue::UNKNOWN){
                    throw INCOMPLETE_ASSIGNMENT;
                }
            }

        }
    } else{
        throw INVALID_INPUT;
    }
    return retVal;
}

Parser::Parser(const std::string& s): lex(s), mode(ParserMode::SYNTAX_CHECK){
    /*
    1. Validate syntax of the input
    2. Fill out symbol table before evaluation
    */
    result = S_NT();
    lex.reset_token_index();
    
    /*
    Evaluate Boolean Expression
    */
    mode = ParserMode::EVALUATE;
    result = S_NT();
}

void Parser::Assignments_NT(){
    if(currWord.first == Token::EOT){
        //Do Nothing
    } else{
        Assignment_NT();
        AssignmentsPrime_NT();
    }
}

void Parser::AssignmentsPrime_NT(){
    if(currWord.first == Token::Comma){
        currWord = lex.get_next_token();
        Assignments_NT();
    } else if(currWord.first == Token::EOT){
        //Do Nothing
    } else{
        throw INVALID_INPUT;
    }
}

void Parser::Assignment_NT(){
    if(currWord.first == Token::Identifier){
        std::string idStr = currWord.second;
        currWord = lex.get_next_token();
        if(currWord.first == Token::Colon){
            currWord = lex.get_next_token();
            if(currWord.first == Token::True or currWord.first == Token::False){

                IdentifierValue idVal = currWord.first == Token::True ? 
                                        IdentifierValue::TRUE : IdentifierValue::FALSE;
                
                currWord = lex.get_next_token();

                try{
                    IdentifierValue existingVal = get_ID_val(idStr);    // Might throw error. See catch.
                    if( existingVal != IdentifierValue::UNKNOWN and
                        existingVal != idVal){

                        throw CONTRADICTING_ASSIGNMENT;
                    }
                } catch(const int i){
                    /*
                    <Boolean Expression> ; <Assignments>
                    It happens when Assigment has an Identifier that is not in the boolen expression.
                    It is not an error but simply an extra Identifier that is not used.
                    Do nothing here.
                    */
                }

                set_ID_val(idStr, idVal);

            } else{
                throw INVALID_INPUT;
            }
        } else{
            throw INVALID_INPUT;
        }
    } else{
        throw INVALID_INPUT;
    }
}

std::ostream& operator<<(std::ostream& os, const Parser& p){
    os << p.result;
    return os;
}

/*
If ID is not in the map, throwing -1. Handle this error!
*/
IdentifierValue Parser::get_ID_val(const std::string& id){
    if(symbolTable.find(id) == symbolTable.end()){
        throw -1;
    }
    return symbolTable[id];
}

void Parser::set_ID_val(const std::string& id, const IdentifierValue& val){
    symbolTable[id] = val;
}
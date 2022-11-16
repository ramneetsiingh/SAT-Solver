#include<iostream>
#include<string>
#include "Parser.h"

void evaluate(const std::string& s){
    try{
        Parser parser(s);
        std::cout<<parser<<std::endl;
    } catch(const char* s){
        std::cout<<"Error: "<<s<<std::endl;
    } catch(const int i){
        //Do Nothing
    }
}

int main(){
    std::string s;
    while(getline(std::cin, s)){
        evaluate(s);
    }
    return 0;
}
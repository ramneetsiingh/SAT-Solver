#include<iostream>
#include<string>
#include "SATSolver.h"

void evaluate(const std::string& s){
    try{
        SATSolver::solve(s);
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
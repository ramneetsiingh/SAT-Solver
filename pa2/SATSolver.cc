#include "SATSolver.h"
#include "Parser.h"
#include "Tseitin.h"

void printTseitin(std::vector<std::vector<int>> cnf){
    for(auto v: cnf){
        std::cout<<"[";
        for(int i = 0; i<v.size(); i++){
            std::cout<<v[i];
            if(i != v.size() - 1){
                std::cout<<",";
            }
        }
        std::cout<<"]";
    }
    std::cout<<std::endl;
}


bool SATSolver::solve(std::string s){
    Parser parser(s);
    Tseitin tseitin(parser.getASTRoot());
    printTseitin(tseitin.getCNF());
    return true;
}
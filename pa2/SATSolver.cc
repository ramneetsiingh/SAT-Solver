#include "SATSolver.h"
#include "Parser.h"
#include "Tseitin.h"

#include "minisat/core/SolverTypes.h"
#include "minisat/core/Solver.h"
#include<memory>


// void printTseitin(std::vector<std::vector<int>> cnf){
//     for(auto v: cnf){
//         std::cout<<"[";
//         for(int i = 0; i<v.size(); i++){
//             std::cout<<v[i];
//             if(i != v.size() - 1){
//                 std::cout<<",";
//             }
//         }
//         std::cout<<"]";
//     }
//     std::cout<<std::endl;
// }


bool SATSolver::solve(std::string s){
    Parser parser(s);
    Tseitin tseitin(parser.getASTRoot());
    std::vector<std::vector<int>> cnf = tseitin.getCNF();

    std::unique_ptr<Minisat::Solver> solver(new Minisat::Solver());
    
    //Minisat::Lit x = Minisat::mkLit(solver->newVar());
    Minisat::Lit literalMap[tseitin.getNumLiterals() + 1];
    for(int i=1; i<=tseitin.getNumLiterals(); i++){
        literalMap[i] = Minisat::mkLit(solver->newVar());
    }
    
    for(auto c: cnf){
        Minisat::vec<Minisat::Lit> v;
        for(auto l: c){
            //v.push(literalMap[std::abs(l)]);
            if(l>0) v.push(literalMap[l]);
            else v.push(~literalMap[std::abs(l)]);
        }
        solver->addClause(v);
    }

    return solver->solve();
}
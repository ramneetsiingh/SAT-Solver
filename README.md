# SAT SOLVER

SAT Solver is an algorithm for [Boolean satisfiability problem](https://en.wikipedia.org/wiki/Boolean_satisfiability_problem). It is implemented using [LL](https://en.wikipedia.org/wiki/LL_parser)(1) parsing technique, [Tseytin transformation](https://en.wikipedia.org/wiki/Tseytin_transformation), and [DPLL algorithm](https://en.wikipedia.org/wiki/DPLL_algorithm) using [minisat](https://github.com/niklasso/minisat).

## Usage

```bash
% git clone https://github.com/agurfinkel/minisat
% mkdir build
% cd build
% cmake ../
% make
% ./SAT
```



## Input

Input must follow the following grammer:

```bash
Formula    -->    ConjTerm + Formula
ConjTerm   -->    Term * ConjTerm
Term       -->    VarName
Term       -->    - Term
Term       -->    ( Formula )
```
- "+", "-", "*", "(", ")" are terminal symbols.
- E is epsilon.
- "+" represents OR
- "*" represents AND
- "-" represents unary operator NOT

## Output

"sat" if the boolean expression is satisfiable, "unsat" otherwise.

## Example

``` bash
% ./SAT
a+b
sat
a*(-a)      
unsat
```

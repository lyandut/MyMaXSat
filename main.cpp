#include <iostream>
#include "algorithm/randomizedSolver.hpp"
#include "algorithm/derandomizedSolver.hpp"
#include "algorithm/LPSolver.hpp"
#include "algorithm/LPDerandomizedSolver.hpp"

int main() {
    List<Variable> variables = {{0},
                                {1}};
    List<Clause> clauses;
    Clause clause(10);
    clause.addVariable(variables[0]);
    clause.addVariable(variables[1]);
    clauses.push_back(clause);

    clause = Clause(15);
    clause.addVariable(variables[0]);
    clause.addVariable({variables[1].id, Variable::VarType::negative});
    clauses.push_back(clause);

    clause = Clause(5);
    clause.addVariable({variables[0].id, Variable::VarType::negative});
    clause.addVariable(variables[1]);
    clauses.push_back(clause);

    clause = Clause(20);
    clause.addVariable({variables[0].id, Variable::VarType::negative});
    clause.addVariable({variables[1].id, Variable::VarType::negative});
    clauses.push_back(clause);

    Formula f(clauses, variables);

    std::cout << "=== 1. Randomized Solver ===" << std::endl;

	RandomizedSolver randomizedSolver(f);
    randomizedSolver.solve();

    std::cout << "=== 2. Derandomized Solver ===" << std::endl;

    DerandomizedSolver derandomizedSolver(f);
    derandomizedSolver.solve();

    std::cout << "=== 3. LP Solver ===" << std::endl;

	using namespace szx;
	LPSolver lpSolver(f);
	lpSolver.solve();

    std::cout << "=== 4. LPDerandomized Solver ===" << std::endl;

	LPDerandomizedSolver lpDerandomizedSolver(f);
	lpDerandomizedSolver.solve();

	system("PAUSE");

    return 0;
}
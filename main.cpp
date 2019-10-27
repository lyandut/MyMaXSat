#include <iostream>
#include "algorithm/randomizedSolver.hpp"
#include "algorithm/derandomizedSolver.hpp"
#include "algorithm/LPSolver.hpp"
#include "algorithm/LPDerandomizedSolver.hpp"
#include "data/instanceReader.hpp"
#include "fileFilter.hpp"

void test() {
	List<Variable> variables = { {0}, {1} };
	List<Clause> clauses;

	Clause clause(10);
	clause.addVariable(variables[0]);
	clause.addVariable(variables[1]);
	clauses.push_back(clause);

	clause = Clause(15);
	clause.addVariable(variables[0]);
	clause.addVariable({ variables[1].id, Variable::VarType::negative });
	clauses.push_back(clause);

	clause = Clause(5);
	clause.addVariable({ variables[0].id, Variable::VarType::negative });
	clause.addVariable(variables[1]);
	clauses.push_back(clause);

	clause = Clause(20);
	clause.addVariable({ variables[0].id, Variable::VarType::negative });
	clause.addVariable({ variables[1].id, Variable::VarType::negative });
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

}

int main() {
	//test();

#pragma region runSingleInstance
	String year = "mse19";
	String type = "bcp";
	String inst = "c5315_F1@0.wcnf";
	InstanceReader inst_reader(year, type, inst);
	using namespace szx;
	LPSolver lpSolver(inst_reader.formula);
	lpSolver.solve();
#pragma endregion runSingleInstance

#pragma region runAllInstances
	//String year = "mse19";
	//HashMap<String, List<String>> inst_map;
	//typeFilter(inst_map, year);
	//for (const auto & each : inst_map) {
	//	String type = each.first;
	//	for (const auto & inst : each.second) {
	//		InstanceReader inst_reader(year, type, inst);
	//	}
	//}
#pragma endregion runAllInstances
	
	system("PAUSE");

	return 0;
}
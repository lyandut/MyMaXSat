//
// Created by liyan on 2019/10/24.
//

#ifndef MYMAXSAT_LPSOLVER_HPP
#define MYMAXSAT_LPSOLVER_HPP

#include "../MpSolver/MpSolver.h"
#include "../data/formula.hpp"

using namespace szx;

using Dvar = MpSolver::DecisionVar;
using Expr = MpSolver::LinearExpr;

class LPSolver {
public:
	Formula formula;

public:
	LPSolver(Formula &_formula) : formula(_formula) {}

	void solve() {
		buildModel();

		//try {
		//	// Create an environment
		//	GRBEnv env = GRBEnv(true);
		//	env.set("LogFile", "mip1.log");
		//	env.start();

		//	// Create an empty model
		//	GRBModel model = GRBModel(env);

		//	// Create variables
		//	GRBVar x = model.addVar(0.0, 1.0, 0.0, GRB_BINARY, "x");
		//	GRBVar y = model.addVar(0.0, 1.0, 0.0, GRB_BINARY, "y");
		//	GRBVar z = model.addVar(0.0, 1.0, 0.0, GRB_BINARY, "z");

		//	// Set objective: maximize x+y+2z
		//	model.setObjective(x + y + 2 * z, GRB_MAXIMIZE);

		//	// Add constraint: x+2y+3z <= 4
		//	model.addConstr(x + 2 * y + 3 * z <= 4, "c0");

		//	// Add constraint: x+y >= 1
		//	model.addConstr(x + y >= 1, "c1");

		//	// Optimize model
		//	model.optimize();

		//	cout << "Obj: " << model.get(GRB_DoubleAttr_ObjVal) << endl;
		//}
		//catch (GRBException e) {
		//	cout << "Error code = " << e.getErrorCode() << endl;
		//	cout << e.getMessage() << endl;
		//}
		//catch (...) {
		//	cout << "Exception during optimization" << endl;
		//}
	}

private:
	void buildModel() {
		/*
		* Initialize environment & empty model
		*/
		MpSolver::Configuration mpCfg(MpSolver::InternalSolver::GurobiMip);
		MpSolver mp(mpCfg);

		/*
		* Decision Variables
		* 1. Bool: y_j correspond to the values of each boolean variable x_j.
		* 2. Bool: q_i correspond to the truth value of each clause C_i.
		* 3. Relax: 0 <= y_i, q_i <= 1.
		*/
		List<Dvar> y(formula.variables.size());
		List<Dvar> q(formula.clauses.size());
		for (const auto & v : formula.variables) {
			y[v.first] = mp.addVar(MpSolver::VariableType::Real, 0, 1);
		}
		for (int i = 0; i < formula.clauses.size(); ++i) {
			q[i] = mp.addVar(MpSolver::VariableType::Real, 0, 1);
		}

		/*
		* Constraint
		* q_i <= Sum(y_j) + Sum(1 - ~y_j)
		*/
		for (int i = 0; i < formula.clauses.size(); ++i) {
			Expr sum_variables = 0;
			for (const auto & v : formula.clauses[i].variables) {
				if (v.type == Variable::VarType::positive) {
					sum_variables += y.at(v.id);
				}
				else {
					sum_variables += (1 - y.at(v.id));
				}
			}
			mp.addConstraint(q.at(i) <= sum_variables);
		}

		/*
		* Objective Function
		* maximize Sum(q_i)
		*/
		Expr obj = 0;
		for (int i = 0; i < formula.clauses.size(); ++i) {
			obj += q.at(i);
		}
		mp.addObjective(obj, MpSolver::OptimaOrientation::Maximize);

		mp.optimize();
		for (auto & v : y) {
			std::cout << mp.getValue(v) << std::endl;
		}
	}


};

#endif //MYMAXSAT_LPSOLVER_HPP

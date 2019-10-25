//
// Created by liyan on 2019/10/24.
//

#ifndef MYMAXSAT_LPSOLVER_HPP
#define MYMAXSAT_LPSOLVER_HPP

#include "../MpSolver/MpSolver.h"
#include "../MpSolver/LogSwitch.h"
#include "../data/formula.hpp"

namespace szx {

    using Dvar = MpSolver::DecisionVar;
    using Expr = MpSolver::LinearExpr;

    class LPSolver {
    public:
        Formula formula;

    public:
        LPSolver(Formula &_formula) : formula(_formula) {}

        void solve() {
            gurobiModel();
        }

    private:
        void mpModel() {
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
            for (const auto &v : formula.variables) {
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
                for (const auto &v : formula.clauses[i].variables) {
                    if (v.type == Variable::VarType::positive) {
                        sum_variables += y.at(v.id);
                    } else {
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

            // Optimize model
            mp.optimize();

            for (auto &y_j : y) {
                Log(LogSwitch::Szx::MpSolver) << mp.getValue(y_j) << std::endl;
            }
        }

        void gurobiModel() {
            try {
                /*
                * Initialize environment & empty model
                */
            	GRBEnv env = GRBEnv(true);
            	env.set("LogFile", "max-sat.log");
            	env.start();
            	GRBModel gm = GRBModel(env);

                /*
                * Decision Variables
                * 1. Bool: y_j correspond to the values of each boolean variable x_j.
                * 2. Bool: q_i correspond to the truth value of each clause C_i.
                * 3. Relax: 0 <= y_i, q_i <= 1.
                */
                List<GRBVar> y(formula.variables.size());
                List<GRBVar> q(formula.clauses.size());
                for (const auto &v : formula.variables) {
                    y[v.first] = gm.addVar(0, 1, 0, GRB_CONTINUOUS);
                }
                for (int i = 0; i < formula.clauses.size(); ++i) {
                    q[i] = gm.addVar(0, 1, 0, GRB_CONTINUOUS);
                }

                /*
                * Constraint
                * q_i <= Sum(y_j) + Sum(1 - ~y_j)
                */
                for (int i = 0; i < formula.clauses.size(); ++i) {
                    GRBLinExpr sum_variables = 0;
                    for (const auto &v : formula.clauses[i].variables) {
                        if (v.type == Variable::VarType::positive) {
                            sum_variables += y.at(v.id);
                        } else {
                            sum_variables += (1 - y.at(v.id));
                        }
                    }
                    gm.addConstr(q.at(i) <= sum_variables);
                }

                /*
                * Objective Function
                * maximize Sum(q_i)
                */
                GRBLinExpr obj = 0;
                for (int i = 0; i < formula.clauses.size(); ++i) {
                    obj += q.at(i);
                }
                gm.setObjective(obj, GRB_MAXIMIZE);

            	// Optimize model
            	gm.optimize();

                Log(LogSwitch::Szx::MpSolver) << "Obj: " << gm.get(GRB_DoubleAttr_ObjVal) << std::endl;
                for (auto &y_j : y) {
                    Log(LogSwitch::Szx::MpSolver) << y_j.get(GRB_DoubleAttr_X) << std::endl;
                }
            }
            catch (GRBException &e) {
                Log(LogSwitch::Szx::MpSolver) << "Error code = " << e.getErrorCode() << std::endl;
                Log(LogSwitch::Szx::MpSolver) << e.getMessage() << std::endl;
            }
            catch (...) {
                Log(LogSwitch::Szx::MpSolver) << "Exception during optimization" << std::endl;
            }
        }


    };
}

#endif //MYMAXSAT_LPSOLVER_HPP

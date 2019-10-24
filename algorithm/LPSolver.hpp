//
// Created by liyan on 2019/10/24.
//

#ifndef MYMAXSAT_LPSOLVER_HPP
#define MYMAXSAT_LPSOLVER_HPP

#include "gurobi_c++.h"
#include "../data/formula.hpp"

class LPSolver {
public:
    Formula formula;

public:
    LPSolver()  {}
    void solve() {
        try {
            // Create an environment
            GRBEnv env = GRBEnv(true);
            env.set("LogFile", "mip1.log");
            env.start();

            // Create an empty model
            GRBModel model = GRBModel(env);

            // Create variables
            GRBVar x = model.addVar(0.0, 1.0, 0.0, GRB_BINARY, "x");
            GRBVar y = model.addVar(0.0, 1.0, 0.0, GRB_BINARY, "y");
            GRBVar z = model.addVar(0.0, 1.0, 0.0, GRB_BINARY, "z");

            // Set objective: maximize x+y+2z
            model.setObjective(x+y+2*z, GRB_MAXIMIZE);

            // Add constraint: x+2y+3z <= 4
            model.addConstr(x+2*y+3*z <= 4, "c0");

            // Add constraint: x+y >= 1
            model.addConstr(x+y >= 1, "c1");

            // Optimize model
            model.optimize();

            cout<<"Obj: "<<model.get(GRB_DoubleAttr_ObjVal) << endl;
        }
        catch(GRBException e) {
            cout << "Error code = " << e.getErrorCode() << endl;
            cout << e.getMessage() << endl;
        } catch(...) {
            cout << "Exception during optimization" << endl;
        }

        return 0;


    }

};

#endif //MYMAXSAT_LPSOLVER_HPP

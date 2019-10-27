//
// Created by liyan on 2019/10/26.
//

#ifndef MYMAXSAT_LPDERANDOMIZEDSOLVER_HPP
#define MYMAXSAT_LPDERANDOMIZEDSOLVER_HPP

#include "derandomizedSolver.hpp"
#include "LPSolver.hpp"


namespace szx {

class LPDerandomizedSolver : public DerandomizedSolver, public LPSolver {

public:
    LPDerandomizedSolver(Formula &_formula) : BaseSolver(_formula) {}

    void solve() override {
        List<double>(LPDerandomizedSolver::*lpFunc)();
#if MP_MODEL
        lpFunc = &LPDerandomizedSolver::mpModel;
#else
        lpFunc = &LPDerandomizedSolver::gurobiModel;
#endif // MP_MODEL

        List<double> p_list = (this->*lpFunc)();
        int total_weight = derandomize(p_list);

#pragma region resultChecker
        if (total_weight == printResult()) {
            // [TODO] add exception
            std::cout << "Check Success" << std::endl;
        }
#pragma endregion resultChecker
    }

};

}

#endif //MYMAXSAT_LPDERANDOMIZEDSOLVER_HPP

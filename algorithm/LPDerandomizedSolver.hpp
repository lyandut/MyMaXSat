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
        LPSolver::solve();
    }

};

}

#endif //MYMAXSAT_LPDERANDOMIZEDSOLVER_HPP

//
// Created by liyan on 2019/10/22.
//

#ifndef MYMAXSAT_RANDOMIZEDSOLVER_HPP
#define MYMAXSAT_RANDOMIZEDSOLVER_HPP

#include <iostream>
#include <random>
#include <ctime>
#include "../data/formula.hpp"

class RandomizedSolver {
public:
    Formula formula;

public:
    RandomizedSolver(Formula &_formula) : formula(_formula) {}

    void solve() {
        randomize();
        int total_weight = 0;
        for (const auto &c : formula.getSatisfiedClauses())
            total_weight += c.weight;

        std::cout << formula.toString() << std::endl;
        for (const auto &v : formula.variables)
            std::cout << "X" << v.first << ": " << v.second << std::endl;
        std::cout << "Total value: " << total_weight << std::endl;
    }

private:
    void randomize(double __p__ = 0.5) {
        std::default_random_engine e(time(nullptr));
        std::bernoulli_distribution u(__p__);
        for (auto &var : formula.variables)
            var.second = u(e);
    }

};


#endif //MYMAXSAT_RANDOMIZEDSOLVER_HPP

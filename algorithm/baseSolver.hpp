//
// Created by liyan on 2019/10/25.
//

#ifndef MYMAXSAT_BASESOLVER_HPP
#define MYMAXSAT_BASESOLVER_HPP

#include <iostream>
#include <random>
#include <ctime>
#include "../data/formula.hpp"

class BaseSolver {

public:
	Formula formula;
private:
	std::default_random_engine e;

public:
	BaseSolver(Formula &_formula) : formula(_formula) { e.seed(time(nullptr)); }

	virtual void solve() = 0;

protected:
	int printResult() {
		int total_weight = 0;
		for (const auto &c : formula.getSatisfiedClauses())
			total_weight += c.weight;

		std::cout << formula.toString() << std::endl;
		for (const auto &v : formula.variables)
			std::cout << "X" << v.first << ": " << v.second << std::endl;
		std::cout << "Total value: " << total_weight << std::endl;

		return total_weight;
	}

	bool getProbRandomNumber(double __p__ = 0.5) {
		std::bernoulli_distribution u(__p__);
		return u(e);
	}

};


#endif //MYMAXSAT_RANDOMIZEDSOLVER_HPP

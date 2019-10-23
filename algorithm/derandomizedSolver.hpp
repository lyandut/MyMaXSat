//
// Created by liyan on 2019/10/22.
//

#ifndef MYMAXSAT_DERANDOMIZEDSOLVER_HPP
#define MYMAXSAT_DERANDOMIZEDSOLVER_HPP

#include <cmath>
#include <algorithm>
#include "../data/formula.hpp"

class DerandomizedSolver {

public:
    Formula formula;

public:
    DerandomizedSolver(Formula &_formula) : formula(_formula) {}

    void solve() {
        int total_weight = calculate();
        std::cout << formula.toString() << std::endl;
        for (auto &v : formula.variables)
            std::cout << v.toString() << ": " << v.value << std::endl;
        std::cout << "Total value: " << total_weight << std::endl;
    }

private:
    int calculate() {
        List<int> unfilled_num(formula.clauses.size(), 0);     // 剩余未指定变量数
        List<bool> full_filled(formula.clauses.size(), false); // 子句是否完全填充

        // 计算一般期望，同时初始化 unfilled_num
        expected(formula.clauses, unfilled_num);
        for (auto &v : formula.variables) {
            double expectedTrue = expectedIf(formula.clauses, unfilled_num, full_filled, v, true)
                                  + numberFulfilledByVar(formula.clauses, unfilled_num, full_filled, v, true);
            double expectedFalse = expectedIf(formula.clauses, unfilled_num, full_filled, v, true)
                                   + numberFulfilledByVar(formula.clauses, unfilled_num, full_filled, v, false);

            if (expectedTrue > expectedFalse) {
                v.value = true;
                expectedUpdate(formula.clauses, unfilled_num, full_filled, v, true);
            } else {
                v.value = false;
                expectedUpdate(formula.clauses, unfilled_num, full_filled, v, false);
            }
        }

        int total_weight = 0;
        for (int i = 0; i < formula.clauses.size(); ++i) {
            if (full_filled[i]) { total_weight += formula.clauses[i].weight; }
        }
        return total_weight;
    }

    double expected(const List<Clause> &clauses, List<int> &unfilled_num) {
        double sum = 0.0;
        for (int i = 0; i < clauses.size(); ++i) {
            unfilled_num[i] = static_cast<int>(clauses[i].variables.size());
            sum += (1 - 1 / std::pow(2, unfilled_num[i])) * clauses[i].weight;
        }
        return sum;
    }

    double expectedIf(const List<Clause> &clauses, const List<int> &unfilled_num, const List<bool> &full_filled,
                      const Variable &var, bool val) {
        double sum = 0.0;
        for (int i = 0; i < clauses.size(); ++i) {
            if (!full_filled[i] && unfilled_num[i]) {
                auto iter = std::find(clauses[i].variables.begin(), clauses[i].variables.end(), var);
                if (iter != clauses[i].variables.end()) { // 子句包含当前变量
                    if ((iter->type == Variable::VarType::positive && val) ||
                        (iter->type == Variable::VarType::negative && !val)) {
                        sum += clauses[i].weight;
                    } else {
                        sum += (1 - 1 / std::pow(2, unfilled_num[i] - 1)) * clauses[i].weight;
                    }
                } else { // 子句不包含当前变量
                    sum += (1 - 1 / std::pow(2, unfilled_num[i])) * clauses[i].weight;
                }
            }
            if (full_filled[i]) {  // 子句已完全填充
                sum += clauses[i].weight;
            }
        }
        return sum;
    }

    int numberFulfilledByVar(const List<Clause> &clauses, const List<int> &unfilled_num, const List<bool> &full_filled,
                             const Variable &var, bool val) {
        int sum = 0;
        for (int i = 0; i < clauses.size(); ++i) {
            if (!full_filled[i] && unfilled_num[i]) {
                auto iter = std::find(clauses[i].variables.begin(), clauses[i].variables.end(), var);
                if (iter != clauses[i].variables.end()) {
                    if ((iter->type == Variable::VarType::positive && val) ||
                        (iter->type == Variable::VarType::negative && !val)) {
                        sum += clauses[i].weight;
                    }
                }
            }
        }
        return sum;
    }

    void expectedUpdate(const List<Clause> &clauses, List<int> &unfilled_num, List<bool> &full_filled,
                        const Variable &var, bool val) {
        for (int i = 0; i < clauses.size(); ++i) {
            if (!full_filled[i] && unfilled_num[i] != 0) {
                auto iter = std::find(clauses[i].variables.begin(), clauses[i].variables.end(), var);
                if (iter != clauses[i].variables.end()) {
                    if ((iter->type == Variable::VarType::positive && val) ||
                        (iter->type == Variable::VarType::negative && !val)) {
                        full_filled[i] = true;
                    }
                    --unfilled_num[i];
                }
            }
        }
    }
};


#endif //MYMAXSAT_DERANDOMIZEDSOLVER_HPP

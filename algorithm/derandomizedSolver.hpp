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
        int total_weight = derandomize();
        int total_weight2 = 0;
        for (auto &c : formula.getSatisfiedClauses())
            total_weight2 += c.weight;

        std::cout << formula.toString() << std::endl;
        for (auto &v : formula.variables)
            std::cout << "X" << v.first << ": " << v.second << std::endl;
        std::cout << "Total value: " << total_weight << " " << total_weight2 << std::endl;
    }

private:
    int derandomize() {
        List<int> unspecified_num(formula.clauses.size(), 0);   // 剩余未指定变量数
        List<bool> is_satisfied(formula.clauses.size(), false); // 子句是否满足

        expectedGeneral(unspecified_num);
        for (auto &v : formula.variables) {
            double expectedTrue = expectedConditional(unspecified_num, is_satisfied, v.first, true);
            double expectedFalse = expectedConditional(unspecified_num, is_satisfied, v.first, false);

            if (expectedTrue > expectedFalse) {
                v.second = true;
                expectedUpdate(unspecified_num, is_satisfied, v.first, true);
            } else {
                v.second = false;
                expectedUpdate(unspecified_num, is_satisfied, v.first, false);
            }
        }

        int total_weight = 0;
        for (int i = 0; i < formula.clauses.size(); ++i) {
            if (is_satisfied[i]) { total_weight += formula.clauses[i].weight; }
        }
        return total_weight;
    }

    // 计算一般期望，同时初始化 unfilled_num
    double expectedGeneral(List<int> &unspecified_num) {
        const auto &clauses = formula.clauses;
        double sum = 0.0;
        for (int i = 0; i < clauses.size(); ++i) {
            unspecified_num[i] = static_cast<int>(clauses[i].variables.size());
            sum += (1 - 1 / std::pow(2, unspecified_num[i])) * clauses[i].weight;
        }
        return sum;
    }

    // 计算条件期望
    double expectedConditional(const List<int> &unspecified_num, const List<bool> &is_satisfied, ID var, bool val) {
        const auto &clauses = formula.clauses;
        double sum = 0.0;
        for (int i = 0; i < clauses.size(); ++i) {
            if (is_satisfied[i]) {  // 子句已满足
                sum += clauses[i].weight;
            }
            if (!is_satisfied[i] && unspecified_num[i]) { // 子句未满足 & 有空变量
                auto iter = std::find_if(clauses[i].variables.begin(), clauses[i].variables.end(),
                                         [=](auto &v) { return v.id == var; });
                if (iter != clauses[i].variables.end()) { // 子句包含当前变量
                    if ((iter->type == Variable::VarType::positive && val) ||
                        (iter->type == Variable::VarType::negative && !val)) {
                        sum += clauses[i].weight;
                    } else {
                        sum += (1 - 1 / std::pow(2, unspecified_num[i] - 1)) * clauses[i].weight;
                    }
                } else { // 子句不包含当前变量
                    sum += (1 - 1 / std::pow(2, unspecified_num[i])) * clauses[i].weight;
                }
            }
        }
        return sum;
    }

    // 更新 unspecified_num & is_satisfied
    void expectedUpdate(List<int> &unspecified_num, List<bool> &is_satisfied, ID var, bool val) {
        const auto &clauses = formula.clauses;
        for (int i = 0; i < clauses.size(); ++i) {
            if (!is_satisfied[i] && unspecified_num[i]) {
                auto iter = std::find_if(clauses[i].variables.begin(), clauses[i].variables.end(),
                                         [=](auto &v) { return v.id == var; });
                if (iter != clauses[i].variables.end()) {
                    --unspecified_num[i];
                    if ((iter->type == Variable::VarType::positive && val) ||
                        (iter->type == Variable::VarType::negative && !val)) {
                        is_satisfied[i] = true;
                    }
                }
            }
        }
    }
};


#endif //MYMAXSAT_DERANDOMIZEDSOLVER_HPP

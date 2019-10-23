//
// Created by liyan on 2019/10/22.
//

#ifndef MYMAXSAT_FORMULA_HPP
#define MYMAXSAT_FORMULA_HPP

#include <algorithm>
#include <utility>
#include "clause.hpp"

class Formula {
public:
    List<Clause> clauses;
    List<Variable> variables;
private:
    HashMap<ID, bool> variables_map;

public:
    Formula(List<Clause> cla, List<Variable> var) : clauses(std::move(cla)), variables(std::move(var)) {
        for (auto &v : variables) { variables_map[v.id] = v.value; }
    }

    Formula() = default;

    List<Clause> getSatisfiedClauses() {
        List<Clause> satisfied_clauses;
        satisfied_clauses.reserve(clauses.size());
        for (auto &c : clauses) {
            bool satisfied = false;
            for (auto &v : c.variables) {
                satisfied |= v.type == Variable::VarType::positive == getVariableValue(v);
            }
            if (satisfied)
                satisfied_clauses.push_back(c);
        }
        return satisfied_clauses;
    }

    String toString() const {
        String str = "[";
        for (auto iter = clauses.begin(); iter != clauses.end() - 1; ++iter)
            str += iter->toString() + " /\\ ";
        str += clauses.back().toString() + "]";
        return str;
    }

private:
    bool getVariableValue(Variable &var) {
        auto iter = std::find(variables.begin(), variables.end(), var);
        assert(iter != variables.end());
        return iter->value;
    }

    bool getVariableValue(ID var_id) {
        auto iter = variables_map.find(var_id);
        assert(iter != variables_map.end());
        return variables_map.at(var_id);
    }

};


#endif //MYMAXSAT_FORMULA_HPP

//
// Created by liyan on 2019/10/22.
//

#ifndef MYMAXSAT_FORMULA_HPP
#define MYMAXSAT_FORMULA_HPP

#include <utility>

#include "clause.hpp"

class Formula {
public:
    List<Clause> clauses;
    List<Variable> variables;
    HashMap<ID, bool> var_value_map;

public:
    Formula(List<Clause> cla, List<Variable> var) : clauses(std::move(cla)), variables(std::move(var)) {
        for (auto &v : variables) { var_value_map[v.id] = v.value; }
    }

    Formula() = default;

    List<Clause> getSatisfiedClauses() {
        List<Clause> satisfied_clauses;
        satisfied_clauses.reserve(clauses.size());
        for (auto &c : clauses) {
            bool satisfied = true;
            for (auto &v : c.variables)
                satisfied &= v.type == Variable::VarType::positive == getVariableValue(v.id);
            if (satisfied)
                satisfied_clauses.push_back(c);
        }
        return satisfied_clauses;
    }

    String toString() {
        String str = "[";
        for (auto iter = clauses.begin(); iter != clauses.end() - 1; ++iter)
            str += iter->toString() + " /\\ ";
        str += clauses.back().toString() + "]";
        return str;
    }

private:
    bool getVariableValue(Variable &var) {
        for (auto &v : variables)
            if (v.id == var.id)
                return v.value;
        return false;
    }

    inline bool getVariableValue(ID var_id) {
        if (var_value_map.find(var_id) != var_value_map.end())
            return var_value_map.at(var_id);
        return false;
    }

};


#endif //MYMAXSAT_FORMULA_HPP

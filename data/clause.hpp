//
// Created by liyan on 2019/10/22.
//

#ifndef MYMAXSAT_CLAUSE_HPP
#define MYMAXSAT_CLAUSE_HPP

#include "variable.hpp"
#include <cassert>

class Clause {
public:
    List<Variable> variables;
    int weight;

public:
    Clause(List<Variable> & var, int w) : variables(var), weight(w) { assert(w >= 0); }
    Clause(int w) : weight(w) { assert(w>=0); }
    Clause() : Clause(0) {}







};


#endif //MYMAXSAT_CLAUSE_HPP

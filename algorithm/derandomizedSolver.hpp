//
// Created by liyan on 2019/10/22.
//

#ifndef MYMAXSAT_DERANDOMIZEDSOLVER_HPP
#define MYMAXSAT_DERANDOMIZEDSOLVER_HPP

class Variable {
    enum VarType { positive , negated };

public:
    int id;
    bool value;
    VarType type;

};

#endif //MYMAXSAT_DERANDOMIZEDSOLVER_HPP

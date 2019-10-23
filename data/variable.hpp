//
// Created by liyan on 2019/10/22.
//

#ifndef MYMAXSAT_VARIABLE_HPP
#define MYMAXSAT_VARIABLE_HPP

#include "../config.h"

class Variable {

public:
    ID id;
    bool value;
    enum VarType {
        positive, negative
    } type;


public:
    Variable(int _id, bool _value, VarType _type) : id(_id), value(_value), type(_type) {}

    Variable(int _id, VarType _type) : Variable(_id, false, _type) {}

    Variable(int _id) : Variable(_id, VarType::positive) {}

    Variable() : Variable(0) {}

    bool operator==(const Variable &var) const { return id == var.id; }

    String toString() const {
        return type == VarType::positive ? "X" + std::to_string(id) : "~X" + std::to_string(id);
    }


};

#endif //MYMAXSAT_VARIABLE_HPP

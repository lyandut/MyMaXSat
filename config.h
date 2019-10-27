//
// Created by 李研 on 2019/10/22.
//

#ifndef MYMAXSAT_CONFIG_H
#define MYMAXSAT_CONFIG_H

#include <vector>
#include <string>
#include <unordered_map>

using ID = int;

using String = std::string;

template <typename T>
using List = std::vector<T>;

template <typename Key, typename Value>
using HashMap = std::unordered_map<Key, Value>;

#define MP_MODEL 0

const String InstanceFolder = "../Instance/";


#endif //MYMAXSAT_CONFIG_H

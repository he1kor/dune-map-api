#pragma once
#include <map>

template <typename T>
class PriorityMap{
public:
    PriorityMap();
    PriorityMap(bool is_strict);
    PriorityMap(std::map<T, int> priority_map);
    PriorityMap(std::map<T, int> priority_map, bool is_strict);
    void addPriority(T value, int priority);
    int getPriority(T value);

    bool isHigher(T old_value, T new_value);
    void setStrict(bool is_strict);
    bool isStrict();
private:
    std::map<T, int> priority_map;
    bool is_strict = false;
};
#pragma once
#include <map>

template <typename T>
class PriorityMap{
public:PriorityMap(){}

    PriorityMap(bool is_strict) : is_strict{is_strict}{}

    PriorityMap(std::map<T, int> priority_map) : priority_map{priority_map}{}

    PriorityMap(std::map<T, int> priority_map, bool is_strict) : priority_map{priority_map}, is_strict{is_strict}{}

    void addPriority(T value, int priority){
        priority_map[value] = priority;
    }

    int getPriority(T value){
        return priority_map.at(value);
    }

    bool isHigher(T new_value, T old_value){
        if (is_strict)
            return priority_map.at(new_value) > priority_map.at(old_value);
        return priority_map.at(new_value) >= priority_map.at(old_value);
    }

    void setStrict(bool is_strict){
        this->is_strict = is_strict;
    }

    bool isStrict(){
        return is_strict;
    }

private:
    std::map<T, int> priority_map;
    bool is_strict = false;
};
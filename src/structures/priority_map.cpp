#include "priority_map.h"

template <typename T>
PriorityMap<T>::PriorityMap(){}

template <typename T>
PriorityMap<T>::PriorityMap(bool is_strict) : is_strict{is_strict}{}

template <typename T>
PriorityMap<T>::PriorityMap(std::map<T, int> priority_map) : priority_map{priority_map}{}

template <typename T>
PriorityMap<T>::PriorityMap(std::map<T, int> priority_map, bool is_strict) : priority_map{priority_map}, is_strict{is_strict}{}

template <typename T>
void PriorityMap<T>::addPriority(T value, int priority){
    priority_map[value] = priority;
}

template <typename T>
int PriorityMap<T>::getPriority(T value){
    return priority_map.at[value];
}

template <typename T>
bool PriorityMap<T>::isHigher(T old_value, T new_value){
    if (is_strict)
        return priority_map.at[new_value] > priority_map.at[old_value];
    return priority_map.at[new_value] >= priority_map.at[old_value];
}

template <typename T>
void PriorityMap<T>::setStrict(bool is_strict){
    this->is_strict = is_strict;
}

template <typename T>
bool PriorityMap<T>::isStrict(){
    return is_strict;
}

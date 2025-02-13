#pragma once


template <typename T>
struct LocatedState{
    LocatedState(T state, int x, int y) : state(state), x(x), y(y){};
    T state;
    int x = 0;
    int y = 0;
    bool operator<(const LocatedState &lt) const{
        return 
            (x < lt.x) || 
            (x == lt.x && y < lt.y);
    }
    
};
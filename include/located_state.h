#pragma once

template <typename T>

struct LocatedState{
    LocatedTile(T state, int x, int y) : state(state), x(x), y(y){};
    T state;
    int x = 0;
    int y = 0;
    bool LocatedTile::operator<(const LocatedTile &lt) const{
        return 
            (x < lt.x) || 
            (x == lt.x && y < lt.y);
    }
    
}
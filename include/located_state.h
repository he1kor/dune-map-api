#pragma once

template <typename T>

struct LocatedState{
    T state;
    int x = 0;
    int y = 0;
    bool LocatedTile::operator<(const LocatedTile &lt) const{
        return 
            (x < lt.x) || 
            (x == lt.x && y < lt.y);
    }
    
}
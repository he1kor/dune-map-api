#pragma once
#include <cmath>
#include "wall_base.h"
#include "location.h"

template <typename T>
class FourSideWall : public WallBase<T>{
public:
    using WallBase<T>::WallBase;
    
    bool join(d2kmapapi::Direction direction){
        Location location = nextLocation(direction);
        return join(location.x, location.y);
    }
    bool join(int x, int y) override {
        int last_x = this->last_position.getX();
        int last_y = this->last_position.getY();
        if (
            y == last_y && abs(x - last_x) <= 1 ||
            x == last_x && abs(y - last_y) <= 1    
        )
            return false;
        return WallBase<T>::join(x, y);
    }
private:
    Location nextLocation(d2kmapapi::Direction direction){
        Location pos = this->last_position;
        switch (direction){
            case d2kmapapi::Direction::UP:
                pos.y--;
            case d2kmapapi::Direction::RIGHT:
                pos.x++;
            case d2kmapapi::Direction::DOWN:
                pos.y++;
            case d2kmapapi::Direction::LEFT:
                pos.x--;
        }
        return pos;
    }
};
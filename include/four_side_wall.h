#pragma once
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
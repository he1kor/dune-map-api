#pragma once

namespace d2kmapapi{
    enum Direction {
        UP = 0,
        LEFT = 1,
        DOWN = 2,
        RIGHT = 3
    };
    Direction reverse(Direction direction);
}
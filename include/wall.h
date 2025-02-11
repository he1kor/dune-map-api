#pragma once
#include <vector>

enum WallSegment {
    NONE = 0,
    REQUIRED = 1,
    OPTIONAL = 2
};

class Wall{
    public:
        Wall();
        Wall(int width, int height);

    private:
        int width = 0;
        int height = 0;
        std::vector<std::vector<WallSegment>> segments;
};
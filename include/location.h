#pragma once

//todo:: make it base for all classes containing x y
class Location {
    public:
        Location(int x, int y);
        int getX() const;
        int getY() const;
    protected:
        int x;
        int y;
};
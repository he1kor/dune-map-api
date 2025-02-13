#pragma once

class SquareZone{
public:
    SquareZone();
    SquareZone(int width, int height, int left_x, int top_y);
    bool isCollided(int x, int y);
    void moveX(int shift_x);
    void moveY(int shift_y);
    void move(int shift_x, int shift_y);
    int getWidth();
    int getHeight();
    int getX();
    int getY();

private:
    int left_x = 0;
    int top_y = 0;
    int width = 0;
    int height = 0;
};
#pragma once

class SquareZone{
public:
    SquareZone();
    SquareZone(int width, int height, int left_x, int top_y);
    bool isCollided(int x, int y) const;
    void moveX(int shift_x);
    void moveY(int shift_y);
    void move(int shift_x, int shift_y);
    void setPosition(int x, int y);
    int getWidth() const;
    int getHeight() const;
    int getX() const;
    int getY() const;

private:
    int left_x = 0;
    int top_y = 0;
    int width = 0;
    int height = 0;
};
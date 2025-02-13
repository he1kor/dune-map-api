#include "square_zone.h"

SquareZone::SquareZone(){}

SquareZone::SquareZone(int width, int height, int left_x, int top_y) : width(width), height(height), left_x(left_x), top_y(top_y){}

bool SquareZone::isCollided(int x, int y) const{
    if (
        left_x <= x && x < left_x + width
        &
        top_y <= y && y < top_y + height
    )
        return true;
    return false;
}

void SquareZone::moveX(int shift_x){
    this->left_x += shift_x;
}

void SquareZone::moveY(int shift_y){
    this->top_y += shift_y;
}

void SquareZone::move(int shift_x, int shift_y){
    this->left_x += shift_x;
    this->top_y += shift_y;
}

void SquareZone::setPosition(int x, int y){
    this->left_x = x;
    this->top_y = y;
}

int SquareZone::getWidth() const{
    return width;
}

int SquareZone::getHeight() const{
    return height;
}

int SquareZone::getX() const{
    return left_x;
}

int SquareZone::getY() const{
    return top_y;
}

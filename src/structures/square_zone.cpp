#include "square_zone.h"

SquareZone::SquareZone(){}

SquareZone::SquareZone(int width, int height, int left_x, int top_y) : width(width), height(height), left_x(left_x), top_y(top_y){}

bool SquareZone::isCollided(int x, int y){
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

int SquareZone::getWidth(){
    return width;
}

int SquareZone::getHeight(){
    return height;
}

int SquareZone::getX(){
    return left_x;
}

int SquareZone::getY(){
    return top_y;
}

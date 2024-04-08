#include "directional_line.h"
#include "util.h"

DirectionalLine::DirectionalLine(const std::vector<uint16_t>& lines, d2kmapapi::Direction normal_direction) : lines{lines}, normal_direction{normal_direction}{}

void DirectionalLine::reverse(){
    normal_direction = d2kmapapi::reverse(normal_direction);
}

int DirectionalLine::size(){
    return lines.size();
}

uint16_t DirectionalLine::operator[](int i){
    return lines.at(i);
}

d2kmapapi::Direction DirectionalLine::getNormalDirection(){
    return normal_direction;
}
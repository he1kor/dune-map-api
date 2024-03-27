#include "block_placer.h"
#include <vector>
#include <utility>

bool BlockPlacer::fit(const Edge &edge) const{
    Direction direction;
    if (edge.getOrientation() == Orientation::horizontal)
        direction = Direction::RIGHT;
    else
        direction = Direction::DOWN;
    
    std::vector<std::pair<int, int>> coords1 = edge.onBefore();
    std::vector<std::pair<int, int>> coords2 = edge.onAfter();
    for (int i = 0; i < edge.getSize(); i++){
        auto [x1, y1] = coords1[i];
        auto [x2, y2] = coords2[i];
        if (!compatible_checker->areCompatible(
            (*map)[y1][y2].tileID,
            direction,
            (*map)[y1][y2].tileID))
            return false;
    }
    return true;
}
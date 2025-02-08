#pragma once
#include "edge.h"

class DirectedEdge{
public:
    DirectedEdge(Edge edge, d2kmapapi::Direction direction);
    const Edge& getEdge() const;
    const d2kmapapi::Direction& getDirection() const;
private:
    Edge edge;
    d2kmapapi::Direction direction;
};
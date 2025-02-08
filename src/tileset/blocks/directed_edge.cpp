#include "directed_edge.h"


DirectedEdge::DirectedEdge(Edge edge, d2kmapapi::Direction direction) : edge(edge), direction(direction){}

const Edge &DirectedEdge::getEdge() const{
    return edge;
}

const d2kmapapi::Direction &DirectedEdge::getDirection() const{
    return direction;
}

#pragma once
#include <stack>
#include <set>
#include "located_tile.h"
#include "map.h"

class HistoryStack{
    public:
        HistoryStack(Map* map);
        void trackChange(std::set<LocatedTile> located_tiles);
        void trackChange(LocatedTile located_tile);
        void quickCommit(std::set<LocatedTile> located_tiles);
        void quickCommit(LocatedTile located_tile);
        void commit();
        void undo();
    private:
        Map* map;
        std::set<LocatedTile> tracked_changes;
        std::stack<std::set<LocatedTile>> history_stack;
}
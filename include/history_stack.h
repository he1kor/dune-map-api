#pragma once
#include <stack>
#include <set>
#include "located_tile.h"
#include "map.h"

class HistoryStack{
    public:
        HistoryStack(Map* map);
        void trackChange(const std::set<LocatedTile>& located_tiles);
        void trackChange(LocatedTile located_tile);
        void quickCommit(const std::set<LocatedTile>& located_tiles);
        void quickCommit(LocatedTile located_tile);
        bool commit();
        void undo();
    private:
        Map* map;
        std::set<LocatedTile> tracked_changes;
        std::stack<std::set<LocatedTile>> history_stack;
};
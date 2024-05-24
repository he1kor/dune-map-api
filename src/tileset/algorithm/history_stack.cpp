#include "history_stack.h"

HistoryStack::HistoryStack(Map *map) : map{map}{}

void HistoryStack::trackChange(std::set<LocatedTile> located_tiles){
    for (auto lt : located_tiles){
        trackChange(lt);
    }
}

void HistoryStack::trackChange(LocatedTile located_tile){
    int x = located_tile.x;
    int y = located_tile.y;
    tracked_changes.insert(LocatedTile((*map)[y][x], x, y));
    (*map)[y][x] = located_tile;
}

bool HistoryStack::commit(){
    if (tracked_changes.empty())
        return false;
    history_stack.push(tracked_changes);
    tracked_changes.clear();
    return true;
}

void HistoryStack::quickCommit(std::set<LocatedTile> located_tiles){
    trackChange(located_tiles);
    commit();
}

void HistoryStack::quickCommit(LocatedTile located_tile){
    trackChange(located_tile);
    commit();
}

void HistoryStack::undo(){
    for (auto lt : history_stack.top()){
        (*map)[lt.y][lt.x] = lt;
    }
    history_stack.pop();
}

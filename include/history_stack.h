#pragma once
#include <set>
#include <stack>
#include "change_tracker.h"

template<typename Change>
class HistoryStack{
    public:
    HistoryStack(ChangeTracker<Change>& change_tracker);
        void trackChange(const std::set<Change>& changes);
        void trackChange(Change change);
        void quickCommit(const std::set<Change>& changes);
        void quickCommit(Change change);
        bool commit();
        void undo();
    private:
        ChangeTracker<Change>& change_tracker;
        std::set<Change> tracked_changes;
        std::stack<std::set<Change>> history_stack;
};

template <typename Change>
inline HistoryStack<Change>::HistoryStack(ChangeTracker<Change>& change_tracker) : change_tracker(change_tracker){}

template <typename Change>
inline void HistoryStack<Change>::trackChange(const std::set<Change> &changes){
    for (auto change : changes){
        trackChange(change);
    }
}

template <typename Change>
inline void HistoryStack<Change>::trackChange(Change change){
    tracked_changes.insert(change_tracker.getOldState(change));
    change_tracker.applyChange(change);
}

template <typename Change>
inline void HistoryStack<Change>::quickCommit(const std::set<Change> &changes){
    trackChange(changes);
    commit();
}

template <typename Change>
inline void HistoryStack<Change>::quickCommit(Change change){
    trackChange(change);
    commit();
}

template <typename Change>
inline bool HistoryStack<Change>::commit(){
    if (tracked_changes.empty())
        return false;
    history_stack.push(tracked_changes);
    tracked_changes.clear();
    return true;
}

template <typename Change>
inline void HistoryStack<Change>::undo(){
    change_tracker.apply(history_stack.top());
    history_stack.pop();
}

#pragma once

template<typename Change>
class ChangeTracker{
    public:
        virtual Change getOldState(const Change& changing_state) const = 0;
        virtual void applyChange(Change change) = 0;
        virtual void undoChange(Change backup_change) = 0;
};
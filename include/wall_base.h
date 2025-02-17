#pragma once

#include <vector>
#include <exception>
#include "priority_map.h"
#include "wall_pattern.h"
#include "change_tracker.h"
#include "located_state.h"
#include "history_stack.h"
#include "square_zone.h"
#include "location.h"
#include "util.h"

enum class ReplacementStatus{
    PLACED,
    LOW_PRIORITY,
    NON_REPLACEABLE,
    OUT_OF_BOUNDS
};

template <typename T>
class WallBase : private ChangeTracker<LocatedState<int>>, private ChangeTracker<LocatedState<T>>, private ChangeTracker<Location>{
    static constexpr int NO_NUMBER = -1;
    static constexpr int NO_COORDS = -1000;
    public:
        WallBase(int width, int height, PriorityMap<T> priority_map, int replacement_distance) :
            WallBase(
                width,
                height,
                priority_map,
                WallPattern<T>(width, height),
                std::vector(0, std::vector<int>(0),
                0,
                0
            )
        )
            {}
        WallBase(int width, int height, PriorityMap<T> priority_map, int replacement_distance, WallPattern<T> pattern, int x_offset, int y_offset) :
            width(width),
            height(height),
            priority_map{priority_map},
            pattern{pattern},
            numbering{std::vector(height, std::vector(width, NO_NUMBER))},
            segments{std::vector(height, std::vector<T>(height))},
            replacement_area(replacement_distance, replacement_distance, NO_COORDS, NO_COORDS),
            segments_history(*this),
            numbering_history(*this),
            replacement_area_history(*this)
            {}
        void setPattern(WallPattern<T> pattern){
            this->pattern = pattern;
        }
        int getWidth(){
            return width;
        };
        int getHeight(){
            return height;
        }
        void setMaxRepleceablePriority(int val){
            this->max_replaceable_priority = val;
        }
        int getMaxRepleceablePriority(){
            return max_replaceable_priority;
        }
        T getSegment(int x, int y) const{
            return segments[y][x];
        }
        void setJoinEndsMaxDistance(int value){
            join_ends_max_distance = value;
        }
        int getJoinEndsMaxDistance(){
            return join_ends_max_distance;
        }
    protected:
        ReplacementStatus addSegment(int x, int y, T t){
            if (y < 0 - pattern.getHeight() || y >= getHeight() + pattern.getHeight())
                return ReplacementStatus::OUT_OF_BOUNDS;
            if (x < 0 - pattern.getWidth() || x >= getWidth() + pattern.getWidth())
                return ReplacementStatus::OUT_OF_BOUNDS;
            if (!priority_map.isHigher(segments[y][x], t))
                return ReplacementStatus::LOW_PRIORITY;
            if (priority_map.getPriority(segments[y][x]) > max_replaceable_priority && !replacement_area.isCollided(x, y))
                return ReplacementStatus::NON_REPLACEABLE;
            segments_history.trackChange({t, x, y});
            return ReplacementStatus::PLACED;
        }
        void addNumber(int x, int y){
            if (numbering[y][x] != NO_NUMBER)
                throw std::invalid_argument("Provided location already has a number");
            numbering_history.quickCommit({NO_NUMBER, x, y});
        }
        void moveReplacementArea(int x, int y){
            replacement_area_history.quickCommit(
                {x - (replacement_area.getWidth() / 2),
                y - (replacement_area.getHeight() / 2)
            });
        }
        //todo:: raycast? determine if inner or not tile inside the wall
        bool virtual joinEnds(){
            int x1 = first_position.getX();
            int y1 = first_position.getY();
            int x2 = last_position.getX();
            int y2 = last_position.getY();
            if (d2kmapapi::getManhattanDistance(x1, y1, x2, y2) > join_ends_max_distance)
            return false;
            int temp = max_replaceable_priority;
            max_replaceable_priority = PriorityMap<T>::HIGHEST_PRIORITY;
            if (x1 < x2){
                x1++;
                while (x1 < x2){
                    join(x1, y1);
                    x1++;
                }
            } else {
                x2++;
                while (x2 < x1){
                    join(x2, y2);
                    x2++;
                }
            }
            if (y1 < y2){
                y1++;
                while (y1 < y2){
                    join(y1, x1);
                    y1++;
                }
            } else {
                y2++;
                while (y2 < y1){
                    join(y2, x2);
                    y2++;
                }
            }
            max_replaceable_priority = temp;
            return true;
        }
        bool virtual join(int x, int y){
            for (int yi = 0; yi < pattern.getHeight(); yi++){
                for (int xi = 0; xi < pattern.getWidth(); xi++){
                    if (addSegment(x + xi - pattern.getXOffset(), y + yi - pattern.getYOffset(), pattern.getSegment(xi, yi)) == ReplacementStatus::NON_REPLACEABLE){
                        segments_history.discardChanges();
                        return false;
                    }
                }
            }
            addNumber(x, y);
            moveReplacementArea(x, y);
            segments_history.commit();
            return true;
        }

        int join_ends_max_distance = 0;
        int width = 0;
        int height = 0;
        PriorityMap<T> priority_map;
        int max_replaceable_priority = 0;
        WallPattern<T> pattern;
        int last_number = -1;
        Location last_position = {NO_COORDS, NO_COORDS};
        Location first_position = {NO_COORDS, NO_COORDS};

        SquareZone replacement_area;
        
        std::vector<std::vector<int>> numbering;
        std::vector<std::vector<T>> segments;

        HistoryStack<Location> replacement_area_history;
        HistoryStack<LocatedState<int>> numbering_history;
        HistoryStack<LocatedState<T>> segments_history;
    private:

        LocatedState<int> getOldState(const LocatedState<int>& changing_number_state) const override{
            return LocatedState<int>(
                numbering[changing_number_state.y][changing_number_state.y],
                changing_number_state.x,
                changing_number_state.y);
        }
        void applyChange(LocatedState<int> changing_number_state) override{
            last_number++;
            last_position = {changing_number_state.x, changing_number_state.y};
            numbering[changing_number_state.y][changing_number_state.x] = last_number;
            if (last_number == 0)
                first_position = {changing_number_state.x, changing_number_state.y};
        }
        void undoChange(LocatedState<int> old_number_state) override{
            last_number--;
            last_position = {old_number_state.x, old_number_state.y};
            numbering[old_number_state.y][old_number_state.x] = old_number_state.state;
            if (last_number == -1)
                first_position = {NO_COORDS, NO_COORDS};
        }


        LocatedState<T> getOldState(const LocatedState<T>& changing_segment) const override{
            return LocatedState<T>(
                segments[changing_segment.y][changing_segment.y],
                changing_segment.x,
                changing_segment.y);
        }

        void applyChange(LocatedState<T> change) override{
            segments[change.y][change.x] = change.state;
        }
        void undoChange(LocatedState<T> old_state) override{
            segments[old_state.y][old_state.x] = old_state.state;
        }

        Location getOldState(const Location& new_replacement_area_location) const override{
            return {replacement_area.getX(), replacement_area.getY()};
        }
        void applyChange(Location changing_replacement_area_location) override{
            replacement_area.setPosition(changing_replacement_area_location.getX(), changing_replacement_area_location.getY());
        }
        void undoChange(Location old_replacement_area_location) override{
            replacement_area.setPosition(old_replacement_area_location.getX(), old_replacement_area_location.getY());
        }
    
    };

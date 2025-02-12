#pragma once

#include <vector>
#include <exception>
#include "priority_map.h"
#include "wall_pattern.h"
#include "change_tracker.h"
#include "located_state.h"
#include "history_stack.h"

static const int NO_NUMBER = -1;

template <typename T>
class Wall : private ChangeTracker<LocatedState<int>>, private ChangeTracker<LocatedState<T>>{
    public:
        Wall(int width, int height, PriorityMap<T> priority_map) :
            Wall(width,
                height,
                priority_map,
                WallPattern<T>(width, height),
                std::vector(0, std::vector<int>(0), 0, 0))
            {}
        Wall(int width, int height, PriorityMap<T> priority_map, WallPattern<T> pattern, int x_offset, int y_offset) :
            width(width),
            height(height),
            priority_map{priority_map},
            pattern{pattern},
            numbering{std::vector(height, std::vector(width, NO_NUMBER))},
            segments{std::vector(height, std::vector<T>(height))}
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
        void place(int x, int y, T t){
            if (priority_map.isHigher(segments[y][x], t))
                segments[y][x] = t;
        }
        void addNumber(int x, int y){
            if (numbering[y][x] != NO_NUMBER)
                throw std::invalid_argument("Provided location already has a number");
            last_number++;
            numbering[y][x] = last_number;
        }

        void join(int x, int y){
            if (pattern.size() == 0)
            throw std::runtime_error("Segment is not set");
            
            addNumber(x, y);
            for (int yi = 0; yi < pattern.getHeight(); yi++){
                for (int xi = 0; xi < pattern.getWidth(); xi++){
                    place(x + xi - pattern.getXOffset(), y + yi - pattern.getYOffset(), pattern.getSegment(xi, yi));
                }
            }
        }

    private:
        LocatedState<int> getOldState(const LocatedState<int>& changing_state){
            return LocatedState<int>(numbering[changing_state.y][changing_state.y], x, y);
        }

        void applyChange(LocatedState<int> change){
            numbering[change.y][change.x] = change.state;
            last_number = change.state;
        }

        LocatedState<T> getOldState(const LocatedState<T>& changing_state){
            return LocatedState<T>(segments[changing_state.y][changing_state.y], x, y);
        }

        void applyChange(LocatedState<T> change){
            segments[change.y][change.x] = change.state;
        }

        int width = 0;
        int height = 0;
        PriorityMap<T> priority_map;
        WallPattern<T> pattern;
        int last_number = -1;
        
        std::vector<std::vector<int>> numbering;
        std::vector<std::vector<T>> segments;

        HistoryStack<LocatedState<int>> numbering_history;
        HistoryStack<LocatedState<T>> segments_history;
    };

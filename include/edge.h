#pragma once
#include <vector>
#include <utility>

enum Orientation{
    vertical,
    horizontal
};

class Edge{
    public:
    protected:
        Edge(int x, int y, int size, Orientation orientation);
        int x;
        int y;
        int size;
        Orientation orientation;
};

class Horizontal : public Edge{
    public:
        static Horizontal fromTop(int x, int y);
        static Horizontal fromTop(int x1, int x2, int y);
        static Horizontal fromBottom(int x, int y);
        static Horizontal fromBottom(int x1, int x2, int y);
    protected:
        Horizontal(int x, int y, int size);
};

class Vertical : public Edge{
    public:
        static Vertical fromLeft(int x, int y);
        static Vertical fromLeft(int x1, int x2, int y);
        static Vertical fromRight(int x, int y);
        static Vertical fromRight(int x1, int x2, int y);
        std::vector<std::pair<int, int>> onLeft();
        std::pair<int, int> onLeft(int i);
        std::vector<std::pair<int, int>> onRight();
        std::pair<int, int> onRight(int i);
    protected:
        Vertical(int x, int y, int size);
};
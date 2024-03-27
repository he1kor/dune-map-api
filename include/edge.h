#pragma once
#include <vector>
#include <utility>

enum Orientation{
    vertical,
    horizontal
};

class Edge{
    public:
        std::vector<std::pair<int, int>> onBefore() const;
        std::pair<int, int> onBefore(int i) const;
        std::vector<std::pair<int, int>> onAfter() const;
        std::pair<int, int> onAfter(int i) const;
        int getX() const;
        int getY() const;
        int getSize() const;
        Orientation getOrientation() const;
    protected:
        Edge(int x, int y, int size, Orientation orientation);
        int x;
        int y;
        int size;
        Orientation orientation;
        static bool checkLeftBounds(int x);
        static bool checkRightBounds(int x);
        static bool checkTopBounds(int y);
        static bool checkBottomBounds(int y);
};

class Horizontal : public Edge{
    public:
        static Horizontal fromTop(int x, int y);
        static Horizontal fromTop(int x1, int x2, int y);
        static Horizontal fromBottom(int x, int y);
        static Horizontal fromBottom(int x1, int x2, int y);
        std::vector<std::pair<int, int>> onTop();
        std::pair<int, int> onTop(int i);
        std::vector<std::pair<int, int>> onBottom();
        std::pair<int, int> onBottom(int i);
    protected:
        Horizontal(int x, int y, int size);
};

class Vertical : public Edge{
    public:
        static Vertical fromLeft(int x, int y);
        static Vertical fromLeft(int y1, int y2, int x);
        static Vertical fromRight(int x, int y);
        static Vertical fromRight(int y1, int y2, int x);
        std::vector<std::pair<int, int>> onLeft();
        std::pair<int, int> onLeft(int i);
        std::vector<std::pair<int, int>> onRight();
        std::pair<int, int> onRight(int i);
    protected:
        Vertical(int x, int y, int size);
};
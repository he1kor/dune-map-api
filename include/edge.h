#pragma once
#include <vector>
#include <utility>
#include "util.h"

/*!
	\brief Orientation of an edge
*/
enum Orientation{
    vertical,
    horizontal
};

/*!
	\brief Base class representing edge at some coords between two rows of tiles.
    Can be either vertical or horizontal, contains its coords and size.
    No public constructor, Horizontal or Vertical should be used for instancing.
    Coords represent X and Y of tile AFTER the edge. So, Y of tile before horizontal is horizontal Y - 1
*/
class Edge{
    public:
        /**
         * \brief Returns coords of tiles before edge.
         * \return Array of pairs, representing X and Y coords.
        */
        std::vector<std::pair<int, int>> onBefore() const;
        /**
         * \brief Returns coords of i-th tile before edge.
         * \return Pair representing X and Y coords.
        */
        std::pair<int, int> onBefore(int i) const;
        /**
         * \brief Returns coords of tiles after edge.
         * \return Array of pairs, representing X and Y coords.
        */
        std::vector<std::pair<int, int>> onAfter() const;
        /**
         * \brief Returns coords of i-th tile after edge.
         * \return Pair representing X and Y coords.
        */
        std::pair<int, int> onAfter(int i) const;
        /**
         * \brief Getter for X position.
         * \return X integer.
        */
        int getX() const;
        /**
         * \brief Getter for Y position.
         * \return this x.
        */
        int getY() const;
        /**
         * \brief Getter for size (length) of the edge.
         * \return thix y.
        */
        int getSize() const;
        /**
         * \brief Getter for Orientation of the edge.
         * \return this orientation.
        */
        Orientation getOrientation() const;
        bool isAlong(d2kmapapi::Direction direction);
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
/*!
	\brief Edge that can be horizontal only.
*/
class Horizontal : public Edge{
    public:
        /**
         * \brief Initializer of 1-size Horizontal, which will be under provided Y.
         * \param x X of the horizontal.
         * \param y Y of tile above the horizontal.
         * \return constructed Horizontal.
        */
        static Horizontal fromTop(int x, int y);
        /**
         * \brief Initializer of Horizontal with size x2-x1, which will be under provided Y.
         * \param x1 The left X of the horizontal.
         * \param x2 The right X of the horizontal.
         * \param y Y of tile above the horizontal.
         * \return constructed Horizontal.
        */
        static Horizontal fromTop(int x1, int x2, int y);
        /**
         * \brief Initializer of 1-size Horizontal, which will be above provided Y.
         * \param x X of the horizontal.
         * \param y Y of tile under the horizontal.
         * \return constructed Horizontal.
        */
        static Horizontal fromBottom(int x, int y);
        /**
         * \brief Initializer of Horizontal with size x2-x1, which will be above provided Y.
         * \param x1 The left X of the horizontal.
         * \param x2 The right X of the horizontal.
         * \param y Y of tile under the horizontal.
         * \return constructed Horizontal.
        */
        static Horizontal fromBottom(int x1, int x2, int y);

        /**
         * \brief The same as onBefore(), but specifically for horizontal.
         * \return array of tile coords above the horizontal.
        */
        std::vector<std::pair<int, int>> onTop();

        /**
         * \brief The same as onBefore(int i), but specifically for horizontal.
         * \return coords of the tile above the horizontal.
        */
        std::pair<int, int> onTop(int i);

        /**
         * \brief The same as onAfter(), but specifically for horizontal.
         * \return tile coords under the horizontal.
        */
        std::vector<std::pair<int, int>> onBottom();

        /**
         * \brief The same as onAfter(int i), but specifically for horizontal.
         * \return coords of the tile under the horizontal.
        */
        std::pair<int, int> onBottom(int i);
    protected:
        Horizontal(int x, int y, int size);
};
/*!
	\brief Edge that can be vertical only.
*/
class Vertical : public Edge{
    public:
    
        /**
         * \brief Initializer of 1-size Vertical, which will be on the right of the provided X.
         * \param x X of the tile on the left of the verticle.
         * \param y Y of the verticle.
         * \return constructed verticle.
        */
        static Vertical fromLeft(int x, int y);

        /**
         * \brief Initializer of the Vertical with size y2-y1, which will be on right of the provided X.
         * \param y1 The top Y of the verticle.
         * \param y2 The bottom Y of the verticle.
         * \param x X of the tile on the left of the verticle.
         * \return constructed verticle.
        */
        static Vertical fromLeft(int y1, int y2, int x);

        /**
         * \brief Initializer of 1-size Vertical, which will be on the left of the provided X.
         * \param x X of the tile on the right of the verticle.
         * \param y Y of the verticle.
         * \return constructed verticle.
        */
        static Vertical fromRight(int x, int y);

        /**
         * \brief Initializer of the Vertical with size y2-y1, which will be on left of the provided X.
         * \param y1 The top Y of the verticle.
         * \param y2 The bottom Y of the verticle.
         * \param x X of the tile on the right of the verticle.
         * \return constructed verticle.
        */
        static Vertical fromRight(int y1, int y2, int x);

        /**
         * \brief The same as onBefore(), but specifically for vertical.
         * \return array of tile coords on the left of the vertical.
        */
        std::vector<std::pair<int, int>> onLeft();

        /**
         * \brief The same as onBefore(int i), but specifically for vertical.
         * \return coords of the tile on the left of the vertical.
        */
        std::pair<int, int> onLeft(int i);

        /**
         * \brief The same as onAfter(), but specifically for vertical.
         * \return array of tile coords on the right of the vertical.
        */
        std::vector<std::pair<int, int>> onRight();

        /**
         * \brief The same as onAfter(int i), but specifically for vertical.
         * \return coords of the tile on the right of the vertical.
        */
        std::pair<int, int> onRight(int i);
    protected:
        Vertical(int x, int y, int size);
};
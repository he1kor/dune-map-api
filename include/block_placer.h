
#pragma once
#include <vector>
#include <cstdint>
#include "block_set.h"
#include "map.h"
#include "edge.h"
#include "util.h"
#include "compatible_checker.h"
#include "history_stack.h"
/*!
	\brief Class allows to work with BlockSet on certain map. For that, it contains BlockSet* and Map*.
*/
class BlockPlacer{
    public:
    
        /**
         * \brief Default constructor, need to manually initialize BlockSet and Map later.
        */
        /// Places provided block on the map. Top-left corner of the block is located at [x, y].
        BlockPlacer();
        /**
         * \brief Constructor with BlockSet* given, need to manually initialize Map later.
         * \param block_set pointer to BlockSet which will be used by BlockPlacer.
        */
        BlockPlacer(BlockSet* block_set);

        void setHistoryStack(HistoryStack* history_stack);

        /**
         * \brief Places provided block on the map. Top-left corner of the block is located at [x, y].
         * \param x x position of top-left block corner on the map
         * \param x y position of top-left block corner on the map
         * \param Block block to be placed.
        */
        void place(int x, int y, const Block& block);
        /**
         * \brief Determines do adjacent tiles to the given edge fit each other (According to built-in internal BlockSet CompatibleChecker).
         * \param edge edge, next to which tiles are checked for compatibility.
        */
        bool placeEdge(const Edge& edge, const d2kmapapi::Direction& direction, const Block& block);
        bool fit(const Edge& edge) const;
    private:
        CompatibleChecker* compatible_checker;
        BlockSet* block_set;
        HistoryStack* history_stack;
        Map* map;
};
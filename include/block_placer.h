
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
        void setMap(Map* map);
        void setBlockSet(BlockSet* block_set);

        /**
         * \brief Places provided block on the map. Top-left corner of the block is located at [x, y].
         * \param x x position of top-left block corner on the map
         * \param x y position of top-left block corner on the map
         * \param Block block to be placed.
        */
        void place(int x, int y, const Block &block);
        /**
         * \brief Determines do adjacent tiles to the given edge fit each other (According to built-in internal BlockSet CompatibleChecker).
         * \param edge edge, next to which tiles are checked for compatibility.
        */
        //void findNextPlace(const Edge& edge);
        DirectionalLine getLineFacingEdge(const Edge& edge, const d2kmapapi::Direction &facingDirection);
        std::vector<CompatibleType> getCompatibleTypesFacingEdge(const Edge& edge, const d2kmapapi::Direction &facingDirection);
        int getShift(const Edge& edge, const d2kmapapi::Direction &direction, const Block& block);
        int nextBlockScore(const Edge& edge, const d2kmapapi::Direction &direction, const Block& block, std::vector<CompatibleType> block_next_compatible, std::vector<CompatibleType> temp_next);
        void loopPlace(const Edge& edge, const d2kmapapi::Direction& direction, std::vector<std::vector<CompatibleType>> next_edges);
        bool smartEdgePlace(const Edge &edge, const d2kmapapi::Direction &direction, const Block &block);
        bool placeEdge(const Edge &edge, const d2kmapapi::Direction &direction, const Block &block);
        bool isEdgeCompatible(const Edge& edge) const;
    private:
        void placeUntracked(int x, int y, const Block &block);
        CompatibleChecker* compatible_checker = nullptr;
        BlockSet* block_set = nullptr;
        HistoryStack* history_stack = nullptr;
        Map* map = nullptr;
};
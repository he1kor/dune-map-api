/**
 * \file
 * \brief Contains Block and BlockSet classes.
 * 
*/

#pragma once
#include <vector>
#include <cstdint>
#include "directional_line.h"
#include "compatible_checker.h"

/*!
	\brief Class, which contains very related tiles in the one matrix.
*/
class Block{
    public:
        /**
         * \brief Common constructor, worked by provided tileset coords, width and height of block. The whole tileset width is determined in global.h
         * \param x x of top-left corner of the block in tileset matrix.
         * \param y y of top-left corner of the block in tileset matrix.
        */
        Block(int x, int y, int width, int height);
        
        /**
         * \brief Copy constructor.
        */
        Block(const Block& block);
        
        /**
         * \brief Getter of matrix.
         * \return matrix of block tiles.
        */
        std::vector<std::vector<uint16_t>> getMatrix() const;
        
        /**
         * \brief Getter of top side of the matrix.
         * \return vector of tiles
        */
        std::vector<uint16_t> getTopTiles() const;
        
        /**
         * \brief Getter of left side of the matrix.
         * \return vector of tiles
        */
        std::vector<uint16_t> getLeftTiles() const;
        
        /**
         * \brief Getter of right side of the matrix.
         * \return vector of tiles
        */
        std::vector<uint16_t> getRightTiles() const;

        /**
         * \brief Getter of bottom side of the matrix.
         * \return vector of tiles
        */
        std::vector<uint16_t> getBottomTiles() const;
        /**
         * \brief Getter of width of the matrix.
         * \return width integer
        */
        int getWidth() const;
        /**
         * \brief Getter of height of the matrix.
         * \return width integer
        */
        int getHeight() const;
    private:    
        std::vector<uint16_t> left;
        std::vector<uint16_t> right;
        int width;
        int height;
        std::vector<std::vector<uint16_t>> tiles;
};
class BlockSet{
    public:
        BlockSet(const std::map<std::string, std::vector<Block>>& blocks);
        BlockSet();
        void addCompatibleCheker(const CompatibleChecker* compatible_checker);
        void addGroup(const std::string& group);
        void addBlock(const Block& block, const std::string& group);
        std::vector<Block> operator[](std::string group) const;
        std::vector<std::string> getGroups();
        std::vector<Block> compatibleBlocks(const DirectionalLine& line, std::string group);
    private:
        const CompatibleChecker* compatible_checker;
        std::map<std::string, std::vector<Block>> block_groups;
};
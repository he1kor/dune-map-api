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
	\brief Class, which contains inseparable tiles in the one matrix.
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
        DirectionalLine getDirectionalOutLine(d2kmapapi::Direction direction) const;
        
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
    /*!
	\brief Container of block groups. All groups can be accesed by corresponding string name. CompatibleChecker is included for determing compatibility of different blocks.
    */
   class BlockSet{
       public:
       /**
        * \brief Constructor, setting block_groups field and compatible_checker pointer.
        * \param block_groups map of string to array of blocks.
        * \param compatible_checker CompatibleChecker pointer.
        */
       BlockSet(const std::map<std::string, std::vector<Block>>& block_groups, CompatibleChecker* compatible_checker);
       
       /**
        * \brief Constructor, setting block_groups field.
        * \param block_groups map of string to array of blocks.
        */
       BlockSet(const std::map<std::string, std::vector<Block>>& block_groups);
       /**
        * \brief Constructor with late block_groups initialization.
        */
       BlockSet();
       /**
        * \brief Sets active compatible checker for compatible operations.
        * \param compatible_checker compatible_checker pointer to be set as field
        */
       int getShift(const DirectionalLine& directional_line, const Block& block) const;
       void addCompatibleCheker(CompatibleChecker* compatible_checker);
       /**
        * \brief Adds a new block group to block grouops.
        * \param group block group to be added.
        */
       void addGroup(const std::string& group);
       /**
        * \brief Adds a new block to certain block group.
        * \param block block to be added
         * \param group target group
        */
        void addBlock(const Block& block, const std::string& group);
        /**
         * \brief returns block group by group name.
         * \param group string name of the group
         * \return array of blocks
        */
        std::vector<Block> operator[](std::string group) const;
        /**
         * \brief returns all group names.
         * \return array of all group names
        */
        std::vector<std::string> getGroups();

        /**
         * \brief compatible_checker getter.
         * \return Pointer to CompatibleChecker.
        */
        CompatibleChecker* getCompatibleChecker() const;
        /**
         * \brief Calculates all blocks of given group compatible to given line from its direction.
         * \param line line to which all returned blocks should be compatible
         * \param group name of group in which compatible blocks are searched.
        */
        std::vector<Block> compatibleBlocks(const std::vector<CompatibleType> &compatible_types, d2kmapapi::Direction direction, std::string group_name);
        std::vector<Block> compatibleBlocks(const DirectionalLine &line, std::string group);

    private:
        CompatibleChecker* compatible_checker;
        std::map<std::string, std::vector<Block>> block_groups;
};
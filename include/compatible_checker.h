#pragma once
#include <set>
#include <string>
#include <array>
#include <unordered_map>
#include <map>
#include <cstdint>
#include "util.h"
#include "directional_line.h"

/*!
	\brief String wrapper for containing name of CompatibleType
*/
class CompatibleType{
    public:
        /**
         * \brief Default constructor, assumes "" as the type_name.
        */
        CompatibleType();
        /**
         * \brief Common constructor, takes string as the type_name.
         * \param type_name sets the type_name
        */
        CompatibleType(std::string type_name);
        /**
         * \brief Copy constructor
        */
        CompatibleType(const CompatibleType& compatible_type);
        /**
         * \brief type_name getter
         * \return type_name
        */
        std::string name() const;
        /**
         * \brief equals if type_name variables are equal.
         * \return are type_name equal
        */
        bool operator==(const CompatibleType& second_type) const;
        /**
         * \brief greater if this type_name is greater.
         * \return is this type_name greater
        */
        bool operator>(const CompatibleType& second_type) const;
        /**
         * \brief less if this type_name is less.
         * \return is this type_name less
        */
        bool operator<(const CompatibleType& second_type) const;
    private:
        std::string type_name;
};
/*!
	\brief Struct representing tile and it's compatible type from each side
*/
struct CompatibleTile{
    CompatibleTile(uint16_t tile_id, CompatibleType all_side_compatible_type);
    uint16_t tile_id;
    CompatibleType top;
    CompatibleType left;
    CompatibleType right;
    CompatibleType bottom;
};
/*!
	\brief Class containing all compatible relations between tiles and some useful methods for it.
*/
class CompatibleChecker{
    public:
        /**
         * \brief Common constructor, takes number of tiles for hash map reservation.
         * \param tile_count Required for hash map reservation for better perfomance.
        */
        CompatibleChecker(int tile_count);
        /**
         * \brief puts new tile compatible data to CompatibleChecker.
         * \param tile_count CompatibleTile to put in.
        */
        void putCompatible(CompatibleTile compatible_tile);
        /**
         * \brief returns compatibleType of some of tile's side.
         * \param tile tile id
         * \param direction direction, from what tile side that CompatibleSide
         * \return CompatibleType of the given tile's side
        */
        CompatibleType compatibleType(uint16_t tile, d2kmapapi::Direction direction) const;
        /**
         * \brief Same as compatibleType(uint16_t tile, d2kmapapi::Direction direction), but for array of tiles. Returns array of CompatibleType in the correct order.
         * \param directional_line DirectionalLine where take tile array and the direction.
         * \return vector<CompatibleType> of the given DirectionalLine.
        */
        std::vector<CompatibleType> compatibleTypes(DirectionalLine directional_line) const;
        /**
         * \brief Checks are given two tiles compatible. Direction determines what direction check second tile from the first tile.
         * \param tile1 The first tile id
         * \param tile1_direction Direction from first tile to second one.
         * \param tile2 The second tile id
         * \return are given tiles compatible from the given side
        */
        bool areCompatible(uint16_t tile1, d2kmapapi::Direction tile1_direction, uint16_t tile2) const;
    private:
        std::unordered_map<uint16_t, std::array<CompatibleType, 4>> compatibility;
};
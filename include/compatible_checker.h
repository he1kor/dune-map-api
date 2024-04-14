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
         * \brief Common constructor, takes number of tiles for hash map reservation and set of used CompatibleType
         * \param tile_count Required for hash map reservation for better perfomance.
        */
        CompatibleChecker(int tile_count);
        void putCompatible(CompatibleTile compatible_tile);
        CompatibleType compatibleType(uint16_t tile, d2kmapapi::Direction direction) const;
        std::vector<CompatibleType> compatibleTypes(DirectionalLine directional_line) const;
        bool areCompatible(uint16_t tile1, d2kmapapi::Direction tile1_direction, uint16_t tile2) const;
    private:
        std::unordered_map<uint16_t, std::array<CompatibleType, 4>> compatibility;
};
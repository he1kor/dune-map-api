#pragma once
#include "palette.h"
#include "compatible_checker.h"
#include "block_placer.h"
/*!
	\brief Container of all classes loaded from .json tileset file.
*/
struct TilesetProperties
{
    Palette palette;
    CompatibleChecker compatible_checker;
    BlockSet block_set;
};
#pragma once
#include "palette.h"
#include "compatible_checker.h"
#include "block_placer.h"

struct TilesetProperties
{
    Palette palette;
    CompatibleChecker compatible_checker;
    BlockPlacer blockPlacer;
};
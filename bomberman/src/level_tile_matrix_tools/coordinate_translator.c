#include "../../headers/level_tile_matrix_tools.h"
#include "../../headers/sprite_properties.h"

int pixelFromTile(int t)
{
    return t * TILE_SIZE;
}

int tileFromPixel(int p)
{
    return p / TILE_SIZE;
}
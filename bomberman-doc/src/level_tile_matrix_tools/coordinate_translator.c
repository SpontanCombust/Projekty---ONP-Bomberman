#include "../../headers/level_tile_matrix_tools.h"
#include "../../headers/sprite_properties.h"

float pixelFromTile( int t )
{
    return (float) (t * TILE_SIZE);
}

int tileFromPixel( float p )
{
    return (int) (p / TILE_SIZE);
}
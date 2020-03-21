#include "../headers/level_utilities.h"

void tileCoordsFromPixelCoords(int x, int y, int tileCoords[2])
{
    tileCoords[0] = (x / 32);
    tileCoords[1] = (y / 32);
}

void pixelCoordsFromTileCoords(int x, int y, int pixelCoords[2])
{
    pixelCoords[0] = ( x * 32 );
    pixelCoords[1] = ( y * 32 );
}
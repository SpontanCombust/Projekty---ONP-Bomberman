#ifndef UTILITIES_H
#define UTILITIES_H

int **createLevelTileMatrix(char *path, int rows, int collumns, int **tileMatrix);

void tileCoordsFromPixelCoords(int x, int y, int tileCoords[2]);
void pixelCoordsFromTileCoords(int x, int y, int pixelCoords[2]);

#endif
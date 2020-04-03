#ifndef TILE_MATRIX_H
#define TILE_MATRIX_H

#include "../libs/matrix.h"
#include <stdio.h>
#include <stdbool.h>

// ======================== tile_matrix_creator.c =======================

int **createLevelTileMatrix( FILE *map_file, int *rows, int *collumns );


// ===================================== coordinate_translator.c =================================

int pixelFromTile( int t );
int tileFromPixel( int p );

#endif
#ifndef TILE_MATRIX_H
#define TILE_MATRIX_H

#include "../libs/matrix.h"
#include <stdio.h>
#include <stdbool.h>

// ======================== tile_matrix_creator.c =======================

int **createLevelTileMatrix( FILE *map_file, int *rows, int *collumns, unsigned char *r, unsigned char *g, unsigned char *b );


// ===================================== coordinate_translator.c =================================

float pixelFromTile( int t );
int tileFromPixel( float p );

#endif
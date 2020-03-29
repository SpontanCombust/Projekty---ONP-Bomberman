#ifndef TILE_MATRIX_H
#define TILE_MATRIX_H

#include <stdio.h>

// ======================== tile_matrix_creator.c =======================
int **allocateMatrix( int rows, int collumns );
int **createLevelTileMatrix( FILE *map_file, int *rows, int *collumns );

// ======================== tile_matrix_handler.c =======================
int getTileContent( int **tile_matrix, int x, int y );
void setTileContent( int **tile_matrix, int x, int y, int content );
void freeMatrix( int **matrix, int rows );

// ===================================== coordinate_translator.c =================================
int pixelFromTile( int t );
int tileFromPixel( int p );

#endif
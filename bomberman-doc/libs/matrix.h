#ifndef MATRIX_H
#define MATRIX_H

#include <stdbool.h>

// ================================ matrix.c ==================================

int **allocateMatrix( int rows, int collumns );
int getTileContent( int **tile_matrix, int tile_x, int tile_y );
void setTileContent( int **tile_matrix, int tile_x, int tile_y, int content );
bool areCoordsOutOfBounds( int tile_x, int tile_y, int rows, int collumns );
int countContentInMatrix( int **tile_matrix, int rows, int collumns, int content );
void printMatrix( int **matrix, int rows, int colls );
void freeMatrix( int **matrix, int rows );

#endif
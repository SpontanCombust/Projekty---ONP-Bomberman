#include "../headers/tile_matrix_tools.h"

#include <stdlib.h>

int getTileContent( int **tile_matrix, int x, int y )
{
    return tile_matrix[ y ][ x ];
}

void setTileContent( int **tile_matrix, int x, int y, int content )
{
    tile_matrix[y][x] = content;
}

void freeMatrix( int **matrix, int rows )
{
    for (int i = 0; i < rows; i++)
        free( matrix[i] );

    free( matrix );
    matrix = NULL;
}
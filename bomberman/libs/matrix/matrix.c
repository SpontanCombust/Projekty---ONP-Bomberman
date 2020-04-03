#include "../matrix.h"

#include <stdio.h>
#include <stdlib.h>

int **allocateMatrix( int rows, int collumns )
{
    int **matrix = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++)
        matrix[i] = (int *)malloc(collumns * sizeof(int));

    if( !matrix )
    {
        puts("Failed to allocate matrix!");
        return NULL;
    }

    return matrix;
}

int getTileContent( int **tile_matrix, int tile_x, int tile_y )
{
    return tile_matrix[ tile_y ][ tile_x ];
}

void setTileContent( int **tile_matrix, int tile_x, int tile_y, int content )
{
    tile_matrix[tile_y][tile_x] = content;
}

bool areCoordsOutOfBounds( int tile_x, int tile_y, int rows, int collumns )
{
    if( tile_x < 0 || tile_x >= collumns || tile_y < 0 || tile_y >= rows )
        return true;
    return false;
}

int countContentInMatrix( int **tile_matrix, int rows, int collumns, int content )
{
    int count = 0;

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < collumns; j++)
            if( tile_matrix[i][j] == content )
                count++;
    
    return count;
}

void printMatrix( int **matrix, int rows, int colls )
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < colls; j++)
        {
            printf("%d ", matrix[i][j] );
        }
        puts("");
    }
    
}

void freeMatrix( int **matrix, int rows )
{
    for (int i = 0; i < rows; i++)
        free( matrix[i] );

    free( matrix );
    matrix = NULL;
}
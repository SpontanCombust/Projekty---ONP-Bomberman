#include "../headers/level_utilities.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int **allocateMatrix( int rows, int collumns)
{
    int **matrix = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++)
        matrix[i] = (int *)malloc(collumns * sizeof(int));

    return matrix;
}

int **createLevelTileMatrix( char *path, int *rows, int *collumns )
{
    FILE *mapFile = fopen( path, "r" );
    
    if( mapFile == NULL ){
        fprintf( stderr, "Failed to open file %s", path );
        return NULL;
    }

    int **tileMatrix = NULL;

    char buffer[100];
    char subbuf[3];
    while ( fgets( buffer, 100, mapFile ) != NULL )
    {
        if( buffer[0] == ';' )
            continue;

        else if( strcmp( buffer, "[dimensions]\n" ) == 0 )
        {
            for (int i = 0; i < 2; i++)
            {
                fgets( buffer, 100, mapFile );
                strncpy( subbuf, buffer+1, 2);
                subbuf[2] = '\0';

                if( buffer[0] == 'r' )
                    *rows = atoi( subbuf );
                else if( buffer[0] == 'c' )
                    *collumns = atoi( subbuf );      
            }
            
            tileMatrix = allocateMatrix(*rows, *collumns);
        }

        else if( strcmp( buffer, "[data]\n" ) == 0 )
        {
            for (int i = 0; i < *rows; i++)
            {
                fgets( buffer, 100, mapFile );
                for (int j = 0; j < *collumns; j++)
                    tileMatrix[i][j] = buffer[j] - '0'; 
            }   
        }
    }

    if( fclose( mapFile ) == EOF ){
        fprintf( stderr, "Failed to close file %s", path );
        return NULL;
    }

    free( mapFile );

    return tileMatrix;
}

enum BlockTypes getBlockTypeAtTile( int tile_x, int tile_y, int **map )
{
    return map[ tile_y ][ tile_x ];
}

void destroyMap( int **map, int rows )
{
    for (int i = 0; i < rows; i++)
        free( map[i] );

    free( map );
    map = NULL;
}


int main()
{   
    int rows, collumns;
    int **map = createLevelTileMatrix("../levels/test_map.txt", &rows, &collumns);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < collumns; j++)
        {
            printf("%d ", map[i][j]);
        }
        puts("");
    }
    
    
}
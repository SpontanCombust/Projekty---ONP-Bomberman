#include "../../headers/level_tile_matrix_tools.h"

#include <stdlib.h>
#include <string.h>

int **createLevelTileMatrix( FILE *map_file, int *rows, int *collumns )
{
    int **tile_matrix = NULL;

    char buffer[100];
    char subbuf[4];
    while ( fgets( buffer, 100, map_file ) != NULL )
    {
        if( buffer[0] == ';' )
            continue;

        else if( strcmp( buffer, "[dimensions]\n" ) == 0 )
        {
            for (int i = 0; i < 2; i++)
            {
                if( fgets( buffer, 100, map_file ) != NULL )
                {
                    strncpy( subbuf, buffer + 1, strlen( buffer ) - 2);
                    subbuf[ strlen( subbuf ) ] = '\0';

                    if( buffer[0] == 'r' )
                        *rows = atoi( subbuf );
                    else if( buffer[0] == 'c' )
                        *collumns = atoi( subbuf );      
                }
            }
            
            tile_matrix = allocateMatrix(*rows, *collumns);
        }

        else if( strcmp( buffer, "[data]\n" ) == 0 )
        {
            for (int i = 0; i < *rows; i++)
            {
                if( fgets( buffer, 100, map_file ) != NULL )
                    for (int j = 0; j < *collumns; j++)
                        setTileContent( tile_matrix, j, i, buffer[j] - '0' ); 
            }   
        }
    }

    return tile_matrix;
}

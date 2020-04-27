#include "../../headers/level_tile_matrix_tools.h"

#include <stdlib.h>
#include <string.h>

int **createLevelTileMatrix( FILE *map_file, int *rows, int *collumns, unsigned char *r, unsigned char *g, unsigned char *b )
{
    *rows = *collumns = 0;
    *r = *g = *b = 0;
    int **tile_matrix = NULL;

    char buffer[100];
    char subbuf[100];
    while ( fgets( buffer, 100, map_file ) != NULL )
    {
        if( buffer[0] == ';' )
            continue;
        else if( strcmp( buffer, "[background]\n" ) == 0 )
        {
            for (int i = 0; i < 3; i++)
            {
                if( fgets( buffer, 100, map_file ) != NULL )
                {
                    strncpy( subbuf, buffer + 2, strlen( buffer ) - 3);
                    subbuf[ strlen( subbuf ) ] = '\0';

                    if( buffer[0] == 'r' && buffer[1] == '=' )
                        *r = atoi( subbuf );
                    else if( buffer[0] == 'g' && buffer[1] == '=' )
                        *g = atoi( subbuf );
                    else if( buffer[0] == 'b' && buffer[1] == '=' )
                        *b = atoi( subbuf );

                    memset( subbuf, '\0', 100 );
                }
            } 
        }
        else if( strcmp( buffer, "[dimensions]\n" ) == 0 )
        {
            for (int i = 0; i < 2; i++)
            {
                if( fgets( buffer, 100, map_file ) != NULL )
                {
                    strncpy( subbuf, buffer + 2, strlen( buffer ) - 3);
                    subbuf[ strlen( subbuf ) ] = '\0';

                    if( buffer[0] == 'r' && buffer[1] == '=' )
                        *rows = atoi( subbuf );
                    else if( buffer[0] == 'c' && buffer[1] == '=' )
                        *collumns = atoi( subbuf );

                    memset( subbuf, '\0', 100 );     
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

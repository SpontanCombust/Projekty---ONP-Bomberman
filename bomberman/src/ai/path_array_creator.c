#include "../../headers/ai.h"

#include "../../headers/level_tile_matrix_tools.h"
#include <stdio.h>

static void handlePoint( PathStep * steps, int i, char *point )
{
    char *tok = strtok( point, "," );
    steps[i].dest_x = pixelFromTile( atoi( tok ) );

    tok = strtok( NULL, "," );
    steps[i].dest_y = pixelFromTile( atoi( tok ) );
    tok = NULL;
}

PathStep * createPathStepArray( char *line, int *step_num )
{
    PathStep * steps;

    char *tok = strtok( line, " " );
    *step_num = atoi( tok );

    steps = (PathStep *)calloc( *step_num, sizeof( PathStep ) );

    char * tokens[ *step_num ];
    int i = 0;

    tok = strtok( NULL, " " );
    while ( tok != NULL )
    {
        tokens[i++] = tok;
        tok = strtok( NULL, " " );
    }
    
    for (i = 0; i < *step_num; i++)
        handlePoint( steps, i, tokens[i] );
    
    return steps;
}

Path * createPathArray( char *enemies_file_path, int *paths_num )
{
    Path * paths_array = NULL;

    FILE *enemies_file = fopen( enemies_file_path, "r" );

    if( enemies_file != NULL )
    {
        char buffer[100];
        char subbuf[100];

        while ( fgets( buffer, 100, enemies_file ) != NULL )
        {
            if( buffer[0] == ';' )
                continue;

            else if( strcmp( buffer, "[quantity]\n" ) == 0 )
            {
                if( fgets( buffer, 100, enemies_file ) != NULL )
                {
                    strncpy( subbuf, buffer + 1, strlen( buffer ) - 2);
                    subbuf[ strlen( subbuf ) ] = '\0';

                    if( buffer[0] == 'n' )
                        *paths_num = atoi( subbuf );
                }

                paths_array = (Path *)calloc( *paths_num, sizeof( Path ) );
            }

            else if( strcmp( buffer, "[paths]\n" ) == 0 )
            {
                for (int i = 0; i < *paths_num; i++)
                {
                    if( fgets( buffer, 100, enemies_file ) != NULL )
                    {
                        int step_num = 0;
                        PathStep * steps = createPathStepArray( buffer, &step_num );

                        paths_array[i].step_num = step_num;
                        paths_array[i].steps = steps;
                    }
                }
            }
        }

        if( fclose( enemies_file ) == EOF )
            printf("Failed to close file %s !", enemies_file_path );

        return paths_array;
    }
    else
    {
        printf("Failed to open file %s !", enemies_file_path );
        return NULL;
    }
}

void printPath( Path path )
{
    for (int i = 0; i < path.step_num; i++)
    {
        printf("(%lf, %lf) ", path.steps[i].dest_x, path.steps[i].dest_y );
    }
    puts("");
}

void destroyPathArray( Path ** array )
{
    free( (* array)->steps );
    free( * array );
    * array = NULL;
}
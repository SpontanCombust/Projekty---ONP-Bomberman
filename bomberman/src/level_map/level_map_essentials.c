#include "../../headers/level_map.h"

#include "../../headers/sprite_properties.h"
#include "../../headers/tile_matrix_tools.h"
#include <allegro5/allegro.h>
#include <stdio.h>

LevelMap *createLevelMap( char *map_path )
{
    LevelMap *level_map = (LevelMap *)malloc( sizeof( LevelMap ) );

    if( level_map )
    {
        
        FILE *map_file = fopen( map_path, "r" );

        if( map_file == NULL)
        {
            printf("Failed to pen file %s !", map_path );
            return NULL;
        }

        int rows, collumns;
        int **tile_matrix = createLevelTileMatrix( map_file, &rows, &collumns );

        if( fclose( map_file ) == EOF )
        {
            printf("Failed to close file %s !", map_path );
        }


        level_map -> rows = rows;
        level_map -> collumns = collumns;
        level_map -> tile_matrix = tile_matrix;
        level_map -> bmp = al_create_bitmap( collumns * TILE_SIZE, rows * TILE_SIZE );
    } 
    else
    {
        puts("Failed to allcoate level map!");
        return NULL;
    }    

    return level_map;
}

void destroyLevelMap( LevelMap **level_map )
{
    freeMatrix( (*level_map)->tile_matrix , (*level_map)->rows );
    al_destroy_bitmap( (*level_map)->bmp );

    free( *level_map );
    *level_map = NULL;
}
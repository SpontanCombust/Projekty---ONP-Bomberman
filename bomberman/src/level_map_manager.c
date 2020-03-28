#include "../headers/level_utilities.h"

#include <stdlib.h>
#include <stdio.h>

int **createLevelTileMatrix( char *path, int rows, int collumns )
{
    int **tileMatrix = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++)
    {
        tileMatrix[i] = (int *)malloc(collumns * sizeof(int));
    }
    

    FILE *mapFile = fopen( path, "r" );
    
    if( mapFile == NULL ){
        fprintf( stderr, "Failed to open file %s", path );
        return NULL;
    }
    
    char line[100]; 
    int i = 0;
    while( fgets( line, 100, mapFile ) != NULL )
    {
        if( line[0] == ';')
            continue;

        for ( int j = 0; j < collumns; j++ )
        {
            tileMatrix[i][j] = line[j] - '0';
        }

        i++;
        
    }

    if( fclose( mapFile ) == EOF ){
        fprintf( stderr, "Failed to close file %s", path );
        return NULL;
    }

    free( mapFile );

    return tileMatrix;
}

void drawSolidBlock( int x, int y, ALLEGRO_BITMAP *solid_block_sprite )
{
    al_draw_bitmap( solid_block_sprite, pixelFromTile(x), pixelFromTile(y), 0 );
}

void drawBrittleBlock( int x, int y, ALLEGRO_BITMAP *brittle_block_sprite )
{
    al_draw_bitmap( brittle_block_sprite, pixelFromTile(x), pixelFromTile(y), 0 );
}

void generateMapBitmap( int **map, int rows, int collumns, ALLEGRO_BITMAP *map_bitmap, ALLEGRO_BITMAP *solid_block_sprite, ALLEGRO_BITMAP *brittle_block_sprite, ALLEGRO_DISPLAY *display )
{
    al_set_target_bitmap( map_bitmap );

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < collumns; j++)
        {
            if( map[i][j] == 1 )
                drawSolidBlock( j, i, solid_block_sprite );
            else if( map[i][j] == 2 )
                drawBrittleBlock( j, i, brittle_block_sprite );
        }    
    }
    
    al_set_target_bitmap(al_get_backbuffer( display ));   
}

void destroyMap( int **map, int rows )
{
    for (int i = 0; i < rows; i++)
        free( map[i] );

    free( map );
    map = NULL;
}
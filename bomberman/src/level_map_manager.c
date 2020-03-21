#include "../headers/level_utilities.h"

#include <stdlib.h>
#include <stdio.h>

int **createLevelTileMatrix(char *path, int rows, int collumns, int **tileMatrix)
{
    tileMatrix = (int **)malloc(rows * sizeof(int *));
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

    free(mapFile);

    return tileMatrix;
}

void drawSolidBlock(int y, int x, ALLEGRO_BITMAP *solid_block_sprite)
{
    int pixelCoords[2];
    pixelCoordsFromTileCoords(x, y, pixelCoords);
    al_draw_bitmap(solid_block_sprite, pixelCoords[0], pixelCoords[1], 0);
}

void drawBrittleBlock(int y, int x, ALLEGRO_BITMAP *brittle_block_sprite)
{
    int pixelCoords[2];
    pixelCoordsFromTileCoords(x, y, pixelCoords);
    al_draw_bitmap(brittle_block_sprite, pixelCoords[0], pixelCoords[1], 0);
}

void generateMapBitmap(int **map, int rows, int collumns, ALLEGRO_BITMAP *map_bitmap, ALLEGRO_BITMAP *solid_block_sprite, ALLEGRO_BITMAP *brittle_block_sprite, ALLEGRO_DISPLAY *display)
{
    al_set_target_bitmap(map_bitmap);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < collumns; j++)
        {
            if( map[i][j] == 1 )
                drawSolidBlock(i, j, solid_block_sprite);
            else if( map[i][j] == 2 )
                drawBrittleBlock(i, j, brittle_block_sprite);
        }
        
    }

    al_set_target_bitmap(al_get_backbuffer(display));   
}

/*
int main(void){
    int **map = NULL;
    map = createLevelTileMatrix("test_map.txt", 5, 5, map);

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            printf("%d ", map[i][j]);
        }
        puts("");
    }  
}
*/
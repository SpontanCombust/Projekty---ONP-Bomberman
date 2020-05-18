#ifndef LEVEL_MAP_H
#define LEVEL_MAP_H

#include <allegro5/allegro.h>

typedef struct S_LevelMap
{
    int rows, collumns;
    int **tile_matrix;
    ALLEGRO_COLOR bg;
    ALLEGRO_BITMAP *bmp;

} LevelMap;


// ======================== level_map_essentials.c ========================

LevelMap *createLevelMap( char *map_file_path );
void destroyLevelMap( LevelMap **level_map );


// ======================== level_map_gfx.c ========================

void updateLevelMapBitmap( LevelMap *level_map, ALLEGRO_BITMAP *solid_block_sprite, ALLEGRO_BITMAP *brittle_block_sprite, ALLEGRO_DISPLAY *display );

#endif
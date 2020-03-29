#ifndef LEVEL_MAP_H
#define LEVEL_MAP_H

#include <allegro5/allegro.h>

struct SLevelMap
{
    int rows, collumns;
    int **tile_matrix;
    ALLEGRO_BITMAP *bmp;
};
typedef struct SLevelMap LevelMap;

// ======================== level_map_essentials.c ========================
LevelMap *createLevelMap( char *map_path );
void destroyLevelMap( LevelMap **level_map );

// ======================== level_map_gfx.c ========================
void updateLevelMapBitmap( LevelMap *level_map, ALLEGRO_BITMAP *solid_block_sprite, ALLEGRO_BITMAP *brittle_block_sprite, ALLEGRO_DISPLAY *display );

#endif
#ifndef LEVEL_UTILITIES_H
#define LEVEL_UTILITIES_H

#include <allegro5/allegro.h>

enum BlockTypes { EMPTY_BLOCK, SOLID_BLOCK, BRITTLE_BLOCK }; // kolejnosc jest wazna

// ===================================== level_map_manager.c =====================================
int **createLevelTileMatrix( char *path, int *rows, int *collumns );
enum BlockTypes getBlockTypeAtTile( int tile_x, int tile_y, int **map );
void destroyMap( int **map, int rows );

// ======================================= level_map_fx.c ========================================
void drawSolidBlock( int x, int y, ALLEGRO_BITMAP *solid_block_sprite );
void drawBrittleBlock( int x, int y, ALLEGRO_BITMAP *brittle_block_sprite );
void generateMapBitmap( int **map, int rows, int collumns, ALLEGRO_BITMAP *map_bitmap, ALLEGRO_BITMAP *solid_block_sprite, ALLEGRO_BITMAP *brittle_block_sprite, ALLEGRO_DISPLAY *display );

// ===================================== coordinate_translator.c =================================
int pixelFromTile( int t );
int tileFromPixel( int p );

#endif
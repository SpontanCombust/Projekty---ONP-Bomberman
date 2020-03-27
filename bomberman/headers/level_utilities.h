#ifndef LEVEL_UTILITIES_H
#define LEVEL_UTILITIES_H

#include <allegro5/allegro.h>

// ===================================== level_map_manager.c =====================================
int **createLevelTileMatrix( char *path, int rows, int collumns );
void drawSolidBlock( int y, int x, ALLEGRO_BITMAP *solid_block_sprite );
void drawBrittleBlock( int y, int x, ALLEGRO_BITMAP *brittle_block_sprite );
void generateMapBitmap( int **map, int rows, int collumns, ALLEGRO_BITMAP *map_bitmap, ALLEGRO_BITMAP *solid_block_sprite, ALLEGRO_BITMAP *brittle_block_sprite, ALLEGRO_DISPLAY *display );
void freeMap( int **map, int rows );

// ===================================== coordinate_translator.c =================================
int pixelFromTile( int t );
int tileFromPixel( int p );

#endif
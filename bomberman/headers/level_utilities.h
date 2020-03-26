#ifndef LEVEL_UTILITIES_H
#define LEVEL_UTILITIES_H

#include <allegro5/allegro.h>

int **createLevelTileMatrix(char *path, int rows, int collumns, int **tileMatrix);
void drawSolidBlock(int y, int x, ALLEGRO_BITMAP *solid_block_sprite);
void drawBrittleBlock(int y, int x, ALLEGRO_BITMAP *brittle_block_sprite);
void generateMapBitmap(int **map, int rows, int collumns, ALLEGRO_BITMAP *map_bitmap, ALLEGRO_BITMAP *solid_block_sprite, ALLEGRO_BITMAP *brittle_block_sprite, ALLEGRO_DISPLAY *display);

int pixelFromTile(int t);
int tileFromPixel(int p);

#endif
/** @file level_map.h
 * 
 * @brief Plik zawiera definicję typu LevelMapi deklaracje funkcji stworzonych dla tego typu
 * 
 * @author  Przemysław Cedro
 * @date    2020.05.29
*/


#ifndef LEVEL_MAP_H
#define LEVEL_MAP_H

#include <allegro5/allegro.h>

/**
 * @brief Struktura mapy poziomu, LevelMap
 * 
 * Struktura posiada tablicę dwuwymiarową przechowującą informacje o zawartości mapy, wymiary tej mapy, \n
 * kolor tła oraz bitmapę.
 */
typedef struct S_LevelMap
{
    int rows, collumns; /**< ilość rzędów i kolumn tablicy dwuwymiarowej */
    int **tile_matrix; /**< tablica dwuwymiarowa zawartości mapy */
    ALLEGRO_COLOR bg; /**< kolor tła mapy */
    ALLEGRO_BITMAP *bmp; /**< bitmapa mapy */

} LevelMap;


// ======================== level_map_essentials.c ========================

/** @brief Tworzy mapę poziomu */
LevelMap *createLevelMap( char *map_file_path );
/** @brief Zwalnia pamięć z mapy poziomu */
void destroyLevelMap( LevelMap **level_map );


// ======================== level_map_gfx.c ========================

/** @brief Renderuje bitmapę mapy poziomu */
void updateLevelMapBitmap( LevelMap *level_map, ALLEGRO_BITMAP *solid_block_sprite, ALLEGRO_BITMAP *brittle_block_sprite, ALLEGRO_DISPLAY *display );

#endif
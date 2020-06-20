/** @file level_map_rendering.c
 * 
 * @brief Plik zawiera funkcje rysowania mapy poziomu
 * 
 * Zawiera funkcje odpowiedzialne za nakładanie na bitmapę mapy poziomu elementów tej mapy
 * 
 * @author  Przemysław Cedro
 * @date    2020.05.24
*/


#include "../../headers/level_map.h"

#include "../../headers/block_type.h"
#include "../../headers/level_tile_matrix_tools.h"

/** @brief Rysuje na obecną docelową bitmapę blok twardy
 * 
 * @param x                     współrzędna pola mapy w osi X
 * @param y                     współrzędna pola mapy w osi Y
 * @param solid_block_sprite    wskaźnik na bitmapę twardego bloku
*/
void drawSolidBlock( int x, int y, ALLEGRO_BITMAP *solid_block_sprite )
{
    al_draw_bitmap( solid_block_sprite, pixelFromTile(x), pixelFromTile(y), 0 );
}

/** @brief Rysuje na obecną docelową bitmapę blok kruchy
 * 
 * @param x                     współrzędna pola mapy w osi X
 * @param y                     współrzędna pola mapy w osi Y
 * @param brittle_block_sprite  wskaźnik na bitmapę kruchego bloku
*/
void drawBrittleBlock( int x, int y, ALLEGRO_BITMAP *brittle_block_sprite )
{
    al_draw_bitmap( brittle_block_sprite, pixelFromTile(x), pixelFromTile(y), 0 );
}

/** @brief Renderuje bitmapę mapy poziomu
 * 
 * Jako docelową bitmapę rysowania ustawia bitmapę mapy poziomu, czyści ją do koloru tła, a następnie \n
 * nanosi na nią kolejne elementy mapy odczytane z macierzy mapy poziomu. \n
 * Po tym ustawia docelową bitmapę rysowania dla Allegro z powrotem na tylni bufor wyświetlacza. 
 *
 * @param level_map             wskaźnik na mapę poziomu 
 * @param solid_block_sprite    wskaźnik na bitmapę twardego bloku
 * @param brittle_block_sprite  wskaźnik na bitmapę kruchego bloku
 * @param display               wskaźnik na wyświetlacz Allegro
*/
void updateLevelMapBitmap( LevelMap *level_map, ALLEGRO_BITMAP *solid_block_sprite, ALLEGRO_BITMAP *brittle_block_sprite, ALLEGRO_DISPLAY *display )
{
    al_set_target_bitmap( level_map->bmp );
    al_clear_to_color( level_map->bg );

    for (int i = 0; i < level_map->rows; i++)
    {
        for (int j = 0; j < level_map->collumns; j++)
        {
            if( getTileContent( level_map->tile_matrix, j, i ) == SOLID_BLOCK )
                drawSolidBlock( j, i, solid_block_sprite );
            else if( getTileContent( level_map->tile_matrix, j, i ) == BRITTLE_BLOCK )
                drawBrittleBlock( j, i, brittle_block_sprite );
        }    
    }
    
    al_set_target_backbuffer( display );   
}
/** @file bomb_placing.c 
 * 
 * @brief Plik zawiera funkcje uzywane przy stawianiu bomb
 * 
 * Zawiera funkcje stawiania bomby o bardzo podstawowych wartościach oraz do ustawiania jej wartości
 * 
 * @author  Przemysław Cedro
 * @date    2020.05.25
*/


#include "../../headers/bomb.h"

#include "../../headers/sprite_properties.h"
#include "../../headers/level_tile_matrix_tools.h"
#include <allegro5/allegro.h>

/** @brief Tworzy bombę na tej samej pozycji co aktor
 * 
 * Tworzy bombę o tylko ustawionej pozycji, z zerowym czasem eksplozji, zasięgiem i brakiem bitmapy \n
 * na tym samym polu, na którym stoi aktor.
 *
 * @param actor wskaźnik na aktora
 * 
 * @return utworzona bomba
*/
Bomb *createEmptyBombAtActor( Actor *actor )
{
    Bomb *bomb = createBomb( tileFromPixel( actor->x + TILE_SIZE/2 ), tileFromPixel( actor->y + TILE_SIZE/2 ), 0, 0, NULL );
    return bomb;
}

/** @brief Ustawia konkretne cechy bomby
 * 
 * Ustawia czas do wybuchu, zasięg wybuchu i bitmapę bomby.
 *
 * @param bomb          wskaźnik na bombę
 * @param fuse          czas do wybuchu
 * @param blast_range   zasięg wybuchu
 * @param bmp           bitmapa dla bomby
*/
void setBombProperties( Bomb *bomb, int fuse, int blast_range, ALLEGRO_BITMAP *bmp )
{
    bomb -> fuse = fuse;
    bomb -> blast_range = blast_range;
    bomb -> bmp = bmp;
}

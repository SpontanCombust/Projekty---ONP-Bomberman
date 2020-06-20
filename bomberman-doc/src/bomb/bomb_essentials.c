/** @file bomb_essentials.c
 * 
 * @brief Plik zawiera podstawowe funkcje dla bomb.
 * 
 * Zawiera funkcje do tworzenia i zwalniania pamięci ze zmiennych typu Bomb.
 * 
 * @author  Przemysław Cedro
 * @date    2020.05.25
*/


#include "../../headers/bomb.h"

#include <stdlib.h>
#include <stdio.h>

/** @brief Tworzy bombę
 * 
 * Alokuje pamięć na dynamiczną zmienną typu Bomb i ustawia jej pola na wartości podane w parametrach.
 *
 * @param tile_x        pole mapy w osi X, na którym ma być postawiona bomba
 * @param tile_y        pole mapy w osi Y, na którym ma być postawiona bomba
 * @param fuse          czas, w którym bomba ma eksplodować
 * @param blast_range   zasięg eksplozji bomby
 * @param bmp           wskaźnik na bitmapę, która ma być używana przez bombę
 * 
 * @return wskaźnik na bombę o danych cechach
*/
Bomb *createBomb( int tile_x, int tile_y, int fuse, int blast_range, ALLEGRO_BITMAP *bmp )
{
    Bomb *bomb = (Bomb *)malloc( sizeof( Bomb ) );

    if( bomb )
    {
        bomb -> tile_x = tile_x;
        bomb -> tile_y = tile_y;
        bomb -> fuse = fuse;
        bomb -> blast_range = blast_range;
        bomb -> anim_frame = 0;
        bomb -> bmp = bmp;
    }
    else
    {
        puts("Failed to allcate bomb!");
        return NULL;
    }
    
    return bomb;
}

/** @brief Zwalnia pamięć z bomby
 * 
 * Zwalnia pamięć z dynamcznej zmiennej typu Bomb 
 *
 * @param bomb podwójny wskaźnik na bombę
*/
void destroyBomb( Bomb **bomb )
{
    free( *bomb );
    *bomb = NULL;
}
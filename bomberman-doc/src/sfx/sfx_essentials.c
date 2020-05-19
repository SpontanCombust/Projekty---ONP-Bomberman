/** @file sfx_essentials.c
 * 
 * @brief Plik zawiera podstawowe metody dla SFX
 * 
 * Zawiera metody dla specjalnych efektow SFX odpowiadajace za tworzenie i zwalnianie pamieci\n
 * z dynamicznie alokowanych zmiennych typu SFX.
 *
 * @author  Przemyslaw Cedro
 * @date    2020.05.19
*/

#include "../../headers/sfx.h"

#include <stdlib.h>
#include <stdio.h>

/** @brief Tworzy i zwraca SFX o danej zawartosci
 * 
 * Dynamicznie alokuje pamiec na zmienna typu SFX i przypisuje do pol jej struktury wartosci\n
 * podane w parametrach.
 * 
 * @param x             wspolrzedna pikselowa x na mapie poziomu
 * @param y             wspolrzedna pikselowa y na mapie poziomu
 * @param lifespan      czas istnienia SFX
 * @param type          typ SFX
 * @param orientation   orientacja SFX
 * @param bmp           wskaznik na bitmape, jaka ma uzyc SFX
 * 
 * @return wskaznik na utworzone SFX 
*/
SFX *createSFX( float x, float y, int lifespan, SFX_Type type, SFX_Orientation orientation, ALLEGRO_BITMAP *bmp )
{
    SFX *sfx = (SFX *)malloc( sizeof( SFX ) );

    if( sfx )
    {
        sfx -> x = x;
        sfx -> y = y;
        sfx -> lifespan = lifespan;
        sfx -> type = type;
        sfx -> orientation = orientation;
        sfx -> anim_frame = 0;
        sfx -> bmp = bmp;
    }
    else
    {
        puts("Failed to allocate SFX!");
        return NULL;
    }
    
    return sfx;
}

/** @brief Zwalnia pamiec z SFX
 * 
 * Zwalnia pamiec z dynamicznie zalokowanej zmiennej typu SFX.
 * 
 * @param sfx wskaznik na wskaznik na SFX
*/
void destroySFX( SFX **sfx )
{
    free( *sfx );
    *sfx = NULL;
}


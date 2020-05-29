/** @file sfx_essentials.c
 * 
 * @brief Plik zawiera podstawowe metody dla SFX
 * 
 * Zawiera metody dla specjalnych efektów SFX odpowiadajace za tworzenie i zwalnianie pamięci \n
 * z dynamicznie alokowanych zmiennych typu SFX.
 *
 * @author  Przemysław Cedro
 * @date    2020.05.19
*/


#include "../../headers/sfx.h"

#include <stdlib.h>
#include <stdio.h>

/** @brief Tworzy i zwraca SFX o danej zawartosci
 * 
 * Dynamicznie alokuje pamięc na zmienną typu SFX i przypisuje do pól jej struktury wartości \n
 * podane w parametrach.
 * 
 * @param x             wspólrzędna pikselowa x na mapie poziomu
 * @param y             wspólrzędna pikselowa y na mapie poziomu
 * @param lifespan      czas istnienia SFX
 * @param type          typ SFX
 * @param orientation   orientacja SFX
 * @param bmp           wskaźnik na bitmape, jaka ma użyc SFX
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

/** @brief Zwalnia pamięć z SFX
 * 
 * Zwalnia pamięć z dynamicznie alokowanej zmiennej typu SFX.
 * 
 * @param sfx podwójny wskaźnik na SFX
*/
void destroySFX( SFX **sfx )
{
    free( *sfx );
    *sfx = NULL;
}


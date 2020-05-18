/** @file sfx_container_manager.c
 * 
 * Plik zawiera metody do obslugi tablicy wskaznikow na struktury SFX
 * 
 * Plik zawiera metody do obslugi tablicy wskaznikow na struktury SFX\n
 * o wielkosci zdefiniowanej przez SFX_BUDGET w _game_rules.h
 * 
 * @author Przemyslaw Cedro
 * @date 2020.05.19
*/

#include "../../headers/sfx.h"

#include "../../headers/level_tile_matrix_tools.h"
#include "../../headers/_game_rules.h"

/** @brief Zwraca, czy tablica SFX jest pusta
*   
*   Iteruje po tablicy wskaznikow na struktury SFX i porownuje kazdy wskaznik do NULLa
*
*   @param container tablica wskaznikow na struktury SFX
*
*   @return true jesli tablica zawiera same NULLe, false w przeciwnym wypadku
*/
bool isSFXContainerEmpty( SFX * container[] )
{
    for (int i = 0; i < SFX_BUDGET; i++)
        if( container[i] != NULL )
            return false;

    return true;
}

/** @brief Dodaje SFX do tablicy SFX
 * 
 * Jesli dana tablica wskaznikow na struktury SFX nie jest pelna,\n
 * przypisuje pierwszemu napotkanemu nie-NULLowemu elementowi wskaznik\n
 * na dana strukture SFX. W przeciwnym wypadku zwalnia pamiec z danej\n
 * dynamicznie zalokowanej struktury SFX.
 * 
 * @param sfx wskaznik na wskaznik na strukture SFX
 * @param container tablica wskaznikow na struktury SFX
 */
void addSFXToContainer( SFX **sfx, SFX * container[] )
{
    bool valid = false;
    for (int i = 0; i < SFX_BUDGET; i++)
    {
        if ( container[i] == NULL )
        {
            valid = true;
            container[i] = *sfx;
            break;
        }     
    }

    if( !valid )
        destroySFX( sfx );
}

/** @brief Sprawdza, czy na danych koordynatach planszy poziomu znajduje sie SFX danego typu
 * 
 * Jesli tablica wskaznikow na SFX jest niepusta, iteruje po jej elementach\n
 * i sprawdza, czy ktorys ze wskaznikow, ktore przechowuje tablica, wskazuje na\n
 * strukture SFX polozonej na danych koordynatach na planszy poziomu.
 * 
 * @param tile_x wspolrzedna x na planszy poziomu
 * @param tile_y wspolrzedna y na planszy poziomu
 * @param sfx_container tablica wskazikow na struktury SFX
 * @param type typ SFX
 * 
 * @return true jesli na danych koordynatach znajduje sie SFX, false w przeciwnym wypadku
*/
bool isSFXAtTile( int tile_x, int tile_y, SFX *sfx_container[], SFX_Type type )
{
    if( !isSFXContainerEmpty( sfx_container ) )
    {
        for (int i = 0; i < SFX_BUDGET; i++)
        {
            if( sfx_container[i] != NULL && sfx_container[i]->type == type )
            {
                if( tileFromPixel( sfx_container[i]->x ) == tile_x && tileFromPixel( sfx_container[i]->y ) == tile_y )
                    return true;   
            }
        } 
    }
    return false;
}

/** @brief Aktualizuje klatke animacji elementow tablicy SFX
 * 
 * Iteruje po elementach tablicy wskaznikow na struktury SFX\n
 * i aktualizuje stan ich pola anim_frame
 * 
*/
void updateAnimFrameForSFXContainer( SFX *sfx_container[] )
{
    for (int i = 0; i < SFX_BUDGET; i++)
    {
        if( sfx_container[i] != NULL )
            updateAnimFrameForSFX( sfx_container[i] );
    }
}
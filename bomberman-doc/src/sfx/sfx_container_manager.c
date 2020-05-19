/** @file sfx_container_manager.c
 * 
 * @brief Plik zawiera metody do obslugi tablicy wskaznikow na zmienne typu SFX
 * 
 * Plik zawiera metody do obslugi tablicy wskaznikow na zmienne typu SFX o wielkosci zdefiniowanej\n
 * przez SFX_BUDGET w _game_rules.h.
 * 
 * @author  Przemyslaw Cedro
 * @date    2020.05.19
*/

#include "../../headers/sfx.h"

#include "../../headers/level_tile_matrix_tools.h"
#include "../../headers/_game_rules.h"

/** @brief Zwraca, czy tablica SFX jest pusta
*   
*   Iteruje po tablicy wskaznikow na zmienne typu SFX i porownuje kazdy wskaznik do NULLa
*
*   @param container tablica wskaznikow na SFX
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
 * Jesli dana tablica wskaznikow na zmienne typu SFX nie jest pelna, przypisuje pierwszemu\n
 * napotkanemu nie-NULLowemu elementowi wskaznik na dana zmienna typu SFX. W przeciwnym wypadku\n
 * zwalnia pamiec z danej dynamicznie zalokowanej zmiennej typu SFX.
 * 
 * @param sfx       wskaznik na wskaznik na SFX
 * @param container tablica wskaznikow na SFX
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

/** @brief Sprawdza, czy na danych koordynatach mapy poziomu znajduje sie SFX danego typu
 * 
 * Jesli tablica wskaznikow na SFX jest niepusta, iteruje po jej elementach\n
 * i sprawdza, czy ktorys ze wskaznikow o wartości nie-NULLowej, ktore przechowuje tablica,\n
 * wskazuje na zmienna typu SFX o podanym typie, ktorej pola wspolrzednych wskazuja na podana pozycje
 * 
 * @param tile_x        wspolrzedna kafelkowa x na mapie poziomu
 * @param tile_y        wspolrzedna kafelkowa y na mapie poziomu
 * @param sfx_container tablica wskazikow na SFX
 * @param type          typ SFX
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
 * Iteruje po elementach tablicy wskaznikow na zmienne typu SFX i aktualizuje stan ich pola anim_frame.
 * 
 * @param sfx_container tablica wskaznikow na SFX
*/
void updateAnimFrameForSFXContainer( SFX *sfx_container[] )
{
    for (int i = 0; i < SFX_BUDGET; i++)
    {
        if( sfx_container[i] != NULL )
            updateAnimFrameForSFX( sfx_container[i] );
    }
}
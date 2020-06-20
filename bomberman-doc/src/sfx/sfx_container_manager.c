/** @file sfx_container_manager.c
 * 
 * @brief Plik zawiera metody do obsługi tablicy wskaźnikow na zmienne typu SFX
 * 
 * Plik zawiera metody do obsługi tablicy wskaźnikow na zmienne typu SFX o wielkosci zdefiniowanej \n
 * przez SFX_BUDGET w _game_rules.h.
 * 
 * @author  Przemysław Cedro
 * @date    2020.05.19
*/


#include "../../headers/sfx.h"

#include "../../headers/level_tile_matrix_tools.h"
#include "../../headers/_game_rules.h"

/** @brief Zwraca, czy tablica SFX jest pusta
*   
*   Iteruje po tablicy wskaźnikow na zmienne typu SFX i porównuje każdy wskaźnik do NULLa
*
*   @param container tablica wskaźnikow na SFX
*
*   @return true jeśli tablica zawiera same NULLe, false w przeciwnym wypadku
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
 * Jesli dana tablica wskaźnikow na zmienne typu SFX nie jest pełna, przypisuje pierwszemu \n
 * napotkanemu nie-NULLowemu elementowi wskaźnik na daną zmienną typu SFX. W przeciwnym wypadku \n
 * zwalnia pamięć z danej dynamicznie alokowanej zmiennej typu SFX.
 * 
 * @param sfx       wskaźnik na wskaźnik na SFX
 * @param container tablica wskaźnikow na SFX
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

/** @brief Sprawdza, czy na danych koordynatach mapy poziomu znajduje się SFX danego typu
 * 
 * Jeśli tablica wskaźników na SFX jest niepusta, iteruje po jej elementach \n
 * i sprawdza, czy któryś ze wskaźnikow o wartości nie-NULLowej, które przechowuje tablica, \n
 * wskazuje na zmienną typu SFX o podanym typie, której pola wspólrzędnych wskazują na podaną pozycję.
 * 
 * @param tile_x        współrzędna pola mapy w osi x na mapie poziomu
 * @param tile_y        współrzędna pola mapy w osi y na mapie poziomu
 * @param sfx_container tablica wskaźników na SFX
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

/** @brief Aktualizuje klatkę animacji elementów tablicy SFX
 * 
 * Iteruje po elementach tablicy wskaźników na zmienne typu SFX i aktualizuje stan ich pola anim_frame.
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
/** @file sfx_handler.c
 * 
 * @brief Plik zawiera metody obsługi specjalnych efektow SFX
 * 
 * Zawiera metody dla specjalnych efektow SFX zmieniajace stan pól struktury typu SFX
 * @author  Przemysław Cedro
 * @date    2020.05.19
*/


#include "../../headers/sfx.h"

#include "../../headers/_game_rules.h"

/** @brief Aktualizuje klatkę animacji dla SFX
 * 
 * Aktualizuje stan pola anim_frame zmiennej typu SFX w zależnosci od pola typu tego SFX.
 * 
 * @param sfx wskaźnik na SFX
*/
void updateAnimFrameForSFX( SFX *sfx )
{
    sfx -> anim_frame++;
    if( sfx->type == EXPLOSION ) {
        if( sfx->anim_frame > EXPLOSION_ANIM_FRAMES - 1 )
            sfx -> anim_frame = 0;
    }
}

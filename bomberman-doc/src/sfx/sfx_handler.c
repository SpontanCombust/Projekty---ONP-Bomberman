/** @file sfx_handler.c
 * 
 * @brief Plik zawiera metody obslugi specjalnych efektow SFX
 * 
 * Zawiera metody dla specjalnych efektow SFX zmieniajace stan pol struktury typu SFX
 * @author  Przemyslaw Cedro
 * @date    2020.05.19
*/

#include "../../headers/sfx.h"

#include "../../headers/_game_rules.h"

/** @brief Aktualizuje klatke animacji dla SFX
 * 
 * Aktualizuje stan pola anim_frame zmiennej typu SFX w zaleznosci pola typu tego SFX
 * 
 * @param sfx wskaznik na SFX
*/
void updateAnimFrameForSFX( SFX *sfx )
{
    sfx -> anim_frame++;
    if( sfx->type == EXPLOSION ) {
        if( sfx->anim_frame > EXPLOSION_ANIM_FRAMES - 1 )
            sfx -> anim_frame = 0;
    }
}

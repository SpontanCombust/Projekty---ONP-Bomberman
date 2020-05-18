#include "../../headers/sfx.h"

#include "../../headers/_game_rules.h"

void updateAnimFrameForSFX( SFX *sfx )
{
    sfx -> anim_frame++;
    if( sfx->type == EXPLOSION ) {
        if( sfx->anim_frame > EXPLOSION_ANIM_FRAMES - 1 )
            sfx -> anim_frame = 0;
    }
}

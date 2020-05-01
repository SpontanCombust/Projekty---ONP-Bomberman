#include "../../headers/actor.h"

#include "../../headers/_game_rules.h"
#include "../../headers/logic.h"

void applyCollisionToActor( Actor *actor, float cx, float cy, float cw, float ch )
{
    actor -> enabled_collision = true;
    actor -> cx = cx;
    actor -> cy = cy;
    actor -> cw = cw;
    actor -> ch = ch;
}

void applyCollisionToActorArray( Actor * *actors, int actor_num, float cx, float cy, float cw, float ch )
{
    for (int i = 0; i < actor_num; i++)
        applyCollisionToActor( actors[i], cx, cy, cw, ch );
}

bool isActorAlive( Actor *actor ) {
    return actor->lives > 0;
}

void damageActor( Actor *actor ) {
    actor -> lives--;
}

void updateAnimFrameForActor( Actor *actor )
{
    if( !isActorMoving( actor ) )
        actor -> anim_frame = 0;
    else
    {
        actor -> anim_frame++;
        if( actor->anim_frame > ACTOR_ANIM_FRAMES - 1 )
            actor->anim_frame = 0;
    }
}
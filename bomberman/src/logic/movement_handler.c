#include "../../headers/logic.h"

#include "../../headers/_game_rules.h"
#include <allegro5/allegro.h>

void updateVelocityX( Actor *actor, bool vx0, bool vx1 )
{
    actor -> vx[0] = vx0;
    actor -> vx[1] = vx1;
}

void updateVelocityY( Actor *actor, bool vy0, bool vy1 )
{
    actor -> vy[0] = vy0;
    actor -> vy[1] = vy1;
}

void resetVelocity( Actor *actor )
{
    actor -> vx[0] = false;
    actor -> vx[1] = false;
    actor -> vy[0] = false;
    actor -> vy[1] = false;
}

bool isActorMoving( Actor *actor ) {
    return actor->vx[0] || actor->vx[1] || actor->vy[0] || actor->vy[1];
}

void resolveDirection( Actor *actor )
{
    if( actor->vy[0] & !( actor->vx[0] ) & !( actor->vx[1] ) )
        actor -> dir = UP;
    else if( actor->vy[1] & !( actor->vx[0] ) & !( actor->vx[1] ) )
        actor -> dir = DOWN;        
    else if( actor->vx[0] & !( actor->vy[0] ) & !( actor->vy[1] ) )
        actor -> dir = LEFT;
    else if( actor->vx[1] & !( actor->vy[0] ) & !( actor->vy[1] ) )
        actor -> dir = RIGHT;
}

void updatePositionX( Actor *actor )
{
    actor -> x += actor->speed * ( -( actor->vx[0] ) + actor->vx[1] );
}

void updatePositionY( Actor *actor )
{   
    actor -> y += actor->speed * ( -( actor->vy[0] ) + actor->vy[1] ); 
}
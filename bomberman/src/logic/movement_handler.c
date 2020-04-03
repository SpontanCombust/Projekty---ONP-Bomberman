#include "../../headers/logic.h"

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

void handleMovementInputKeyDown( char eventKeyboardKeycode, Actor *actor, bool *done )
{
    switch (eventKeyboardKeycode)
    {
        case ALLEGRO_KEY_UP:
            updateVelocityY( actor, true, actor->vy[1] );
            break;
        case ALLEGRO_KEY_DOWN:
            updateVelocityY( actor, actor->vy[0], true );
            break;
        case ALLEGRO_KEY_LEFT:
            updateVelocityX( actor, true, actor->vx[1] );
            break;
        case ALLEGRO_KEY_RIGHT:
            updateVelocityX( actor, actor->vx[0], true );
            break;
        case ALLEGRO_KEY_ESCAPE:
            *done = true;
            break;
    }
}

void handleMovementInputKeyUp( char eventKeyboardKeycode, Actor *actor ) 
{
    switch (eventKeyboardKeycode)
    {
        case ALLEGRO_KEY_UP:
            updateVelocityY( actor, false, actor->vy[1] );
            break;
        case ALLEGRO_KEY_DOWN:
            updateVelocityY( actor, actor->vy[0], false );
            break;
        case ALLEGRO_KEY_LEFT:
            updateVelocityX( actor, false, actor->vx[1] );
            break;
        case ALLEGRO_KEY_RIGHT:
            updateVelocityX( actor, actor->vx[0], false );
            break;
    }
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
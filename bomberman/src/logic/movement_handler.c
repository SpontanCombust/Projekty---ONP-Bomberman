#include "../../headers/logic.h"

#include <allegro5/allegro.h>

void handleMovementInputKeyDown( char eventKeyboardKeycode, Actor *actor, bool *done )
{
    switch (eventKeyboardKeycode)
    {
        case ALLEGRO_KEY_UP:
            actor -> vy[0] = true;
            break;
        case ALLEGRO_KEY_DOWN:
            actor -> vy[1] = true;
            break;
        case ALLEGRO_KEY_LEFT:
            actor -> vx[0] = true;
            break;
        case ALLEGRO_KEY_RIGHT:
            actor -> vx[1] = true;
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
            actor -> vy[0] = false;
            break;
        case ALLEGRO_KEY_DOWN:
            actor -> vy[1] = false;
            break;
        case ALLEGRO_KEY_LEFT:
            actor -> vx[0] = false;
            break;
        case ALLEGRO_KEY_RIGHT:
            actor -> vx[1] = false;
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
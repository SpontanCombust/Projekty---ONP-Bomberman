#include "logic_handlers.h"
#include <allegro5/allegro.h>


void handleEventKeyDown(char eventKeyboardKeycode, bool vx[2], bool vy[2], bool *done)
{
    switch (eventKeyboardKeycode)
    {
        case ALLEGRO_KEY_UP:
            vy[0] = true;
            break;
        case ALLEGRO_KEY_DOWN:
            vy[1] = true;
            break;
        case ALLEGRO_KEY_LEFT:
            vx[0] = true;
            break;
        case ALLEGRO_KEY_RIGHT:
            vx[1] = true;
            break;
        case ALLEGRO_KEY_ESCAPE:
            *done = true;
            break;
    }
}

void handleEventKeyUp(char eventKeyboardKeycode, bool vx[2], bool vy[2])
{
    switch (eventKeyboardKeycode)
    {
        case ALLEGRO_KEY_UP:
            vy[0] = false;
            break;
        case ALLEGRO_KEY_DOWN:
            vy[1] = false;
            break;
        case ALLEGRO_KEY_LEFT:
            vx[0] = false;
            break;
        case ALLEGRO_KEY_RIGHT:
            vx[1] = false;
            break;
    }
}

void resolveDirection( enum Direction *dir, bool vx[2], bool vy[2] )
{
    if( vy[0] & !vx[0] & !vx[1] )
        *dir = UP;
    else if( vy[1] & !vx[0] & !vx[1] )
        *dir = DOWN;        
    else if( vx[0] & !vy[0] & !vy[1])
        *dir = LEFT;
    else if( vx[1] & !vy[0] & !vy[1] )
        *dir = RIGHT;
}
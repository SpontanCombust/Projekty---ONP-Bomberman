#include "../headers/actor.h"

#include <stdlib.h>
#include <stdio.h>

Actor *createActor( int x, int y, int speed, enum Direction dir, ALLEGRO_BITMAP *bmp )
{
    Actor *actor = (Actor *)malloc( sizeof( Actor ) );

    if( actor ){
        actor -> x = x;
        actor -> y = y;
        actor -> vx[0] = false;
        actor -> vx[1] = false;
        actor -> vy[0] = false;
        actor -> vy[1] = false;
        actor -> speed = speed;
        actor -> dir = dir;
        actor -> bmp = bmp;
    } 
    else
    {
        puts("Failed to allocate actor!");
        return NULL;
    }
    
    
    return actor;
}

void destroyActor( Actor **actor )
{
    free( *actor );
    *actor = NULL;
}
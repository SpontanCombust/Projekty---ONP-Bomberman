#include "../headers/actor.h"

#include <stdlib.h>
#include <stdio.h>

Actor *createActor( float x, float y, float speed, enum Direction dir, ALLEGRO_BITMAP *bmp )
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
        actor -> alive = true;
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

void destroyActors( Actor ** enemies, int enemy_num )
{
    for (int i = 0; i < enemy_num; i++)
        destroyActor( &enemies[i] );
}
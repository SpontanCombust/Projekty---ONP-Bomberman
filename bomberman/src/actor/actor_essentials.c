#include "../headers/actor.h"

#include <stdlib.h>
#include <stdio.h>

Actor *createActor( float x, float y, float speed, ALLEGRO_BITMAP *bmp )
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
        actor -> cx = 0;
        actor -> cy = 0;
        actor -> cw = 0;
        actor -> ch = 0;
        actor -> enabled_collision = false;
        actor -> lives = 1;
        actor -> dir = DOWN;
        actor -> anim_frame = 0;
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

void destroyActorArray( Actor ** *actors, int actor_num )
{
    for (int i = 0; i < actor_num; i++)
        destroyActor( &(*actors)[i] );
    free( *actors );
    *actors = NULL;
}
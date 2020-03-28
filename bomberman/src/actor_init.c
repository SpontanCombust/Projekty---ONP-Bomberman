#include "../headers/actor.h"

Actor *createActor( int x, int y, int speed, enum Direction dir, ALLEGRO_BITMAP *bmp )
{
    Actor *actor = (Actor *)malloc( sizeof( Actor ) );

    actor -> x = x;
    actor -> y = y;
    actor -> vx[0] = false;
    actor -> vx[1] = false;
    actor -> vy[0] = false;
    actor -> vy[1] = false;
    actor -> speed = speed;
    actor -> dir = dir;
    actor -> bmp = bmp;

    return actor;
}

void destroyActor( Actor *actor )
{
    free( actor );
    actor = NULL;
}
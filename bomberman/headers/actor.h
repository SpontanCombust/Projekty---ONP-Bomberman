#ifndef ACTOR_H
#define ACTOR_H

#include "direction.h"
#include <allegro5/allegro.h>
#include <stdbool.h>

/*
         | vy[0]
         |
vx[0]----0---> vx[1]
         |
         \/ vy[1]
*/

typedef struct S_Actor
{
    float x, y;
    bool vx[2], vy[2];
    float speed;
    bool alive;
    enum Direction dir;
    ALLEGRO_BITMAP *bmp;
    
} Actor; 


// ======================== actor_essentials.c =========================

Actor *createActor( float x, float y, float speed, enum Direction dir, ALLEGRO_BITMAP *bmp );
void destroyActor( Actor **actor );
void destroyActorArray( Actor ** *enemies, int enemy_num );

#endif
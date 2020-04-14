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
    float cx, cy, cw, ch;
    bool enabled_collision;
    bool alive;
    enum Direction dir;
    ALLEGRO_BITMAP *bmp;
    
} Actor; 


// ======================== actor_essentials.c =========================

Actor *createActor( float x, float y, float speed, ALLEGRO_BITMAP *bmp );
void applyCollisionToActor( Actor *actor, float cx, float cy, float cw, float ch );
void applyCollisionToActorArray( Actor * *actors, int actor_num, float cx, float cy, float cw, float ch );
void destroyActor( Actor **actor );
void destroyActorArray( Actor ** *actors, int actors_num );

#endif
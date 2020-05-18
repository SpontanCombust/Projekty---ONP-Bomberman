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
    int lives;
    Direction dir;
    int anim_frame;
    ALLEGRO_BITMAP *bmp;
    
} Actor; 


// ======================== actor_essentials.c =========================

Actor *createActor( float x, float y, float speed, ALLEGRO_BITMAP *bmp );
void destroyActor( Actor **actor );
void destroyActorArray( Actor ** *actors, int actors_num );


// ======================== actor_handling.c ===========================

void applyCollisionToActor( Actor *actor, float cx, float cy, float cw, float ch );
void applyCollisionToActorArray( Actor * *actors, int actor_num, float cx, float cy, float cw, float ch );
void damageActor( Actor *actor );
bool isActorAlive( Actor *actor );
void updateAnimFrameForActor( Actor *actor );

#endif
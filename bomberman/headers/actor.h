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
    double x, y;
    bool vx[2], vy[2];
    double speed;
    enum Direction dir;
    ALLEGRO_BITMAP *bmp;
    
} Actor; 


// ======================== actor_essentials.c =========================

Actor *createActor( double x, double y, double speed, enum Direction dir, ALLEGRO_BITMAP *bmp );
void destroyActor( Actor **actor );

#endif
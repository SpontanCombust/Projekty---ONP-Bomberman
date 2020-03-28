#ifndef CHARACTER_H
#define CHARACTER_H

#include "direction.h"

#include <allegro5/allegro.h>

/*
         | vy[0]
         |
vx[0]----0---> vx[1]
         |
         \/ vy[1]
*/

struct SActor {
    int x, y;
    bool vx[2], vy[2];
    int speed;
    enum Direction dir;
    ALLEGRO_BITMAP *bmp;
};
typedef struct SActor Actor; 

// ======================== actor_init.c =========================
Actor *createActor( int x, int y, int speed, enum Direction dir, ALLEGRO_BITMAP *bmp );
void destroyActor( Actor *actor );

#endif
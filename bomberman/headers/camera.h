#ifndef CAMERA_H
#define CAMERA_H

#include "actor.h"
#include "level_map.h"
#include <allegro5/allegro.h>

typedef struct
{
    Actor *target;
    float x, y;
    float max_x, max_y;
    ALLEGRO_TRANSFORM transform;

} Camera;

typedef struct
{
    Actor *pivot;
    Actor *actor1, *actor2;

} CentralPivotModule;


// =================== camera_essentials.c ====================

Camera *createCamera( Actor *target, LevelMap *lvl_map );
void destroyCamera( Camera **camera );


// =================== camera_handler.c =======================

void updateCamera( Camera *camera );
void disableCamera( Camera *camera );


// =================== central_pivot.c =======================

void applyActorsToPivot( CentralPivotModule *cpm, Actor *actor1, Actor *actor2 );
void updatePivot( CentralPivotModule *cpm );

#endif
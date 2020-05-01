#ifndef CAMERA_H
#define CAMERA_H

#include "actor.h"
#include "level_map.h"
#include <allegro5/allegro.h>

typedef struct S_Camera
{
    Actor *target;
    float x, y;
    float max_x, max_y;
    ALLEGRO_TRANSFORM transform;

} Camera;

typedef struct S_MultiPlayerCameraModule
{
    Actor *target;
    Actor *actor1, *actor2;

} MultiPlayerCameraModule;


// =================== camera_essentials.c ====================

Camera *createCamera( Actor *target, LevelMap *lvl_map );
void destroyCamera( Camera **camera );


// =================== camera_handler.c =======================

void updateCamera( Camera *camera );
void disableCamera( Camera *camera );


// =================== central_pivot.c =======================

void applyActorsToCameraModule( MultiPlayerCameraModule *mpcm, Actor *actor1, Actor *actor2 );
void updateCameraModule( MultiPlayerCameraModule *mpcm );

#endif
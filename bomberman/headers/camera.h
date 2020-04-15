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


// =================== camera_essentials.c ====================

Camera *createCamera( Actor *target, LevelMap *lvl_map );
void destroyCamera( Camera **camera );


// =================== camera_handler.c =======================

void updateCamera( Camera *camera );
void disableCamera( Camera *camera );

#endif
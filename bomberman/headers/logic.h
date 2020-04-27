#ifndef LOGIC_HANDLERS_H
#define LOGIC_HANDLERS_H

#include "direction.h"
#include "actor.h"
#include "level_map.h"
#include <stdbool.h>

// ================================== movement_handler.c ==================================

void updateVelocityX( Actor *actor, bool vx0, bool vx1 );
void updateVelocityY( Actor *actor, bool vy0, bool vy1 );
void resetVelocity( Actor *actor );
void resolveDirection( Actor *actor );
void updatePositionX( Actor *actor );
void updatePositionY( Actor *actor );


// ================================== collision_handler.c ==================================

bool isOutOfBounds( Actor *actor, LevelMap *level_map, enum Direction *cdir );
void handleOutOfBounds( Actor *actor, LevelMap *level_map, enum Direction cdir );
bool isTerrainCollisionX( Actor *actor, LevelMap *level_map, enum Direction *cdir );
bool isTerrainCollisionY( Actor *actor, LevelMap *level_map, enum Direction *cdir );
void handleTerrainCollision( Actor *actor, enum Direction cdir );
bool isActorCollision( Actor *actor1, Actor *actor2 );

#endif

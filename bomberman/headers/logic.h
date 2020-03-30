#ifndef LOGIC_HANDLERS_H
#define LOGIC_HANDLERS_H

#include "direction.h"
#include "actor.h"
#include "level_map.h"
#include <stdbool.h>

// ================================== movement_handler.c ==================================
void handleMovementInputKeyDown( char eventKeyboardKeycode, Actor *actor, bool *done );
void handleMovementInputKeyUp( char eventKeyboardKeycode, Actor *actor );
void resolveDirection( Actor *actor );
void updatePositionX( Actor *actor );
void updatePositionY( Actor *actor );

// ================================== collision_handler.c ==================================
bool isOutOfBounds( Actor *actor, LevelMap *level_map, enum Direction *cdir, int cx, int cy, int cw, int ch );
void handleOutOfBounds( Actor *actor, LevelMap *level_map, enum Direction cdir, int cx, int cy, int cw, int ch );
bool isTerrainCollisionX( Actor *actor, LevelMap *level_map, enum Direction *cdir, int cx, int cy, int cw, int ch );
bool isTerrainCollisionY( Actor *actor, LevelMap *level_map, enum Direction *cdir, int cx, int cy, int cw, int ch );
void handleTerrainCollision( Actor *actor, enum Direction cdir, int cx, int cy, int cw, int ch );

#endif

#ifndef LOGIC_HANDLERS_H
#define LOGIC_HANDLERS_H

#include "direction.h"
#include "entity.h"

#include <allegro5/allegro.h>
#include <stdbool.h>

// ================================== movement_handler.c ==================================
void handleEventKeyDown( char eventKeyboardKeycode, bool vx[2], bool vy[2], bool *done );
void handleEventKeyUp( char eventKeyboardKeycode, bool vx[2], bool vy[2] );
void resolveDirection( enum Direction *dir, bool vx[2], bool vy[2] );
void updateMovementX( Entity *player, bool vx[2], int speed );
void updateMovementY( Entity *player, bool vy[2], int speed );

// ================================== collision_handler.c ==================================
bool isOutOfBounds( Entity *player, enum Direction *cdir, int screen_w, int screen_h, int cx, int cy, int cw, int ch );
void handleOutOfBounds( Entity *player, enum Direction cdir, int screen_w, int screen_h, int cx, int cy, int cw, int ch );
bool isTerrainCollisionX( Entity *player, enum Direction *cdir, int **map, int cx, int cy, int cw, int ch );
bool isTerrainCollisionY( Entity *player, enum Direction *cdir, int **map, int cx, int cy, int cw, int ch );
void handleTerrainCollision( Entity *player, enum Direction cdir, int **map, int cx, int cy, int cw, int ch );

#endif

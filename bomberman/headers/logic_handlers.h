#ifndef LOGIC_HANDLERS_H
#define LOGIC_HANDLERS_H

#include "direction.h"
#include "entity.h"
#include "level_utilities.h"

#include <allegro5/allegro.h>
#include <stdbool.h>

void handleEventKeyDown( char eventKeyboardKeycode, bool vx[2], bool vy[2], bool *done );
void handleEventKeyUp( char eventKeyboardKeycode, bool vx[2], bool vy[2] );
void resolveDirection( enum Direction *dir, bool vx[2], bool vy[2] );
void updateMovementX( Entity *player, bool vx[2], int speed );
void updateMovementY( Entity *player, bool vy[2], int speed );

bool isCollision(Entity *player, int **map, int screen_w, int screen_h, int cx, int cy, int cw, int ch);
bool isOutOfBounds(Entity *player, int screen_w, int screen_h, int cx, int cy, int cw, int ch);
bool isTerrainCollision(Entity *player, int **map, int cx, int cy, int cw, int ch);

#endif

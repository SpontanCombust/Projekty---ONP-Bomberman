#ifndef LOGIC_HANDLERS_H
#define LOGIC_HANDLERS_H

#include "entity.h"

#include <allegro5/allegro.h>
#include <stdbool.h>

enum Direction { DOWN, UP, LEFT, RIGHT };

void handleEventKeyDown( char eventKeyboardKeycode, bool vx[2], bool vy[2], bool *done );
void handleEventKeyUp( char eventKeyboardKeycode, bool vx[2], bool vy[2] );
void resolveDirection( enum Direction *dir, bool vx[2], bool vy[2] );
void updateMovement( Entity *player, bool vx[2], bool vy[2], int speed);

bool isBlockCollision(int **map, Entity *player);
void correctPosition(Entity *player, bool vx[2], bool vy[2]);
#endif

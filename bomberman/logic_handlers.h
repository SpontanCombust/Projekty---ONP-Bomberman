#ifndef LOGIC_HANDLERS_H
#define LOGIC_HANDLERS_H

#include <stdbool.h>

enum Direction { DOWN, UP, LEFT, RIGHT };

void handleEventKeyDown( char eventKeyboardKeycode, bool vx[2], bool vy[2], bool *done );
void handleEventKeyUp( char eventKeyboardKeycode, bool vx[2], bool vy[2] );
void resolveDirection( enum Direction *dir, bool vx[2], bool vy[2] );

#endif

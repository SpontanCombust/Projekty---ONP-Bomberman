#ifndef PLAYER_INPUT_H
#define PLAYER_INPUT_H

#include "actor.h"
#include "bomb.h"

// ==================== input_handler.c ====================

void handleInputKeyDown( char keyboard_keycode, Actor *player, int bomb_blast_range, ALLEGRO_BITMAP *bomb_bmp, Bomb *bomb_container[], bool *done );
void handleInputKeyUp( char keyboard_keycode, Actor *player );

#endif
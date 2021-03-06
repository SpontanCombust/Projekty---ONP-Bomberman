#ifndef PLAYER_INPUT_H
#define PLAYER_INPUT_H

#include "actor.h"
#include "bomb.h"
#include "menus.h"

typedef enum E_InputScheme { STANDARD, ALTERNATIVE } InputScheme;

// ==================== input_handler.c ====================

void handleGameInputKeyDown( char keyboard_keycode, InputScheme is, Actor *player, int bomb_blast_range, ALLEGRO_BITMAP *bomb_bmp, Bomb *bomb_container[], GameState *gs );
void handleGameInputKeyUp( char keyboard_keycode, InputScheme is, Actor *player );
void handleMenuInputKeyDown( char keyboard_keycode, Menu *menu, GameState *gs );

#endif
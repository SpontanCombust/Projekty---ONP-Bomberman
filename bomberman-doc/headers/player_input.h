/** @file player_input.h 
 * 
 * @brief Plik zawiera enum typu sterowania i deklaracje funkcji obsługi wejść z klawiatury
 * 
 * @author  Przemysław Cedro
 * @date    2020.05.29
*/


#ifndef PLAYER_INPUT_H
#define PLAYER_INPUT_H

#include "actor.h"
#include "bomb.h"
#include "menus.h"

/** Enum informujące o domyślnym lub alternatywnym trybie sterowania */
typedef enum E_InputScheme { STANDARD, ALTERNATIVE } InputScheme;

// ==================== input_handler.c ====================

/** @brief Obsługuje naciśnięcie danego klawisza w trakcie rozgrywki */
void handleGameInputKeyDown( char keyboard_keycode, InputScheme is, Actor *player, int bomb_blast_range, ALLEGRO_BITMAP *bomb_bmp, Bomb *bomb_container[], GameState *gs );
/** @brief Obsługuje zwolnienie danego klawisza w trakcie rozgrywki */
void handleGameInputKeyUp( char keyboard_keycode, InputScheme is, Actor *player );
/** @brief Obsługuje naciśnięcie danego klawisza w trakcie pobytu w menu */
void handleMenuInputKeyDown( char keyboard_keycode, Menu *menu, GameState *gs );

#endif
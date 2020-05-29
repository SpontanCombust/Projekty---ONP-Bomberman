/** @file 
 * 
 * @brief Plik zawiera deklaracje funkcji rysowania elementów gry na ekran
 * 
 * @author  Przemysław Cedro
 * @date    2020.05.29
*/


#ifndef RENDERING_H
#define RENDERING_H

#include "_game_rules.h"
#include "sprite_properties.h"
#include "bomb.h"
#include "sfx.h"
#include "actor.h"
#include "ai.h"
#include "level_map.h"
#include "menus.h"
#include <allegro5/allegro5.h>


// ======================== rendering.c =======================

/** @brief Rysuje bomby */
void drawBombs( Bomb *bomb_container[] );
/** @brief Rysuje specjalne efekty SFX */
void drawSFX( SFX *sfx_container[] );
/** @brief Rysuje aktora */
void drawActor( Actor *actor );
/** @brief Rysuje mapę poziomu */
void drawLevelMap( LevelMap *level_map );
/** @brief Rysuje menu */
void drawMenu( Menu *menu );

#endif
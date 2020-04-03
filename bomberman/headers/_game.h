#ifndef GAME_H
#define GAME_H

#include "actor.h"
#include "ai.h"
#include "bomb.h"
#include "direction.h"
#include "level_map.h"
#include "logic.h"
#include "sfx.h"
#include "sprite_properties.h"
#include "level_tile_matrix_tools.h"

#include <stdio.h>
#include <stdbool.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#define SCREEN_HEIGHT 352
#define SCREEN_WIDTH 864

#define FPS 60.0
#define SECOND_TIMER 1.0

#define BOMB_BUDGET 5
#define SFX_BUDGET 50

#define PLAYER_SPEED 1.3


// =========================================================== game.c =======================================================================

void updateContainers( Bomb * bomb_container[], SFX * sfx_container[], LevelMap *level_map, ALLEGRO_BITMAP *explosion_bmp, bool *map_update );
void drawBombs( Bomb * bomb_container[] );
void drawSFX( SFX * sfx_container[] );
void updatePlayerPosition( Actor *player, LevelMap *level_map );
void updateEnemyPosition( AIModule ** modules, int enemy_num );
void drawPlayer( Actor *player );
void drawEnemies( AIModule ** enemies, int enemy_num );
void updateGFX( Actor *player, AIModule ** modules, int enemy_num, LevelMap *level_map, Bomb * bomb_container[], SFX * sfx_container[] );
void destroyEnemies( Actor ** enemies, int enemy_num );
void destroyAIModules( AIModule ** modules, int module_num );

#endif
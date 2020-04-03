#ifndef GAME_H
#define GAME_H

#include "_game_rules.h"
#include "actor.h"
#include "bomb.h"
#include "direction.h"
#include "level.h"
#include "logic.h"
#include "sfx.h"
#include "sprite_properties.h"
#include "level_tile_matrix_tools.h"
#include "level.h"

#include <stdio.h>
#include <stdbool.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>


// =========================================================== game.c =======================================================================

void updateContainers( Bomb * bomb_container[], SFX * sfx_container[], LevelMap *level_map, Actor **enemies, int enemy_num, ALLEGRO_BITMAP *explosion_bmp, bool *map_update );
void drawBombs( Bomb * bomb_container[] );
void drawSFX( SFX * sfx_container[] );
void updatePlayerPosition( Actor *player, LevelMap *level_map );
void updateEnemyPosition( AIModule ** modules, int enemy_num );
void drawPlayer( Actor *player );
void drawEnemies( AIModule ** enemies, int enemy_num );
void updateGFX( Actor *player, AIModule ** modules, int enemy_num, LevelMap *level_map, Bomb * bomb_container[], SFX * sfx_container[] );
bool areAllEnemiesDead( Actor ** enemies, int enemy_num );


#endif
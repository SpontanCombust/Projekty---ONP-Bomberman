#ifndef GAME_H
#define GAME_H

#include "_game_rules.h"
#include "_game_state.h"
#include "actor.h"
#include "bomb.h"
#include "camera.h"
#include "direction.h"
#include "level.h"
#include "logic.h"
#include "menus.h"
#include "player_input.h"
#include "rendering.h"
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


// =========================================================== game_funtions.c =======================================================================

void updateContainers( Bomb *bomb_container[], SFX *explosion_container[], SFX *corpse_container[], LevelMap *level_map, Actor **enemies, int enemy_num, ALLEGRO_BITMAP *explosion_bmp, bool *map_update );
bool areEmptyContainers( Bomb *bomb_container[], SFX *explosion_container[], SFX *corpse_container[] );
void updatePlayer( Actor *player, LevelMap *level_map, Actor * *enemies, int enemy_num, SFX *explosion_container[], SFX *corpse_container[] );
void updateEnemies( AIModule * *enemy_modules, int enemy_num, SFX *explosion_container[], SFX *corpse_container[] );
void updateGFX( Actor *player, Actor * *enemies, int enemy_num, LevelMap *level_map, Bomb *bomb_container[], SFX *explosion_container[], SFX *corpse_container[] );
void updateGFXOnPause( ALLEGRO_BITMAP *game_stop_frame, Menu *pause_menu );
bool areAllEnemiesDead( Actor ** enemies, int enemy_num );


#endif
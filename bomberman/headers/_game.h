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

extern ALLEGRO_DISPLAY *display;

extern ALLEGRO_FONT *font_big;
extern ALLEGRO_FONT *font_small;
extern ALLEGRO_FONT *font_vsmall;

extern ALLEGRO_BITMAP *solid_block_sprite;
extern ALLEGRO_BITMAP *brittle_block_sprite;    
extern ALLEGRO_BITMAP *bomb_sprite;
extern ALLEGRO_BITMAP *explosion_sprite;
extern ALLEGRO_BITMAP *player_sprites;
extern ALLEGRO_BITMAP *enemy1_sprites;


// ========================================================= game_essentials.c =======================================================================

int initAllegro( void );
int validateAssets( void );
int initAssets( void );
void clearUp( void );

// =========================================================== game_funtions.c =======================================================================

void updateContainers( Bomb *bomb_container[], SFX *explosion_container[], SFX *corpse_container[], LevelMap *level_map, Actor **enemies, int enemy_num, ALLEGRO_BITMAP *explosion_bmp, bool *map_update );
bool areEmptyContainers( Bomb *bomb_container[], SFX *explosion_container[], SFX *corpse_container[] );
void updatePlayer( Actor *player, LevelMap *level_map, Actor * *enemies, int enemy_num, SFX *explosion_container[], SFX *corpse_container[] );
void updateEnemies( AIModule * *enemy_modules, int enemy_num, SFX *explosion_container[], SFX *corpse_container[] );
void updateGFX( Actor *player1, Actor *player2, Actor * *enemies, int enemy_num, LevelMap *level_map, Bomb *bomb_container[], SFX *explosion_container[], SFX *corpse_container[] );
void updateGFXOnPause( ALLEGRO_BITMAP *game_stop_frame, Menu *pause_menu );
bool areAllEnemiesDead( Actor ** enemies, int enemy_num );


#endif
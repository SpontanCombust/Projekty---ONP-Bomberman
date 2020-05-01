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
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>

extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_BITMAP *game_window;

extern ALLEGRO_FONT *font_big;
extern ALLEGRO_FONT *font_small;
extern ALLEGRO_FONT *font_vsmall;

extern ALLEGRO_BITMAP *solid_block_sprite;
extern ALLEGRO_BITMAP *brittle_block_sprite;    
extern ALLEGRO_BITMAP *bomb_sprite;
extern ALLEGRO_BITMAP *explosion_sprite;
extern ALLEGRO_BITMAP *player1_sprites;
extern ALLEGRO_BITMAP *player2_sprites;
extern ALLEGRO_BITMAP *enemy1_sprites;

extern GameState gs;


// ========================================================= game_essentials.c =======================================================================

int initAllegro( void );
int validateAssets( void );
int initAssets( void );
void clearUp( void );


// =========================================================== game_funtions.c =======================================================================

void updateSelectedLevelVar( Menu *ls_menu );
void updateSelectedSkinVars( Menu *opt_menu );
int loadSelectedSkins( void );
void switchMenu( Menu **current, Menu *goal );
void updateContainers( Bomb *bomb_container[], SFX *sfx_container[], LevelMap *level_map, Actor **enemies, int enemy_num, ALLEGRO_BITMAP *explosion_bmp, bool *map_update );
bool areContainersEmpty( Bomb *bomb_container[], SFX *sfx_container[] );
void updatePlayer( Actor *player, LevelMap *level_map, Actor * *enemies, int enemy_num, SFX *sfx_container[] );
void updateEnemies( AIModule * *enemy_modules, int enemy_num, SFX *sfx_container[] );
void updateGFX( Camera *camera, Actor *player1, Actor *player2, Actor * *enemies, int enemy_num, LevelMap *level_map, Bomb *bomb_container[], SFX *sfx_container[] );
void updateGFXOnPause( ALLEGRO_BITMAP *game_stop_frame, Menu *pause_menu );
bool areAllEnemiesDead( Actor ** enemies, int enemy_num );
void handleCameraOnPlayerDeath( Camera *camera, MultiPlayerCameraModule *mpcm, Actor *player1, Actor *player2 );
void handleTakingGameStopFrame( ALLEGRO_BITMAP **gsf, Camera *camera, Actor *player1, Actor *player2, ALLEGRO_EVENT_QUEUE *eq );
bool areAllPlayersDead( Actor *player1, Actor *player2 );
void updateAnimFrameForPlayers( Actor *player1, Actor *player2 );
void updateAnimFrameForEnemies( Actor * *enemies, int enemy_num );

#endif
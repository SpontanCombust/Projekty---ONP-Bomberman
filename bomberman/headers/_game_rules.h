#ifndef GAME_RULES_H
#define GAME_RULES_H

#define SCREEN_HEIGHT 600
#define SCREEN_WIDTH 720
#define GAME_WINDOW_Y_OFFSET 60

#define MAX_LOADED_LEVELS 10

#define CAMERA_SCALE 2

#define FPS 60.0
#define SECOND_TIMER 1.0
#define ANIM_TIMER 10.0

#define ACTOR_ANIM_FRAMES 8
#define EXPLOSION_ANIM_FRAMES 2
#define BOMB_ANIM_FRAMES 3

#define BOMB_BUDGET 5
#define SFX_BUDGET 50

#define EXPLOSION_LIFESPAN 2
#define CORPSE_LIFESPAN 2

#define PLAYER_SPEED 1.3
#define ENEMY_SPEED 1.2

#define COLOR_BLACK al_map_rgb( 0, 0, 0 )
#define COLOR_WHITE al_map_rgb( 255, 255, 255 )
#define COLOR_YELLOW al_map_rgb( 255, 255, 0 )
#define COLOR_RED al_map_rgb( 255, 0, 0 )
#define COLOR_GRAY al_map_rgb( 170, 170, 170 )

#define FONT_SRC "./fonts/PixelFJVerdana12pt.ttf"
#define LEVELS_FOLDER "./levels"
#define SOLID_BLOCK_SPRITES_SRC "./sprites/solid_block.png"
#define BRITTLE_BLOCK_SPRITES_SRC "./sprites/brittle_block.png" 
#define BOMB_SPRITES_SRC "./sprites/bomb.png"
#define EXPLOSION_SPRITES_SRC "./sprites/explosion.png"
#define PLAYER_SPRITES_ORIG_SRC "./sprites/player_sheet_orig.png"
#define PLAYER_SPRITES_ALT1_SRC "./sprites/player_sheet_alt1.png"
#define PLAYER_SPRITES_ALT2_SRC "./sprites/player_sheet_alt2.png"
#define ENEMY1_SPRITES_SRC "./sprites/enemy1_sheet.png"

#endif
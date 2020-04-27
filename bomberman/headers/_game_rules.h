#ifndef GAME_RULES_H
#define GAME_RULES_H

#define SCREEN_HEIGHT 540
#define SCREEN_WIDTH 720

#define MAX_LOADED_LEVELS 10

#define CAMERA_SCALE 2

#define FPS 60.0
#define SECOND_TIMER 1.0

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

#define FONT_SRC "./fonts/PixelFJVerdana12pt.ttf"
#define LEVELS_FOLDER "./levels"
#define SOLID_BLOCK_SPRITES_SRC "./sprites/solid_block.png"
#define BRITTLE_BLOCK_SPRITES_SRC "./sprites/brittle_block.png" 
#define BOMB_SPRITES_SRC "./sprites/bomb.png"
#define EXPLOSION_SPRITES_SRC "./sprites/explosion.png"
#define PLAYER_SPRITES_SRC "./sprites/player_sheet.png"
#define ENEMY1_SPRITES_SRC "./sprites/enemy1_sheet.png"

#define PLAYER_SPRITES_PINK_SRC "./sprites/player_sheet_pink.png"
#define PLAYER_SPRITES_RED_SRC "./sprites/player_sheet_red.png"
#define PLAYER_SPRITES_BLUE_SRC "./sprites/player_sheet_blue.png"


#endif
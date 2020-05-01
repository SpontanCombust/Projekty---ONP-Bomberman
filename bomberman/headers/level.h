#ifndef LEVEL_H
#define LEVEL_H

#include "level_map.h"
#include "ai.h"

#include <allegro5/allegro_font.h>

typedef struct S_Level
{
    LevelMap *level_map;
    Path * enemy_paths;
    int enemy_intit_count;
    Actor ** enemies;
    AIModule ** ai_modules;

} Level;

typedef enum E_LevelClearCondition { DESTROY_ALL_BLOCKS, KILL_ALL_ENEMIES, KILL_OPPONENT } LevelClearCondition;


// ======================== level_essentials.c ===========================

void doTitleScreen( ALLEGRO_FONT *font_big, ALLEGRO_FONT *font_small, float x, float y, char *level_id, LevelClearCondition condition );
void doEndScreen( ALLEGRO_FONT *font, float x, float y, bool won, char player_id, LevelClearCondition condition );
void destroyLevel( Level **level );

// ========================== level_creator.c ============================

Level *createLevel( char *level_id, ALLEGRO_BITMAP *enemy_bmp );

#endif
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

typedef enum E_LevelClearCondition { DESTROY_ALL_BLOCKS, KILL_ALL_ENEMIES } LevelClearCondition;


// ======================== level_essentials.c ===========================

void doTitleScreen( ALLEGRO_FONT *font_big, ALLEGRO_FONT *font_small, float x, float y, int level_number, LevelClearCondition condition );
void doEndScreen( ALLEGRO_FONT *font, float x, float y, bool won );
void destroyLevel( Level **level );

// ========================== level_creator.c ============================

Level *createLevel( int level_number, ALLEGRO_BITMAP *enemy_bmp );

#endif
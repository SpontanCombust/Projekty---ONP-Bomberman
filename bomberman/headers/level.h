#ifndef LEVEL_H
#define LEVEL_H

#include "level_map.h"
#include "ai.h"

#include <allegro5/allegro_font.h>

#define LEVELS_MADE 1

typedef struct S_Level {
    int level_id;

    LevelMap *level_map;
    Path * enemy_paths;
    int enemy_intit_count;
    Actor ** enemies;
    AIModule ** enemy_modules;

    // int enemy_count;
    // int block_count;

} Level;

enum LevelClearCondition { DESTROY_ALL_BLOCKS, KILL_ALL_ENEMIES };


// ======================== level_essentials.c ===========================

void doTitleScreen( ALLEGRO_FONT *font_big, ALLEGRO_FONT *font_small, float x, float y, int level_number, enum LevelClearCondition condition );
void doEndScreen( ALLEGRO_FONT *font, float x, float y, bool won );
void destroyLevel( Level **level );

// ========================== level_creator.c ============================

Level *createLevel( int level_number, ALLEGRO_BITMAP *enemy_bmp );

#endif
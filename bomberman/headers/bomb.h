#ifndef BOMB_H
#define BOMB_H

#include "actor.h"
#include "level_map.h"
#include "sfx.h"
#include <allegro5/allegro.h>

struct SBomb 
{
    int tile_x, tile_y;
    int fuse;
    int blast_range;
    ALLEGRO_BITMAP *bomb_bmp;
    ALLEGRO_BITMAP *explosion_bmp;
};
typedef struct SBomb Bomb;

#define DEFAULT_FUSE 3
#define DEFAULT_BLAST_RANGE 1

// ======================== bomb_essentials.c =========================
Bomb *createBomb( int tile_x, int tile_y, int fuse, int blast_range, ALLEGRO_BITMAP *bmp );
void destroyBomb( Bomb **bomb );

// ================================ bomb_placing.c ====================================
void handleBombInputKeyDown( char eventKeyboardKeycode, Actor *actor, Bomb **bomb_ptr );
void setBombProperties( Bomb *bomb, int fuse, int blast_range, ALLEGRO_BITMAP *bmp );
bool isEmptyBombContainer( Bomb * container[], int max_size );
void addBombToContainer( Bomb *container[], int max_size, Bomb *bomb );

// ================================= bomb_action.c ====================================
void explodeBomb( Bomb *bomb, LevelMap *level_map, SFX * sfx_container[], int container_size, ALLEGRO_BITMAP *explosion_bmp );

#endif
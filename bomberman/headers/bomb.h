#ifndef BOMB_H
#define BOMB_H

#include "actor.h"
#include "level_map.h"
#include "sfx.h"
#include <allegro5/allegro.h>

typedef struct S_Bomb
{
    int tile_x, tile_y;
    int fuse;
    int blast_range;
    int anim_frame;
    ALLEGRO_BITMAP *bmp;

} Bomb;

#define DEFAULT_FUSE 3
#define DEFAULT_BLAST_RANGE 1


// =============================== bomb_essentials.c ==================================

Bomb *createBomb( int tile_x, int tile_y, int fuse, int blast_range, ALLEGRO_BITMAP *bmp );
void destroyBomb( Bomb **bomb );


// ================================ bomb_placing.c ====================================

Bomb *createEmptyBombAtActor( Actor *actor );
void setBombProperties( Bomb *bomb, int fuse, int blast_range, ALLEGRO_BITMAP *bmp );


// ============================ bomb_container_manager.c ==============================

bool isBombContainerEmpty( Bomb * container[] );
void addBombToContainer( Bomb **bomb, Bomb *container[] );


// ================================= bomb_action.c ====================================

void explodeBomb( Bomb *bomb, LevelMap *level_map, SFX * sfx_container[], ALLEGRO_BITMAP *explosion_bmp );
void updateAnimFrameForBomb( Bomb *bomb );

#endif
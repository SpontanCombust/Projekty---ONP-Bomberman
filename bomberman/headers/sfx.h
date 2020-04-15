#ifndef SFX_H
#define SFX_H

#include <allegro5/allegro.h>
#include <stdbool.h>

enum SFX_Type { EXPLOSION, CORPSE };

typedef struct
{
    float x, y;
    int lifespan;
    enum SFX_Type type;
    ALLEGRO_BITMAP *bmp;
    
} SFX;

//======================= sfx_container_manager.c ===========================

bool isEmptySFXContainer( SFX * container[], int max_size );
void addSFXToContainer(SFX * container[], int max_size, SFX *sfx );
bool isSFXAtTile( int tile_x, int tile_y, SFX *sfx_container[], int max_size );

//========== sfx_essentials.c ===========

SFX *createSFX( float x, float y, int lifespan, enum SFX_Type type, ALLEGRO_BITMAP *bmp );
void destroySFX( SFX **sfx );



#endif
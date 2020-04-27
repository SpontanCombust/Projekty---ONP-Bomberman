#ifndef SFX_H
#define SFX_H

#include <allegro5/allegro.h>
#include <stdbool.h>

typedef enum E_SFX_Type { EXPLOSION, CORPSE } SFX_Type;

typedef struct S_SFX
{
    float x, y;
    int lifespan;
    SFX_Type type;
    ALLEGRO_BITMAP *bmp;
    
} SFX;

//======================= sfx_container_manager.c ===========================

bool isSFXContainerEmpty( SFX * container[] );
void addSFXToContainer(SFX **sfx, SFX * container[] );
bool isSFXAtTile( int tile_x, int tile_y, SFX *sfx_container[], SFX_Type type );

//========== sfx_essentials.c ===========

SFX *createSFX( float x, float y, int lifespan, SFX_Type type, ALLEGRO_BITMAP *bmp );
void destroySFX( SFX **sfx );



#endif
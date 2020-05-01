#ifndef SFX_H
#define SFX_H

#include <allegro5/allegro.h>
#include <stdbool.h>

typedef enum E_SFX_Type { EXPLOSION, CORPSE } SFX_Type;
typedef enum E_SFX_Orientation { CENTRE, VERTICAL, HEAD_DOWN, HEAD_UP, HORIZONTAL, HEAD_LEFT, HEAD_RIGHT } SFX_Orientation;

typedef struct S_SFX
{
    float x, y;
    int lifespan;
    SFX_Type type;
    SFX_Orientation orientation;
    int anim_frame;
    ALLEGRO_BITMAP *bmp;
    
} SFX;


//========== sfx_essentials.c ===========

SFX *createSFX( float x, float y, int lifespan, SFX_Type type, SFX_Orientation orientation, ALLEGRO_BITMAP *bmp );
void destroySFX( SFX **sfx );


// ========= sfx_handling.c =============

void updateAnimFrameForSFX( SFX *sfx );

//======================= sfx_container_manager.c ===========================

bool isSFXContainerEmpty( SFX * container[] );
void addSFXToContainer(SFX **sfx, SFX * container[] );
bool isSFXAtTile( int tile_x, int tile_y, SFX *sfx_container[], SFX_Type type );
void updateAnimFrameForSFXContainer( SFX *sfx_container[] );


#endif
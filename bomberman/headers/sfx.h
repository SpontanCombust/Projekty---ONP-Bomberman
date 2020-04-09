#ifndef SFX_H
#define SFX_H

#include <allegro5/allegro.h>
#include <stdbool.h>

typedef struct S_SFX
{
    float x, y;
    int lifespan;
    ALLEGRO_BITMAP *bmp;
    
} SFX;


//========== sfx_essentials.c ===========

SFX *createSFX( float x, float y, int lifespan, ALLEGRO_BITMAP *bmp );
void destroySFX( SFX **sfx );


//======================= sfx_manager.c ===========================

bool isEmptySFXContainer( SFX * container[], int max_size );
void addSFXToContainer(SFX * container[], int max_size, SFX *sfx );

#endif
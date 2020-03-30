#ifndef SFX_H
#define SFX_H

#include <allegro5/allegro.h>
#include <stdbool.h>

struct SSFX
{
    int tile_x, tile_y;
    int lifespan;
    ALLEGRO_BITMAP *bmp;
};
typedef struct SSFX SFX;

//========== sfx_essentials.c ===========
SFX *createSFX(int x, int y, int lifespan, ALLEGRO_BITMAP *bmp);
void destroySFX( SFX **sfx );

//======================= sfx_manager.c ===========================
bool isEmptySFXContainer( SFX * container[], int max_size );
void addSFXToContainer(SFX * container[], int max_size, SFX *sfx );

#endif
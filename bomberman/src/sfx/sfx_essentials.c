#include "../../headers/sfx.h"

#include <stdlib.h>
#include <stdio.h>

SFX *createSFX( int tile_x, int tile_y, int lifespan, ALLEGRO_BITMAP *bmp )
{
    SFX *sfx = (SFX *)malloc( sizeof( SFX ) );

    if( sfx )
    {
        sfx -> tile_x = tile_x;
        sfx -> tile_y = tile_y;
        sfx -> lifespan = lifespan;
        sfx -> bmp = bmp;
    }
    else
    {
        puts("Failed to allocate SFX!");
        return NULL;
    }
    
    return sfx;
}

void destroySFX( SFX **sfx )
{
    free( *sfx );
    *sfx = NULL;
}


#include "../../headers/sfx.h"

#include <stdlib.h>
#include <stdio.h>

SFX *createSFX( float x, float y, int lifespan, enum SFX_Type type, ALLEGRO_BITMAP *bmp )
{
    SFX *sfx = (SFX *)malloc( sizeof( SFX ) );

    if( sfx )
    {
        sfx -> x = x;
        sfx -> y = y;
        sfx -> lifespan = lifespan;
        sfx -> type = type;
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


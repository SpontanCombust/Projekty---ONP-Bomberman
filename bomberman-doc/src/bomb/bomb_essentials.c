#include "../../headers/bomb.h"

#include <stdlib.h>
#include <stdio.h>

Bomb *createBomb( int tile_x, int tile_y, int fuse, int blast_range, ALLEGRO_BITMAP *bmp )
{
    Bomb *bomb = (Bomb *)malloc( sizeof( Bomb ) );

    if( bomb )
    {
        bomb -> tile_x = tile_x;
        bomb -> tile_y = tile_y;
        bomb -> fuse = fuse;
        bomb -> blast_range = blast_range;
        bomb -> anim_frame = 0;
        bomb -> bmp = bmp;
    }
    else
    {
        puts("Failed to allcate bomb!");
        return NULL;
    }
    
    return bomb;
}

void destroyBomb( Bomb **bomb )
{
    free( *bomb );
    *bomb = NULL;
}
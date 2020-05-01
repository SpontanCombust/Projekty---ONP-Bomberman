#include "../../headers/bomb.h"

#include "../../headers/sprite_properties.h"
#include "../../headers/level_tile_matrix_tools.h"
#include <allegro5/allegro.h>

Bomb *createEmptyBombAtActor( Actor *actor )
{
    Bomb *bomb = createBomb( tileFromPixel( actor->x + TILE_SIZE/2 ), tileFromPixel( actor->y + TILE_SIZE/2 ), 0, 0, NULL );
    return bomb;
}

void setBombProperties( Bomb *bomb, int fuse, int blast_range, ALLEGRO_BITMAP *bmp )
{
    bomb -> fuse = fuse;
    bomb -> blast_range = blast_range;
    bomb -> bmp = bmp;
}

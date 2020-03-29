#include "../../headers/bomb.h"

#include "../../headers/sprite_properties.h"
#include "../../headers/tile_matrix_tools.h"
#include <allegro5/allegro.h>

Bomb *createBombAtActor( Actor *actor )
{
    Bomb *bomb = createBomb( tileFromPixel( actor->x + TILE_SIZE/2 ), tileFromPixel( actor->y + TILE_SIZE/2 ), 0, 0, NULL );
    return bomb;
}

void handleBombInputKeyDown( char eventKeyboardKeycode, Actor *actor, Bomb **bomb_ptr )
{
    if( eventKeyboardKeycode == ALLEGRO_KEY_SPACE )
    {
        *bomb_ptr = createBombAtActor( actor );
    }
}

void setBombProperties( Bomb *bomb, int fuse, int blast_range, ALLEGRO_BITMAP *bmp )
{
    bomb -> fuse = fuse;
    bomb -> blast_range = blast_range;
    bomb -> bomb_bmp = bmp;
}

bool isEmptyBombContainer( Bomb * container[], int max_size )
{
    for (int i = 0; i < max_size; i++)
        if( container[i] != NULL )
            return false;

    return true;
}

bool isTileTaken( Bomb * container[], int max_size, Bomb *bomb )
{
    for (int i = 0; i < max_size; i++)
    {
        if( container[i] != NULL  && container[i]->tile_x == bomb->tile_x && container[i]->tile_y == bomb->tile_y)
            return true;
    }

    return false;
}

void addBombToContainer( Bomb * container[], int max_size, Bomb *bomb )
{
    if( !isTileTaken( container, max_size, bomb ) )
    {
        for (int i = 0; i < max_size; i++)
        {
            if( container[i] == NULL )
            {
                container[i] = bomb;
                break;
            }
        }
    }
}

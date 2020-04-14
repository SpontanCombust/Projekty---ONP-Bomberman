#include "../../headers/sfx.h"

#include "../../headers/level_tile_matrix_tools.h"

bool isEmptySFXContainer( SFX * container[], int max_size )
{
    for (int i = 0; i < max_size; i++)
        if( container[i] != NULL )
            return false;

    return true;
}

void addSFXToContainer(SFX * container[], int max_size, SFX *sfx )
{
    for (int i = 0; i < max_size; i++)
    {
        if ( container[i] == NULL )
        {
            container[i] = sfx;
            break;
        }     
    }
}

bool isSFXAtTile( int tile_x, int tile_y, SFX *sfx_container[], int max_size )
{
    if( !isEmptySFXContainer( sfx_container, max_size ) )
    {
        for (int i = 0; i < max_size; i++)
        {
            if( sfx_container[i] != NULL)
            {
                if( tileFromPixel( sfx_container[i]->x ) == tile_x && tileFromPixel( sfx_container[i]->y ) == tile_y )
                    return true;   
            }
        } 
    }
    return false;
}
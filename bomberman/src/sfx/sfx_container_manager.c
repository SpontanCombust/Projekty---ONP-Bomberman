#include "../../headers/sfx.h"

#include "../../headers/level_tile_matrix_tools.h"
#include "../../headers/_game_rules.h"

bool isSFXContainerEmpty( SFX * container[] )
{
    for (int i = 0; i < SFX_BUDGET; i++)
        if( container[i] != NULL )
            return false;

    return true;
}

void addSFXToContainer( SFX **sfx, SFX * container[] )
{
    bool valid = false;
    for (int i = 0; i < SFX_BUDGET; i++)
    {
        if ( container[i] == NULL )
        {
            valid = true;
            container[i] = *sfx;
            break;
        }     
    }

    if( !valid )
        destroySFX( sfx );
}

bool isSFXAtTile( int tile_x, int tile_y, SFX *sfx_container[], SFX_Type type )
{
    if( !isSFXContainerEmpty( sfx_container ) )
    {
        for (int i = 0; i < SFX_BUDGET; i++)
        {
            if( sfx_container[i] != NULL && sfx_container[i]->type == type )
            {
                if( tileFromPixel( sfx_container[i]->x ) == tile_x && tileFromPixel( sfx_container[i]->y ) == tile_y )
                    return true;   
            }
        } 
    }
    return false;
}
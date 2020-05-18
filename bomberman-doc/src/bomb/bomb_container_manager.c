#include "../../headers/bomb.h"

#include "../../headers/_game_rules.h"

bool isBombContainerEmpty( Bomb * container[] )
{
    for (int i = 0; i < BOMB_BUDGET; i++)
        if( container[i] != NULL )
            return false;

    return true;
}

static bool isTileTaken( Bomb * container[], Bomb *bomb )
{
    for (int i = 0; i < BOMB_BUDGET; i++)
    {
        if( container[i] != NULL  && container[i]->tile_x == bomb->tile_x && container[i]->tile_y == bomb->tile_y)
            return true;
    }

    return false;
}

void addBombToContainer( Bomb **bomb, Bomb * container[] )
{
    bool valid = false;
    if( !isTileTaken( container, *bomb ) )
    {
        for (int i = 0; i < BOMB_BUDGET; i++)
        {
            if( container[i] == NULL )
            {
                valid = true;
                container[i] = *bomb;
                break;
            }
        }
    }
    
    if( !valid )
        destroyBomb( bomb );
}
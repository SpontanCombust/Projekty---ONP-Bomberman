#include "../../headers/bomb.h"

bool isEmptyBombContainer( Bomb * container[], int max_size )
{
    for (int i = 0; i < max_size; i++)
        if( container[i] != NULL )
            return false;

    return true;
}

static bool isTileTaken( Bomb * container[], int max_size, Bomb *bomb )
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
    bool valid = false;
    if( !isTileTaken( container, max_size, bomb ) )
    {
        for (int i = 0; i < max_size; i++)
        {
            if( container[i] == NULL )
            {
                valid = true;
                container[i] = bomb;
                break;
            }
        }
    }
    
    if( !valid )
        destroyBomb( &bomb );
}
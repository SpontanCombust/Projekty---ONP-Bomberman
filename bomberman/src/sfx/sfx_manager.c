#include "../../headers/sfx.h"

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

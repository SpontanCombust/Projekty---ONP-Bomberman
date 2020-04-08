#include "../../headers/ai.h"

#include <stdio.h>

AIModule *createAIModule( Actor *actor, Path path )
{
    AIModule *module = ( AIModule *)malloc( sizeof( AIModule ) );

    module -> actor = actor;
    module -> path = path;
    module -> current_step = path.steps[0];
    module -> step_index = 0;
    module -> reversed_path = false;

    return module; 
}

void destroyAIModule( AIModule **module )
{
    free( *module );
    *module = NULL;
}

void destroyAIModules( AIModule ** modules, int module_num )
{
    for (int i = 0; i < module_num; i++)
        destroyAIModule( &modules[i] );
}

Actor *createAIActor( Path path, float speed, enum Direction dir, ALLEGRO_BITMAP *bmp )
{
    return createActor( path.steps[0].dest_x, path.steps[0].dest_y, speed, dir, bmp );
}

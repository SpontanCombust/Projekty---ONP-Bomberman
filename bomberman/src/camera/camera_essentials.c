#include "../../headers/camera.h"

#include "../../headers/sprite_properties.h"

Camera *createCamera( Actor *target, LevelMap *lvl_map )
{
    Camera *camera = (Camera *)malloc( sizeof( Camera ) );

    camera -> target = target;
    camera -> max_x = lvl_map->collumns * TILE_SIZE - 1;
    camera -> max_y = lvl_map->rows * TILE_SIZE - 1;
    camera -> x = 0;
    camera -> y = 0;

    return camera;
}

void destroyCamera( Camera **camera )
{
    free( *camera );
    *camera = NULL;
}
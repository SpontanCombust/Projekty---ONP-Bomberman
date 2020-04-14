#include "../../headers/camera.h"

#include "../../headers/_game_rules.h"
#include "../../headers/sprite_properties.h"

static void updateCameraPosition( Camera *camera )
{
    camera -> x = ( camera->target->x + TILE_SIZE/2 ) - ( SCREEN_WIDTH/2 / CAMERA_SCALE );
    camera -> y = ( camera->target->y + TILE_SIZE/2 ) - ( SCREEN_HEIGHT/2 / CAMERA_SCALE );

    if( camera->x < 0 )
        camera -> x = 0;
    else if( camera->x > camera->max_x - SCREEN_WIDTH / CAMERA_SCALE + 1)
        camera -> x = camera->max_x - SCREEN_WIDTH / CAMERA_SCALE + 1;
    
    if( camera->y < 0 )
        camera -> y = 0;
    else if( camera->y > camera->max_y - SCREEN_HEIGHT / CAMERA_SCALE + 1)
        camera -> y = camera->max_y - SCREEN_HEIGHT / CAMERA_SCALE + 1;
}

void updateCamera( Camera *camera )
{
    updateCameraPosition( camera );
    al_identity_transform( &( camera->transform ) );
    al_scale_transform( &( camera->transform ), CAMERA_SCALE, CAMERA_SCALE );
    al_translate_transform( &( camera->transform ), -( camera->x * CAMERA_SCALE ), -( camera->y * CAMERA_SCALE ) );
    al_use_transform( &( camera->transform ) );
}

void disableCamera( Camera *camera )
{
    al_identity_transform( &( camera->transform ) );
    al_use_transform( &( camera->transform ) );
}
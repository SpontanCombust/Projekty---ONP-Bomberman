#include "../../headers/rendering.h"

#include "../../headers/level_tile_matrix_tools.h"

void drawBombs( Bomb *bomb_container[] )
{
    for (int i = 0; i < BOMB_BUDGET; i++)
    {
        if( bomb_container[i] != NULL )
            al_draw_bitmap( bomb_container[i]->bomb_bmp, pixelFromTile( bomb_container[i]->tile_x ), pixelFromTile( bomb_container[i]->tile_y ), 0 );
    }
}

void drawSFX( SFX *sfx_container[] )
{
    for (int i = 0; i < SFX_BUDGET; i++)
    {
        if( sfx_container[i] != NULL )
        {
            if( sfx_container[i]->type == EXPLOSION )
                al_draw_bitmap( sfx_container[i]->bmp, sfx_container[i]->x, sfx_container[i]->y, 0 );
            else if( sfx_container[i]->type == CORPSE )
                al_draw_tinted_bitmap_region( sfx_container[i]->bmp, COLOR_RED, 0, 0, TILE_SIZE, TILE_SIZE, sfx_container[i]->x, sfx_container[i]->y, 0 );
        }
    }
}

void drawActor( Actor *actor ) {
    al_draw_bitmap_region( actor->bmp, actor->dir * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE, actor->x, actor->y, 0 );
}

void drawLevelMap( LevelMap *level_map ) {
    al_draw_bitmap( level_map->bmp, 0, 0, 0 );
}

void drawMenu( Menu *menu ) {
    al_draw_bitmap( menu->bmp, menu->bg_x, menu->bg_y, 0 );
}
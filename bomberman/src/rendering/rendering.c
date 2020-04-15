#include "../../headers/rendering.h"

#include "../../headers/level_tile_matrix_tools.h"

void drawBombs( Bomb *bomb_container[] )
{
    if( !isEmptyBombContainer( bomb_container, BOMB_BUDGET ) )
    {
        for (int i = 0; i < BOMB_BUDGET; i++)
        {
            if( bomb_container[i] != NULL )
                al_draw_bitmap( bomb_container[i]->bomb_bmp, pixelFromTile( bomb_container[i]->tile_x ), pixelFromTile( bomb_container[i]->tile_y ), 0 );
        }
    }
}

void drawSFX( SFX *sfx_container[], enum SFX_Type type )
{
    if( type == EXPLOSION && !isEmptySFXContainer( sfx_container, EXPLOSION_BUDGET ) )
    {
        for (int i = 0; i < EXPLOSION_BUDGET; i++)
        {
            if( sfx_container[i] != NULL )
                al_draw_bitmap( sfx_container[i]->bmp, sfx_container[i]->x, sfx_container[i]->y, 0 );
        }
    }
    else if( type == CORPSE && !isEmptySFXContainer( sfx_container, CORPSE_BUDGET ) )
    {
        for (int i = 0; i < CORPSE_BUDGET; i++)
        {
            if( sfx_container[i] != NULL )
                al_draw_tinted_bitmap_region( sfx_container[i]->bmp, al_map_rgb( 255, 0, 0 ), 0, 0, TILE_SIZE, TILE_SIZE, sfx_container[i]->x, sfx_container[i]->y, 0 );
        }
    } 
}

void drawPlayer( Actor *player )
{
    if( player->alive )
        al_draw_bitmap_region( player->bmp, player->dir * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE, player->x, player->y, 0 );
}

void drawEnemies( Actor * *enemies, int enemy_num )
{
    for (int i = 0; i < enemy_num; i++)
    {
        if( enemies[i]->alive )
            al_draw_bitmap_region( enemies[i]->bmp, enemies[i]->dir * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE, enemies[i]->x, enemies[i]->y, 0);
    }
    
}
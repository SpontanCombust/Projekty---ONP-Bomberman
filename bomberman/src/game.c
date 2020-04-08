#include "../headers/_game.h"

void updateContainers( Bomb *bomb_container[], SFX *sfx_container[], LevelMap *level_map, Actor **enemies, int enemy_num, ALLEGRO_BITMAP *explosion_bmp, bool *map_update )
{
    if( !isEmptyBombContainer( bomb_container, BOMB_BUDGET ) )
    {
        for (int i = 0; i < BOMB_BUDGET; i++)
        {
            if( bomb_container[i] != NULL )
            {
                bomb_container[i] -> fuse--;

                if( bomb_container[i]->fuse == 0 )
                {
                    explodeBomb(bomb_container[i], level_map, sfx_container, SFX_BUDGET, explosion_bmp );
                    destroyBomb( &bomb_container[i] );
                    *map_update = true;
                }
            }
        }        
    }

    if( !isEmptySFXContainer( sfx_container, SFX_BUDGET ) )
    {
        for (int i = 0; i < SFX_BUDGET; i++)
        {
            if( sfx_container[i] != NULL )
            {   
                sfx_container[i] -> lifespan--;

                if( sfx_container[i]->lifespan == 0)
                    destroySFX( &sfx_container[i] );

            }
        }   
    }
}

static bool isSFXAtPosition( float x, float y, SFX *sfx_container[] )
{
    if( !isEmptySFXContainer( sfx_container, SFX_BUDGET ) )
    {
        for (int i = 0; i < SFX_BUDGET; i++)
        {
            if( sfx_container[i] != NULL)
            {
                if( sfx_container[i]->tile_x == tileFromPixel( x ) && sfx_container[i]->tile_y == tileFromPixel( y ) )
                    return true;   
            }
        } 
    }
    return false;
}

static void drawBombs( Bomb *bomb_container[] )
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

static void drawSFX( SFX *sfx_container[] )
{
    if( !isEmptySFXContainer( sfx_container, SFX_BUDGET ) )
    {
        for (int i = 0; i < SFX_BUDGET; i++)
        {
            if( sfx_container[i] != NULL )
                al_draw_bitmap( sfx_container[i]->bmp, pixelFromTile( sfx_container[i]->tile_x ), pixelFromTile( sfx_container[i]->tile_y ), 0 );
        }
    }
}

static void updatePlayerPosition( Actor *player, LevelMap *level_map )
{
    enum Direction cdir;

    updatePositionX( player );
    if( isOutOfBounds( player, level_map, &cdir, CBX_PLAYER, CBY_PLAYER, CBW_PLAYER, CBH_PLAYER ) )
        handleOutOfBounds( player, level_map, cdir, CBX_PLAYER, CBY_PLAYER, CBW_PLAYER, CBH_PLAYER );
    else if( isTerrainCollisionX( player, level_map, &cdir, CBX_PLAYER, CBY_PLAYER, CBW_PLAYER, CBH_PLAYER ) )
        handleTerrainCollision( player, cdir, CBX_PLAYER, CBY_PLAYER, CBW_PLAYER, CBH_PLAYER );

    updatePositionY( player );
    if( isOutOfBounds( player, level_map, &cdir, CBX_PLAYER, CBY_PLAYER, CBW_PLAYER, CBH_PLAYER ) )
        handleOutOfBounds( player, level_map, cdir, CBX_PLAYER, CBY_PLAYER, CBW_PLAYER, CBH_PLAYER );
    else if( isTerrainCollisionY( player, level_map, &cdir, CBX_PLAYER, CBY_PLAYER, CBW_PLAYER, CBH_PLAYER ) )
        handleTerrainCollision( player, cdir, CBX_PLAYER, CBY_PLAYER, CBW_PLAYER, CBH_PLAYER );

    resolveDirection( player );
}

void updatePlayer( Actor *player, LevelMap *level_map, SFX *sfx_container[] )
{
    updatePlayerPosition( player, level_map );

    if( isSFXAtPosition( player->x + TILE_SIZE/2, player->y + TILE_SIZE/2, sfx_container ) )
        player -> alive = false;
}

static void updateEnemyPosition( AIModule *enemy_module )
{
    if( reachedDestination( enemy_module ) )
        doNextStep( enemy_module );
    
    updatePositionX( enemy_module -> actor );
    updatePositionY( enemy_module -> actor );

    resolveDirection( enemy_module -> actor );
}

void updateEnemies( AIModule * *enemy_modules, int enemy_num, SFX *sfx_container[] )
{
    for (int i = 0; i < enemy_num; i++)
    {
        if( enemy_modules[i]->actor->alive )
        {
            updateEnemyPosition( enemy_modules[i] );

            if( isSFXAtPosition( enemy_modules[i]->actor->x + TILE_SIZE/2, enemy_modules[i]->actor->y + TILE_SIZE/2, sfx_container ) )
                enemy_modules[i] -> actor -> alive = false;
        }
    }
}

static void drawPlayer( Actor *player )
{
    al_draw_bitmap_region( player->bmp, player->dir * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE, (int) player->x, (int) player->y, 0 );
}

static void drawEnemies( AIModule * *modules, int enemy_num )
{
    for (int i = 0; i < enemy_num; i++)
    {
        if( modules[i]->actor->alive )
            al_draw_bitmap_region( modules[i]->actor->bmp, modules[i]->actor->dir * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE, modules[i]->actor->x, modules[i]->actor->y, 0);
    }
    
}

void updateGFX( Actor *player, AIModule * *modules, int enemy_num, LevelMap *level_map, Bomb *bomb_container[], SFX *sfx_container[] )
{
    al_clear_to_color( al_map_rgb( 0, 150, 0 ) );

    al_draw_bitmap( level_map->bmp, 0, 0, 0 );
    drawBombs( bomb_container );
    drawSFX( sfx_container );
    drawPlayer( player );
    drawEnemies( modules, enemy_num );

    al_flip_display();
}

bool areAllEnemiesDead( Actor * *enemies, int enemy_num )
{
    for (int i = 0; i < enemy_num; i++)
    {
        if( enemies[i]->alive )
            return false;
    }
    return true;
}

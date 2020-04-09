#include "../headers/_game.h"

void updateContainers( Bomb *bomb_container[], SFX *explosion_container[], SFX *corpse_container[], LevelMap *level_map, Actor **enemies, int enemy_num, ALLEGRO_BITMAP *explosion_bmp, bool *map_update )
{
    for (int i = 0; i < BOMB_BUDGET; i++)
    {
        if( bomb_container[i] != NULL )
        {
            bomb_container[i] -> fuse--;

            if( bomb_container[i]->fuse == 0 )
            {
                explodeBomb(bomb_container[i], level_map, explosion_container, EXPLOSION_BUDGET, explosion_bmp );
                destroyBomb( &bomb_container[i] );
                *map_update = true;
            }
        }
    }        

    for (int i = 0; i < EXPLOSION_BUDGET; i++)
    {
        if( explosion_container[i] != NULL )
        {   
            explosion_container[i] -> lifespan--;

            if( explosion_container[i]->lifespan == 0)
                destroySFX( &explosion_container[i] );
        }
    }   
    
    for (int i = 0; i < CORPSE_BUDGET; i++)
    {
        if( corpse_container[i] != NULL )
        {   
            corpse_container[i] -> lifespan--;

            if( corpse_container[i]->lifespan == 0)
                destroySFX( &corpse_container[i] );
        }
    } 
}

bool areEmptyContainers( Bomb *bomb_container[], SFX *explosion_container[], SFX *corpse_container[] )
{
    return  isEmptyBombContainer( bomb_container, BOMB_BUDGET )         
        &&  isEmptySFXContainer( explosion_container, EXPLOSION_BUDGET )
        &&  isEmptySFXContainer( corpse_container, CORPSE_BUDGET);
}

static void killActor( Actor *actor, SFX *corpse_container[] )
{
    actor -> alive = false;
    SFX *corpse = createSFX( actor->x, actor->y, CORPSE_LIFESPAN, CORPSE, actor->bmp );
    addSFXToContainer( corpse_container, CORPSE_BUDGET, corpse );
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

void updatePlayer( Actor *player, LevelMap *level_map, SFX *explosion_container[], SFX *corpse_container[] )
{
    if( player->alive )
    {
        updatePlayerPosition( player, level_map );

        if( isSFXAtTile( tileFromPixel( player->x + TILE_SIZE/2 ), tileFromPixel( player->y + TILE_SIZE/2 ), explosion_container, EXPLOSION_BUDGET ) )
            killActor( player, corpse_container );
    }
}

static void updateEnemyPosition( AIModule *enemy_module )
{
    if( reachedDestination( enemy_module ) )
        doNextStep( enemy_module );
    
    updatePositionX( enemy_module -> actor );
    updatePositionY( enemy_module -> actor );

    resolveDirection( enemy_module -> actor );
}

void updateEnemies( AIModule * *enemy_modules, int enemy_num, SFX *explosion_container[], SFX *corpse_container[] )
{
    for (int i = 0; i < enemy_num; i++)
    {
        if( enemy_modules[i]->actor->alive )
        {
            updateEnemyPosition( enemy_modules[i] );

            if( isSFXAtTile( tileFromPixel( enemy_modules[i]->actor->x + TILE_SIZE/2 ), tileFromPixel( enemy_modules[i]->actor->y + TILE_SIZE/2 ), explosion_container, EXPLOSION_BUDGET ) )
                killActor( enemy_modules[i]->actor, corpse_container );
        }
    }
}

void updateGFX( Actor *player, AIModule * *modules, int enemy_num, LevelMap *level_map, Bomb *bomb_container[], SFX *explosion_container[], SFX *corpse_container[] )
{
    al_clear_to_color( al_map_rgb( 0, 150, 0 ) );

    al_draw_bitmap( level_map->bmp, 0, 0, 0 );
    drawBombs( bomb_container );
    drawSFX( explosion_container, EXPLOSION );
    drawSFX( corpse_container, CORPSE );
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

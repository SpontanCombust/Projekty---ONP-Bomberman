#include "../../headers/_game.h"

void updateSelectedLevelVar( Menu *ls_menu ) {
    char level_str[ MAX_ENTRY_VAR_LENGTH ];
    sprintf( level_str, "%d", getSelectedLevel( gs ) );
    updateCurrentEntryVar( ls_menu, level_str );
}

void switchMenu( Menu **current, Menu *goal ) {
    *current = goal;
    resetToDefaultHighlighted( *current );
    signalStopMenuSwitch( &gs );
}

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
    
    if( player->enabled_collision && isOutOfBounds( player, level_map, &cdir ) )
        handleOutOfBounds( player, level_map, cdir );
    else if( player->enabled_collision && isTerrainCollisionX( player, level_map, &cdir ) )
        handleTerrainCollision( player, cdir );
    

    updatePositionY( player );
    
    if( player->enabled_collision && isOutOfBounds( player, level_map, &cdir ) )
        handleOutOfBounds( player, level_map, cdir );
    else if( player->enabled_collision && isTerrainCollisionY( player, level_map, &cdir ) )
        handleTerrainCollision( player, cdir );
    
    resolveDirection( player );
}

static bool isCollisionWithEnemies( Actor *player, Actor * *enemies, int enemy_num )
{
    if( player -> enabled_collision )
    {
        for (int i = 0; i < enemy_num; i++)
        {
            if( isActorCollision( player, enemies[i] ) )
                return true;
        }
    }
    return false;
}

void updatePlayer( Actor *player, LevelMap *level_map, Actor * *enemies, int enemy_num, SFX *explosion_container[], SFX *corpse_container[] )
{
    if( player->alive )
    {
        updatePlayerPosition( player, level_map );

        if( player->enabled_collision )
        {
            bool blown_up = isSFXAtTile( tileFromPixel( player->x + TILE_SIZE/2 ), tileFromPixel( player->y + TILE_SIZE/2 ), explosion_container, EXPLOSION_BUDGET );
            bool touched_enemy = isCollisionWithEnemies( player, enemies, enemy_num );
        
            if( blown_up || touched_enemy ) {
                killActor( player, corpse_container );
                signalPlayerDied( &gs );
            }
        }
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

void updateGFX( Actor *player1, Actor *player2, Actor * *enemies, int enemy_num, LevelMap *level_map, Bomb *bomb_container[], SFX *explosion_container[], SFX *corpse_container[] )
{
    drawLevelMap( level_map );
    drawBombs( bomb_container );
    drawSFX( explosion_container, EXPLOSION );
    drawSFX( corpse_container, CORPSE );
    drawPlayer( player1 );
    if( player2 != NULL ) drawPlayer( player2 );
    drawEnemies( enemies, enemy_num );
    al_flip_display();
}

void updateGFXOnPause( ALLEGRO_BITMAP *game_stop_frame, Menu *pause_menu )
{
    al_draw_bitmap( game_stop_frame, 0, 0, 0 );
    drawMenu( pause_menu );
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

void handleCameraOnPlayerDeath( Camera *camera, Actor *player1, Actor *player2 )
{
    if( player2 != NULL ) {
        if( !player1->alive && player2->alive )
            camera -> target = player2;
        else if( !player2->alive && player1->alive )
            camera -> target = player1;
    }
}

void handleTakingGameStopFrame( ALLEGRO_BITMAP **gsf, Camera *camera, Actor *player1, Actor *player2, ALLEGRO_EVENT_QUEUE *eq, GameState *gs )
{
    *gsf = al_get_backbuffer( display );

    disableCamera( camera );
    resetVelocity( player1 );
    if( player2 != NULL ) resetVelocity( player2 );

    al_flush_event_queue( eq );
    signalStopTakingGameStopFrame( gs );
}

bool areAllPlayersDead( Actor *player1, Actor *player2 )
{
    return !player1->alive && ( player2 == NULL || !player2->alive );
}
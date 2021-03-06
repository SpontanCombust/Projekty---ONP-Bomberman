#include "../../headers/_game.h"

void updateSelectedLevelVar( Menu *ls_menu ) {
    updateEntryVar( ls_menu, LEVEL_VAR_INDEX, getSelectedLevel( &gs ) );
}

void updateSelectedSkinVars( Menu *opt_menu ) {
    updateEntryVar( opt_menu, SKIN_P1_VAR_INDEX, getSelectedSkinP1( &gs ) );
    updateEntryVar( opt_menu, SKIN_P2_VAR_INDEX, getSelectedSkinP2( &gs ) );
}

static ALLEGRO_BITMAP *resolvePlayerBitmaps( char p )
{
    char skin[10];
    if( p == 0 ) strcpy( skin, getSelectedSkinP1( &gs ) );
    else strcpy( skin, getSelectedSkinP2( &gs ) );

    ALLEGRO_BITMAP *bmp = NULL;
    if( strcmp( skin, "ORIG" ) == 0 )
        bmp = al_load_bitmap( PLAYER_SPRITES_ORIG_SRC );
    if( strcmp( skin, "ALT1" ) == 0 )
        bmp = al_load_bitmap( PLAYER_SPRITES_ALT1_SRC );
    if( strcmp( skin, "ALT2" ) == 0 )
        bmp = al_load_bitmap( PLAYER_SPRITES_ALT2_SRC );
    
    return bmp;
}

int loadSelectedSkins( void )
{
    al_destroy_bitmap( player1_sprites );
    al_destroy_bitmap( player2_sprites );

    player1_sprites = resolvePlayerBitmaps( 0 );
    player2_sprites = resolvePlayerBitmaps( 1 );

    if( player1_sprites == NULL || player2_sprites == NULL ) {
        return -1;
        al_show_native_message_box( NULL, "ERROR", "Player sprites loading error!", "Failed to laod player sprites.", NULL, ALLEGRO_MESSAGEBOX_ERROR );
    }
    return 0;
}

void switchMenu( Menu **current, Menu *goal ) {
    *current = goal;
    resetToDefaultHighlighted( *current );
    signalStopMenuSwitch( &gs );
}

void updateContainers( Bomb *bomb_container[], SFX *sfx_container[], LevelMap *level_map, Actor **enemies, int enemy_num, ALLEGRO_BITMAP *explosion_bmp, bool *map_update )
{
    for (int i = 0; i < BOMB_BUDGET; i++)
    {
        if( bomb_container[i] != NULL )
        {
            updateAnimFrameForBomb( bomb_container[i] );
            bomb_container[i] -> fuse--;
            if( bomb_container[i]->fuse == 0 )
            {
                explodeBomb( bomb_container[i], level_map, sfx_container, explosion_bmp );
                destroyBomb( &bomb_container[i] );
                *map_update = true;
            }
        }
    }        

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

bool areContainersEmpty( Bomb *bomb_container[], SFX *sfx_container[] ) {
    return  isBombContainerEmpty( bomb_container ) &&  isSFXContainerEmpty( sfx_container );
}

static void killActor( Actor *actor, SFX *sfx_container[] ) {
    SFX *corpse = createSFX( actor->x, actor->y, CORPSE_LIFESPAN, CORPSE, 0, actor->bmp );
    addSFXToContainer( &corpse, sfx_container );
}

static void updatePlayerPosition( Actor *player, LevelMap *level_map )
{
    Direction cdir;

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

static bool touchedExplosion( Actor *actor, SFX * sfx_container[] ) {
    return isSFXAtTile( tileFromPixel( actor->x + TILE_SIZE/2 ), tileFromPixel( actor->y + TILE_SIZE/2 ), sfx_container, EXPLOSION );
}

void updatePlayer( Actor *player, LevelMap *level_map, Actor * *enemies, int enemy_num, SFX *sfx_container[] )
{
    if( player != NULL && isActorAlive( player ) )
    {
        updatePlayerPosition( player, level_map );

        if( player->enabled_collision && ( touchedExplosion( player, sfx_container ) || isCollisionWithEnemies( player, enemies, enemy_num ) ) ) 
        {
            damageActor( player );

            if( !isActorAlive( player ) ) {
                killActor( player, sfx_container );
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

void updateEnemies( AIModule * *enemy_modules, int enemy_num, SFX *sfx_container[] )
{
    for (int i = 0; i < enemy_num; i++)
    {
        if( isActorAlive( enemy_modules[i]->actor ) )
        {
            updateEnemyPosition( enemy_modules[i] );

            if( touchedExplosion( enemy_modules[i]->actor, sfx_container ) ) 
            {
                damageActor( enemy_modules[i]->actor );

                if( !isActorAlive( enemy_modules[i]->actor ) )
                    killActor( enemy_modules[i]->actor, sfx_container );
            }
        }
    }
}

void updateGFX( Camera *camera, Actor *player1, Actor *player2, Actor * *enemies, int enemy_num, LevelMap *level_map, Bomb *bomb_container[], SFX *sfx_container[] )
{
    drawLevelMap( level_map );
    drawBombs( bomb_container );
    drawSFX( sfx_container );
    if( isActorAlive( player1 ) )
        drawActor( player1 );
    if( player2 != NULL && isActorAlive( player2) )
        drawActor( player2 );
    for (int i = 0; i < enemy_num; i++)
        if( isActorAlive( enemies[i] ) )   
            drawActor( enemies[i] );

    disableCamera( camera );
    al_set_target_backbuffer( display );
    al_clear_to_color( COLOR_GRAY );
    al_draw_bitmap( game_window, 0, GAME_WINDOW_Y_OFFSET, 0 );
    al_draw_textf( font_small, COLOR_BLACK, SCREEN_WIDTH/2, -1, ALLEGRO_ALIGN_CENTER, "LEVEL %s", getSelectedLevel( &gs ) );

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
        if( isActorAlive( enemies[i]) )
            return false;
    }
    return true;
}

void handleCameraOnPlayerDeath( Camera *camera, MultiPlayerCameraModule *mpcm, Actor *player1, Actor *player2 )
{
    if( player2 != NULL ) {
        if( !isActorAlive( player1 ) && isActorAlive( player2 ) )
            camera -> target = player2;
        else if( !isActorAlive( player2 ) && isActorAlive( player1 ) )
            camera -> target = player1;
        destroyActor( &mpcm->target );
    }
}

void handleTakingGameStopFrame( ALLEGRO_BITMAP **gsf, Camera *camera, Actor *player1, Actor *player2, ALLEGRO_EVENT_QUEUE *eq )
{
    *gsf = al_get_backbuffer( display );

    disableCamera( camera );
    resetVelocity( player1 );
    if( player2 != NULL ) resetVelocity( player2 );

    al_flush_event_queue( eq );
    signalStopTakingGameStopFrame( &gs );
}

bool areAllPlayersDead( Actor *player1, Actor *player2 )
{
    return !isActorAlive( player1 ) && ( player2 == NULL || !isActorAlive( player2 ) );
}

void updateAnimFrameForPlayers( Actor *player1, Actor *player2 )
{
    if( isActorAlive( player1 ) )
        updateAnimFrameForActor( player1 );
    if( player2 != NULL && isActorAlive( player2 ) )
        updateAnimFrameForActor( player2 );
}

void updateAnimFrameForEnemies( Actor * *enemies, int enemy_num )
{
    for (int i = 0; i < enemy_num; i++)
    {
        if( isActorAlive( enemies[i] ) )
            updateAnimFrameForActor( enemies[i] );
    }
}

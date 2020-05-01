#include "./headers/_game.h"

ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_BITMAP *game_window = NULL;

ALLEGRO_FONT *font_big = NULL;
ALLEGRO_FONT *font_small = NULL;
ALLEGRO_FONT *font_vsmall = NULL;

ALLEGRO_BITMAP *solid_block_sprite = NULL;
ALLEGRO_BITMAP *brittle_block_sprite = NULL;
ALLEGRO_BITMAP *bomb_sprite = NULL;
ALLEGRO_BITMAP *explosion_sprite = NULL;
ALLEGRO_BITMAP *player1_sprites = NULL;
ALLEGRO_BITMAP *player2_sprites = NULL;
ALLEGRO_BITMAP *enemy1_sprites = NULL;

GameState gs;

void playLevel( char *level_id );

int main( void )
{
    if( initAllegro() != 0 || initAssets() != 0 ){
        al_show_native_message_box( NULL, "ERROR", "ALLEGRO ERROR!", "Allegro 5 failed to initialize!", NULL, ALLEGRO_MESSAGEBOX_ERROR );
        return -1;
    }

    ALLEGRO_EVENT_QUEUE *main_eq = al_create_event_queue();

    al_register_event_source( main_eq, al_get_display_event_source( display ) );
    al_register_event_source( main_eq, al_get_keyboard_event_source() );

    initGameState( &gs );

    Menu *main_menu = createMainMenu( font_big, font_small );
    Menu *options_menu = createOptionsMenu( font_small, font_vsmall );
    updateSelectedSkinVars( options_menu );
    Menu *mode_menu = createModeSelectionMenu( font_small, font_vsmall );
    Menu *level_menu = createLevelSelectionMenu( font_small, font_vsmall );
    updateSelectedLevelVar( level_menu );
    Menu *current_menu = main_menu;

    updateMenuBitmap( current_menu, display );
    drawMenu( current_menu );
    al_flip_display();
    
    ALLEGRO_EVENT events;

    while ( isProgramRunning( gs ) )
    {
        al_wait_for_event( main_eq, &events );

        if ( events.type == ALLEGRO_EVENT_DISPLAY_CLOSE )
            signalShuttingDown( &gs );
        else if( events.type == ALLEGRO_EVENT_KEY_DOWN ) {
            handleMenuInputKeyDown( events.keyboard.keycode, current_menu, &gs );

            if( wasLevelSelected( gs ) ) {
                updateSelectedLevelVar( level_menu );
                signalStopSelectedALevel( &gs );
            }
            else if( wasSkinSelected( gs ) ) {
                updateSelectedSkinVars( options_menu );
                signalStopSelectedASkin( &gs );
            }
            signalRenderUpdate( &gs );
        }

        if( isMenuSwitch( gs ) )
        {
            if( isInOptions( gs ) ) 
                switchMenu( &current_menu, options_menu );
            else if( isInModeSelection( gs ) )
                switchMenu( &current_menu, mode_menu );
            else if( isInLevelSelection( gs ) )
                switchMenu( &current_menu, level_menu );
            else
                switchMenu( &current_menu, main_menu );
        }

        if( isRenderUpdate( gs ) )
        {
            if( isMenuUpdate( gs ) ) {
                updateMenuBitmap( current_menu, display );
                signalStopMenuUpdate( &gs );
            }
            drawMenu( current_menu );
            al_flip_display();
            signalStopRenderUpdate( &gs );
        }

        if( isGameRunning( gs ) && loadSelectedSkins() != -1 )
        {
            al_pause_event_queue( main_eq, true );
            playLevel( getSelectedLevel( &gs ) );
            al_pause_event_queue( main_eq, false );
        }
    }
    
    current_menu = NULL;
    destroyMenu( &main_menu );
    destroyMenu( &options_menu );
    destroyMenu( &mode_menu );
    destroyMenu( &level_menu );
    clearUp();

    return 0;
}





void playLevel( char *level_id )
{
    ALLEGRO_EVENT_QUEUE *eq = NULL;
    ALLEGRO_TIMER *game_timer = NULL;
    ALLEGRO_TIMER *second_timer = NULL;
    ALLEGRO_TIMER *anim_timer = NULL;

    Menu *pause_menu = NULL;
    ALLEGRO_BITMAP *game_stop_frame = NULL;

    Actor *player1 = NULL, *player2 = NULL;
    MultiPlayerCameraModule mpcm = { NULL, NULL, NULL };

    LevelMap *level_map = NULL;
    int enemy_num = 0;
    Path * enemy_paths = NULL;
    Actor * *enemies = NULL;
    AIModule * *ai_modules = NULL;

    Bomb *bomb_container[ BOMB_BUDGET ] = { NULL };
    int current_blast_range = DEFAULT_BLAST_RANGE;
    SFX *sfx_container[ SFX_BUDGET ] = { NULL };

    Camera *camera = NULL;

    LevelClearCondition clear_cond = 0;

    bool clean = true;
    bool map_update = false;
    bool won = false, sudden_exit = true;

    Level *level = createLevel( level_id, enemy1_sprites );

    if( level != NULL )
    {
        eq = al_create_event_queue();

        game_timer = al_create_timer( 1.0 / FPS );
        second_timer = al_create_timer( 1.0 / SECOND_TIMER );
        anim_timer = al_create_timer( 1.0 / ANIM_TIMER );

        al_register_event_source( eq, al_get_keyboard_event_source() );
        al_register_event_source( eq, al_get_timer_event_source( game_timer ) );
        al_register_event_source( eq, al_get_timer_event_source( second_timer ) );
        al_register_event_source( eq, al_get_timer_event_source( anim_timer ) );
        al_register_event_source( eq, al_get_display_event_source( display ) );

        pause_menu = createPauseMenu( font_vsmall, font_vsmall );

        level_map = level->level_map;
        enemy_num = level->enemy_intit_count;
        enemy_paths = level->enemy_paths;
        enemies = level->enemies;
        applyCollisionToActorArray( enemies, enemy_num, CBX_ENEMY1, CBY_ENEMY1, CBW_ENEMY1, CBH_ENEMY1 );
        ai_modules = level->ai_modules;

        player1 = createActor(0, 0, PLAYER_SPEED, player1_sprites);
        applyCollisionToActor( player1, CBX_PLAYER, CBY_PLAYER, CBW_PLAYER, CBH_PLAYER );

        if( getGameMode( gs ) != SINGLE_PLAYER ) {
            player2 = createActor( 0, 0, PLAYER_SPEED, player2_sprites );
            applyCollisionToActor( player2, CBX_PLAYER, CBY_PLAYER, CBW_PLAYER, CBH_PLAYER );
            applyActorsToCameraModule( &mpcm, player1, player2 );
        }

        if( player2 == NULL )
            camera = createCamera( player1, level_map );
        else
            camera = createCamera( mpcm.target, level_map );

        if( getGameMode( gs ) != PVP )
            clear_cond = KILL_ALL_ENEMIES;
        else
            clear_cond = KILL_OPPONENT;

        doTitleScreen( font_big, font_small, SCREEN_WIDTH/2, SCREEN_HEIGHT/2 - 75, level_id, clear_cond );

        updateLevelMapBitmap( level_map, solid_block_sprite, brittle_block_sprite, display );
        // al_save_bitmap( "./map_screencap.png", level_map->bmp );

        al_start_timer( game_timer );
        al_start_timer( second_timer );
        al_start_timer( anim_timer );

    } else signalEndingGame( &gs );


    ALLEGRO_EVENT events;
    while( isGameRunning( gs ) || !clean )
    {
        al_wait_for_event( eq, &events );

        if ( events.type == ALLEGRO_EVENT_DISPLAY_CLOSE )
            signalShuttingDown( &gs );    
        else if( events.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            if( !isGamePaused( gs ) ) {
                handleGameInputKeyDown( events.keyboard.keycode, ALTERNATIVE, player2, current_blast_range, bomb_sprite, bomb_container, &gs );
                handleGameInputKeyDown( events.keyboard.keycode, STANDARD, player1, current_blast_range, bomb_sprite, bomb_container, &gs );
            }
            else
                handleMenuInputKeyDown( events.keyboard.keycode, pause_menu, &gs );
        }
        else if( events.type == ALLEGRO_EVENT_KEY_UP)
        {
            if( !isGamePaused( gs ) ) {
                handleGameInputKeyUp( events.keyboard.keycode, ALTERNATIVE, player2 );
                handleGameInputKeyUp( events.keyboard.keycode, STANDARD, player1 );
            }
        }

        if( isTakingGameStopFrame( gs ) ) {
            handleTakingGameStopFrame( &game_stop_frame, camera, player1, player2, eq );
        }

        if ( events.type == ALLEGRO_EVENT_TIMER )
        {   
            if( !isGamePaused( gs ) )
            {
                if( events.timer.source == game_timer )
                {
                    updatePlayer( player1, level_map, enemies, enemy_num, sfx_container );
                    updatePlayer( player2, level_map, enemies, enemy_num, sfx_container );
                    updateEnemies( ai_modules, enemy_num, sfx_container );
                    if( getGameMode( gs ) != SINGLE_PLAYER ) {
                        updateCameraModule( &mpcm );
                    }
                    if( map_update ) {
                        updateLevelMapBitmap( level_map, solid_block_sprite, brittle_block_sprite, display );
                        map_update = false;
                    }

                    al_set_target_bitmap( game_window );
                    updateCamera( camera );

                    signalRenderUpdate( &gs );  
                }
                else if( events.timer.source == second_timer )
                {
                    updateContainers( bomb_container, sfx_container, level_map, enemies, enemy_num, explosion_sprite, &map_update );
                    clean = areContainersEmpty( bomb_container, sfx_container );
                }
                else if( events.timer.source == anim_timer )
                {
                    updateAnimFrameForPlayers( player1, player2 );
                    updateAnimFrameForEnemies( enemies, enemy_num );
                    updateAnimFrameForSFXContainer( sfx_container );
                }
            }
            else
            {
                if( events.timer.source == game_timer )
                {
                    if( isMenuUpdate( gs ) ) {
                        updateMenuBitmap( pause_menu, display );
                        signalStopMenuUpdate( &gs );
                    }
                    signalRenderUpdate( &gs );
                }
            }
            
        }

        if( isRenderUpdate( gs ) )
        {
            if( !isGamePaused( gs ) )
                updateGFX( camera, player1, player2, enemies, enemy_num, level_map, bomb_container, sfx_container );
            else
                updateGFXOnPause( game_stop_frame, pause_menu );

            signalStopRenderUpdate( &gs ); 
        }

        if( didPlayerDie( gs ) ) {
            handleCameraOnPlayerDeath( camera, &mpcm, player1, player2 );
            if( areAllPlayersDead( player1, player2 ) ) {
                signalEndingGame( &gs );
                sudden_exit = false;
                won = false;
            }
            else if( clear_cond == KILL_OPPONENT ) {
                signalEndingGame( &gs );
                sudden_exit = false;
                won = true;
            }
            signalStopPlayerDied( &gs );
        }

        if( clear_cond == KILL_ALL_ENEMIES && areAllEnemiesDead( enemies, enemy_num ) ) {
            signalEndingGame( &gs );
            sudden_exit = false;
            won = true;
        }
    }

    if( !sudden_exit )
    {
        disableCamera( camera );
        al_rest(1);

        char id;
        if( !isActorAlive( player1 ) ) 
            id = '2';
        else 
            id = '1';

        doEndScreen( font_big, SCREEN_WIDTH/2, SCREEN_HEIGHT/2 - 75, won, id, clear_cond );
    }


    if( eq != NULL ) al_destroy_event_queue( eq );
    if( game_timer != NULL ) al_destroy_timer( game_timer );
    if( second_timer != NULL ) al_destroy_timer( second_timer );
    if( anim_timer != NULL ) al_destroy_timer( anim_timer );

    if( pause_menu != NULL ) destroyMenu( &pause_menu );
    if( level_map != NULL ) destroyLevelMap( &level_map );
    if( player1 != NULL ) destroyActor( &player1 );
    if( player2 != NULL ) destroyActor( &player2 );
    if( &mpcm.target != NULL ) destroyActor( &mpcm.target );         
    if( level != NULL ) {
        destroyLevel( &level );
        destroyPathArray( &enemy_paths );
        destroyActorArray( &enemies, enemy_num );
        destroyAIModuleArray( &ai_modules, enemy_num );
    }
    if( camera != NULL ) destroyCamera( &camera );
    
    signalGoingToMainMenu( &gs );
    signalRenderUpdate( &gs );
}
#include "./headers/_game.h"

ALLEGRO_DISPLAY *display = NULL;

ALLEGRO_FONT *font_big = NULL;
ALLEGRO_FONT *font_small = NULL;
ALLEGRO_FONT *font_vsmall = NULL;

ALLEGRO_BITMAP *solid_block_sprite = NULL;
ALLEGRO_BITMAP *brittle_block_sprite = NULL;
ALLEGRO_BITMAP *bomb_sprite = NULL;
ALLEGRO_BITMAP *explosion_sprite = NULL;
ALLEGRO_BITMAP *player_sprites = NULL;
ALLEGRO_BITMAP *enemy1_sprites = NULL;

GameState gs;

void playLevel( int level_num );

int main( void )
{
    if( initAllegro() != 0 || initAssets() != 0 ){
        fprintf( stderr, "ERROR!\n" );
        return -1;
    }

    ALLEGRO_EVENT_QUEUE *main_eq = al_create_event_queue();

    al_register_event_source( main_eq, al_get_display_event_source( display ) );
    al_register_event_source( main_eq, al_get_keyboard_event_source() );

    initGameState( &gs );

    Menu *main_menu = createMainMenu( font_big );
    Menu *options_menu = createOptionsMenu( font_big );
    Menu *mode_menu = createModeSelectionMenu( font_big );

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
            signalRenderUpdate( &gs );
        }

        if( isInOptions( gs ) )
            current_menu = options_menu;
        else if( isInModeSelection( gs ) )
            current_menu = mode_menu;
        else
            current_menu = main_menu;

        if( isRenderUpdate( gs ) )
        {
            updateMenuBitmap( current_menu, display );
            drawMenu( current_menu );
            al_flip_display();

            signalRenderStop( &gs );
        }

        if( isGameRunning( gs ) )
        {
            al_pause_event_queue( main_eq, true );
            playLevel( getSelectedLevel( gs ) );
            al_pause_event_queue( main_eq, false );
        }
    }
    
    current_menu = NULL;
    destroyMenu( &main_menu );
    destroyMenu( &options_menu );
    destroyMenu( &mode_menu );
    clearUp();

    return 0;
}





void playLevel( int level_num )
{
    ALLEGRO_EVENT_QUEUE *eq = al_create_event_queue();

    ALLEGRO_TIMER *game_timer = al_create_timer( 1.0 / FPS );
    ALLEGRO_TIMER *second_timer = al_create_timer( 1.0 / SECOND_TIMER );

    al_register_event_source( eq, al_get_keyboard_event_source() );
    al_register_event_source( eq, al_get_timer_event_source( game_timer ) );
    al_register_event_source( eq, al_get_timer_event_source( second_timer ) );
    al_register_event_source( eq, al_get_display_event_source( display ) );

    Menu *pause_menu = createPauseMenu( font_vsmall );
    ALLEGRO_BITMAP *game_stop_frame = NULL;


    Actor *player1 = NULL, *player2 = NULL;
    CentralPivotModule cpm = { NULL, NULL, NULL };

    player1 = createActor(0, 0, PLAYER_SPEED, player_sprites);
    applyCollisionToActor( player1, CBX_PLAYER, CBY_PLAYER, CBW_PLAYER, CBH_PLAYER );

    if( getGameMode( gs ) != SINGLE_PLAYER ) {
        player2 = createActor( 0, 0, PLAYER_SPEED, player_sprites );
        applyCollisionToActor( player2, CBX_PLAYER, CBY_PLAYER, CBW_PLAYER, CBH_PLAYER );
        applyActorsToPivot( &cpm, player1, player2 );
    }


    Level *level = createLevel( level_num, enemy1_sprites );
    LevelMap *level_map = level->level_map;
    int enemy_num = level->enemy_intit_count;
    Path * enemy_paths = level->enemy_paths;
    Actor * *enemies = level->enemies;
    applyCollisionToActorArray( enemies, enemy_num, CBX_ENEMY1, CBY_ENEMY1, CBW_ENEMY1, CBH_ENEMY1 );
    AIModule * *ai_modules = level->ai_modules;

    Bomb *bomb_container[ BOMB_BUDGET ] = { NULL };
    int current_blast_range = DEFAULT_BLAST_RANGE;
    SFX *explosion_container[ EXPLOSION_BUDGET ] = { NULL };
    SFX *corpse_container[ CORPSE_BUDGET ] = { NULL };

    Camera *camera = NULL;
    if( player2 == NULL )
        camera = createCamera( player1, level_map );
    else
        camera = createCamera( cpm.pivot, level_map );

    enum LevelClearCondition clear_cond = KILL_ALL_ENEMIES;

    bool clean = true;
    bool map_update = false;
    bool won = false, sudden_exit = true;

    doTitleScreen( font_big, font_small, SCREEN_WIDTH/2, SCREEN_HEIGHT/2 - 75, level_num, clear_cond );

    updateLevelMapBitmap( level_map, solid_block_sprite, brittle_block_sprite, display );
    updateGFX( player1, player2, enemies, enemy_num, level_map, bomb_container, explosion_container, corpse_container );

    ALLEGRO_EVENT events;
    al_start_timer( game_timer );
    al_start_timer( second_timer );

    while( isGameRunning( gs ) || !clean )
    {
        al_wait_for_event( eq, &events );

        if ( events.type == ALLEGRO_EVENT_DISPLAY_CLOSE )
            signalShuttingDown( &gs );    
        else if( events.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            if( !isGamePaused( gs ) ) {
                handleGameInputKeyDown( events.keyboard.keycode, STANDARD, player1, current_blast_range, bomb_sprite, bomb_container, &gs );
                if( player2 != NULL ) handleGameInputKeyDown( events.keyboard.keycode, ALTERNATIVE, player2, current_blast_range, bomb_sprite, bomb_container, &gs );
            }
            else
                handleMenuInputKeyDown( events.keyboard.keycode, pause_menu, &gs );
        }
        else if( events.type == ALLEGRO_EVENT_KEY_UP)
        {
            if( !isGamePaused( gs ) ) {
                handleGameInputKeyUp( events.keyboard.keycode, STANDARD, player1 );
                if( player2 != NULL ) handleGameInputKeyUp( events.keyboard.keycode, ALTERNATIVE, player2 );
            }
        }

        if( isTakingGameStopFrame( gs ) ) {
            game_stop_frame = al_get_backbuffer( display );

            disableCamera( camera );
            resetVelocity( player1 );
            if( player2 != NULL ) resetVelocity( player2 );

            al_flush_event_queue( eq );
            signalNotTakingGameStopFrame( &gs );
        }

        if ( events.type == ALLEGRO_EVENT_TIMER )
        {   
            if( !isGamePaused( gs ) )
            {
                if( events.timer.source == game_timer )
                {
                    updatePlayer( player1, level_map, enemies, enemy_num, explosion_container, corpse_container );
                    if( player2 != NULL ) {
                        updatePlayer( player2, level_map, enemies, enemy_num, explosion_container, corpse_container );
                        updatePivot( &cpm );
                    }
                    updateEnemies( ai_modules, enemy_num, explosion_container, corpse_container );

                    if( map_update )
                        updateLevelMapBitmap( level_map, solid_block_sprite, brittle_block_sprite, display );
                    
                    updateCamera( camera );

                    signalRenderUpdate( &gs );  
                }

                if( events.timer.source == second_timer )
                {
                    updateContainers( bomb_container, explosion_container, corpse_container, level_map, enemies, enemy_num, explosion_sprite, &map_update );
                    clean = areEmptyContainers( bomb_container, explosion_container, corpse_container );
                }
            }
            else
            {
                if( events.timer.source == game_timer )
                {
                    if( isMenuUpdate( gs ) )
                        updateMenuBitmap( pause_menu, display );

                    signalRenderUpdate( &gs );
                }
            }
            
        }

        if( isRenderUpdate( gs ) )
        {
            if( !isGamePaused( gs ) )
                updateGFX( player1, player2, enemies, enemy_num, level_map, bomb_container, explosion_container, corpse_container );
            else
                updateGFXOnPause( game_stop_frame, pause_menu );

            signalRenderStop( &gs ); 
        }


        if( player2 != NULL ) {
            if( !player1->alive && player2->alive )
                camera -> target = player2;
            else if( !player2->alive && player1->alive )
                camera -> target = player1;
        }

        if( areAllEnemiesDead( enemies, enemy_num ) ) {
            signalEndingGame( &gs );
            sudden_exit = false;
            won = true;
        }
        else if( !player1->alive && !player2->alive ) {
            signalEndingGame( &gs );
            sudden_exit = false;
        }
    }

    if( !sudden_exit )
    {
        disableCamera( camera );
        al_rest(1);
        doEndScreen( font_big, SCREEN_WIDTH/2, SCREEN_HEIGHT/2 - 75, won );
    }


    al_destroy_event_queue( eq );
    al_destroy_timer( game_timer );
    al_destroy_timer( second_timer );

    destroyMenu( &pause_menu );
    destroyLevelMap( &level_map );
    destroyActor( &player1 );
    if( player2 != NULL ) {
        destroyActor( &player2 );
        destroyActor( &cpm.pivot );
    }
    destroyPathArray( &enemy_paths );
    destroyActorArray( &enemies, enemy_num );
    destroyAIModuleArray( &ai_modules, enemy_num );
    destroyLevel( &level );
    destroyCamera( &camera );
    
    signalGoingToMainMenu( &gs );
    signalRenderUpdate( &gs );
}
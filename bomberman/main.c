#include "./headers/_game.h"

ALLEGRO_DISPLAY *display = NULL;

ALLEGRO_FONT *font_big = NULL;
ALLEGRO_FONT *font_small = NULL;
ALLEGRO_FONT *font_vsmall = NULL;

ALLEGRO_BITMAP *solid_block_sprite = NULL;
ALLEGRO_BITMAP *brittle_block_sprite = NULL;    
ALLEGRO_BITMAP *bomb_bitmap = NULL;
ALLEGRO_BITMAP *explosion_bitmap = NULL;
ALLEGRO_BITMAP *player_sprites = NULL;
ALLEGRO_BITMAP *enemy1_sprites = NULL;

GameState gs;

int initAllegro();
int initAssets();

void playLevel( int level_num );
void clearUp();

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
    clearUp();

    return 0;
}

int initAllegro()
{
    if( !al_init() )
    {
        fprintf( stderr, "Failed to initialize allegro!\n" );
        return -1;
    }

    display = al_create_display( SCREEN_WIDTH, SCREEN_HEIGHT );

    if( !display )
    {
        fprintf( stderr, "Failed to create display!\n" );
        return -2;
    }

    al_set_new_display_flags( ALLEGRO_WINDOWED );
    al_set_window_title( display, "BOMBERMAN" );
    al_set_window_position( display, 600, 300 );

    al_install_keyboard();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    return 0;
}

int validateAssets()
{
    if( font_big == NULL || font_small == NULL || font_vsmall == NULL ){
        fprintf(stderr, "Failed to load font!\n");
        return -3;
    }
    else if( solid_block_sprite == NULL ){
        fprintf(stderr, "Failed to load solid block bitmap!\n");
        return -4;
    }
    else if( brittle_block_sprite == NULL ){
        fprintf(stderr, "Failed to load brittle block bitmap!\n");
        return -5;
    }
    else if( bomb_bitmap == NULL ){
        fprintf(stderr, "Failed to load bomb bitmap!\n");
        return -6;
    }
    else if( explosion_bitmap == NULL ){
        fprintf(stderr, "Failed to load explosion bitmap!\n");
        return -7;
    }
    else if( player_sprites == NULL ){
        fprintf(stderr, "Failed to load player bitmap!\n");
        return -8;
    }
    else if( enemy1_sprites == NULL ){
        fprintf(stderr, "Failed to load enemy1 bitmap!\n");
        return -9;
    }
    return 0;
}

int initAssets()
{
    font_big = al_load_font( FONT_SRC, 40, 0 );
    font_small = al_load_font( FONT_SRC, 30, 0 );
    font_vsmall = al_load_font( FONT_SRC, 12, 0 );

    solid_block_sprite = al_load_bitmap( SOLID_BLOCK_SPRITES_SRC );
    brittle_block_sprite = al_load_bitmap( BRITTLE_BLOCK_SPRITES_SRC );    
    bomb_bitmap = al_load_bitmap( BOMB_SPRITES_SRC );
    explosion_bitmap = al_load_bitmap( EXPLOSION_SPRITES_SRC );
    player_sprites = al_load_bitmap( PLAYER_SPRITES_SRC );
    enemy1_sprites = al_load_bitmap( ENEMY1_SPRITES_SRC );

    return validateAssets();
}

void clearUp()
{
    al_destroy_bitmap( solid_block_sprite );
    al_destroy_bitmap( brittle_block_sprite );
    al_destroy_bitmap( bomb_bitmap );
    al_destroy_bitmap( explosion_bitmap );
    al_destroy_bitmap( player_sprites );
    al_destroy_bitmap( enemy1_sprites );
    al_destroy_font( font_big );
    al_destroy_font( font_small );
    al_destroy_display( display ); 
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

    Actor *player = createActor(0, 0, PLAYER_SPEED, player_sprites);
    applyCollisionToActor( player, CBX_PLAYER, CBY_PLAYER, CBW_PLAYER, CBH_PLAYER );

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

    Camera *camera = createCamera( player, level_map );


    enum LevelClearCondition clear_cond = KILL_ALL_ENEMIES;

    bool clean = true;
    bool map_update = false;
    bool won = false, sudden_exit = true;

    doTitleScreen( font_big, font_small, SCREEN_WIDTH/2, SCREEN_HEIGHT/2 - 75, level_num, clear_cond );

    updateLevelMapBitmap( level_map, solid_block_sprite, brittle_block_sprite, display );
    updateGFX( player, enemies, enemy_num, level_map, bomb_container, explosion_container, corpse_container );

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
            if( !isGamePaused( gs ) )
                handleGameInputKeyDown( events.keyboard.keycode, player, current_blast_range, bomb_bitmap, bomb_container, &gs );
            else
                handleMenuInputKeyDown( events.keyboard.keycode, pause_menu, &gs );
        }
        else if( events.type == ALLEGRO_EVENT_KEY_UP)
        {
            if( !isGamePaused( gs ) )
                handleGameInputKeyUp( events.keyboard.keycode, player);
        }

        if( isTakingGameStopFrame( gs ) ) {
            game_stop_frame = al_get_backbuffer( display );
            disableCamera( camera );
            signalNotTakingGameStopFrame( &gs );
        }

        if ( events.type == ALLEGRO_EVENT_TIMER )
        {   
            if( !isGamePaused( gs ) )
            {
                if( events.timer.source == game_timer )
                {
                    updatePlayer( player, level_map, enemies, enemy_num, explosion_container, corpse_container );
                    updateEnemies( ai_modules, enemy_num, explosion_container, corpse_container );

                    if( map_update )
                        updateLevelMapBitmap( level_map, solid_block_sprite, brittle_block_sprite, display );

                    updateCamera( camera );

                    signalRenderUpdate( &gs );  
                }

                if( events.timer.source == second_timer )
                {
                    updateContainers( bomb_container, explosion_container, corpse_container, level_map, enemies, enemy_num, explosion_bitmap, &map_update );
                    clean = areEmptyContainers( bomb_container, explosion_container, corpse_container );
                }
            }
            else
            {
                if( events.timer.source == game_timer )
                {
                    updateMenuBitmap( pause_menu, display );
                    signalRenderUpdate( &gs );
                }
            }
            
        }

        if( isRenderUpdate( gs ) )
        {
            if( !isGamePaused( gs ) )
                updateGFX( player, enemies, enemy_num, level_map, bomb_container, explosion_container, corpse_container );
            else
                updateGFXOnPause( game_stop_frame, pause_menu );

            signalRenderStop( &gs ); 
        }

        if( areAllEnemiesDead( enemies, enemy_num ) ) {
            signalEndingGame( &gs );
            sudden_exit = false;
            won = true;
        }
        else if( !player->alive ) {
            signalEndingGame( &gs );
            sudden_exit = false;
        }
    }

    if( !sudden_exit )
    {
        al_rest(1);
        disableCamera( camera );
        doEndScreen( font_big, SCREEN_WIDTH/2, SCREEN_HEIGHT/2 - 75, won );
    }

    al_destroy_event_queue( eq );
    al_destroy_timer( game_timer );
    al_destroy_timer( second_timer );
    destroyMenu( &pause_menu );
    destroyLevelMap( &level_map );
    destroyActor( &player );
    destroyPathArray( &enemy_paths );
    destroyActorArray( &enemies, enemy_num );
    destroyAIModuleArray( &ai_modules, enemy_num );
    destroyLevel( &level );
    destroyCamera( &camera );

    signalGoingToMainMenu( &gs );
    signalRenderUpdate( &gs );
}

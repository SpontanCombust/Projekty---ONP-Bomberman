#include "./headers/_game.h"

int main(void)
{
    if( !al_init() )
    {
        fprintf( stderr, "Failed to initialize allegro!\n" );
        return -1;
    }

    ALLEGRO_DISPLAY *display = al_create_display( SCREEN_WIDTH, SCREEN_HEIGHT );

    if( !display )
    {
        fprintf( stderr, "Failed to create display!\n" );
        return -1;
    }

    al_set_new_display_flags( ALLEGRO_WINDOWED );
    al_set_window_title( display, "BOMBERMAN" );
    al_set_window_position( display, 600, 300 );

    al_install_keyboard();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    
    ALLEGRO_FONT *font_big = al_load_font( FONT_SRC, 50, 0 );
    ALLEGRO_FONT *font_small = al_load_font( FONT_SRC, 30, 0 );

    ALLEGRO_EVENT_QUEUE *eq = al_create_event_queue();

    ALLEGRO_TIMER *game_timer = al_create_timer( 1.0 / FPS );
    ALLEGRO_TIMER *second_timer = al_create_timer( 1.0 / SECOND_TIMER );

    al_register_event_source( eq, al_get_keyboard_event_source() );
    al_register_event_source( eq, al_get_timer_event_source( game_timer ) );
    al_register_event_source( eq, al_get_timer_event_source( second_timer ) );
    al_register_event_source( eq, al_get_display_event_source( display ) );

    ALLEGRO_BITMAP *solid_block_sprite = al_load_bitmap( SOLID_BLOCK_SPRITES_SRC );
    ALLEGRO_BITMAP *brittle_block_sprite = al_load_bitmap( BRITTLE_BLOCK_SPRITES_SRC );    
    ALLEGRO_BITMAP *bomb_bitmap = al_load_bitmap( BOMB_SPRITES_SRC );
    ALLEGRO_BITMAP *explosion_bitmap = al_load_bitmap( EXPLOSION_SPRITES_SRC );
    ALLEGRO_BITMAP *player_sprites = al_load_bitmap( PLAYER_SPRITES_SRC );
    ALLEGRO_BITMAP *enemy_sprites = al_load_bitmap( ENEMY1_SPRITES_SRC );

    Actor *player = createActor(0, 0, PLAYER_SPEED, player_sprites);
    applyCollisionToActor( player, CBX_PLAYER, CBY_PLAYER, CBW_PLAYER, CBH_PLAYER );

    Level *level = createLevel( 1, enemy_sprites );

    LevelMap *level_map = level->level_map;
    int enemy_num = level->enemy_intit_count;
    Path * enemy_paths = level->enemy_paths;
    Actor * *enemies = level->enemies;
    applyCollisionToActorArray( enemies, enemy_num, CBX_ENEMY1, CBY_ENEMY1, CBW_ENEMY1, CBH_ENEMY1 );
    AIModule * *ai_modules = level->ai_modules;
    
    updateLevelMapBitmap( level_map, solid_block_sprite, brittle_block_sprite, display );

    Bomb *bomb_container[ BOMB_BUDGET ] = { NULL };
    SFX *explosion_container[ EXPLOSION_BUDGET ] = { NULL };
    SFX *corpse_container[ CORPSE_BUDGET ] = { NULL };

    enum LevelClearCondition clear_cond = KILL_ALL_ENEMIES;

    bool done = false, clean = true;
    bool render = false, map_update = false;
    bool won = false;

    doTitleScreen( font_big, font_small, SCREEN_WIDTH/2, SCREEN_HEIGHT/2 - 75, 1, clear_cond );

    updateGFX( player, enemies, enemy_num, level_map, bomb_container, explosion_container, corpse_container );
    al_start_timer( game_timer );
    al_start_timer( second_timer );

    while( !done || !clean )
    {
        ALLEGRO_EVENT events;
        al_wait_for_event( eq, &events );

        if ( events.type == ALLEGRO_EVENT_DISPLAY_CLOSE )
        {
            done = true;
        }
        else if ( events.type == ALLEGRO_EVENT_TIMER )
        {
            if( events.timer.source == game_timer )
                render = true;  

            if( events.timer.source == second_timer )
            {
                updateContainers( bomb_container, explosion_container, corpse_container, level_map, enemies, enemy_num, explosion_bitmap, &map_update );
                clean = areEmptyContainers( bomb_container, explosion_container, corpse_container );
            }
        }
        else if( events.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            handleMovementInputKeyDown( events.keyboard.keycode, player, &done );

            Bomb *bomb = NULL;
            handleBombInputKeyDown( events.keyboard.keycode, player, &bomb);

            if( bomb != NULL)
            {
                setBombProperties( bomb, DEFAULT_FUSE, DEFAULT_BLAST_RANGE, bomb_bitmap );
                addBombToContainer( bomb_container, BOMB_BUDGET, bomb );
            }
        }
        else if( events.type == ALLEGRO_EVENT_KEY_UP)
        {
            handleMovementInputKeyUp( events.keyboard.keycode, player);
        }  

        if(render)
        {
            updatePlayer( player, level_map, enemies, enemy_num, explosion_container, corpse_container );
            updateEnemies( ai_modules, enemy_num, explosion_container, corpse_container );

            if( map_update )
                updateLevelMapBitmap( level_map, solid_block_sprite, brittle_block_sprite, display );

            updateGFX( player, enemies, enemy_num, level_map, bomb_container, explosion_container, corpse_container );

            render = false;
        }

        if( areAllEnemiesDead( enemies, enemy_num ) )
        {
            done = true;
            won = true;
        }
        else if( !player->alive )
        {
            done = true;
        }
    }
    al_rest(1);
    doEndScreen( font_big, SCREEN_WIDTH/2, SCREEN_HEIGHT/2 - 75, won );

    destroyLevelMap( &level_map );
    destroyActor( &player );
    destroyPathArray( &enemy_paths );
    destroyActorArray( &enemies, enemy_num );
    destroyAIModuleArray( &ai_modules, enemy_num );
    destroyLevel( &level );
    al_destroy_bitmap( solid_block_sprite );
    al_destroy_bitmap( brittle_block_sprite );
    al_destroy_bitmap( bomb_bitmap );
    al_destroy_bitmap( explosion_bitmap );
    al_destroy_bitmap( player_sprites );
    al_destroy_bitmap( enemy_sprites );
    al_destroy_font( font_big );
    al_destroy_font( font_small );
    al_destroy_event_queue( eq );
    al_destroy_timer( game_timer );
    al_destroy_timer( second_timer );
    al_destroy_display( display );
    
    return 0;
}

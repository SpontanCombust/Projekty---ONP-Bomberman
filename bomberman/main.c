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

    ALLEGRO_EVENT_QUEUE *eq = al_create_event_queue();

    ALLEGRO_TIMER *game_timer = al_create_timer( 1.0 / FPS );
    ALLEGRO_TIMER *second_timer = al_create_timer( 1.0 / SECOND_TIMER );

    al_register_event_source( eq, al_get_keyboard_event_source() );
    al_register_event_source( eq, al_get_timer_event_source( game_timer ) );
    al_register_event_source( eq, al_get_timer_event_source( second_timer ) );
    al_register_event_source( eq, al_get_display_event_source( display ) );

    ALLEGRO_BITMAP *solid_block_sprite = al_load_bitmap( "./sprites/solid_block.png" );
    ALLEGRO_BITMAP *brittle_block_sprite = al_load_bitmap( "./sprites/brittle_block.png" );    
    ALLEGRO_BITMAP *bomb_bitmap = al_load_bitmap( "./sprites/bomb.png" );
    ALLEGRO_BITMAP *explosion_bitmap = al_load_bitmap( "./sprites/explosion.png" );
    ALLEGRO_BITMAP *player_sprites = al_load_bitmap( "./sprites/player_sheet.png" );
    // ALLEGRO_BITMAP *player_sprites = al_load_bitmap("./sprites/debug_bomberclone_sprites_with_bounding_box.png");

    LevelMap *level_map = createLevelMap( "./levels/test_map.txt" );
    updateLevelMapBitmap( level_map, solid_block_sprite, brittle_block_sprite, display );

    Actor *player = createActor(0, 0, PLAYER_SPEED, DOWN, player_sprites);

    Bomb * bomb_container[ BOMB_BUDGET ] = { NULL };
    SFX * sfx_container[ SFX_BUDGET ] = { NULL };

    bool done = false, render = false, map_update = false; 

    updateGFX( player, level_map ,bomb_container, sfx_container );
    
    al_start_timer( game_timer );
    al_start_timer( second_timer );

    while( !done )
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
                updateContainers( bomb_container, sfx_container, level_map, explosion_bitmap, &map_update );
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

        resolveDirection( player );

        if(render)
        {
            updatePlayerPosition( player, level_map );
            
            if( map_update )
                updateLevelMapBitmap( level_map, solid_block_sprite, brittle_block_sprite, display );

            updateGFX( player, level_map, bomb_container, sfx_container );

            render = false;
        }
    }
    
    destroyLevelMap( &level_map );
    destroyActor( &player );
    al_destroy_bitmap( solid_block_sprite );
    al_destroy_bitmap( brittle_block_sprite );
    al_destroy_bitmap( player_sprites );
    al_destroy_bitmap( bomb_bitmap );
    al_destroy_bitmap( explosion_bitmap );
    al_destroy_event_queue( eq );
    al_destroy_timer( game_timer );
    al_destroy_timer( second_timer );
    al_destroy_display( display );
    
    return 0;
}

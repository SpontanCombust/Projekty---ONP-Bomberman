#include "../../headers/_game.h"

int initAllegro( void )
{
    if( !al_init() )
    {
        fprintf( stderr, "Failed to initialize allegro!\n" );
        return -1;
    }

    al_set_new_display_flags( ALLEGRO_WINDOWED );
    display = al_create_display( SCREEN_WIDTH, SCREEN_HEIGHT );

    if( !display )
    {
        fprintf( stderr, "Failed to create display!\n" );
        return -2;
    }

    al_set_window_title( display, "BOMBERMAN" );
    al_set_window_position( display, 600, 300 );

    al_install_keyboard();
    al_init_primitives_addon();
    al_init_native_dialog_addon();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    return 0;
}

int initAssets( void )
{
    font_big = al_load_font( FONT_SRC, 40, 0 );
    font_small = al_load_font( FONT_SRC, 30, 0 );
    font_vsmall = al_load_font( FONT_SRC, 12, 0 );

    solid_block_sprite = al_load_bitmap( SOLID_BLOCK_SPRITES_SRC );
    brittle_block_sprite = al_load_bitmap( BRITTLE_BLOCK_SPRITES_SRC );    
    bomb_sprite = al_load_bitmap( BOMB_SPRITES_SRC );
    explosion_sprite = al_load_bitmap( EXPLOSION_SPRITES_SRC );
    player_sprites = al_load_bitmap( PLAYER_SPRITES_SRC );
    enemy1_sprites = al_load_bitmap( ENEMY1_SPRITES_SRC );

    return validateAssets();
}

int validateAssets( void )
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
    else if( bomb_sprite == NULL ){
        fprintf(stderr, "Failed to load bomb bitmap!\n");
        return -6;
    }
    else if( explosion_sprite == NULL ){
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

void clearUp( void )
{
    al_destroy_bitmap( solid_block_sprite );
    al_destroy_bitmap( brittle_block_sprite );
    al_destroy_bitmap( bomb_sprite );
    al_destroy_bitmap( explosion_sprite );
    al_destroy_bitmap( player_sprites );
    al_destroy_bitmap( enemy1_sprites );
    al_destroy_font( font_big );
    al_destroy_font( font_small );
    al_destroy_font( font_vsmall );
    al_destroy_display( display ); 

    al_uninstall_keyboard();
    al_shutdown_native_dialog_addon();
    al_shutdown_image_addon();
    al_shutdown_font_addon();
    al_shutdown_ttf_addon();
}
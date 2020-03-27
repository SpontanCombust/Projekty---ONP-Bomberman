#include "./headers/sprite_properties.h"
#include "./headers/direction.h"
#include "./headers/entity.h"
#include "./headers/level_utilities.h"
#include "./headers/logic_handlers.h"

#include <stdio.h>
#include <stdbool.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#define SCREEN_HEIGHT 480
#define SCREEN_WIDTH 672
#define FPS 60.0

#define SPEED 3


void updatePlayerMovement( Entity *player, int **map, bool vx[2], bool vy[2] )
{
    enum Direction cdir;

    updateMovementX(player, vx, SPEED);
    if( isOutOfBounds( player, &cdir, SCREEN_WIDTH, SCREEN_HEIGHT, CBX_PLAYER, CBY_PLAYER, CBW_PLAYER, CBH_PLAYER ) )
        handleOutOfBounds( player, cdir, SCREEN_WIDTH, SCREEN_HEIGHT, CBX_PLAYER, CBY_PLAYER, CBW_PLAYER, CBH_PLAYER );
    else if( isTerrainCollisionX( player, &cdir, map, CBX_PLAYER, CBY_PLAYER, CBW_PLAYER, CBH_PLAYER ) )
        handleTerrainCollision( player, cdir, map, CBX_PLAYER, CBY_PLAYER, CBW_PLAYER, CBH_PLAYER );

    updateMovementY( player, vy, SPEED );
    if( isOutOfBounds( player, &cdir, SCREEN_WIDTH, SCREEN_HEIGHT, CBX_PLAYER, CBY_PLAYER, CBW_PLAYER, CBH_PLAYER ) )
        handleOutOfBounds( player, cdir, SCREEN_WIDTH, SCREEN_HEIGHT, CBX_PLAYER, CBY_PLAYER, CBW_PLAYER, CBH_PLAYER );
    else if( isTerrainCollisionY( player, &cdir, map, CBX_PLAYER, CBY_PLAYER, CBW_PLAYER, CBH_PLAYER ) )
        handleTerrainCollision( player, cdir, map, CBX_PLAYER, CBY_PLAYER, CBW_PLAYER, CBH_PLAYER );
}

void updateGFX( Entity *player, enum Direction dir, ALLEGRO_BITMAP *map_bitmap)
{
    al_clear_to_color(al_map_rgb(0, 150, 0));
    al_draw_bitmap(map_bitmap, 0, 0, 0);
    al_draw_bitmap_region(player->bmp, dir * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE, player->x, player->y, 0);
    al_flip_display();
}

int main(void)
{
    if (!al_init())
    {
        fprintf(stderr, "Failed to initialize allegro!\n");
        return -1;
    }

    ALLEGRO_DISPLAY *display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);

    if (!display)
    {
        fprintf(stderr, "Failed to create display!\n");
        return -1;
    }

    al_set_new_display_flags(ALLEGRO_WINDOWED);
    al_set_window_title(display, "BOMBERMAN");
    al_set_window_position(display, 600, 300);

    al_install_keyboard();
    al_init_image_addon();

    ALLEGRO_EVENT_QUEUE *eq = al_create_event_queue();
    ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);

    al_register_event_source( eq, al_get_keyboard_event_source() );
    al_register_event_source( eq, al_get_timer_event_source( timer ) );
    al_register_event_source( eq, al_get_display_event_source( display ) );

    ALLEGRO_BITMAP *solid_block_sprite = al_load_bitmap("./sprites/solid_block.png");
    ALLEGRO_BITMAP *brittle_block_sprite = al_load_bitmap("./sprites/brittle_block.png");    
    
    int **map = createLevelTileMatrix("./levels/test_map.txt", 15, 21);

    ALLEGRO_BITMAP *map_bitmap = al_create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
    generateMapBitmap(map, 15, 21, map_bitmap, solid_block_sprite, brittle_block_sprite, display);
    
    // ALLEGRO_BITMAP *player_sprites = al_load_bitmap("./sprites/player_sheet.png");
    ALLEGRO_BITMAP *player_sprites = al_load_bitmap("./sprites/debug_bomberclone_sprites_with_bounding_box.png");
    Entity player;
    initEntity(&player, 0, 0, player_sprites);

    bool vx[2] = {false, false};
    bool vy[2] = {false, false};
    enum Direction dir = DOWN;
    /*
             | vy[0]
             |
    vx[0]----0---> vx[1]
             |
            \/ vy[1]
    */
    

    bool done = false, render = false;

    updateGFX(&player, dir, map_bitmap);
    
    al_start_timer( timer );

    // petla gry
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
            render = true;  
        }
        else if( events.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            handleEventKeyDown(events.keyboard.keycode, vx, vy, &done);
        }
        else if( events.type == ALLEGRO_EVENT_KEY_UP)
        {
            handleEventKeyUp(events.keyboard.keycode, vx, vy);
        }  

        resolveDirection( &dir, vx, vy );

        if(render)
        {
            updatePlayerMovement( &player, map, vx, vy );
            updateGFX(&player, dir, map_bitmap);

            render = false;
        }
    }
    
    freeMap(map, 15);
    al_destroy_bitmap(map_bitmap);
    al_destroy_bitmap(solid_block_sprite);
    al_destroy_bitmap(brittle_block_sprite);
    al_destroy_bitmap(player_sprites);
    al_destroy_event_queue(eq);
    al_destroy_timer(timer);
    al_destroy_display(display);
    
    return 0;
}

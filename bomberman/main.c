#include "./headers/level_utilities.h"
#include "./headers/logic_handlers.h"
#include "./headers/entity.h"

#include <stdio.h>
#include <stdbool.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#define SCREEN_HEIGHT 480
#define SCREEN_WIDTH 640
#define FPS 60.0

#define SPEED 2

void updateGFX( Entity *player, enum Direction dir, ALLEGRO_BITMAP *map_bitmap)
{
    al_clear_to_color(al_map_rgb(0, 150, 0));
    al_draw_bitmap(map_bitmap, 0, 0, 0);
    al_draw_bitmap_region(player->bmp, dir * 32, 0, 32, 32, player->x, player->y, 0);
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
    
    int **map = NULL;
    map = createLevelTileMatrix("./levels/test_map.txt", 15, 20, map);
    ALLEGRO_BITMAP *map_bitmap = al_create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
    generateMapBitmap(map, 15, 20, map_bitmap, solid_block_sprite, brittle_block_sprite, display);

    ALLEGRO_BITMAP *player_sprites = al_load_bitmap("./sprites/player_sheet.png");
    Entity player;
    initEntity(&player, 100, 100, player_sprites);

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
    

    bool done = false, draw = false;

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
            draw = true;  
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

        if(draw)
        {
            updateMovement(&player, vx, vy, SPEED);
            updateGFX(&player, dir, map_bitmap);
            // wazne, by "draw" ustawiac na false po kazdym zwroceniu bufora, by nie marnowac zasobow na nadmierne renderowanie
            // aktualne tylko w przypadku, gdy nic nie porusza sie na ekranie 
            draw = false;
        }
    }
    
    free(map);
    al_destroy_bitmap(map_bitmap);
    al_destroy_bitmap(solid_block_sprite);
    al_destroy_bitmap(brittle_block_sprite);
    al_destroy_bitmap(player_sprites);
    al_destroy_event_queue(eq);
    al_destroy_timer(timer);
    al_destroy_display(display);
    
    return 0;
}

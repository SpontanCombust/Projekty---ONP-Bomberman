#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#define SCREEN_HEIGHT 480
#define SCREEN_WIDTH 640
#define R 50

int main(int argc, char *argv[])
{

    if (!al_init())
    {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }

    ALLEGRO_DISPLAY *display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);

    if (!display)
    {
        fprintf(stderr, "failed to create display!\n");
        return -1;
    }

    al_set_new_display_flags(ALLEGRO_WINDOWED);
    al_set_window_title(display, "BOMBERMAN");
    al_set_window_position(display, 600, 300);

    al_init_primitives_addon();
    al_install_keyboard();

    ALLEGRO_EVENT_QUEUE *eq = al_create_event_queue();
    ALLEGRO_TIMER *timer = al_create_timer(1.0 / 60.0);
    ALLEGRO_KEYBOARD_STATE keyState;

    al_register_event_source( eq, al_get_keyboard_event_source() );
    al_register_event_source( eq, al_get_timer_event_source( timer ) );
    al_register_event_source( eq, al_get_display_event_source( display ) );


    bool done = false, draw = false;

    al_start_timer( timer );

    while( !done )
    {
        ALLEGRO_EVENT event;
        al_wait_for_event( eq, &event );

        if ( event.type == ALLEGRO_EVENT_DISPLAY_CLOSE )
            done = true;

        else if ( event.type == ALLEGRO_EVENT_TIMER )
        {
            al_get_keyboard_state( &keyState );

            draw = true;
        }

        if ( draw )
        {

        }    
    }

    al_destroy_event_queue(eq);
    al_destroy_timer(timer);
    al_destroy_display(display);

    return 0;
}

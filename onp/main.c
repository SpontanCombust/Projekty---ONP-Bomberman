#include "onp.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include "allegro_data.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

int main()
{
    if( al_init() == NULL ) {
        fprintf( stderr, "Failed to initialize Allegro!\n" );
        return -1;
    }

    al_set_new_display_flags( ALLEGRO_WINDOWED );
    ALLEGRO_DISPLAY *display = al_create_display( SCRREN_W, SCREEN_H );
    if( display == NULL ) {
        fprintf( stderr, "Failed to create display!\n" );
        return -1;
    }
    al_set_window_title( display, "ONP" );
    al_set_window_position( display, 600, 300 );

    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_keyboard();
    al_install_mouse();

    ALLEGRO_EVENT_QUEUE *eq = al_create_event_queue();
    al_register_event_source( eq, al_get_keyboard_event_source() );
    al_register_event_source( eq, al_get_mouse_event_source() );
    // char input[20];
    // puts( "Enter Reverse Polish Notation of max. length of 20:" );
    // scanf("%21[^\n]s", input );
    // // Sprawdzenie czy wprowadzany ciag ma powyzej 20 znakow
    // if( strlen( input ) > 20 )
    // {
    //     printf( "Given input is too long!!!" );
    //     return -1;
    // }
    // printf("The result is: %f", get_ONP_result( input , show_steps() ) );

    return 0;
}


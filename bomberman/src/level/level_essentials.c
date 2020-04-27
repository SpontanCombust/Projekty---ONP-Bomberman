#include "../../headers/level.h"

void doTitleScreen( ALLEGRO_FONT *font_big, ALLEGRO_FONT *font_small, float x, float y, int level_number, LevelClearCondition condition )
{
    al_clear_to_color( al_map_rgb( 0, 0, 0 ) );
    al_draw_textf( font_big, al_map_rgb( 255, 255, 255 ), x, y, ALLEGRO_ALIGN_CENTER, "LEVEL %d", level_number );
    al_flip_display();
    al_rest( 2 );
    al_clear_to_color( al_map_rgb( 0, 0, 0 ) );
    if( condition == KILL_ALL_ENEMIES )
        al_draw_text( font_small, al_map_rgb( 255, 255, 255 ), x, y + 10, ALLEGRO_ALIGN_CENTER, "KILL ALL ENEMIES!!!" );
    al_flip_display();
    al_rest( 2 );
}

void doEndScreen( ALLEGRO_FONT *font, float x, float y, bool won )
{
    al_clear_to_color( al_map_rgb( 0, 0, 0 ) );

    if( won )
        al_draw_text( font, al_map_rgb( 255, 255, 255 ), x, y, ALLEGRO_ALIGN_CENTER, "YOU'VE WON!" );
    else
        al_draw_text( font, al_map_rgb( 255, 255, 255 ), x, y, ALLEGRO_ALIGN_CENTER, "GAME OVER!" );

    al_flip_display();
    al_rest( 3 );
}

void destroyLevel( Level **level )
{
    free( *level );
    *level = NULL;
}
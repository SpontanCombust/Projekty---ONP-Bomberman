#include "../../headers/level.h"

#include "../../headers/_game_rules.h"

void doTitleScreen( ALLEGRO_FONT *font_big, ALLEGRO_FONT *font_small, float x, float y, char *level_id, LevelClearCondition condition )
{
    al_clear_to_color( COLOR_BLACK );
    al_draw_textf( font_big, COLOR_WHITE, x, y, ALLEGRO_ALIGN_CENTER, "LEVEL %s", level_id );
    al_flip_display();
    al_rest( 2 );

    al_clear_to_color( COLOR_BLACK );
    if( condition == KILL_ALL_ENEMIES )
        al_draw_text( font_small, COLOR_WHITE, x, y + 10, ALLEGRO_ALIGN_CENTER, "KILL ALL ENEMIES!!!" );
    else if( condition == KILL_OPPONENT )
        al_draw_text( font_small, COLOR_WHITE, x, y + 10, ALLEGRO_ALIGN_CENTER, "KILL YOUR OPPONENT!!!" );

    al_flip_display();
    al_rest( 2 );
}

void doEndScreen( ALLEGRO_FONT *font, float x, float y, bool won, char player_id, LevelClearCondition condition )
{
    al_clear_to_color( COLOR_BLACK );

    if( won )
        if( condition != KILL_OPPONENT )
            al_draw_text( font, COLOR_WHITE, x, y, ALLEGRO_ALIGN_CENTER, "YOU'VE WON!" );
        else
            al_draw_textf( font, COLOR_WHITE, x, y, ALLEGRO_ALIGN_CENTER, "PLAYER %c WON!", player_id );
    else
        if( condition != KILL_OPPONENT )
            al_draw_text( font, COLOR_WHITE, x, y, ALLEGRO_ALIGN_CENTER, "GAME OVER!" );
        else
            al_draw_text( font, COLOR_WHITE, x, y, ALLEGRO_ALIGN_CENTER, "DRAW!" );

    al_flip_display();
    al_rest( 3 );
}

void destroyLevel( Level **level )
{
    free( *level );
    *level = NULL;
}
#include "button.h"

#include <string.h>
#include <allegro5/allegro_primitives.h>

void setButton( Button *btn, float x, float y, float w, float h, char text[BTN_TEXT_LENGTH] )
{
    btn->x = x;
    btn->y = y;
    btn->w = w;
    btn->h = h;
    strcpy( btn->text, text );
    btn->bmp = al_create_bitmap( w, h );
}

void updateButtonBmp( Button *btn )
{
    al_set_target_bitmap( btn->bmp );
    al_clear_to_color( BUTTON_FILL_COLOR );
    al_draw_line( 0, 0, btn->w - 1, 0, BUTTON_BORDER_COLOR, BUTTON_BORDER_THICKNESS );
    al_draw_line( 0, 0, 0, btn->h - 1, BUTTON_BORDER_COLOR, BUTTON_BORDER_THICKNESS );
    al_draw_line( btn->w - 1, 0, btn->w - 1, btn->h - 1, BUTTON_BORDER_COLOR, BUTTON_BORDER_THICKNESS );
    al_draw_line( 0, btn->h - 1, btn->w - 1, btn->h - 1, BUTTON_BORDER_COLOR, BUTTON_BORDER_THICKNESS );
}

void drawButton( Button btn ) {
    al_draw_bitmap( btn.bmp, btn.x, btn.y, 0 );
}

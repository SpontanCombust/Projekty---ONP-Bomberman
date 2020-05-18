#include "label.h"

void setLabel( Label *label, float x, float y, ALLEGRO_FONT *font, char text[LABEL_TEXT_LENGTH] )
{
    label->x = x;
    label->y = y;
    label->font = font;
    strcpy( label->text, text );
}

void drawLabel( Label label ) {
    al_draw_text( label.font, al_map_rgb( 0, 0, 0 ), label.x, label.y, 0, label.text );
}
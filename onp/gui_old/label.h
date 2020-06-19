#ifndef __LABEL_H
#define __LABEL_H

#include "../allegro_data.h"
#include <allegro5/allegro_font.h>

typedef struct
{
    float x, y;
    ALLEGRO_FONT *font;
    char text[LABEL_TEXT_LENGTH];
    
} Label;

void setLabel( Label *label, float x, float y, ALLEGRO_FONT *font, char text[LABEL_TEXT_LENGTH] );
void drawLabel( Label label );

#endif
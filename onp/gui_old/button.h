#ifndef __BUTTON_H
#define __BUTTON_H

#include <allegro5/allegro.h>
#include "../allegro_data.h"

typedef struct
{
    float x, y, w, h;
    char text[BTN_TEXT_LENGTH];
    ALLEGRO_BITMAP *bmp;

} Button;

void setButton( Button *btn, float x, float y, float w, float h, char text[BTN_TEXT_LENGTH] );
void updateButtonBmp( Button *btn );
void drawButton( Button btn );

void setCalculatorButtons( Button btns[ BUTTONS_NUMBER ] );

#endif
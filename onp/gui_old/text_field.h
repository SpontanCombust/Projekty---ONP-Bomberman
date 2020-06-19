#ifndef __TEXT_FIELD_H
#define __TEXT_FIELD_H

#include <stdbool.h>
#include <allegro5/allegro_font.h>

typedef struct
{
    float x, y, w, h;
    bool writable;
    ALLEGRO_FONT *font;

} TextField;

#endif
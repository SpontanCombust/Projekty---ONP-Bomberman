#include "../headers/entity.h"

void initEntity(Entity *entity, int x, int y, ALLEGRO_BITMAP *bmp)
{
    entity -> x = x;
    entity -> y = y;
    entity -> bmp = bmp;
}
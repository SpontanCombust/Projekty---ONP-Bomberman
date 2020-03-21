#ifndef ENTITY_H
#define ENTITY_H

#include <allegro5/allegro.h>

struct SEntity {
    int x, y;
    ALLEGRO_BITMAP *bmp;
};
typedef struct SEntity Entity; 

void initEntity(Entity *entity, int x, int y, ALLEGRO_BITMAP *bmp);

#endif
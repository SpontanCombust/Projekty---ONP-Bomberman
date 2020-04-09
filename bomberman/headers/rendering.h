#ifndef RENDERING_H
#define RENDERING_H

#include "_game_rules.h"
#include "sprite_properties.h"
#include "bomb.h"
#include "sfx.h"
#include "actor.h"
#include "ai.h"
#include <allegro5/allegro5.h>


// ======================== rendering.c =======================

void drawBombs( Bomb *bomb_container[] );
void drawSFX( SFX *sfx_container[], enum SFXType type );
void drawPlayer( Actor *player );
void drawEnemies( AIModule * *modules, int enemy_num );

#endif
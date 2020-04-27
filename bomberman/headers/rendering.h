#ifndef RENDERING_H
#define RENDERING_H

#include "_game_rules.h"
#include "sprite_properties.h"
#include "bomb.h"
#include "sfx.h"
#include "actor.h"
#include "ai.h"
#include "level_map.h"
#include "menus.h"
#include <allegro5/allegro5.h>


// ======================== rendering.c =======================

void drawBombs( Bomb *bomb_container[] );
void drawSFX( SFX *sfx_container[] );
void drawActor( Actor *actor );
void drawLevelMap( LevelMap *level_map );
void drawMenu( Menu *menu );

#endif
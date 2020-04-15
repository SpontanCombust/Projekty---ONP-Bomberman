#include "../../headers/player_input.h"

#include "../../headers/_game_rules.h"
#include "../../headers/logic.h"

void handleInputKeyDown( char keyboard_keycode, Actor *player, int bomb_blast_range, ALLEGRO_BITMAP *bomb_bmp, Bomb *bomb_container[], bool *done )
{
    switch ( keyboard_keycode )
    {
        case ALLEGRO_KEY_UP:
            updateVelocityY( player, true, player->vy[1] );
            break;
        case ALLEGRO_KEY_DOWN:
            updateVelocityY( player, player->vy[0], true );
            break;
        case ALLEGRO_KEY_LEFT:
            updateVelocityX( player, true, player->vx[1] );
            break;
        case ALLEGRO_KEY_RIGHT:
            updateVelocityX( player, player->vx[0], true );
            break;
        case ALLEGRO_KEY_SPACE: ;   // srednik by zapobiec bledowi z tworzeniem deklaracji po etykiecie 'case'
            Bomb *bomb = createEmptyBombAtActor( player );
            setBombProperties( bomb, DEFAULT_FUSE, bomb_blast_range, bomb_bmp );
            addBombToContainer( bomb_container, BOMB_BUDGET, bomb );
            break;
        case ALLEGRO_KEY_ESCAPE:
            *done = true;
            break;
    }
}

void handleInputKeyUp( char keyboard_keycode, Actor *player )
{
    switch ( keyboard_keycode )
    {
        case ALLEGRO_KEY_UP:
            updateVelocityY( player, false, player->vy[1] );
            break;
        case ALLEGRO_KEY_DOWN:
            updateVelocityY( player, player->vy[0], false );
            break;
        case ALLEGRO_KEY_LEFT:
            updateVelocityX( player, false, player->vx[1] );
            break;
        case ALLEGRO_KEY_RIGHT:
            updateVelocityX( player, player->vx[0], false );
            break;
    }
}
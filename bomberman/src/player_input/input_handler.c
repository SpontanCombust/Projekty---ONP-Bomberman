#include "../../headers/player_input.h"

#include "../../headers/_game_rules.h"
#include "../../headers/logic.h"

static void retrieveInput( InputScheme is, char *down, char *up, char *left, char *right, char *bomb )
{
    if( is == STANDARD )
        *up = ALLEGRO_KEY_UP, *down = ALLEGRO_KEY_DOWN, *left = ALLEGRO_KEY_LEFT, *right = ALLEGRO_KEY_RIGHT, *bomb = ALLEGRO_KEY_SPACE ;
    else if( is == ALTERNATIVE )
        *up = ALLEGRO_KEY_W, *down = ALLEGRO_KEY_S, *left = ALLEGRO_KEY_A, *right = ALLEGRO_KEY_D, *bomb = ALLEGRO_KEY_LCTRL;
}

void handleGameInputKeyDown( char keyboard_keycode, InputScheme is, Actor *player, int bomb_blast_range, ALLEGRO_BITMAP *bomb_bmp, Bomb *bomb_container[], GameState *gs )
{
    char down = 0, up = 0, left = 0, right = 0, bomb = 0;
    retrieveInput( is, &down, &up, &left, &right, &bomb );

    if      ( keyboard_keycode == down  )   updateVelocityY( player, player->vy[0], true );
    else if ( keyboard_keycode == up    )   updateVelocityY( player, true, player->vy[1] );
    else if ( keyboard_keycode == left  )   updateVelocityX( player, true, player->vx[1] );
    else if ( keyboard_keycode == right )   updateVelocityX( player, player->vx[0], true );
    else if ( keyboard_keycode == bomb  ) {
        Bomb *bomb = createEmptyBombAtActor( player );
        setBombProperties( bomb, DEFAULT_FUSE, bomb_blast_range, bomb_bmp );
        addBombToContainer( bomb_container, BOMB_BUDGET, bomb ); 
    }
    else if ( keyboard_keycode == ALLEGRO_KEY_ESCAPE || keyboard_keycode == ALLEGRO_KEY_P ) {
        signalPausingGame( gs );
        signalMenuUpdate( gs );
    }
}

void handleGameInputKeyUp( char keyboard_keycode, InputScheme is, Actor *player )
{
    char down = 0, up = 0, left = 0, right = 0, bomb = 0;
    retrieveInput( is, &down, &up, &left, &right, &bomb );

    if      ( keyboard_keycode == down  )   updateVelocityY( player, player->vy[0], false );
    else if ( keyboard_keycode == up    )   updateVelocityY( player, false, player->vy[1] );
    else if ( keyboard_keycode == left  )   updateVelocityX( player, false, player->vx[1] );
    else if ( keyboard_keycode == right )   updateVelocityX( player, player->vx[0], false );
}

void handleMenuInputKeyDown( char keyboard_keycode, Menu *menu, GameState *gs )
{
    switch ( keyboard_keycode )
    {
        case ALLEGRO_KEY_DOWN:
            updateCurrentlySelectedEntry( menu, 1 );
            signalMenuUpdate( gs );
            break;
        case ALLEGRO_KEY_UP:
            updateCurrentlySelectedEntry( menu, -1 );
            signalMenuUpdate( gs );
            break;
        case ALLEGRO_KEY_LEFT:
            executeLeftOperation( menu, gs );
            signalMenuUpdate( gs );
            break;
        case ALLEGRO_KEY_RIGHT:
            executeRightOperation( menu, gs );
            signalMenuUpdate( gs );
            break;
        case ALLEGRO_KEY_ENTER:
            executeSelectOperation( menu, gs );
            signalMenuUpdate( gs );
            break;
        case ALLEGRO_KEY_ESCAPE:
            executeEscOperation( menu, gs );
            signalMenuUpdate( gs );
            break;
    }
}
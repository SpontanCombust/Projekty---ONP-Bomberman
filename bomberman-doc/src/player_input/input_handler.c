/** @file input_handler.c 
 * 
 * @brief Zawiera metody do obslugi wejść użytkownika
 * 
 * Zawiera metody obsługi wejść z klawiatury odpowiednio dla obecności w menu \n
 * jak i w trakcie rozgrywki.
 * 
 * @author  Przemysław Cedro
 * @date    2020.05.19
*/


#include "../../headers/player_input.h"

#include "../../headers/_game_rules.h"
#include "../../headers/logic.h"

/** @brief Ustawia odpowiedni input dla akcji
 * 
 * Ustawia odpowiedni input dla akcji w menu i podczas rozgrywki w zależnosci od podanego schematu wejścia. \n
 * Schemat STANDARD: GÓRA, DÓŁ, LEWO, PRAWO, SPACJA \n
 * Schemat ALTERNATIVE: W, S, A, D, LCtrl \n
 * 
 * @param is    schemat sterowania wskazujący na dany zestaw wejść z klawiatury
 * @param down  wskaźnik na wartość klawisza odpowiadającemu akcji 'na dól'
 * @param up    wskaźnik na wartość klawisza odpowiadającemu akcji 'w górę'
 * @param left  wskaźnik na wartość klawisza odpowiadającemu akcji 'w lewo'
 * @param right wskaźnik na wartość klawisza odpowiadającemu akcji 'w prawo'
 * @param bomb  wskaźnik na wartość klawisza odpowiadającemu akcji 'podlóż bombę'
*/
static void retrieveInput( InputScheme is, char *down, char *up, char *left, char *right, char *bomb )
{
    if( is == STANDARD )
        *up = ALLEGRO_KEY_UP, *down = ALLEGRO_KEY_DOWN, *left = ALLEGRO_KEY_LEFT, *right = ALLEGRO_KEY_RIGHT, *bomb = ALLEGRO_KEY_SPACE ;
    else if( is == ALTERNATIVE )
        *up = ALLEGRO_KEY_W, *down = ALLEGRO_KEY_S, *left = ALLEGRO_KEY_A, *right = ALLEGRO_KEY_D, *bomb = ALLEGRO_KEY_LCTRL;
}

/** @brief Obsługuje naciśnięcie danego klawisza w trakcie rozgrywki
 * 
 * Podejmuje odpowiednie akcje w zależności od naciśnięcia i trzymania danego przycisku klawiatury \n
 * w trakcie przechodzenia poziomu. Odpowiednio wysyła komendy o zmiane wektorów predkości, \n
 * podłożeniu bomby lub zapauzowaniu gry.
 * 
 * @param keyboard_keycode  kod klawisza zdefiniowany przez bibliotekę Allegro
 * @param is                schemat sterowania wskazujący na dany zestaw wejść z klawiatury
 * @param player            wskaźnik na aktora danego gracza
 * @param bomb_blast_range  zasięg wybuchu bomby dla danego gracza
 * @param bomb_bmp          bitmapa bomby, którą ta ma użyć
 * @param bomb_container    tablica wskaźników na bomby
 * @param gs                stan gry                   
*/
void handleGameInputKeyDown( char keyboard_keycode, InputScheme is, Actor *player, int bomb_blast_range, ALLEGRO_BITMAP *bomb_bmp, Bomb *bomb_container[], GameState *gs )
{
    if( player != NULL && isActorAlive( player ) )
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
            addBombToContainer( &bomb, bomb_container ); 
        }
        else if ( keyboard_keycode == ALLEGRO_KEY_ESCAPE || keyboard_keycode == ALLEGRO_KEY_P ) {
            signalPausingGame( gs );
            signalMenuUpdate( gs );
        }
    }
}

/** @brief Obsługuje zwolnienie danego klawisza w trakcie rozgrywki
 * 
 * Podejmuje odpowiednie akcje w zależności od zwolnienia danego przycisku klawiatury \n
 * w trakcie przechodzenia poziomu. Odpowiednio wysyła komendy o zmiane wektorow predkosci.
 * 
 * @param keyboard_keycode  kod klawisza zdefiniowany przez biblioteke Allegro
 * @param is                schemat sterowania wskazujący na dany zestaw wejść z klawiatury
 * @param player            wskaźnik na aktora danego gracza
*/
void handleGameInputKeyUp( char keyboard_keycode, InputScheme is, Actor *player )
{
    if( player != NULL && isActorAlive( player ) )
    {
        char down = 0, up = 0, left = 0, right = 0, bomb = 0;
        retrieveInput( is, &down, &up, &left, &right, &bomb );

        if      ( keyboard_keycode == down  )   updateVelocityY( player, player->vy[0], false );
        else if ( keyboard_keycode == up    )   updateVelocityY( player, false, player->vy[1] );
        else if ( keyboard_keycode == left  )   updateVelocityX( player, false, player->vx[1] );
        else if ( keyboard_keycode == right )   updateVelocityX( player, player->vx[0], false );
    }
}

/** @brief Obsługuje naciśnięcie danego klawisza w trakcie pobytu w menu
 * 
 * Podejmuje odpowiednie akcje w zależności od nacisnięcia i trzymania danego przycisku klawiatury \n
 * w trakcie pobytu w menu. Odpowiednio wysyła komendy o zmianie wybranego wpisu w menu \n
 * lub zmianie zmiennej przechowywanej w wpisie.
 * 
 * @param keyboard_keycode  kod klawisza zdefiniowany przez biblioteke Allegro
 * @param menu              wskaźnik na obecne menu
 * @param gs                stan gry                   
*/
void handleMenuInputKeyDown( char keyboard_keycode, Menu *menu, GameState *gs )
{
    switch ( keyboard_keycode )
    {
        case ALLEGRO_KEY_DOWN:
            switchEntry( menu, 1 );
            signalMenuUpdate( gs );
            break;
        case ALLEGRO_KEY_UP:
            switchEntry( menu, -1 );
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
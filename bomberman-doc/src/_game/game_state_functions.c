/** @file game_state_functions.c
 * 
 * @brief Plik zawiera funkcje obsługi zmiany Stanu Gry  
 * 
 * @author  Przemysław Cedro
 * @date    2020.05.29
*/


#include "../../headers/_game.h"

#include "../../headers/level_scan_tools.h"
#include "../../headers/_game_rules.h"

int levels_made; /** Ilość stworzonych poziomów */
char levels[MAX_LOADED_LEVELS][10]; /** Tablica nazw stworzonych poziomów */
#define SKINS_MADE 3 /** Ilość stworzonych skórek postaci */
char skins[SKINS_MADE][10] = { "ORIG", "ALT1", "ALT2" }; /** Tablica nazw stworzonych skórek postaci */

/**
 * @brief Inicjuje Stan Gry
 * 
 * Przypisuje domyślne wartości polom Stanu Gry
 * 
 * @param gs wskaźnik na Stan Gry
 */
void initGameState( GameState *gs )
{
    scanForLevels( levels, &levels_made );

    gs -> done = false;

    gs -> options = false;
    gs -> mode_selection = false;
    gs -> level_selection = false;
    gs -> game_on = false;
    gs -> pause = false;

    gs -> game_mode = SINGLE_PLAYER;
    gs -> selected_a_level = false;
    strcpy( gs -> current_level, levels[0] );

    gs -> selected_a_skin = false;
    strcpy( gs -> current_skinP1, skins[0] );
    strcpy( gs -> current_skinP2, skins[1] );

    gs -> take_stop_frame = false;
    gs -> player_died = false;

    gs -> menu_update = false; 
    gs -> render_update = false;
}

/**
 * @brief Sygnalizuje zamykanie programu
 * @param gs wskaźnik na Stan Gry
 */
void signalShuttingDown( GameState *gs ) 
{
    initGameState( gs );
    gs -> done = true; 
}

/**
 * @brief Sprawdza, czy program powinien wciąż być włączony
 * @param gs Stan Gry
 * @return wynik sprawdzenia
 */
bool isProgramRunning( GameState gs ) {
    return !gs.done;
}

/**
 * @brief Sygnalizuje pójście do Menu opcji
 * @param gs wskaźnik na Stan Gry
 */
void signalGoingToOptions( GameState *gs ) {
    gs -> options = true;
    gs -> menu_switch = true;
}

/**
 * @brief Sprawdza, czy obecnie uczęszczane Menu to Menu opcji
 * @param gs Stan Gry
 * @return wynik sprawdzenia
 */
bool isInOptions( GameState gs ) {
    return gs.options;
}

/**
 * @brief Wybiera kolejną nazwę poziomu w Stanie Gry i sygnalizuje wybranie poziomu
 * @param gs wskaźnik na Stan Gry
 */
void selectNextLevel( GameState *gs ) 
{
    for (int i = 0; i < levels_made - 1; i++)
    {
        if( strcmp( gs->current_level, levels[i] ) == 0 )
        {
            memset( gs->current_level, '\0', 2 );
            strcpy( gs->current_level, levels[i + 1] );
            gs -> selected_a_level = true;
            break;
        }
    }
}

/**
 * @brief Wybiera poprzednią nazwę poziomu w Stanie Gry i sygnalizuje wybranie poziomu
 * @param gs wskaźnik na Stan Gry
 */
void selectPrevLevel( GameState *gs ) 
{
    for (int i = 1; i < levels_made; i++)
    {
        if( strcmp( gs->current_level, levels[i] ) == 0 )
        {
            memset( gs->current_level, '\0', 2 );
            strcpy( gs->current_level, levels[i - 1] );
            gs -> selected_a_level = true;
            break;
        }
    }
}

/**
 * @brief Sygnalizuje koniec wybierania poziomu
 * @param gs wskaźnik na Stan Gry
 */
void signalStopSelectedALevel( GameState *gs ) {
    gs -> selected_a_level = false;
}

/**
 * @brief Sprawdza, czy został wybrany poziom
 * @param gs Stan Gry
 * @return wynik sprawdzenia 
 */
bool wasLevelSelected( GameState gs ) {
    return gs.selected_a_level;
}

/**
 * @brief Zwraca nazwę obecnie wybranego Poziomu Gry
 * @param gs wskaźnik na Stan Gry
 * @return nazwa Poziomu Gry
 */
char *getSelectedLevel( GameState *gs ) {
    return gs->current_level;
}

/**
 * @brief Sygnalizuje pójście do Menu głównego
 * @param gs wskaźnik na Stan Gry
 */
void signalGoingToMainMenu( GameState *gs ) 
{
    gs -> pause = false;
    gs -> options = false;
    gs -> mode_selection = false;
    gs -> level_selection = false;
    gs -> menu_switch = true;
}

/**
 * @brief Sygnalizuje rozpoczęcie rozgrywki
 * @param gs wskaźnik na Stan Gry
 */
void signalStartingGame( GameState *gs ) {
    gs -> game_on = true;
}

/**
 * @brief Sygnalizuje skończenie rozgrywki
 * @param gs wskaźnik na Stan Gry
 */
void signalEndingGame( GameState *gs ) {
    gs -> pause = false;
    gs -> game_on = false;
}

/**
 * @brief Sprawdza, czy trwa rozgrywka
 * @param gs Stan Gry
 * @return wynik sprawdzenia
 */
bool isGameRunning( GameState gs ) {
    return gs.game_on;
}

/**
 * @brief Sygnalizuje zapauzowanie rozgrywki
 * @param gs wskaźnik na Stan Gry
 */
void signalPausingGame( GameState *gs ) {
    gs -> pause = true;
    gs -> take_stop_frame = true;
}

/**
 * @brief Sygnalizuje wznowienie rozgrywki
 * @param gs wskaźnik na Stan Gry
 */
void signalUnpausingGame( GameState *gs ) {
    gs -> pause = false;
}

/**
 * @brief Sprawdza, czy gra jest zapauzowana
 * @param gs Stan Gry
 * @return wynik sprawdzenia
 */
bool isGamePaused( GameState gs ) {
    return gs.pause;
}

/**
 * @brief Sygnalizuje rysowanie obrazu
 * @param gs wskaźnik na Stan Gry
 */
void signalRenderUpdate( GameState *gs ) {
    gs -> render_update = true;
}

/**
 * @brief Sygnalizuje koniec rysowania obrazu
 * @param gs wskaźnik na Stan Gry
 */
void signalStopRenderUpdate( GameState *gs ) {
    gs -> render_update = false;
}

/**
 * @brief Sprawdza, czy powinien zostać narysowany obraz
 * @param gs Stan Gry
 * @return wynik sprawdzenia
 */
bool isRenderUpdate( GameState gs ) {
    return gs.render_update;
}

/**
 * @brief Sygnalizuje koniec robienia stopklatki gry
 * @param gs wskaźnik na Stan Gry
 */
void signalStopTakingGameStopFrame( GameState *gs ) {
    gs -> take_stop_frame = false;
}

/**
 * @brief Sprawdza, czy powinna być robiona stopklatka gry
 * @param gs Stan Gry
 * @return wynik sprawdzenia
 */
bool isTakingGameStopFrame( GameState gs ) {
    return gs.take_stop_frame;
}

/**
 * @brief Sygnalizuje aktualizację stan Menu
 * @param gs wskaźnik na Stan Gry
 */
void signalMenuUpdate( GameState *gs ) {
    gs -> menu_update = true;
}

/**
 * @brief Sygnalizuje koniec aktualizacji stanu Menu
 * @param gs wskaźnik na Stan Gry
 */
void signalStopMenuUpdate( GameState *gs ) {
    gs -> menu_update = false;
}

/**
 * @brief Sprawdza, czy Menu potrzebuje aktualizacji
 * @param gs Stan Gry
 * @return wynik sprawdzenia
 */
bool isMenuUpdate( GameState gs ) {
    return gs.menu_update;
}

/**
 * @brief Sygnalizuje wybranie trybu dla pojedynczego gracza
 * @param gs wskaźnik na Stan Gry
 */
void signalChoosingSinglePlayerMode( GameState *gs ) {
    gs -> game_mode = SINGLE_PLAYER;
    gs -> mode_selection = false;
    gs -> level_selection = true;
    gs -> menu_switch = true;
}

/**
 * @brief Sygnalizuje wybranie trybu kooperacyjnego
 * @param gs wskaźnik na Stan Gry
 */
void signalChoosingCoopMode( GameState *gs ) {
    gs -> game_mode = COOP;
    gs -> mode_selection = false;
    gs -> level_selection = true;
    gs -> menu_switch = true;
}

/**
 * @brief Sygnalizuje wybranie trybu PvP
 * @param gs wskaźnik na Stan Gry
 */
void signalChoosingPvPMode( GameState *gs ) {
    gs -> game_mode = PVP;
    gs -> mode_selection = false;
    gs -> level_selection = true;
    gs -> menu_switch = true;
}

/**
 * @brief Zwraca obecny tryb gry
 * @param gs Stan Gry
 * @return obecny tryb gry
 */
GameMode getGameMode( GameState gs ) {
    return gs.game_mode;
}

/**
 * @brief Sygnalizuje pójście do Menu wyboru trybu gry
 * @param gs wskaźnik na Stan Gry
 */
void signalGoingToModeSelection( GameState *gs ) {
    gs -> level_selection = false;
    gs -> mode_selection = true;
    gs -> menu_switch = true;
}

/**
 * @brief Sprawdza, czy obecnie uczęszczane Menu to Menu wyboru trybu gry
 * @param gs Stan Gry
 * @return wynik sprawdzenia
 */
bool isInModeSelection( GameState gs ) {
    return gs.mode_selection;
}

/**
 * @brief Sygnalizuje śmierć Aktora gracza
 * @param gs wskaźnik na Stan Gry
 */
void signalPlayerDied( GameState *gs ) {
    gs -> player_died = true;
}

/**
 * @brief Sygnalizuje koniec śmierci gracza
 * @param gs wskaźnik na Stan Gry
 */
void signalStopPlayerDied( GameState *gs ) {
    gs -> player_died = false;
}

/**
 * @brief Sprawdza, czy umarł gracz
 * @param gs Stan Gry
 * @return wynik sprawdzenia
 */
bool didPlayerDie( GameState gs ) {
    return gs.player_died;
}

/**
 * @brief Sprawdza, czy obecnie uczęszczane Menu to Menu wyboru poziomu
 * @param gs Stan Gry
 * @return wynik sprawdzenia
 */
bool isInLevelSelection( GameState gs ) {
    return gs.level_selection;
}

/**
 * @brief Sygnalizuje zmianę obecnie uczęszczanego Menu
 * @param gs wskaźnik na Stan Gry
 */
void signalStopMenuSwitch( GameState *gs ) {
    gs -> menu_switch = false;
}

/**
 * @brief Sprawdza, czy powinno zostać zmienione obecnie uczęszczane Menu
 * @param gs Stan Gry
 * @return wynik sprawdzenia
 */
bool isMenuSwitch( GameState gs ) {
    return gs.menu_switch;
}

/**
 * @brief Wybiera następną skórkę dla pierwszego gracza w Stanie Gry
 * @param gs wskaźnik na Stan Gry
 */
void selectNextSkinP1( GameState *gs )
{
    for (int i = 0; i < SKINS_MADE - 1; i++)
    {
        if( strcmp( gs->current_skinP1, skins[i] ) == 0 )
        {
            memset( gs->current_skinP1, '\0', 10 );
            strcpy( gs->current_skinP1, skins[i + 1] );
            gs -> selected_a_skin = true;
            break;
        }
    }
}

/**
 * @brief Wybiera poprzednią skórkę dla pierwszego gracza w Stanie Gry
 * @param gs wskaźnik na Stan Gry
 */
void selectPrevSkinP1( GameState *gs )
{
    for (int i = 1; i < SKINS_MADE; i++)
    {
        if( strcmp( gs->current_skinP1, skins[i] ) == 0 ) {
            memset( gs->current_skinP1, '\0', 10 );
            strcpy( gs->current_skinP1, skins[i - 1] );
            gs -> selected_a_skin = true;
            break;
        }
    }
}

/**
 * @brief Zwraca obecną skórkę dla pierwszego gracza w Stanie Gry
 * @param gs wskaźnik na Stan Gry
 * @return nazwa skórki
 */
char *getSelectedSkinP1( GameState *gs ) {
    return gs->current_skinP1;
}

/**
 * @brief Wybiera następną skórkę dla drugiego gracza w Stanie Gry
 * @param gs wskaźnik na Stan Gry
 */
void selectNextSkinP2( GameState *gs )
{
    for (int i = 0; i < SKINS_MADE - 1; i++)
    {
        if( strcmp( gs->current_skinP2, skins[i] ) == 0 ) {
            memset( gs->current_skinP2, '\0', 10 );
            strcpy( gs->current_skinP2, skins[i + 1] );
            gs -> selected_a_skin = true;
            break;
        }
    }
}

/**
 * @brief Wybiera poprzednią skórkę dla drugiego gracza w Stanie Gry
 * @param gs wskaźnik na Stan Gry
 */
void selectPrevSkinP2( GameState *gs )
{
    for (int i = 1; i < SKINS_MADE; i++)
    {
        if( strcmp( gs->current_skinP2, skins[i] ) == 0 ) {
            memset( gs->current_skinP2, '\0', 10 );
            strcpy( gs->current_skinP2, skins[i - 1] );
            gs -> selected_a_skin = true;
            break;
        }
    }
}

/**
 * @brief Zwraca obecną skórkę dla drugiego gracza w Stanie Gry
 * @param gs wskaźnik na Stan Gry
 * @return nazwa skórki
 */
char *getSelectedSkinP2( GameState *gs ) {
    return gs->current_skinP2;
}

/**
 * @brief Sygnalizuje zmianę skórki dla gracza
 * @param gs wskaźnik na Stan Gry
 */
void signalStopSelectedASkin( GameState *gs ) {
    gs -> selected_a_skin = false;
}

/**
 * @brief Sprawdza, czy została wybrana skórka dla gracza
 * @param gs Stan Gry
 * @return wynik sprawdzenia
 */
bool wasSkinSelected( GameState gs ) {
    return gs.selected_a_skin;
}
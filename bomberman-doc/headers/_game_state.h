/** @file _game_state.h
 * 
 * @brief Plik zawiera definicję typów GameMode i GameState oraz deklaracje funkcji stworzonych dla tego typu
 * 
 * @author  Przemysław Cedro
 * @date    2020.05.29
*/


#ifndef _GAME_STATE_H
#define _GAME_STATE_H

#include <stdbool.h>

/** Enum wybranego trybu gry. Dostępne tryby to SINGLE, COOP i PVP. */
typedef enum E_GameMode { SINGLE_PLAYER, COOP, PVP } GameMode; 

/**
 * @brief Struktura Stanu Gry, GameState
 * 
 * Struktura ta przechowuje informacje o obecnym stanie programu t.j. czy znajduje się w danym menu, \n
 * jaki jest aktualnie wybrany tryb gry, poziom, czy należy odświeżyć renderowanie obrazu. \n
 * Wszystko to stworzone głównie na potrzeby konstrukcji menu, których wpisy potrzebują wskaźników \n
 * na funkcje o konkretnej konstrukcji.  
 */
typedef struct 
{
    bool done; /**< Czy program powinien nadal działać */

    bool menu_switch; /**< Czy nastąpiła zmiana menu */
    bool options; /**< Czy aktualne menu to opcje */
    bool mode_selection; /**< Czy aktualne menu to wybór trybu gry */
    bool level_selection; /**< Czy aktualne menu to wybór poziomu */
    bool game_on; /**< Czy aktualnie rozgrywany jest poziom */
    bool pause; /**< Czy gra jest zapauzowana */

    GameMode game_mode; /**< Obecny tryb gry */
    bool selected_a_level; /**< Czy wybrany został poziom gry */
    char current_level[2]; /**< Nazwa obecnego poziomu gry */

    bool selected_a_skin; /**< Czy wybrana została skórka dla gracza */
    char current_skinP1[10]; /**< Nazwa obecnej skórki dla pierwszego gracza */
    char current_skinP2[10]; /**< Nazwa obecnej skórki dla drugiego gracza */

    bool take_stop_frame; /**< Czy powinna zostać zrobiona stopklatka gry */
    bool player_died; /**< Czy umarł jeden z graczy */

    bool menu_update; /**< Czy bitmapa menu powinna zostać zaktualizowana */
    bool render_update; /**< Czy powinna zostać narysowana kolejna klatka obrazu programu */

} GameState;


// ================ game_state_funtions.c ================

/** @brief Inicjuje Stan Gry */
void initGameState( GameState *gs );
/** @brief Sygnalizuje zamykanie programu */
void signalShuttingDown( GameState *gs );
/** @brief Sprawdza, czy program powinien wciąż być włączony */
bool isProgramRunning( GameState gs );
/** @brief Sygnalizuje pójście do Menu opcji */
void signalGoingToOptions( GameState *gs );
/** @brief Sprawdza, czy obecnie uczęszczane Menu to Menu opcji */
bool isInOptions( GameState gs );
/** @brief Wybiera kolejną nazwę poziomu w Stanie Gry i sygnalizuje wybranie poziomu */
void selectNextLevel( GameState *gs );
/** @brief Wybiera poprzednią nazwę poziomu w Stanie Gry i sygnalizuje wybranie poziomu */
void selectPrevLevel( GameState *gs );
/** @brief Zwraca nazwę obecnie wybranego Poziomu Gry */
char *getSelectedLevel( GameState *gs );
/** @brief Sygnalizuje koniec wybierania poziomu */
void signalStopSelectedALevel( GameState *gs );
/** @brief Sprawdza, czy został wybrany poziom */
bool wasLevelSelected( GameState gs );
/** @brief Sygnalizuje pójście do Menu głównego */
void signalGoingToMainMenu( GameState *gs );
/** @brief Sygnalizuje rozpoczęcie rozgrywki */
void signalStartingGame( GameState *gs );
/** @brief Sygnalizuje skończenie rozgrywki */
void signalEndingGame( GameState *gs );
/** @brief Sprawdza, czy trwa rozgrywka */
bool isGameRunning( GameState gs );
/** @brief Sygnalizuje zapauzowanie rozgrywki */
void signalPausingGame( GameState *gs );
/** @brief Sygnalizuje wznowienie rozgrywki */
void signalUnpausingGame( GameState *gs );
/** @brief Sprawdza, czy gra jest zapauzowana */
bool isGamePaused( GameState gs );
/** @brief Sygnalizuje rysowanie obrazu */
void signalRenderUpdate( GameState *gs );
/** @brief Sygnalizuje koniec rysowania obrazu */
void signalStopRenderUpdate( GameState *gs );
/** @brief Sprawdza, czy powinien zostać narysowany obraz */
bool isRenderUpdate( GameState gs );
/** @brief Sygnalizuje koniec robienia stopklatki gry */
void signalStopTakingGameStopFrame( GameState *gs );
/** @brief Sprawdza, czy powinna być robiona stopklatka gry */
bool isTakingGameStopFrame( GameState gs );
/** @brief Sygnalizuje aktualizację stan Menu */
void signalMenuUpdate( GameState *gs );
/** @brief Sygnalizuje koniec aktualizacji stanu Menu */
void signalStopMenuUpdate( GameState *gs );
/** @brief Sprawdza, czy Menu potrzebuje aktualizacji */
bool isMenuUpdate( GameState gs );
/** @brief Sygnalizuje wybranie trybu dla pojedynczego gracza */
void signalChoosingSinglePlayerMode( GameState *gs );
/** @brief Sygnalizuje wybranie trybu kooperacyjnego */
void signalChoosingCoopMode( GameState *gs );
/** @brief Sygnalizuje wybranie trybu PvP */
void signalChoosingPvPMode( GameState *gs );
/** @brief Zwraca obecny tryb gry */
GameMode getGameMode( GameState gs );
/** @brief Sygnalizuje pójście do Menu wyboru trybu gry */
void signalGoingToModeSelection( GameState *gs );
/** @brief Sprawdza, czy obecnie uczęszczane Menu to Menu wyboru trybu gry */
bool isInModeSelection( GameState gs );
/** @brief Sygnalizuje śmierć Aktora gracza */
void signalPlayerDied( GameState *gs );
/** @brief Sygnalizuje koniec śmierci gracza */
void signalStopPlayerDied( GameState *gs );
/** @brief Sprawdza, czy umarł gracz */
bool didPlayerDie( GameState gs );
/** @brief Sprawdza, czy obecnie uczęszczane Menu to Menu wyboru poziomu */
bool isInLevelSelection( GameState gs );
/** @brief Sygnalizuje zmianę obecnie uczęszczanego Menu */
void signalStopMenuSwitch( GameState *gs );
/** @brief Sprawdza, czy powinno zostać zmienione obecnie uczęszczane Menu */
bool isMenuSwitch( GameState gs );
/** @brief Wybiera następną skórkę dla pierwszego gracza w Stanie Gry */
void selectNextSkinP1( GameState *gs );
/** @brief Wybiera poprzednią skórkę dla pierwszego gracza w Stanie Gry */
void selectPrevSkinP1( GameState *gs );
/** @brief Zwraca obecną skórkę dla pierwszego gracza w Stanie Gry */
char *getSelectedSkinP1( GameState *gs );
/** @brief Wybiera następną skórkę dla drugiego gracza w Stanie Gry */
void selectNextSkinP2( GameState *gs );
/** @brief Wybiera poprzednią skórkę dla drugiego gracza w Stanie Gry */
void selectPrevSkinP2( GameState *gs );
/** @brief Zwraca obecną skórkę dla drugiego gracza w Stanie Gry */
char *getSelectedSkinP2( GameState *gs );
/** @brief Sygnalizuje zmianę skórki dla gracza */
void signalStopSelectedASkin( GameState *gs );
/** @brief Sprawdza, czy została wybrana skórka dla gracza */
bool wasSkinSelected( GameState gs );

#endif
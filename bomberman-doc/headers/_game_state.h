#ifndef _GAME_STATE_H
#define _GAME_STATE_H

#include <stdbool.h>

typedef enum E_GameMode { SINGLE_PLAYER, COOP, PVP } GameMode; 

typedef struct 
{
    bool done;

    bool menu_switch;
    bool options;
    bool mode_selection;
    bool level_selection;
    bool game_on;
    bool pause;

    GameMode game_mode;
    bool selected_a_level;
    char current_level[2];

    bool selected_a_skin;
    char current_skinP1[10];
    char current_skinP2[10];

    bool take_stop_frame;
    bool player_died;

    bool menu_update;
    bool render_update;

} GameState;


// ================ game_state_funtions.c ================

void initGameState( GameState *gs );
void signalShuttingDown( GameState *gs );
bool isProgramRunning( GameState gs );
void signalGoingToOptions( GameState *gs );
bool isInOptions( GameState gs );
void selectNextLevel( GameState *gs );
void selectPrevLevel( GameState *gs );
char *getSelectedLevel( GameState *gs );
void signalStopSelectedALevel( GameState *gs );
bool wasLevelSelected( GameState gs );
void signalGoingToMainMenu( GameState *gs );
void signalStartingGame( GameState *gs );
void signalEndingGame( GameState *gs );
bool isGameRunning( GameState gs );
void signalPausingGame( GameState *gs );
void signalUnpausingGame( GameState *gs );
bool isGamePaused( GameState gs );
void signalRenderUpdate( GameState *gs );
void signalStopRenderUpdate( GameState *gs );
bool isRenderUpdate( GameState gs );
void signalStopTakingGameStopFrame( GameState *gs );
bool isTakingGameStopFrame( GameState gs );
void signalMenuUpdate( GameState *gs );
void signalStopMenuUpdate( GameState *gs );
bool isMenuUpdate( GameState gs );
void signalChoosingSinglePlayerMode( GameState *gs );
void signalChoosingCoopMode( GameState *gs );
void signalChoosingPvPMode( GameState *gs );
GameMode getGameMode( GameState gs );
void signalGoingToModeSelection( GameState *gs );
bool isInModeSelection( GameState gs );
void signalPlayerDied( GameState *gs );
void signalStopPlayerDied( GameState *gs );
bool didPlayerDie( GameState gs );
bool isInLevelSelection( GameState gs );
void signalStopMenuSwitch( GameState *gs );
bool isMenuSwitch( GameState gs );
void selectNextSkinP1( GameState *gs );
void selectPrevSkinP1( GameState *gs );
char *getSelectedSkinP1( GameState *gs );
void selectNextSkinP2( GameState *gs );
void selectPrevSkinP2( GameState *gs );
char *getSelectedSkinP2( GameState *gs );
void signalStopSelectedASkin( GameState *gs );
bool wasSkinSelected( GameState gs );

#endif
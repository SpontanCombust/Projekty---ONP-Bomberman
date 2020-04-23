#ifndef _GAME_STATE_H
#define _GAME_STATE_H

#include <stdbool.h>

typedef enum { SINGLE_PLAYER, COOP, PvP } GameMode; 

typedef struct 
{
    bool done;

    bool options;
    bool mode_selection;
    bool game_on;
    bool pause;

    int selected_level;

    GameMode game_mode;

    bool take_stop_frame;
    bool menu_update;
    bool render_update;

} GameState;


// ================ game_state_funtions.c ================

void initGameState( GameState *gs );
void signalShuttingDown( GameState *gs );
bool isProgramRunning( GameState gs );
void signalInOptions( GameState *gs );
bool isInOptions( GameState gs );
void selectNextLevel( GameState *gs );
void selectPrevLevel( GameState *gs );
int getSelectedLevel( GameState gs );
void signalGoingToMainMenu( GameState *gs );
void singalStartingGame( GameState *gs );
void signalEndingGame( GameState *gs );
bool isGameRunning( GameState gs );
void signalPausingGame( GameState *gs );
void signalUnpausingGame( GameState *gs );
bool isGamePaused( GameState gs );
void signalRenderUpdate( GameState *gs );
void signalRenderStop( GameState *gs );
bool isRenderUpdate( GameState gs );
void signalTakingGameStopFrame( GameState *gs );
void signalNotTakingGameStopFrame( GameState *gs );
bool isTakingGameStopFrame( GameState gs );
void signalMenuUpdate( GameState *gs );
void signalNoMenuUpdate( GameState *gs );
bool isMenuUpdate( GameState gs );
void signalSinglePlayerMode( GameState *gs );
void signalCoopMode( GameState *gs );
void signalPvPMode( GameState *gs );
GameMode getGameMode( GameState gs );
void signalInModeSelection( GameState *gs );
bool isInModeSelection( GameState gs );


#endif
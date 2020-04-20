#ifndef _GAME_STATE_H
#define _GAME_STATE_H

#include <stdbool.h>

typedef struct 
{
    bool done;
    bool options;
    int selected_level;
    bool game_on;
    bool pause;
    bool take_stop_frame;
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

#endif
#include "../../headers/_game.h"

void initGameState( GameState *gs )
{
    gs -> done = false;
    gs -> options = false;
    gs -> selected_level = 1;
    gs -> game_on = false;
    gs -> pause = false;
    gs -> take_stop_frame = false;
    gs -> render_update = false;
}

void signalShuttingDown( GameState *gs ) {
    gs -> pause = false;
    gs -> game_on = false;
    gs -> options = false;
    gs -> done = true; 
}

bool isProgramRunning( GameState gs ) {
    return !gs.done;
}

void signalGoingToOptions( GameState *gs ) {
    gs -> options = true;
}

bool isInOptions( GameState gs ) {
    return gs.options;
}

void selectNextLevel( GameState *gs ) {
    gs -> selected_level += 1;

    if( gs->selected_level > LEVELS_MADE )
        gs -> selected_level = LEVELS_MADE;
}

void selectPrevLevel( GameState *gs ) {
    gs -> selected_level -= 1;

    if( gs->selected_level < 1 )
        gs -> selected_level = 1;
}

int getSelectedLevel( GameState gs ) {
    return gs.selected_level;
}

void signalGoingToMainMenu( GameState *gs ) {
    gs -> pause = false;
    gs -> options = false;
    gs -> game_on = false;
}

void singalStartingGame( GameState *gs ) {
    gs -> game_on = true;
}

void signalEndingGame( GameState *gs ) {
    gs -> game_on = false;
}

bool isGameRunning( GameState gs ) {
    return gs.game_on;
}

void signalPausingGame( GameState *gs ) {
    gs -> pause = true;
    gs -> take_stop_frame = true;
}

void signalUnpausingGame( GameState *gs ) {
    gs -> pause = false;
}

bool isGamePaused( GameState gs ) {
    return gs.pause;
}

void signalRenderUpdate( GameState *gs ) {
    gs -> render_update = true;
}

void signalRenderStop( GameState *gs ) {
    gs -> render_update = false;
}

bool isRenderUpdate( GameState gs ) {
    return gs.render_update;
}

void signalTakingGameStopFrame( GameState *gs )
{
    gs -> take_stop_frame = true;
}

void signalNotTakingGameStopFrame( GameState *gs )
{
    gs -> take_stop_frame = false;
}

bool isTakingGameStopFrame( GameState gs )
{
    return gs.take_stop_frame;
}
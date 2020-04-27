#include "../../headers/_game.h"

void initGameState( GameState *gs )
{
    gs -> done = false;
    gs -> options = false;
    gs -> mode_selection = false;
    gs -> level_selection = false;
    gs -> pause = false;
    gs -> current_level = 1;
    gs -> game_on = false;
    gs -> game_mode = SINGLE_PLAYER;
    gs -> take_stop_frame = false;
    gs -> render_update = false;
    gs -> menu_update = false; 
}
void signalShuttingDown( GameState *gs ) 
{
    initGameState( gs );
    gs -> done = true; 
}
bool isProgramRunning( GameState gs ) {
    return !gs.done;
}
void signalGoingToOptions( GameState *gs ) {
    gs -> options = true;
    gs -> menu_switch = true;
}
bool isInOptions( GameState gs ) {
    return gs.options;
}
void selectNextLevel( GameState *gs ) 
{
    if( gs->current_level < LEVELS_MADE ) {
        gs -> current_level += 1;
        gs -> selected_a_level = true;
    }
}
void selectPrevLevel( GameState *gs ) 
{
    if( gs->current_level > 1 ) {
        gs -> current_level -= 1;
        gs -> selected_a_level = true;
    }
}
int getSelectedLevel( GameState gs ) {
    return gs.current_level;
}
void signalGoingToMainMenu( GameState *gs ) 
{
    gs -> pause = false;
    gs -> options = false;
    gs -> mode_selection = false;
    gs -> level_selection = false;
    gs -> menu_switch = true;
}
void signalStartingGame( GameState *gs ) {
    gs -> game_on = true;
}
void signalEndingGame( GameState *gs ) {
    gs -> pause = false;
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
void signalStopRenderUpdate( GameState *gs ) {
    gs -> render_update = false;
}
bool isRenderUpdate( GameState gs ) {
    return gs.render_update;
}
void signalStopTakingGameStopFrame( GameState *gs ) {
    gs -> take_stop_frame = false;
}
bool isTakingGameStopFrame( GameState gs ) {
    return gs.take_stop_frame;
}
void signalMenuUpdate( GameState *gs ) {
    gs -> menu_update = true;
}
void signalStopMenuUpdate( GameState *gs ) {
    gs -> menu_update = false;
}
bool isMenuUpdate( GameState gs ) {
    return gs.menu_update;
}
void signalChoosingSinglePlayerMode( GameState *gs ) {
    gs -> game_mode = SINGLE_PLAYER;
    gs -> mode_selection = false;
    gs -> level_selection = true;
    gs -> menu_switch = true;
}
void signalChoosingCoopMode( GameState *gs ) {
    gs -> game_mode = COOP;
    gs -> mode_selection = false;
    gs -> level_selection = true;
    gs -> menu_switch = true;
}
void signalChoosingPvPMode( GameState *gs ) {
    gs -> game_mode = PVP;
    gs -> mode_selection = false;
    gs -> level_selection = true;
    gs -> menu_switch = true;
}
GameMode getGameMode( GameState gs ) {
    return gs.game_mode;
}
void signalGoingToModeSelection( GameState *gs ) {
    gs -> level_selection = false;
    gs -> mode_selection = true;
    gs -> menu_switch = true;
}
bool isInModeSelection( GameState gs ) {
    return gs.mode_selection;
}
void signalPlayerDied( GameState *gs ) {
    gs -> player_died = true;
}
void signalStopPlayerDied( GameState *gs ) {
    gs -> player_died = false;
}
bool didPlayerDie( GameState gs ) {
    return gs.player_died;
}
bool isInLevelSelection( GameState gs ) {
    return gs.level_selection;
}
void signalStopSelectedALevel( GameState *gs ) {
    gs -> selected_a_level = false;
}
bool wasLevelSelected( GameState gs ) {
    return gs.selected_a_level;
}
void signalStopMenuSwitch( GameState *gs ) {
    gs -> menu_switch = false;
}
bool isMenuSwitch( GameState gs ) {
    return gs.menu_switch;
}
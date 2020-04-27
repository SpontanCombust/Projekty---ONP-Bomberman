#include "../../headers/_game.h"

#include "../../headers/level_scan_tools.h"
#include "../../headers/_game_rules.h"

int levels_made;
char levels[MAX_LOADED_LEVELS][10]; 
#define SKINS_MADE 3
char skins[SKINS_MADE][10] = { "PINK", "RED", "BLUE" };

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
void signalStopSelectedALevel( GameState *gs ) {
    gs -> selected_a_level = false;
}
bool wasLevelSelected( GameState gs ) {
    return gs.selected_a_level;
}
char *getSelectedLevel( GameState *gs ) {
    return gs->current_level;
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
void signalStopMenuSwitch( GameState *gs ) {
    gs -> menu_switch = false;
}
bool isMenuSwitch( GameState gs ) {
    return gs.menu_switch;
}
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
char *getSelectedSkinP1( GameState *gs ) {
    return gs->current_skinP1;
}
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
char *getSelectedSkinP2( GameState *gs ) {
    return gs->current_skinP2;
}
void signalStopSelectedASkin( GameState *gs ) {
    gs -> selected_a_skin = false;
}
bool wasSkinSelected( GameState gs ) {
    return gs.selected_a_skin;
}
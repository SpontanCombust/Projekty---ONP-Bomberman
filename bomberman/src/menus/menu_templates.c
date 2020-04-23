#include "../../headers/menus.h"

#include "../../headers/_game_rules.h"
#include "../../headers/_game_state.h"

Menu *createMainMenu( ALLEGRO_FONT *font )
{
    Menu *main_menu = createMenu( font );
    setMenuBgData( main_menu, al_map_rgb( 0, 0, 0 ), 1, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );
    setMenuTextData( main_menu, al_map_rgb( 255, 255, 255 ), SCREEN_WIDTH/2, SCREEN_HEIGHT/4, DEFAULT_LINE_SPACING );

    setEntryText( main_menu, 0, "PLAY" );
    setEntrySelectOperation( main_menu, 0, signalInModeSelection );
    enableEntry( main_menu, 0 );

    setEntryText( main_menu, 1, "OPTIONS" );
    setEntrySelectOperation( main_menu, 1, signalInOptions );
    enableEntry( main_menu, 1 );

    setEntryText( main_menu, 3, "EXIT" );
    setEntrySelectOperation( main_menu, 3, signalShuttingDown );
    enableEntry( main_menu, 3 );

    return main_menu;
}

Menu *createOptionsMenu( ALLEGRO_FONT *font )
{
    Menu *options = createMenu( font );
    setMenuBgData( options, al_map_rgb( 0, 0, 0 ), 1, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );
    setMenuTextData( options, al_map_rgb( 255, 255, 255 ), SCREEN_WIDTH/2, SCREEN_HEIGHT/4, DEFAULT_LINE_SPACING );

    setEntryText( options, 3, "GO BACK" );
    setEntrySelectOperation( options, 3, signalGoingToMainMenu );
    enableEntry( options, 3 );

    setMenuEscOperation( options, signalGoingToMainMenu );

    return options;
}

Menu *createPauseMenu( ALLEGRO_FONT *font )
{
    Menu *pause = createMenu( font );
    setMenuBgData( pause,  al_map_rgb( 0, 0, 0 ), 0.5, 0, 0, SCREEN_WIDTH/3, SCREEN_HEIGHT );
    setMenuTextData( pause, al_map_rgb( 255, 255, 255 ), pause->bg_w/2, pause->bg_h/8, DEFAULT_LINE_SPACING );

    setEntryText( pause, 0, "RESUME" );
    setEntrySelectOperation( pause, 0, signalUnpausingGame );
    enableEntry( pause, 0 );

    setEntryText( pause, 1, "TO MAIN MENU");
    setEntrySelectOperation( pause, 1, signalGoingToMainMenu );
    enableEntry( pause, 1 );

    setMenuEscOperation( pause, signalUnpausingGame );

    return pause;
}

Menu *createModeSelectionMenu( ALLEGRO_FONT *font )
{
    Menu *mode = createMenu( font );
    setMenuBgData( mode, al_map_rgb( 0, 0, 0 ), 1, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );
    setMenuTextData( mode, al_map_rgb( 255, 255, 255 ), SCREEN_WIDTH/2, SCREEN_HEIGHT/8, DEFAULT_LINE_SPACING );

    setEntryText( mode, 0, "SINGLE PLAYER" );
    setEntrySelectOperation( mode, 0, signalSinglePlayerMode );
    enableEntry( mode, 0 );

    setEntryText( mode, 1, "CO-OP");
    setEntrySelectOperation( mode, 1, signalCoopMode );
    enableEntry( mode, 1 );

    setEntryText( mode, 2, "PvP" );
    setEntrySelectOperation( mode, 2, signalPvPMode );
    enableEntry( mode, 2 );

    setEntryText( mode, 4, "GO BACK" );
    setEntrySelectOperation( mode, 4, signalGoingToMainMenu );
    enableEntry( mode, 4 );

    setMenuEscOperation( mode, signalGoingToMainMenu );

    return mode;
}
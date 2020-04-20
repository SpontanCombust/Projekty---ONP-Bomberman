#include "../../headers/menus.h"

#include "../../headers/_game_rules.h"
#include "../../headers/_game_state.h"

Menu *createMainMenu( ALLEGRO_FONT *font )
{
    Menu *main_menu = createMenu( font );
    setMenuBg( main_menu, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, al_map_rgb( 0, 0, 0 ) );
    setMenuTextData( main_menu, al_map_rgb( 255, 255, 255 ), SCREEN_WIDTH/2, SCREEN_HEIGHT/4, DEFAULT_LINE_SPACING );

    setEntryText( main_menu, 0, "START" );
    setEntrySelectOperation( main_menu, 0, singalStartingGame );
    enableEntry( main_menu, 0 );

    setEntryText( main_menu, 1, "OPIONS" );
    setEntrySelectOperation( main_menu, 1, signalGoingToOptions );
    enableEntry( main_menu, 1 );

    setEntryText( main_menu, 3, "EXIT" );
    setEntrySelectOperation( main_menu, 3, signalShuttingDown );
    enableEntry( main_menu, 3 );

    return main_menu;
}

Menu *createOptionsMenu( ALLEGRO_FONT *font )
{
    Menu *options = createMenu( font );
    setMenuBg( options, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, al_map_rgb( 0, 0, 0 ) );
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
    setMenuBg( pause, 0, 0, SCREEN_WIDTH/3, SCREEN_HEIGHT, al_map_rgba( 0, 0, 0, 50 ) );
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
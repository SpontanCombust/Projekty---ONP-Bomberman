#include "../../headers/menus.h"

#include "../../headers/_game_rules.h"
#include "../../headers/_game_state.h"

Menu *createMainMenu( ALLEGRO_FONT *main_font, ALLEGRO_FONT *sub_font )
{
    Menu *menu = createMenu( main_font, sub_font );
    setMenuBgData( menu, COLOR_BLACK, 1, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );
    setMenuTextData( menu, COLOR_WHITE, COLOR_YELLOW, SCREEN_WIDTH/2, SCREEN_HEIGHT/4, DEFAULT_LINE_SPACING );

    setEntryText( menu, 0, "PLAY" );
    setEntrySelectOperation( menu, 0, signalGoingToModeSelection );
    setHighlightable( menu, 0 );
    enableEntry( menu, 0 );

    setEntryText( menu, 1, "OPTIONS" );
    setEntrySelectOperation( menu, 1, signalGoingToOptions );
    setHighlightable( menu, 1 );
    enableEntry( menu, 1 );

    setEntryText( menu, 3, "EXIT" );
    setEntrySelectOperation( menu, 3, signalShuttingDown );
    setHighlightable( menu, 3 );
    enableEntry( menu, 3 );

    setDefaultHighlighted( menu, 0 );

    return menu;
}

Menu *createOptionsMenu( ALLEGRO_FONT *main_font, ALLEGRO_FONT *sub_font )
{
    Menu *menu = createMenu( main_font, sub_font );
    setMenuBgData( menu, COLOR_BLACK, 1, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );
    setMenuTextData( menu, COLOR_WHITE, COLOR_YELLOW, SCREEN_WIDTH/2, SCREEN_HEIGHT/8, DEFAULT_LINE_SPACING );

    setEntryText( menu, 0, "OPTIONS" );
    enableEntry( menu, 0 );

    setEntryText( menu, SKIN_P1_VAR_INDEX, "PLAYER1 SKIN:" );
    setEntryVar( menu, SKIN_P1_VAR_INDEX, "" );
    setEntryLeftOperation( menu, SKIN_P1_VAR_INDEX, selectPrevSkinP1 );
    setEntryRightOperation( menu, SKIN_P1_VAR_INDEX, selectNextSkinP1 );
    setHighlightable( menu, SKIN_P1_VAR_INDEX );
    enableEntry( menu, SKIN_P1_VAR_INDEX );

    setEntryText( menu, SKIN_P2_VAR_INDEX, "PLAYER2 SKIN:" );
    setEntryVar( menu, SKIN_P2_VAR_INDEX, "" );
    setEntryLeftOperation( menu, SKIN_P2_VAR_INDEX, selectPrevSkinP2 );
    setEntryRightOperation( menu, SKIN_P2_VAR_INDEX, selectNextSkinP2 );
    setHighlightable( menu, SKIN_P2_VAR_INDEX );
    enableEntry( menu, SKIN_P2_VAR_INDEX );

    setEntryText( menu, 5, "GO BACK" );
    setEntrySelectOperation( menu, 5, signalGoingToMainMenu );
    setHighlightable( menu, 5 );
    enableEntry( menu, 5 );

    setMenuEscOperation( menu, signalGoingToMainMenu );
    setDefaultHighlighted( menu, 3 );

    return menu;
}

Menu *createPauseMenu( ALLEGRO_FONT *main_font, ALLEGRO_FONT *sub_font )
{
    Menu *menu = createMenu( main_font, sub_font );
    setMenuBgData( menu,  COLOR_BLACK, 0.5, 0, 0, SCREEN_WIDTH/3, SCREEN_HEIGHT );
    setMenuTextData( menu, COLOR_WHITE, COLOR_YELLOW, menu->bg_w/2, menu->bg_h/8, DEFAULT_LINE_SPACING );

    setEntryText( menu, 0, "PAUSE" );
    enableEntry( menu, 0 );

    setEntryText( menu, 2, "RESUME" );
    setEntrySelectOperation( menu, 2, signalUnpausingGame );
    setHighlightable( menu, 2 );
    enableEntry( menu, 2 );

    setEntryText( menu, 3, "TO MAIN MENU");
    setEntrySelectOperation( menu, 3, signalEndingGame );
    setHighlightable( menu, 3 );
    enableEntry( menu, 3 );

    setMenuEscOperation( menu, signalUnpausingGame );
    setDefaultHighlighted( menu, 2 );

    return menu;
}

Menu *createModeSelectionMenu( ALLEGRO_FONT *main_font, ALLEGRO_FONT *sub_font )
{
    Menu *menu = createMenu( main_font, sub_font );
    setMenuBgData( menu, COLOR_BLACK, 1, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );
    setMenuTextData( menu, COLOR_WHITE, COLOR_YELLOW, SCREEN_WIDTH/2, SCREEN_HEIGHT/16, DEFAULT_LINE_SPACING );

    setEntryText( menu, 0, "MODE SELECTION" );
    enableEntry( menu, 0 );

    setEntryText( menu, 2, "SINGLE PLAYER" );
    setEntrySelectOperation( menu, 2, signalChoosingSinglePlayerMode );
    setHighlightable( menu, 2 );
    enableEntry( menu, 2 );

    setEntryText( menu, 3, "CO-OP");
    setEntrySelectOperation( menu, 3, signalChoosingCoopMode );
    setHighlightable( menu, 3 );
    enableEntry( menu, 3 );

    setEntryText( menu, 4, "PvP" );
    setEntrySelectOperation( menu, 4, signalChoosingPvPMode );
    setHighlightable( menu, 4 );
    enableEntry( menu, 4 );

    setEntryText( menu, 6, "GO BACK" );
    setEntrySelectOperation( menu, 6, signalGoingToMainMenu );
    setHighlightable( menu, 6 );
    enableEntry( menu, 6 );

    setMenuEscOperation( menu, signalGoingToMainMenu );
    setDefaultHighlighted( menu, 2 );

    return menu;
}

Menu *createLevelSelectionMenu( ALLEGRO_FONT *main_font, ALLEGRO_FONT *sub_font )
{
    Menu *menu = createMenu( main_font, sub_font );
    setMenuBgData( menu, COLOR_BLACK, 1, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );
    setMenuTextData( menu, COLOR_WHITE, COLOR_YELLOW, SCREEN_WIDTH/2, SCREEN_HEIGHT/8, DEFAULT_LINE_SPACING );
    setDefaultHighlighted( menu, 2 );

    setEntryText( menu, 0, "SELECT LEVEL" );
    enableEntry( menu, 0 );

    setEntryText( menu, 2, "START!" );
    setEntrySelectOperation( menu, 2, signalStartingGame );
    setHighlightable( menu, 2 );
    enableEntry( menu, 2 );

    setEntryText( menu, LEVEL_VAR_INDEX, "LEVEL:" );
    setEntryVar( menu, LEVEL_VAR_INDEX, "" );
    setEntryLeftOperation( menu, LEVEL_VAR_INDEX, selectPrevLevel );
    setEntryRightOperation( menu, LEVEL_VAR_INDEX, selectNextLevel );
    setHighlightable( menu, LEVEL_VAR_INDEX );
    enableEntry( menu, LEVEL_VAR_INDEX );

    setEntryText( menu, 5, "GO BACK" );
    setEntrySelectOperation( menu, 5, signalGoingToModeSelection );
    setHighlightable( menu, 5 );
    enableEntry( menu, 5 );

    setMenuEscOperation( menu, signalGoingToModeSelection );

    return menu;
}
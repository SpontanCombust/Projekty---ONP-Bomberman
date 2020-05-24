/** @file menu_templates.c
 * 
 * @brief Plik zawiera funkcje tworzenia menu wzorców menu
 * 
 * Plik zawiera funkcje tworzące już gotowe wzorce konkretnych menu: menu głównego, menu opcji,\n
 * menu wyboru trybu gry, menu wyboru poziomu i menu pauzy.
 * 
 * @author  Przemysław Cedro
 * @date    2020.05.21
*/


#include "../../headers/menus.h"

#include "../../headers/_game_rules.h"
#include "../../headers/_game_state.h"

/** @brief Zwraca wzorzec menu głównego
 * 
 * Tworzy menu główne, którego konstrukcja to:\n
 * 1. czarne tło na cały ekran\n
 * 2. wpis z etykietą "PLAY" prowadzący do menu wyboru trybu gry\n
 * 3. wpis z etykietą "OPTIONS" prowadzący do menu opcji\n
 * 4. wpis z etykietą "EXIT" zamykający program\n
 *
 * @param main_font wskaźnik na główną czcionkę
 * @param sub_font  wskaźnik na poboczną czcionkę
 * 
 * @return wskaźnik na utworzone menu główne
*/
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

/** @brief Zwraca wzorzec menu opcji
 * 
 * Tworzy menu opcji, którego konstrukcja to:\n
 * 1. czarne tło na cały ekran\n
 * 2. wpis z etykietą "OPTIONS" będący nagłówkiem menu\n
 * 3. wpis z etykietą "PLAYER1 SKIN:" i zmienną z zawartością nazwy skórki dla Gracza 1\n
 *    wpis ten dla operacji poprzedniej i następnej zawartości argumentu przegląda skórki dla graczy\n
 * 4. wpis z etykietą "PLAYER2 SKIN:" i zmienną z zawartością nazwy skórki dla Gracza 2\n
 *    wpis ten dla operacji poprzedniej i następnej zawartości argumentu przegląda skórki dla graczy\n
 * 5. wpis z etykietą "GO BACK" prowadzący z powrotem do menu głównego\n
 * 6. operacja pod klawisz ESC prowadząca z powrotem do menu głównego\n
 *
 * @param main_font wskaźnik na główną czcionkę
 * @param sub_font  wskaźnik na poboczną czcionkę
 * 
 * @return wskaźnik na utworzone menu opcji
*/
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

/** @brief Zwraca wzorzec menu pauzy
 * 
 * Tworzy menu główne, którego konstrukcja to:\n
 * 1. czarne, półprzezroczyste tło na 1/3 szerokości ekranu\n
 * 2. wpis z etykietą "PAUSE" będący nagłówkiem menu\n
 * 3. wpis z etykietą "RESUME" wznawiający grę\n
 * 4. wpis z etykietą "TO MAIN MENU" kończący rozgrywkę i prowadzący do menu głównego\n
 * 5. operacja pod klawisz ESC wznawiająca grę\n
 *
 * @param main_font wskaźnik na główną czcionkę
 * @param sub_font  wskaźnik na poboczną czcionkę
 * 
 * @return wskaźnik na utworzone menu pauzy
*/
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

/** @brief Zwraca wzorzec menu wyboru trybu gry
 * 
 * Tworzy menu główne, którego konstrukcja to:\n
 * 1. czarne tło na cały ekran\n
 * 2. wpis z etykietą "MODE SELECTION" będący nagłówkiem menu\n
 * 3. wpis z etykietą "SINGLE PLAYER" ustawiający tryb gry na tryb pojedynczego gracza\n
 *    i prowadzący do menu wyboru poziomu\n
 * 4. wpis z etykietą "CO-OP" ustawiający tryb gry na tryb kooperacyjny\n
 *    i prowadzący do menu wyboru poziomu\n
 * 5. wpis z etykietą "PvP" ustawiający tryb gry na tryb gracz przeciw graczowi\n
 *    i prowadzący do menu wyboru poziomu\n
 * 6. wpis z etykietą "GO BACK" prowadzący z powrotem do menu głównego
 * 7. operacja pod klawisz ESC prowadząca z powrotem do menu głównego
 *
 * @param main_font wskaźnik na główną czcionkę
 * @param sub_font  wskaźnik na poboczną czcionkę
 * 
 * @return wskaźnik na utworzone menu wyboru trybu gry
*/
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

/** @brief Zwraca wzorzec menu wyboru poziomu
 * 
 * Tworzy menu opcji, którego konstrukcja to:\n
 * 1. czarne tło na cały ekran\n
 * 2. wpis z etykietą "SELECT_LEVEL" będący nagłówkiem menu\n
 * 3. wpis z etykietą "START!" prowadzący do rozpoczęcia rozgrywki
 * 4. wpis z etykietą "LEVEL:" i zmienną z zawartością nazwy poziomu\n
 *    wpis ten dla operacji poprzedniej i następnej zawartości argumentu przegląda dostępne poziomy\n
 * 5. wpis z etykietą "GO BACK" prowadzący z powrotem do menu wyboru trybu gry\n
 * 6. operacja pod klawisz ESC prowadząca z powrotem do menu wyboru trybu gry\n
 *
 * @param main_font wskaźnik na główną czcionkę
 * @param sub_font  wskaźnik na poboczną czcionkę
 * 
 * @return wskaźnik na utworzone menu wyboru poziomu
*/
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
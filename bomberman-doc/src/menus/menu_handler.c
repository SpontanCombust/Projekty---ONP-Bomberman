/** @file menu_handler.c
 * 
 * @brief Plik zawiera funkcje do egzekwowania przypisanych elementom menu operacji i aktualizowania stanu menu
 * 
 * Plik zawiera funkcje egzekwujące operacje przypisane operacji wybrania i/lub operacjom zmiany \n
 * zmiennej wpisu. Znajdują sie tu również funkcje przełączania kolejnych wpisow w menu oraz aktualizowania \n
 * stanu wpisu ze zmienna.
 * 
 * @author  Przemysław Cedro
 * @date    2020.05.21
*/


#include "../../headers/menus.h"

/** @brief Egzekwuje wybranie obecnie zaznaczonego wpisu 
 * 
 * Egzekwuje funkcję sygnalizacyjną stanu gry przypisana do operacji wybrania dla obecnie zaznaczonego wpisu menu.
 *
 * @param menu  wskaźnik na menu
 * @param gs    wskaznik na stan gry
*/
void executeSelectOperation( Menu *menu, GameState *gs )
{
    if( menu->entries[ menu->currently_highlighted ].operation_select != NULL )
        menu->entries[ menu->currently_highlighted ].operation_select( gs );
}

/** @brief Egzekwuje zmianę zmiennej wpisu na poprzednią zawartość
 * 
 * Egzekwuje funkcję sygnalizacyjną stanu gry przypisaną do operacji zmiany zmiennej wpisu \n
 * na poprzednią zawartość dla obecnie zaznaczonego wpisu menu.
 *
 * @param menu  wskaźnik na menu
 * @param gs    wskaźnik na stan gry
*/
void executeLeftOperation( Menu *menu, GameState *gs )
{
    if( menu->entries[ menu->currently_highlighted ].operation_left != NULL )
        menu->entries[ menu->currently_highlighted ].operation_left( gs ); 
}

/** @brief Egzekwuje zmianę zmiennej wpisu na nastepną zawartosc
 * 
 * Egzekwuje funkcję sygnalizacyjną stanu gry przypisaną do operacji zmiany zmiennej wpisu \n
 * na nastepną zawartość dla obecnie zaznaczonego wpisu menu.
 *
 * @param menu  wskaźnik na menu
 * @param gs    wskaźnik na stan gry
*/
void executeRightOperation( Menu *menu, GameState *gs )
{
    if( menu->entries[ menu->currently_highlighted ].operation_right != NULL )
        menu->entries[ menu->currently_highlighted ].operation_right( gs );
}

/** @brief Egzekwuje wyjście przez ESC
 * 
 * Egzekwuje funkcję sygnalizacyjną stanu gry przypisaną do operacji wyjścia przez przycisk ESC dla menu
 *
 * @param menu  wskaźnik na menu
 * @param gs    wskaźnik na stan gry
*/
void executeEscOperation( Menu *menu, GameState *gs )
{
    if( menu->operation_esc != NULL )
        menu->operation_esc( gs );
}

/** @brief Wylicza indeks kolejnego możliwego do zaznaczenia wpisu
 * 
 * Cyklicznie podąża po indeksach tablicy wpisów w menu. Jeśli indeks będzie ujemny, wróci na koniec \n
 * tablicy; jeśli ten będzie wykraczał poza zakres tablicy, wróci na jej początek. Ilość przejść jest \n
 * z góry ograniczona przez MAX_ENTRIES. Przy każdej iteracji porusza się o ilość kroków podaną w parametrze. \n
 * Jeśli odnajdzie wpis, który jest aktywny i możliwy do zaznaczenia, zwraca jego indeks. W przeciwnym wypadku \n
 * po zakończeniu poszukiwań zwraca indeks obecnie zaznaczonego wpisu.
 *
 * @param menu wskaźnik na menu
 * @param step minimalna ilość kroków, o którą powinien zmienić sie wpis
 * 
 * @return wyliczony indeks wpisu
*/
static int getNextHighlightableEntryIndex( Menu *menu, int step )
{
    int to_be_highlighted = menu->currently_highlighted;
    for (int i = 0; i < MAX_ENTRIES; i++)
    {
        to_be_highlighted += step;

        if( to_be_highlighted >= MAX_ENTRIES )
            to_be_highlighted = 0;
        else if( to_be_highlighted < 0 )
            to_be_highlighted = MAX_ENTRIES - 1;

        if( menu->entries[ to_be_highlighted ].entry_set && menu->entries[ to_be_highlighted ].highlightable )
            return to_be_highlighted;
    }
    return to_be_highlighted;
}

/** @brief Przełącza obecnie zaznaczony wpis na kolejny możliwy
 * 
 * Pobiera indeks kolejnego możliwego do zaznaczenia wpisu z funkcji getNextHighlightableEntryIndex \n
 * i aplikuje go do obecnego indeksu zaznaczenia, aktualizując jego stan.
 *
 * @param menu wskaźnik na menu
 * @param step minimalna ilość kroków, o którą powinien zmienić sie wpis
*/
void switchEntry( Menu *menu, int step ) {
    menu -> currently_highlighted = getNextHighlightableEntryIndex( menu, step );
}

/** @brief Aktualizuje zmienną wpisu o danym indeksie
 * 
 * Dla wpisu o danym indeksie aktualizuje jego zmienną kopiujac zawartość podanego stringa \n
 * do tekstu zmiennej. Długość skopiowanego stringa ograniczona jest przez MAX_ENTRY_VAR_LENGTH.
 * 
 * @param menu wskaźnik na menu
 * @param var_index indeks wpisu ze zmienną
 * @param entry_var nowy tekst zmiennej
*/
void updateEntryVar( Menu *menu, int var_index, char *entry_var ) {
    strncpy( menu->entries[ var_index ].entry_var, entry_var, MAX_ENTRY_VAR_LENGTH );
}
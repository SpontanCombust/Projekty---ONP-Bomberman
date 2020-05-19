/** @file menu_essentials.c
 * 
 * @brief Plik zawiera podstawowe metody dla menu
 * 
 * Plik zawiera podstawowe metody dla tworzenia, ustawiania zawartości i cech oraz zwalniania\n
 * pamieci z menu.
 * 
 * @author  Przemyslaw Cedro
 * @date    2020.05.19
*/

#include "../../headers/menus.h"

#include "../../headers/_game_rules.h"

/** @brief Inicjuje wartosci dla wpisu w menu
 * 
 * Przypisuje domyslne wartosci i zawartosci dla pol kazdego wpisu (Entry) w menu
 * 
 * @param menu menu, ktore ma zostac wyzerowane
*/
static void initEntries( Menu *menu )
{
    for (int i = 0; i < MAX_ENTRIES; i++)
    {
        menu->entries[i].entry_set = false;
        menu->entries[i].highlightable = false;
        menu->entries[i].has_var = false;
        strcpy( menu->entries[i].entry_text, "" );
        strcpy( menu->entries[i].entry_var, "" );
        menu->entries[i].operation_left = NULL;
        menu->entries[i].operation_right = NULL;
        menu->entries[i].operation_select = NULL;
    }
}

/** @brief Tworzy i zwraca menu o danej zawartosci
 *
 * Dynamicznie alokuje pamiec na zmienna typu Menu, przypisuje wiekoszci jej pol domyslne wartosci,
 * inicujuje wpisy w menu oraz ustawia dla menu czcionki podane w parametrach.
 * Maksymalna liczba wpisow zdefiniowana jest przez MAX_ENTRIES w _game_rules.h.
 * 
 * @param main_font glowna czcionka uzywana w menu
 * @param sub_font  poboczna czcionka uzywana w menu
 * 
 * @return wskaznik na utworzone menu
*/
Menu *createMenu( ALLEGRO_FONT *main_font, ALLEGRO_FONT *sub_font )
{
    Menu *menu = (Menu *)malloc( sizeof( Menu ) );

    menu -> operation_esc = NULL;
    menu -> default_highlighted = 0;
    menu -> currently_highlighted = 0;
    menu -> main_font = main_font;
    menu -> sub_font = sub_font;
    menu -> main_font_color = COLOR_WHITE;
    menu -> sub_font_color = COLOR_WHITE;
    menu -> entry_orig_x = 0;
    menu -> entry_orig_y = 0;
    menu -> line_spacing = 0;
    menu -> bg_x = 0;
    menu -> bg_y = 0;
    menu -> bg_w = 0;
    menu -> bg_h = 0;
    menu -> bg_color = COLOR_BLACK;
    menu -> bmp = NULL;
    initEntries( menu );

    return menu;
}

/** @brief Ustawia dla danego menu pola odpowiadajace za wyglad i rozmieszczenie tekstu
 * 
 * Ustawia dla danego menu pola odpowiadajace za kolor glownej i pobocznej czcionki,\n
 * punkt poczatkowy dla wpisow wzgledem tla menu oraz odleglosc miedzy wpisami w menu.
 *
 * @param menu              menu
 * @param main_font_color   kolor glownej czcionki
 * @param sub_font_color    kolor pobocznej czcionki
 * @param entry_orig_x      wspolrzedna pikselowa x punktu poczatkowego dla wpisow w menu wzgledem punktu poczotkowego tla
 * @param entry_orig_y      wspolrzedna pikselowa y punktu poczatkowego dla wpisow w menu wzgledem punktu poczotkowego tla
 * @param line_spacing      odleglosc miedzy wpisami w menu
*/
void setMenuTextData( Menu *menu, ALLEGRO_COLOR main_font_color, ALLEGRO_COLOR sub_font_color, float entry_orig_x, float entry_orig_y, float line_spacing )
{
    menu -> main_font_color = main_font_color;
    menu -> sub_font_color = sub_font_color;
    menu -> entry_orig_x = entry_orig_x;
    menu -> entry_orig_y = entry_orig_y;
    menu -> line_spacing = line_spacing;
}

/** @brief Ustawia dla danego menu pola odpowiadajace za wyglad i rozmieszczenie tla
 * 
 * Ustawia dla danego menu pola odpowiadajace za kolor tla, kanal alfa tla,\n
 * punkt poczatkowy umieszczenia tla oraz jego wymiary
 *
 * @param menu      menu
 * @param bg_color  kolor tla
 * @param bg_alpha  kanal alfa tla
 * @param bg_x      wspolrzedna pikselowa x punktu poczatkowego dla tla menu
 * @param bg_y      wspolrzedna pikselowa y punktu poczatkowego dla tla menu
 * @param bg_w      szerokosc tla menu
 * @param bg_h      wysokosc tla menu
*/
void setMenuBgData( Menu *menu, ALLEGRO_COLOR bg_color, float bg_alpha, float bg_x, float bg_y, float bg_w, float bg_h )
{
    menu -> bg_x = bg_x;
    menu -> bg_y = bg_y;
    menu -> bg_w = bg_w;
    menu -> bg_h = bg_h;
    menu -> bg_color = bg_color;
    menu -> bg_alpha = bg_alpha;
    menu -> bmp = al_create_bitmap( bg_w, bg_h );
}

/** @brief Ustawia tekst wpisu w menu
 * 
 *  Dla wpisu o danym indeksie w menu ustawia tekst etykiety, jaki bedzie wyswietlany w tym wpisie
 *
 * @param menu          menu
 * @param entry_index   indeks wpisu w menu
 * @param entry_text    tekst etykiety wpisu
*/
void setEntryText( Menu *menu, int entry_index, char *entry_text ) {
    strncpy( menu->entries[ entry_index ].entry_text, entry_text, MAX_ENTRY_TEXT_LENGTH );
}

/** @brief Ustawia zmienna wpisu w menu
 * 
 *  Dla wpisu o danym indeksie w menu ustawia tekst zmiennej, jaki bedzie wyswietlany w tym wpisie
 *
 * @param menu          menu
 * @param entry_index   indeks wpisu w menu
 * @param entry_var     tekst zmiennej wpisu
*/
void setEntryVar( Menu *menu, int entry_index, char *entry_var ) {
    strncpy( menu->entries[ entry_index ].entry_var, entry_var, MAX_ENTRY_VAR_LENGTH );
    menu->entries[ entry_index ].has_var = true;
}

/** @brief Ustawia operacje wyboru dla wpisu w menu
 * 
 * Dla wpisu o danym indeksie w menu ustawia funkcje sygnalizacyjna stanu gry dla operacji wybierania tego wpisu.
 *
 * @param menu              menu
 * @param entry_index       indeks wpisu w menu
 * @param operation_select  wskaznik na funkcje sygnalizacyjna stanu gry dla operacji wybierania tego wpisu
*/
void setEntrySelectOperation( Menu *menu, int entry_index, void ( *operation_select )( GameState * ) ) {
    menu -> entries[ entry_index ].operation_select = operation_select;
}

/** @brief Ustawia operacje zmiany zmiennej w lewo dla wpisu w menu
 * 
 * Dla wpisu o danym indeksie w menu ustawia funkcje sygnalizacyjna stanu gry dla operacji zmiany zmiennej wpisu w lewo.
 *
 * @param menu              menu
 * @param entry_index       indeks wpisu w menu
 * @param operation_select  wskaznik na funkcje sygnalizacyjna stanu gry dla operacji zmiany zmiennej wpisu w lewo
*/
void setEntryLeftOperation( Menu *menu, int entry_index, void ( *operation_left )( GameState * ) ) {
    menu -> entries[ entry_index ].operation_left = operation_left;
}

/** @brief Ustawia operacje zmiany zmiennej w prawo dla wpisu w menu
 * 
 * Dla wpisu o danym indeksie w menu ustawia funkcje sygnalizacyjna stanu gry dla operacji zmiany zmiennej wpisu w prawo.
 *
 * @param menu              menu
 * @param entry_index       indeks wpisu w menu
 * @param operation_select  wskaznik na funkcje sygnalizacyjna stanu gry dla operacji zmiany zmiennej wpisu w prawo
*/
void setEntryRightOperation( Menu *menu, int entry_index, void ( *operation_right )( GameState * ) ) {
    menu -> entries[ entry_index ].operation_right = operation_right;
}

/** @brief Ustawia operacje wyjscia ESC dla menu
 * 
 * Dla danego menu ustawia funkcje sygnalizacyjna stanu gry dla operacji wyjscia z menu za pomoca ESC.
 *
 * @param menu              menu
 * @param operation_select  wskaznik na funkcje sygnalizacyjna stanu gry dla operacji wyjscia z menu za pomoca ESC
*/
void setMenuEscOperation( Menu *menu, void ( *operation_esc )( GameState * ) ) {
    menu -> operation_esc = operation_esc;
}

/** @brief Ustawia wpis jako mozliwy do zaznaczenia
 * 
 * Ustawia wpis o danym indeksie jako zdatny do zaznaczenia (przejscia na niego kursorem) w menu
 *
 * @param menu          menu
 * @param entry_index   indeks wpisu w menu
*/
void setHighlightable( Menu *menu, int entry_index ) {
    menu -> entries[ entry_index ].highlightable = true;
}

/** @brief Ustawia indeks domyslnie zaznaczonego wpisu
 * 
 * Ustawia dany indeks, dla ktorego wpis o tym indeksie ma byc domyslnie zaznaczony przy wejsciu do menu 
 *
 * @param menu              menu
 * @param default_hl_index  indeks domyslnie zaznaczonego wpisu
*/
void setDefaultHighlighted( Menu *menu, int default_hl_index ) {
    menu -> default_highlighted = menu -> currently_highlighted = default_hl_index;
}

/** @brief Resetuje obecnie zaznaczony wpis do domyslnego
 * 
 * Resetuje dla danego menu obecnie zaznaczony wpis i resetuje obecny indeks do indeksu domyslnego
 *
 * @param menu menu
*/
void resetToDefaultHighlighted( Menu *menu ) {
    menu -> currently_highlighted = menu->default_highlighted;
}

/** @brief Uaktywnia wpis
 * 
 * Wpis o danym indeksie dla danego menu zostaje aktywowany i moze teraz zostawac rysowany i/lub\n
 * moga byc na nim wykonywane zaznaczenie lub operacje wyboru i zmian zmiennej.
 *
 * @param menu          menu
 * @param entry_index   indeks wpisu w menu
*/
void enableEntry( Menu *menu, int entry_index ) {
    menu -> entries[ entry_index ].entry_set = true;
}

/** @brief Zwalnia pamiec z menu
 * 
 * Zwalnia pamiec z dynamicznie zalokowanej zmiennej typu Menu i z bitmapy menu.
 *
 * @param menu wskaznik na wskaznik menu
*/
void destroyMenu( Menu **menu )
{
    al_destroy_bitmap( ( *menu )->bmp );
    free( *menu );
    *menu = NULL;
}
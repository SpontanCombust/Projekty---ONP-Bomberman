/** @file menu_essentials.c
 * 
 * @brief Plik zawiera podstawowe metody dla menu
 * 
 * Plik zawiera podstawowe metody dla tworzenia, ustawiania zawartości i cech oraz zwalniania \n
 * pamięci z menu.
 * 
 * @author  Przemysław Cedro
 * @date    2020.05.19
*/


#include "../../headers/menus.h"

#include "../../headers/_game_rules.h"

/** @brief Inicjuje wartości dla wpisu w menu
 * 
 * Przypisuje domyślne wartości i zawartości dla pól każdego wpisu w menu
 * 
 * @param menu menu, które ma zostać wyzerowane
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

/** @brief Tworzy i zwraca menu o danej zawartości
 *
 * Dynamicznie alokuje pamięć na zmienną typu Menu, przypisuje jej polom domyślne wartości, \n
 * inicjuje wpisy w menu oraz ustawia dla menu czcionki podane w parametrach.
 * 
 * @param main_font główna czcionka używana w menu
 * @param sub_font  poboczna czcionka używana w menu
 * 
 * @return wskaźnik na utworzone menu
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

/** @brief Ustawia dla danego menu pola odpowiadające za wygląd i rozmieszczenie tekstu
 * 
 * Ustawia dla danego menu pola odpowiadające za kolor glównej i pobocznej czcionki, \n
 * punkt początkowy dla wpisów wzgledem tła menu oraz odległość miedzy wpisami w menu.
 *
 * @param menu              wskaźnik na menu
 * @param main_font_color   kolor główny dla czcionek
 * @param sub_font_color    kolor poboczny dla czcionek
 * @param entry_orig_x      współrzędna pikselowa x punktu początkowego dla wpisów w menu względem punktu początkowego tła
 * @param entry_orig_y      współrzędna pikselowa y punktu początkowego dla wpisów w menu względem punktu początkowego tła
 * @param line_spacing      odleglość miedzy wpisami w menu
*/
void setMenuTextData( Menu *menu, ALLEGRO_COLOR main_font_color, ALLEGRO_COLOR sub_font_color, float entry_orig_x, float entry_orig_y, float line_spacing )
{
    menu -> main_font_color = main_font_color;
    menu -> sub_font_color = sub_font_color;
    menu -> entry_orig_x = entry_orig_x;
    menu -> entry_orig_y = entry_orig_y;
    menu -> line_spacing = line_spacing;
}

/** @brief Ustawia dla danego menu pola odpowiadające za wygląd i rozmieszczenie tła
 * 
 * Ustawia dla danego menu pola odpowiadające za kolor tła, kanał alfa tła, \n
 * punkt początkowy umieszczenia tła oraz jego wymiary. Tworzy bitmapę menu, \n
 * której rozmiar zdefiniowany jest przez rozmiar tła.
 *
 * @param menu      wskaźnik na menu
 * @param bg_color  kolor tła
 * @param bg_alpha  kanał alfa tła
 * @param bg_x      współrzędna pikselowa x punktu początkowego dla tła menu
 * @param bg_y      współrzędna pikselowa y punktu początkowego dla tła menu
 * @param bg_w      szerokość tła menu
 * @param bg_h      wysokość tła menu
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
 *  Dla wpisu o danym indeksie w menu ustawia tekst etykiety, jaki będzie wyświetlany w tym wpisie.
 *
 * @param menu          wskaźnik na menu
 * @param entry_index   indeks wpisu w menu
 * @param entry_text    tekst etykiety wpisu
*/
void setEntryText( Menu *menu, int entry_index, char *entry_text ) {
    strncpy( menu->entries[ entry_index ].entry_text, entry_text, MAX_ENTRY_TEXT_LENGTH );
}

/** @brief Ustawia zmienną wpisu w menu
 * 
 *  Dla wpisu o danym indeksie w menu ustawia tekst zmiennej, jaki bedzie wyświetlany w tym wpisie
 *
 * @param menu          wskaźnik na menu
 * @param entry_index   indeks wpisu w menu
 * @param entry_var     tekst zmiennej wpisu
*/
void setEntryVar( Menu *menu, int entry_index, char *entry_var ) {
    strncpy( menu->entries[ entry_index ].entry_var, entry_var, MAX_ENTRY_VAR_LENGTH );
    menu->entries[ entry_index ].has_var = true;
}

/** @brief Ustawia operację wyboru dla wpisu w menu
 * 
 * Dla wpisu o danym indeksie w menu ustawia funkcję sygnalizacyjną stanu gry dla operacji \n
 * wybierania tego wpisu.
 *
 * @param menu              wskaźnik na menu
 * @param entry_index       indeks wpisu w menu
 * @param operation_select  wskaźnik na funkcję sygnalizacyjną stanu gry dla operacji wybierania tego wpisu
*/
void setEntrySelectOperation( Menu *menu, int entry_index, void ( *operation_select )( GameState * ) ) {
    menu -> entries[ entry_index ].operation_select = operation_select;
}

/** @brief Ustawia operację zmiany zmiennej wpisu w menu na poprzednią zawartość
 * 
 * Dla wpisu o danym indeksie w menu ustawia funkcję sygnalizacyjną stanu gry dla operacji \n
 * zmiany zmiennej wpisu na poprzednią.
 *
 * @param menu              wskaźnik na menu
 * @param entry_index       indeks wpisu w menu
 * @param operation_select  wskaźnik na funkcję sygnalizacyjną stanu gry dla operacji zmiany zmiennej wpisu na poprzednią
*/
void setEntryLeftOperation( Menu *menu, int entry_index, void ( *operation_left )( GameState * ) ) {
    menu -> entries[ entry_index ].operation_left = operation_left;
}

/** @brief Ustawia operację zmiany zmiennej wpisu w menu na nastepna zawartosc
 * 
 * Dla wpisu o danym indeksie w menu ustawia funkcję sygnalizacyjną stanu gry dla operacji zmiany \n
 * zmiennej wpisu na następną.
 *
 * @param menu              wskaźnik na menu
 * @param entry_index       indeks wpisu w menu
 * @param operation_select  wskaznik na funkcje sygnalizacyjna stanu gry dla operacji zmiany zmiennej wpisu na następną
*/
void setEntryRightOperation( Menu *menu, int entry_index, void ( *operation_right )( GameState * ) ) {
    menu -> entries[ entry_index ].operation_right = operation_right;
}

/** @brief Ustawia operację wyjścia przez ESC dla menu
 * 
 * Dla danego menu ustawia funkcję sygnalizacyjną stanu gry dla operacji wyjścia z menu za pomocą ESC.
 *
 * @param menu              wskaźnik na menu
 * @param operation_select  wskaźnik na funkcję sygnalizacyjną stanu gry dla operacji wyjścia z menu za pomoca ESC
*/
void setMenuEscOperation( Menu *menu, void ( *operation_esc )( GameState * ) ) {
    menu -> operation_esc = operation_esc;
}

/** @brief Ustawia wpis jako możliwy do zaznaczenia
 * 
 * Ustawia wpis o danym indeksie jako zdatny do zaznaczenia (przejścia na niego kursorem) w menu.
 *
 * @param menu          wskaźnik na menu
 * @param entry_index   indeks wpisu w menu
*/
void setHighlightable( Menu *menu, int entry_index ) {
    menu -> entries[ entry_index ].highlightable = true;
}

/** @brief Ustawia indeks domyślnie zaznaczonego wpisu
 * 
 * Ustawia dany indeks, dla którego wpis o tym indeksie ma byc domyślnie zaznaczony przy wejściu do menu.
 *
 * @param menu              wskaźnik na menu
 * @param default_hl_index  indeks domyślnie zaznaczonego wpisu
*/
void setDefaultHighlighted( Menu *menu, int default_hl_index ) {
    menu -> default_highlighted = menu -> currently_highlighted = default_hl_index;
}

/** @brief Resetuje obecnie zaznaczony wpis do domyślnego
 * 
 * Resetuje dla danego menu obecnie zaznaczony wpis i resetuje obecny indeks do indeksu domyślnego.
 *
 * @param menu wskaźnik na menu
*/
void resetToDefaultHighlighted( Menu *menu ) {
    menu -> currently_highlighted = menu->default_highlighted;
}

/** @brief Uaktywnia wpis
 * 
 * Wpis o danym indeksie dla danego menu zostaje aktywowany i może teraz zostawac rysowany i/lub\n
 * mogą byc na nim wykonywane zaznaczenie lub operacje wyboru i zmian zmiennej.
 *
 * @param menu          wskaźnik na menu
 * @param entry_index   indeks wpisu w menu
*/
void enableEntry( Menu *menu, int entry_index ) {
    menu -> entries[ entry_index ].entry_set = true;
}

/** @brief Zwalnia pamięć z menu
 * 
 * Zwalnia pamięć z dynamicznie alokowanej zmiennej typu Menu i z bitmapy menu.
 *
 * @param menu podwójny wskaźnik na menu
*/
void destroyMenu( Menu **menu )
{
    al_destroy_bitmap( ( *menu )->bmp );
    free( *menu );
    *menu = NULL;
}
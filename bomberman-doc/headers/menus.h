/** @file menus.h
 * 
 * @brief Plik zawiera definicje stałych dla menu, struktur MenuEntry i Menu oraz deklaracje stworzonych dla systemu Menu funkcji
 * 
 * @author  Przemysław Cedro
 * @date    2020.05.29
*/

#ifndef MENUS_H
#define MENUS_H

#include "_game_state.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>

#define MAX_ENTRIES 10 /** Maksymalna ilość wpisów MenuEntry w Menu */
#define MAX_ENTRY_TEXT_LENGTH 20 /** Maksymalna długość tekstu etykiety wpisu MenuEntry */
#define MAX_ENTRY_VAR_LENGTH 10 /** Maksymalna długość tekstu zmiennej wpisu MenuEntry */
#define DEFAULT_LINE_SPACING 5 /** Domyślna odległość między wpisami */

/**
 * @brief Struktura wpisu w Menu, MenuEntry
 * 
 * Struktura stworzona na potrzeby posiadania tworu o własnych polach tekstu i operacjach, \n
 * które może wywoływać. Twór ten może istnieć w wielu ilościach wewnątrz jednego menu. \n
 * MenuEntry to nic innego niż linijka w menu, która może przechowywać tekst, ale również \n
 * po naciśnięciu odpowiedniego klawisza, gdy jest podświetlona, wykonać pewną akcję. \n
 * \n
 * Wpis MenuEntry zawiera niezmienialny tekst etykiety oraz może zawierać tekst zmiennej, \n
 * którą typowo można zamieniać przy pomocy strzałek w lewo i prawo. \n
 * Jeśli wpis jest ustawiony jako niemożliwy do podświetlenia, traktowany jest jak nagłówek menu.
 */
typedef struct S_MenuEntry
{
    bool entry_set; /**< Czy wpis jest aktywny (brany pod uwagę przez program) */
    bool highlightable; /**< Czy wpis jest możliwy do podświetlenia (zaznaczenia) */
    bool has_var; /**< Czy wpis posiada zmienną */
    char entry_text[ MAX_ENTRY_TEXT_LENGTH ]; /**< Tekst etykiety o maksymalnej długości MAX_ENTRY_TEXT_LENGTH */
    char entry_var[ MAX_ENTRY_VAR_LENGTH ]; /**< Tekst zmiennej o maksymalnej długości MAX_ENTRY_VAR_LENGTH */
    void ( *operation_select )( GameState * ); /**< Wskaźnik na funkcję wywoływaną przy naciśnięciu ENTER na wpisie */
    void ( *operation_left )( GameState * ); /**< Wskaźnik na funkcję wywoływaną przy naciśnięciu strzałki W LEWO na wpisie */
    void ( *operation_right )( GameState * ); /**< Wskaźnik na funkcję wywoływaną przy naciśnięciu strzałki W PRAWO na wpisie */

} MenuEntry;

/**
 * @brief Struktura Menu
 * 
 * Struktura stworzona na potrzeby systemu o oddzielnych oknach z wpisami, między którymi da się \n
 * przemieszczać i da się bez problemu ustalać ich wygląd. \n
 * \n
 * Menu posiada tablicę wpisów, które są rysowane od danego punktu, dwie czcionki, dwa kolory \n
 * do tych czcionek i tło o danych wymiarach, punkcie początkowym. \n
 * Przechowywana jest informacja o obecnie podświetlonym wpisie i o domyślnie podświetlonym. \n
 * Menu ma też własną operację wykonywaną przy naciśnięciu klawisza ESC.
 */
typedef struct S_Menu
{
    void ( *operation_esc )( GameState * ); /**< Wskaźnik na funkcję wywołaną przy naciśnięciu klawisza ESC */

    int default_highlighted; /**< Indeks domyślnie podświetlonego wpisu */
    int currently_highlighted; /**< Indeks obecnie podświetlonego wpisu */
    MenuEntry entries[ MAX_ENTRIES ]; /**< Tablica wpisów o wielkości MAX_ENTRIES */
    
    ALLEGRO_FONT *main_font; /**< Główna czcionka */
    ALLEGRO_FONT *sub_font; /**< Poboczna czcionka */
    ALLEGRO_COLOR main_font_color; /**< Główny kolor czcionki */
    ALLEGRO_COLOR sub_font_color; /**< Poboczny kolor czcionki */
    float entry_orig_x, entry_orig_y; /**< Punkt początkowy rysowania wpisów */
    float line_spacing; /**< Odstęp między wpisami */

    float bg_x, bg_y, bg_w, bg_h; /**< Punkt początkowy, szerokość i wysokość tła menu */
    ALLEGRO_COLOR bg_color; /**< Kolor tła menu */
    float bg_alpha; /**< Kanał alfa tła menu */
    ALLEGRO_BITMAP *bmp; /**< Bitmapa menu */

} Menu;


// ==================== menu_essentials.c ===================

/** @brief Tworzy i zwraca menu o danej zawartości */
Menu *createMenu( ALLEGRO_FONT *main_font, ALLEGRO_FONT *sub_font );
/** @brief Ustawia dla danego menu pola odpowiadające za wygląd i rozmieszczenie tekstu */
void setMenuTextData( Menu *menu, ALLEGRO_COLOR main_font_color, ALLEGRO_COLOR sub_font_color, float entry_orig_x, float entry_orig_y, float line_spacing );
/** @brief Ustawia dla danego menu pola odpowiadające za wygląd i rozmieszczenie tła */
void setMenuBgData( Menu *menu, ALLEGRO_COLOR bg_color, float bg_alpha, float bg_x, float bg_y, float bg_w, float bg_h );
/** @brief Ustawia tekst wpisu w menu */
void setEntryText( Menu *menu, int entry_index, char *entry_text );
/** @brief Ustawia zmienną wpisu w menu */
void setEntryVar( Menu *menu, int entry_index, char *entry_var );
/** @brief Ustawia operację wyboru dla wpisu w menu */
void setEntrySelectOperation( Menu *menu, int entry_index, void ( *operation_select )( GameState * ) );
/** @brief Ustawia operację zmiany zmiennej wpisu w menu na poprzednią zawartość */
void setEntryLeftOperation( Menu *menu, int entry_index, void ( *operation_left )( GameState * ) );
/** @brief Ustawia operację zmiany zmiennej wpisu w menu na nastepna zawartosc */
void setEntryRightOperation( Menu *menu, int entry_index, void ( *operation_right )( GameState * ) );
/** @brief Ustawia operację wyjścia przez ESC dla menu */
void setMenuEscOperation( Menu *menu, void ( *operation_esc )( GameState * ) );
/** @brief Ustawia wpis jako możliwy do zaznaczenia */
void setHighlightable( Menu *menu, int entry_index );
/** @brief Ustawia indeks domyślnie zaznaczonego wpisu */
void setDefaultHighlighted( Menu *menu, int default_hl_index );
/** @brief Resetuje obecnie zaznaczony wpis do domyślnego */
void resetToDefaultHighlighted( Menu *menu );
/** @brief Uaktywnia wpis */
void enableEntry( Menu *menu, int entry_index );
/** @brief Zwalnia pamięć z menu */
void destroyMenu( Menu **menu );


// ===================== menu_handler.c =====================

/** @brief Egzekwuje wybranie obecnie zaznaczonego wpisu  */
void executeSelectOperation( Menu *menu, GameState *gs );
/** @brief Egzekwuje zmianę zmiennej wpisu na poprzednią zawartość */
void executeLeftOperation( Menu *menu, GameState *gs );
/** @brief Egzekwuje zmianę zmiennej wpisu na nastepną zawartosc */
void executeRightOperation( Menu *menu, GameState *gs );
/** @brief Egzekwuje wyjście przez ESC */
void executeEscOperation( Menu *menu, GameState *gs );
/** @brief Przełącza obecnie zaznaczony wpis na kolejny możliwy */
void switchEntry( Menu *menu, int step );
/** @brief Aktualizuje zmienną wpisu o danym indeksie */
void updateEntryVar( Menu *menu, int var_index, char *entry_var );


// ===================== menu_rendering.c ===================

/** @brief Renderuje bitmapę menu */
void updateMenuBitmap( Menu *menu, ALLEGRO_DISPLAY *display );


// ===================== menu_templates.c ===================

/** @brief Zwraca wzorzec menu głównego */
Menu *createMainMenu( ALLEGRO_FONT *main_font, ALLEGRO_FONT *sub_font );
#define SKIN_P1_VAR_INDEX 2 /** Indeks wpisu ze zmienną skórki dla pierwszego gracza */
#define SKIN_P2_VAR_INDEX 3 /** Indeks wpisu ze zmienną skórki dla drugiego gracza */
/** @brief Zwraca wzorzec menu opcji */
Menu *createOptionsMenu( ALLEGRO_FONT *font, ALLEGRO_FONT *sub_font );
/** @brief Zwraca wzorzec menu pauzy */
Menu *createPauseMenu( ALLEGRO_FONT *font, ALLEGRO_FONT *sub_font );
/** @brief Zwraca wzorzec menu wyboru trybu gry */
Menu *createModeSelectionMenu( ALLEGRO_FONT *font, ALLEGRO_FONT *sub_font );
#define LEVEL_VAR_INDEX 3 /** Indeks wpisu ze zmienną wybranego poziomu */
/** @brief Zwraca wzorzec menu wyboru poziomu */
Menu *createLevelSelectionMenu( ALLEGRO_FONT *main_font, ALLEGRO_FONT *sub_font );

#endif
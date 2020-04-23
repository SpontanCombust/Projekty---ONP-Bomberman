#ifndef MENUS_H
#define MENUS_H

#include "_game_state.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>

#define MAX_ENTRIES 10
#define MAX_ENTRY_TEXT_LENGTH 20
#define DEFAULT_LINE_SPACING 5

typedef struct 
{
    bool entry_set;
    char entry_text[ MAX_ENTRY_TEXT_LENGTH + 1 ];
    void ( *operation_select )( GameState * );
    void ( *operation_left )( GameState * );
    void ( *operation_right )( GameState * );

} MenuEntry;

typedef struct
{
    void ( *operation_esc )( GameState * );

    int currently_selected;
    MenuEntry entries[ MAX_ENTRIES ];
    
    ALLEGRO_FONT *font;
    ALLEGRO_COLOR font_color;
    float entry_orig_x, entry_orig_y;
    float line_spacing;

    float bg_x, bg_y, bg_w, bg_h;
    ALLEGRO_COLOR bg_color;
    float bg_alpha;
    ALLEGRO_BITMAP *bmp;

} Menu;


// ==================== menu_essentials.c ===================

Menu *createMenu( ALLEGRO_FONT *font );
void setMenuTextData( Menu *menu, ALLEGRO_COLOR font_color, float entry_orig_x, float entry_orig_y, float line_spacing );
void setMenuBgData( Menu *menu, ALLEGRO_COLOR bg_color, float bg_alpha, float bg_x, float bg_y, float bg_w, float bg_h );
void destroyMenu( Menu **menu );


// ===================== menu_handler.c =====================

void setEntryText( Menu *menu, int entry_index, char *entry_text );
void setEntrySelectOperation( Menu *menu, int entry_index, void ( *operation_select )( GameState * ) );
void setEntryLeftOperation( Menu *menu, int entry_index, void ( *operation_left )( GameState * ) );
void setEntryRightOperation( Menu *menu, int entry_index, void ( *operation_right )( GameState * ) );
void setMenuEscOperation( Menu *menu, void ( *operation_esc )( GameState * ) );
void enableEntry( Menu *menu, int entry_index );
void executeSelectOperation( Menu *menu, GameState *gs );
void executeLeftOperation( Menu *menu, GameState *gs );
void executeRightOperation( Menu *menu, GameState *gs );
void executeEscOperation( Menu *menu, GameState *gs );
void updateCurrentlySelectedEntry( Menu *menu, int step );


// ===================== menu_rendering.c ===================

void updateMenuBitmap( Menu *menu, ALLEGRO_DISPLAY *display );


// ===================== menu_templates.c ===================

Menu *createMainMenu( ALLEGRO_FONT *font );
Menu *createOptionsMenu( ALLEGRO_FONT *font );
Menu *createPauseMenu( ALLEGRO_FONT *font );
Menu *createModeSelectionMenu( ALLEGRO_FONT *font );

#endif
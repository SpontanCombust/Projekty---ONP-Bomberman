#ifndef MENUS_H
#define MENUS_H

#include "_game_state.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>

#define MAX_ENTRIES 10
#define MAX_ENTRY_TEXT_LENGTH 20
#define MAX_ENTRY_VAR_LENGTH 10
#define DEFAULT_LINE_SPACING 5

typedef struct S_MenuEntry
{
    bool entry_set;
    bool highlightable;
    bool has_var;
    char entry_text[ MAX_ENTRY_TEXT_LENGTH ];
    char entry_var[ MAX_ENTRY_VAR_LENGTH ];
    void ( *operation_select )( GameState * );
    void ( *operation_left )( GameState * );
    void ( *operation_right )( GameState * );

} MenuEntry;

typedef struct S_Menu
{
    void ( *operation_esc )( GameState * );

    int default_highlighted;
    int currently_highlighted;
    MenuEntry entries[ MAX_ENTRIES ];
    
    ALLEGRO_FONT *main_font;
    ALLEGRO_FONT *sub_font;
    ALLEGRO_COLOR main_font_color;
    ALLEGRO_COLOR sub_font_color;
    float entry_orig_x, entry_orig_y;
    float line_spacing;

    float bg_x, bg_y, bg_w, bg_h;
    ALLEGRO_COLOR bg_color;
    float bg_alpha;
    ALLEGRO_BITMAP *bmp;

} Menu;


// ==================== menu_essentials.c ===================

Menu *createMenu( ALLEGRO_FONT *main_font, ALLEGRO_FONT *sub_font );
void setMenuTextData( Menu *menu, ALLEGRO_COLOR main_font_color, ALLEGRO_COLOR sub_font_color, float entry_orig_x, float entry_orig_y, float line_spacing );
void setMenuBgData( Menu *menu, ALLEGRO_COLOR bg_color, float bg_alpha, float bg_x, float bg_y, float bg_w, float bg_h );
void setEntryText( Menu *menu, int entry_index, char *entry_text );
void setEntryVar( Menu *menu, int entry_index, char *entry_var );
void setEntrySelectOperation( Menu *menu, int entry_index, void ( *operation_select )( GameState * ) );
void setEntryLeftOperation( Menu *menu, int entry_index, void ( *operation_left )( GameState * ) );
void setEntryRightOperation( Menu *menu, int entry_index, void ( *operation_right )( GameState * ) );
void setMenuEscOperation( Menu *menu, void ( *operation_esc )( GameState * ) );
void setHighlightable( Menu *menu, int entry_index );
void setDefaultHighlighted( Menu *menu, int default_hl_index );
void resetToDefaultHighlighted( Menu *menu );
void enableEntry( Menu *menu, int entry_index );
void destroyMenu( Menu **menu );


// ===================== menu_handler.c =====================

void executeSelectOperation( Menu *menu, GameState *gs );
void executeLeftOperation( Menu *menu, GameState *gs );
void executeRightOperation( Menu *menu, GameState *gs );
void executeEscOperation( Menu *menu, GameState *gs );
void switchEntry( Menu *menu, int step );
void updateEntryVar( Menu *menu, int var_index, char *entry_var );


// ===================== menu_rendering.c ===================

void updateMenuBitmap( Menu *menu, ALLEGRO_DISPLAY *display );


// ===================== menu_templates.c ===================

Menu *createMainMenu( ALLEGRO_FONT *main_font, ALLEGRO_FONT *sub_font );
#define SKIN_P1_VAR_INDEX 2
#define SKIN_P2_VAR_INDEX 3
Menu *createOptionsMenu( ALLEGRO_FONT *font, ALLEGRO_FONT *sub_font );
Menu *createPauseMenu( ALLEGRO_FONT *font, ALLEGRO_FONT *sub_font );
Menu *createModeSelectionMenu( ALLEGRO_FONT *font, ALLEGRO_FONT *sub_font );
#define LEVEL_VAR_INDEX 3
Menu *createLevelSelectionMenu( ALLEGRO_FONT *main_font, ALLEGRO_FONT *sub_font );

#endif
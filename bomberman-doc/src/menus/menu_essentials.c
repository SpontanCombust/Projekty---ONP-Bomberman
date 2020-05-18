#include "../../headers/menus.h"

#include "../../headers/_game_rules.h"

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

void setMenuTextData( Menu *menu, ALLEGRO_COLOR main_font_color, ALLEGRO_COLOR sub_font_color, float entry_orig_x, float entry_orig_y, float line_spacing )
{
    menu -> main_font_color = main_font_color;
    menu -> sub_font_color = sub_font_color;
    menu -> entry_orig_x = entry_orig_x;
    menu -> entry_orig_y = entry_orig_y;
    menu -> line_spacing = line_spacing;
}

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

void setEntryText( Menu *menu, int entry_index, char *entry_text ) {
    strncpy( menu->entries[ entry_index ].entry_text, entry_text, MAX_ENTRY_TEXT_LENGTH );
}

void setEntryVar( Menu *menu, int entry_index, char *entry_var ) {
    strncpy( menu->entries[ entry_index ].entry_var, entry_var, MAX_ENTRY_VAR_LENGTH );
    menu->entries[ entry_index ].has_var = true;
}

void setEntrySelectOperation( Menu *menu, int entry_index, void ( *operation_select )( GameState * ) ) {
    menu -> entries[ entry_index ].operation_select = operation_select;
}

void setEntryLeftOperation( Menu *menu, int entry_index, void ( *operation_left )( GameState * ) ) {
    menu -> entries[ entry_index ].operation_left = operation_left;
}

void setEntryRightOperation( Menu *menu, int entry_index, void ( *operation_right )( GameState * ) ) {
    menu -> entries[ entry_index ].operation_right = operation_right;
}

void setMenuEscOperation( Menu *menu, void ( *operation_esc )( GameState * ) ) {
    menu -> operation_esc = operation_esc;
}

void setHighlightable( Menu *menu, int entry_index ) {
    menu -> entries[ entry_index ].highlightable = true;
}

void setDefaultHighlighted( Menu *menu, int default_hl_index ) {
    menu -> default_highlighted = menu -> currently_highlighted = default_hl_index;
}

void resetToDefaultHighlighted( Menu *menu ) {
    menu -> currently_highlighted = menu->default_highlighted;
}

void enableEntry( Menu *menu, int entry_index ) {
    menu -> entries[ entry_index ].entry_set = true;
}

void destroyMenu( Menu **menu )
{
    al_destroy_bitmap( ( *menu )->bmp );
    free( *menu );
    *menu = NULL;
}
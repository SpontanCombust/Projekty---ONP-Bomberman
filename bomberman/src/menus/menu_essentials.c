#include "../../headers/menus.h"

static void initEntries( Menu *menu )
{
    for (int i = 0; i < MAX_ENTRIES; i++)
    {
        menu->entries[i].entry_set = false;
        strcpy( menu->entries[i].entry_text, "" );
        menu->entries[i].operation_left = NULL;
        menu->entries[i].operation_right = NULL;
        menu->entries[i].operation_select = NULL;
    }
}

Menu *createMenu( ALLEGRO_FONT *font )
{
    Menu *menu = (Menu *)malloc( sizeof( Menu ) );

    menu -> currently_selected = 0;
    menu -> font = font;
    menu -> font_color = al_map_rgb( 255, 255, 255 );
    menu -> entry_orig_x = 0;
    menu -> entry_orig_y = 0;
    menu -> line_spacing = 0;
    menu -> bg_x = 0;
    menu -> bg_y = 0;
    menu -> bg_w = 0;
    menu -> bg_h = 0;
    menu -> bg_color = al_map_rgb( 0, 0, 0 );
    menu -> bmp = NULL;
    initEntries( menu );

    return menu;
}

void setMenuTextData( Menu *menu, ALLEGRO_COLOR font_color, float entry_orig_x, float entry_orig_y, float line_spacing )
{
    menu -> font_color = font_color;
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

void destroyMenu( Menu **menu )
{
    al_destroy_bitmap( ( *menu )->bmp );
    free( *menu );
    *menu = NULL;
}
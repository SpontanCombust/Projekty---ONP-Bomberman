#include "../../headers/menus.h"


static void drawEntryText( Menu *menu, float y, int i )
{
    if( menu->currently_selected == i ) {
        float cursor_w = al_get_text_width( menu->font, ">" );
        float cursor_x = menu->entry_orig_x - al_get_text_width( menu->font, menu->entries[i].entry_text )/2 - cursor_w - 10;
        al_draw_text( menu->font, menu->font_color, cursor_x, y, 0, ">" );
    }

    al_draw_text( menu->font, menu->font_color, menu->entry_orig_x, y, ALLEGRO_ALIGN_CENTER, menu->entries[i].entry_text );
}

void updateMenuBitmap( Menu *menu, ALLEGRO_DISPLAY *display )
{
    al_set_target_bitmap( menu->bmp );
    al_clear_to_color( al_map_rgba( 0, 0, 0, 0 ) );
    al_clear_to_color( menu->bg_color );
    
    float current_y = menu->entry_orig_y;
    for (int i = 0; i < MAX_ENTRIES; i++)
    {
        if( menu->entries[i].entry_set )
            drawEntryText( menu, current_y, i );
        current_y += menu->line_spacing + al_get_font_ascent( menu->font ); 
    }

    al_set_target_backbuffer( display );
}
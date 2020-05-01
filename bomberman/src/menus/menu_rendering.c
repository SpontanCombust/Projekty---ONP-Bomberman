#include "../../headers/menus.h"

#include <allegro5/allegro_primitives.h>

static void drawEntryContent( Menu *menu, float y, int i )
{
    // al_draw_text( menu->main_font, menu->main_font_color, menu->entry_orig_x, y, ALLEGRO_ALIGN_CENTER, menu->entries[i].entry_text );
    float entry_text_width = al_get_text_width( menu->main_font, menu->entries[i].entry_text );
    
    if( menu->entries[i].has_var )
    {
        float arrow_w = al_get_text_width( menu->sub_font, "<" );
        float var_width = al_get_text_width( menu->main_font, menu->entries[i].entry_var );
        float line_w = entry_text_width + 20 + var_width + 2 * arrow_w;
        float line_x = menu->entry_orig_x - line_w/2;
        float arrow_y = y + al_get_font_ascent( menu->main_font )/2 - al_get_font_ascent( menu->sub_font )/4;
        float left_arrow_x = line_x + entry_text_width + 10;

        al_draw_text( menu->main_font, menu->main_font_color, line_x, y, ALLEGRO_ALIGN_LEFT, menu->entries[i].entry_text );
        al_draw_text( menu->main_font, menu->main_font_color, left_arrow_x + arrow_w + 5, y, ALLEGRO_ALIGN_LEFT, menu->entries[i].entry_var );

        if( menu->currently_highlighted == i )
        {
            float cursor_x = line_x - 10;
            al_draw_text( menu->main_font, menu->sub_font_color, cursor_x, y, ALLEGRO_ALIGN_RIGHT, ">" );
            al_draw_text( menu->sub_font, menu->sub_font_color, left_arrow_x, arrow_y, ALLEGRO_ALIGN_LEFT, "<" );
            al_draw_text( menu->sub_font, menu->sub_font_color, left_arrow_x + arrow_w + 5 + var_width + 5, arrow_y, ALLEGRO_ALIGN_LEFT, ">" );
        } else {
            al_draw_text( menu->sub_font, menu->main_font_color, left_arrow_x, arrow_y, ALLEGRO_ALIGN_LEFT, "<" );
            al_draw_text( menu->sub_font, menu->main_font_color, left_arrow_x + arrow_w + 5 + var_width + 5, arrow_y, ALLEGRO_ALIGN_LEFT, ">" );
        }
    }
    else
    {
        al_draw_text( menu->main_font, menu->main_font_color, menu->entry_orig_x, y, ALLEGRO_ALIGN_CENTER, menu->entries[i].entry_text );

        if( !menu->entries[i].highlightable ) {
            float line_y = y + al_get_font_ascent( menu->main_font ) + 5;
            al_draw_line( menu->entry_orig_x - entry_text_width/2, line_y, menu->entry_orig_x + entry_text_width/2, line_y, menu->main_font_color, 2 );
        }
        else if( menu->currently_highlighted == i ) {
            float cursor_x = menu->entry_orig_x - entry_text_width/2 - 10;
            al_draw_text( menu->main_font, menu->sub_font_color, cursor_x, y, ALLEGRO_ALIGN_RIGHT, ">" );
        }
    }
    
}

void updateMenuBitmap( Menu *menu, ALLEGRO_DISPLAY *display )
{
    al_set_target_bitmap( menu->bmp );
    al_clear_to_color( al_map_rgba_f(0,0,0,0));

    ALLEGRO_BITMAP *bg = al_create_bitmap(menu->bg_w, menu->bg_h);
    al_set_target_bitmap( bg );
    al_clear_to_color( menu->bg_color );

    al_set_target_bitmap( menu->bmp );
    al_draw_tinted_bitmap( bg, al_map_rgba_f( 1, 1, 1, menu->bg_alpha ), 0, 0, 0 );
    al_destroy_bitmap( bg );

    float current_y = menu->entry_orig_y;
    for (int i = 0; i < MAX_ENTRIES; i++)
    {
        if( menu->entries[i].entry_set )
            drawEntryContent( menu, current_y, i );
        current_y += menu->line_spacing + al_get_font_ascent( menu->main_font ); 
    }

    al_set_target_backbuffer( display );
}
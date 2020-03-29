#include "../../headers/level_map.h"

#include "../../headers/block_type.h"
#include "../../headers/tile_matrix_tools.h"

void drawSolidBlock( int x, int y, ALLEGRO_BITMAP *solid_block_sprite )
{
    al_draw_bitmap( solid_block_sprite, pixelFromTile(x), pixelFromTile(y), 0 );
}

void drawBrittleBlock( int x, int y, ALLEGRO_BITMAP *brittle_block_sprite )
{
    al_draw_bitmap( brittle_block_sprite, pixelFromTile(x), pixelFromTile(y), 0 );
}

void updateLevelMapBitmap( LevelMap *level_map, ALLEGRO_BITMAP *solid_block_sprite, ALLEGRO_BITMAP *brittle_block_sprite, ALLEGRO_DISPLAY *display )
{
    al_set_target_bitmap( level_map->bmp );
    al_clear_to_color( al_map_rgba( 0, 0, 0, 0 ) );

    for (int i = 0; i < level_map->rows; i++)
    {
        for (int j = 0; j < level_map->collumns; j++)
        {
            if( getTileContent( level_map->tile_matrix, j, i ) == SOLID_BLOCK )
                drawSolidBlock( j, i, solid_block_sprite );
            else if( getTileContent( level_map->tile_matrix, j, i ) == BRITTLE_BLOCK )
                drawBrittleBlock( j, i, brittle_block_sprite );
        }    
    }
    
    al_set_target_bitmap(al_get_backbuffer( display ));   
}
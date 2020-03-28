#include "../headers/level_utilities.h"

void drawSolidBlock( int x, int y, ALLEGRO_BITMAP *solid_block_sprite )
{
    al_draw_bitmap( solid_block_sprite, pixelFromTile(x), pixelFromTile(y), 0 );
}

void drawBrittleBlock( int x, int y, ALLEGRO_BITMAP *brittle_block_sprite )
{
    al_draw_bitmap( brittle_block_sprite, pixelFromTile(x), pixelFromTile(y), 0 );
}

void generateMapBitmap( int **map, int rows, int collumns, ALLEGRO_BITMAP *map_bitmap, ALLEGRO_BITMAP *solid_block_sprite, ALLEGRO_BITMAP *brittle_block_sprite, ALLEGRO_DISPLAY *display )
{
    al_set_target_bitmap( map_bitmap );

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < collumns; j++)
        {
            if( map[i][j] == SOLID_BLOCK )
                drawSolidBlock( j, i, solid_block_sprite );
            else if( map[i][j] == BRITTLE_BLOCK )
                drawBrittleBlock( j, i, brittle_block_sprite );
        }    
    }
    
    al_set_target_bitmap(al_get_backbuffer( display ));   
}
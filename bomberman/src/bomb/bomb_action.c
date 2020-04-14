#include "../../headers/bomb.h"

#include "../../headers/_game_rules.h"
#include "../../headers/block_type.h"
#include "../../headers/level_tile_matrix_tools.h"

void explosion( LevelMap *level_map, int remaining_range, int tile_x, int tile_y, int x_step, int y_step, SFX * sfx_container[], int container_size, ALLEGRO_BITMAP *explosion_bmp )
{
    if( !areCoordsOutOfBounds( tile_x, tile_y, level_map->rows, level_map->collumns ) && remaining_range > 0 )
    {
        int block = getTileContent( level_map->tile_matrix, tile_x, tile_y );

        if( block != SOLID_BLOCK )
        {
            SFX *sfx = createSFX( pixelFromTile( tile_x ), pixelFromTile( tile_y ), EXPLOSION_LIFESPAN, EXPLOSION, explosion_bmp );
            addSFXToContainer( sfx_container, container_size, sfx );

            if( block == EMPTY_BLOCK )
                explosion( level_map, remaining_range - 1, tile_x + x_step, tile_y + y_step, x_step, y_step, sfx_container, container_size, explosion_bmp );
            else if( block == BRITTLE_BLOCK )
                setTileContent( level_map->tile_matrix, tile_x, tile_y, EMPTY_BLOCK );
        }
    }
}

void explodeBomb( Bomb *bomb, LevelMap *level_map, SFX * sfx_container[], int container_size, ALLEGRO_BITMAP *explosion_bmp )
{
    SFX *sfx = createSFX( pixelFromTile( bomb->tile_x ), pixelFromTile( bomb->tile_y ), EXPLOSION_LIFESPAN, EXPLOSION, explosion_bmp );
    addSFXToContainer( sfx_container, container_size, sfx );
    explosion( level_map, bomb->blast_range, bomb->tile_x, bomb->tile_y - 1, 0, 1, sfx_container, container_size, explosion_bmp );
    explosion( level_map, bomb->blast_range, bomb->tile_x, bomb->tile_y + 1, 0, -1, sfx_container, container_size, explosion_bmp );
    explosion( level_map, bomb->blast_range, bomb->tile_x - 1, bomb->tile_y, -1, 0, sfx_container, container_size, explosion_bmp );
    explosion( level_map, bomb->blast_range, bomb->tile_x + 1, bomb->tile_y, 1, 0, sfx_container, container_size, explosion_bmp );
}
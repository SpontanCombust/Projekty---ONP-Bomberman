/** @file rendering.c
 * 
 * @brief Plik zawiera funkcje rysowania bitmap elementow gry na ekran
 * 
 * Zawiera metody odpowiadające za rysowanie bomb, SFX, aktorów, \n
 * mapy gry i menu na tylnim buforze.
 * 
 * @author  Przemysław Cedro
 * @date    2020.05.19
*/


#include "../../headers/rendering.h"

#include "../../headers/level_tile_matrix_tools.h"

/** @brief Rysuje bomby
 * 
 * Iteruje po tablicy wskaźników na zmienne typu Bomb i dla każdej nie-NULLowej bomby \n
 * rysuje na tylnim buforze jej bitmapę na określonej pozycji i o określonej klatce animacji.
 * 
 * @param bomb_container tablica wskaźników na bomby
*/
void drawBombs( Bomb *bomb_container[] )
{
    Bomb *bomb = NULL;
    for (int i = 0; i < BOMB_BUDGET; i++)
    {
        if( bomb_container[i] != NULL ) {
            bomb = bomb_container[i];  
            al_draw_bitmap_region( bomb->bmp, bomb->anim_frame * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE, pixelFromTile( bomb->tile_x ), pixelFromTile( bomb->tile_y ), 0 );
        }
    }
}

/** @brief Rysuje specjalne efekty SFX
 * 
 * Iteruje po tablicy wskaźnikow na zmienne typu SFX i dla każdego nie-NULLowego SFX \n
 * rysuje na tylnim buforze jego bitmapę na określonej pozycji i o okreslonej klatce animacji, \n
 * kierując sie również jego typem i orientacja. \n
 * Jeśli typ to eksplozja, bada orientację SFX i według niej w razie konieczności obraca pobierane \n
 * subbitmapy explozji. Jeśli typ to zwłoki, rysuje pokolorowaną na czerwono bitmapę aktora, \n
 * która została przekazana do tablicy SFX.
 * 
 * @param sfx_container tablica wskaźników na zmienne typu SFX
*/
void drawSFX( SFX *sfx_container[] )
{
    SFX *sfx = NULL;
    for (int i = 0; i < SFX_BUDGET; i++)
    {
        if( sfx_container[i] != NULL )
        {
            sfx = sfx_container[i];

            if( sfx_container[i]->type == EXPLOSION )
            {
                ALLEGRO_BITMAP *sub = NULL;
                switch( sfx_container[i]->orientation )
                {
                    case CENTRE:
                        sub = al_create_sub_bitmap( sfx->bmp, sfx->anim_frame * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE );
                        al_draw_bitmap( sub, sfx->x, sfx->y, 0 );
                        break;
                    case VERTICAL:
                        sub = al_create_sub_bitmap( sfx->bmp, sfx->anim_frame * TILE_SIZE, TILE_SIZE, TILE_SIZE, TILE_SIZE );
                        al_draw_bitmap( sub, sfx->x, sfx->y, 0 );
                        break;
                    case HEAD_DOWN:
                        sub = al_create_sub_bitmap( sfx->bmp, sfx->anim_frame * TILE_SIZE, 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE );
                        al_draw_bitmap( sub, sfx->x, sfx->y, 0 );
                        break;
                    case HEAD_UP:
                        sub = al_create_sub_bitmap( sfx->bmp, sfx->anim_frame * TILE_SIZE, 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE );
                        al_draw_bitmap( sub, sfx->x, sfx->y, ALLEGRO_FLIP_VERTICAL );
                        break;
                    case HORIZONTAL:
                        sub = al_create_sub_bitmap( sfx->bmp, sfx->anim_frame * TILE_SIZE, TILE_SIZE, TILE_SIZE, TILE_SIZE );
                        al_draw_rotated_bitmap( sub, TILE_SIZE/2, TILE_SIZE/2, sfx->x + TILE_SIZE/2, sfx->y + TILE_SIZE/2, ALLEGRO_PI/2, 0 );
                        break;
                    case HEAD_LEFT:
                        sub = al_create_sub_bitmap( sfx->bmp, sfx->anim_frame * TILE_SIZE, 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE );
                        al_draw_rotated_bitmap( sub, TILE_SIZE/2, TILE_SIZE/2, sfx->x + TILE_SIZE/2, sfx->y + TILE_SIZE/2, ALLEGRO_PI/2, 0 );
                        break;
                    case HEAD_RIGHT:
                        sub = al_create_sub_bitmap( sfx->bmp, sfx->anim_frame * TILE_SIZE, 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE );
                        al_draw_rotated_bitmap( sub, TILE_SIZE/2, TILE_SIZE/2, sfx->x + TILE_SIZE/2, sfx->y + TILE_SIZE/2, ALLEGRO_PI/2, ALLEGRO_FLIP_VERTICAL );
                        break;
                }
            }
            else if( sfx->type == CORPSE )
                al_draw_tinted_bitmap_region( sfx->bmp, COLOR_RED, 0, 0, TILE_SIZE, TILE_SIZE, sfx->x, sfx->y, 0 );
        }
    }
}

/** @brief Rysuje aktora
 * 
 * Rysuje na tylnim buforze bitmapę aktora na określonej pozycji, \n
 * o określonej klatce animacji oraz kierując sie tym, w którą stronę jest skierowany.
 * 
 * @param actor wskaźnik na aktora
*/
void drawActor( Actor *actor ) {
    al_draw_bitmap_region( actor->bmp, actor->anim_frame * TILE_SIZE, actor->dir * TILE_SIZE, TILE_SIZE, TILE_SIZE, actor->x, actor->y, 0 );
}

/** @brief Rysuje mapę poziomu
 * 
 * Rysuje na tylnim buforze bitmapę mapy poziomu.
 * 
 * @param level_map wskaźnik na mapę poziomu
*/
void drawLevelMap( LevelMap *level_map ) {
    al_draw_bitmap( level_map->bmp, 0, 0, 0 );
}

/** @brief Rysuje menu
 * 
 * Rysuje na tylnim buforze bitmapę danego menu.
 * 
 * @param menu wskaźnik na menu
*/
void drawMenu( Menu *menu ) {
    al_draw_bitmap( menu->bmp, menu->bg_x, menu->bg_y, 0 );
}
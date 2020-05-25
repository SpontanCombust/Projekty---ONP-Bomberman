/** @file camera_essentials.c
 * 
 * @brief Plik zawiera podstawowe funkcje dla kamery.
 * 
 * Zawiera funkcje do alokacji i zwalniania pamięci ze zmiennych typu Camera.
 * 
 * @author  Przemysław Cedro
 * @date    2020.05.24
*/


#include "../../headers/camera.h"

#include "../../headers/sprite_properties.h"

/** @brief Tworzy kamerę
 * 
 * Tworzy i zwraca kamerę skierowaną na danego aktora i przystosowaną do działania na danej mapie poziomu.
 *
 * @param target    aktor, który ma być celem kamery
 * @param lvl_map   mapa poziomu
 * 
 * @return utworzona kamera
*/
Camera *createCamera( Actor *target, LevelMap *lvl_map )
{
    Camera *camera = (Camera *)malloc( sizeof( Camera ) );

    camera -> target = target;
    camera -> max_x = lvl_map->collumns * TILE_SIZE - 1;
    camera -> max_y = lvl_map->rows * TILE_SIZE - 1;
    camera -> x = 0;
    camera -> y = 0;

    return camera;
}

/** @brief Zwalnia pamięć z kamery
 * 
 * Zwalnia pamięć z dynamicznie alokowanej zmiennej typu Camera.
 *
 * @param camera podwójny wskaźnik na kamerę
 */
void destroyCamera( Camera **camera )
{
    free( *camera );
    *camera = NULL;
}
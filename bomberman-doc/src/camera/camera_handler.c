/** @file camera_handler.c
 * 
 * @brief Plik zawiera funkcje do obsługi działania kamery
 * 
 * Zawiera funkcje aktualizowania pozycji kamery i tymczasowego jej wyłączania.
 * 
 * @author  Przemysław Cedro
 * @date    2020.05.24
*/


#include "../../headers/camera.h"

#include "../../headers/_game_rules.h"
#include "../../headers/sprite_properties.h"

/** @brief Aktualizuje pozycję kamery 
 * 
 * Aktualizuje obecną pozycję kamery na podstawie pozycji jej docelowego aktora, granic mapy poziomu\n
 * oraz skali z jaką kamera przybliża obraz mapy.
 *
 * @param camera wskaźnik na kamerę
*/
static void updateCameraPosition( Camera *camera )
{
    camera -> x = ( camera->target->x + TILE_SIZE/2 ) - ( SCREEN_WIDTH/2 / CAMERA_SCALE );
    camera -> y = ( camera->target->y + TILE_SIZE/2 ) - ( ( SCREEN_HEIGHT - GAME_WINDOW_Y_OFFSET )/2 / CAMERA_SCALE );

    if( camera->x < 0 )
        camera -> x = 0;
    else if( camera->x > camera->max_x - SCREEN_WIDTH / CAMERA_SCALE + 1)
        camera -> x = camera->max_x - SCREEN_WIDTH / CAMERA_SCALE + 1;
    
    if( camera->y < 0 )
        camera -> y = 0;
    else if( camera->y > camera->max_y - ( SCREEN_HEIGHT - GAME_WINDOW_Y_OFFSET ) / CAMERA_SCALE + 1 )
        camera -> y = camera->max_y - ( SCREEN_HEIGHT - GAME_WINDOW_Y_OFFSET ) / CAMERA_SCALE + 1;
}

/** @brief Aktualizuje stan kamery
 * 
 * Aktualizuje pozycję kamery, a następnie transformuje obraz skalując go i przesuwając na\n
 * przeskalowaną pozycję kamery. Skalowanie obrazu jest ważne, gdy assety gry mają zaledwie\n
 * kilkadziesiąt pikseli wielkości, a chce się wszystko dobrze widzieć.\n
 * Aplikuje transformację do obecnego wyświetlacza Allegro.
 *
 * @param camera wskaźnik na kamerę
*/
void updateCamera( Camera *camera )
{
    updateCameraPosition( camera );
    al_identity_transform( &( camera->transform ) );
    al_scale_transform( &( camera->transform ), CAMERA_SCALE, CAMERA_SCALE );
    al_translate_transform( &( camera->transform ), -( camera->x * CAMERA_SCALE ), -( camera->y * CAMERA_SCALE ) );
    al_use_transform( &( camera->transform ) );
}

/** @brief Wyłącza transformacje kamery
 * 
 * Przywraca domyślną skalę obrazu i aplikuje tę transformację do obecnego wyświetlacza Allegro.
 *
 * @param camera wskaźnik na kamerę
*/
void disableCamera( Camera *camera )
{
    al_identity_transform( &( camera->transform ) );
    al_use_transform( &( camera->transform ) );
}
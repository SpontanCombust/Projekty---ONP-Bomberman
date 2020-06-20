/** @file camera.h
 * 
 * @brief Plik zawiera definicję typu Camera, modułu kamery dla wielu graczy oraz deklaracje funkcji stworzonych dla tych typów
 * 
 * @author  Przemysław Cedro
 * @date    2020.05.29
*/


#ifndef CAMERA_H
#define CAMERA_H

#include "actor.h"
#include "level_map.h"
#include <allegro5/allegro.h>

/**
 * @brief Struktura kamery gry, Camera
 * 
 * Struktura stworzona w celach powiększenia obrazu, który inaczej byłby nieco nieczytelny i cała mapa \n
 * musiałaby zajmować całą wielkość okna programu. Kamera pozwala nie tylko na powiększenie obrazu, \n
 * ale też na podążanie za danym aktorem, dzięki czemu rozgrywka jest o wiele wygodniejsza.
 */
typedef struct S_Camera
{
    Actor *target; /**< Cel kamery */
    float x, y; /**< Pozycja lewego górengo rogu kamery */
    float max_x, max_y; /**< Maksymalna współrzędne, do których obwód kamery powinien się poruszać */
    ALLEGRO_TRANSFORM transform; /**< Zmienna macierzy transformacji Allegro */

} Camera;

/**
 * @brief Struktura modułu kamery dla dwóch graczy, MultiPlayerCameraModule
 * 
 * Stworzona w celach optymalnego wyświetlania obrazu dla obu graczy naraz poprzez podążanie \n
 * za punktem, który jest umieszczony zawsze w połowie dystansu między oboma graczami.
 */
typedef struct S_MultiPlayerCameraModule
{
    Actor *target; /**< Cel kamery */
    Actor *actor1, *actor2; /**< Wskaźniki na Aktorów graczy */

} MultiPlayerCameraModule;


// =================== camera_essentials.c ====================

/** @brief Tworzy kamerę */
Camera *createCamera( Actor *target, LevelMap *lvl_map );
/** @brief Zwalnia pamięć z kamery */
void destroyCamera( Camera **camera );


// =================== camera_handler.c =======================

/** @brief Aktualizuje stan kamery */
void updateCamera( Camera *camera );
/** @brief Wyłącza transformacje kamery */
void disableCamera( Camera *camera );


// =================== mp_camera_module.c =======================

/** @brief Aplikuje aktorów do modułu kamery dla wielu graczy */
void applyActorsToCameraModule( MultiPlayerCameraModule *mpcm, Actor *actor1, Actor *actor2 );
/** @brief Aktualizuje stan modułu kamery dla wielu graczy */
void updateCameraModule( MultiPlayerCameraModule *mpcm );

#endif
/** @file actor.h
 * 
 * @brief Plik zawiera definicję typu Actor i deklaracje funkcji stworzonych dla tego typu
 * 
 * @author  Przemysław Cedro
 * @date    2020.05.29
*/


#ifndef ACTOR_H
#define ACTOR_H

#include "direction.h"
#include <allegro5/allegro.h>
#include <stdbool.h>

/*

*/

/**
 * @brief Struktura Aktora, Actor
 * 
 * Struktura stworzona na potrzeby posiadania postaci, która mogłaby poruszać się po mapie w dany \n
 * sposób, jak i również kolidować z otoczeniem. \n
 * Aktor porusza się na podstawie nadanej mu szybkości oraz składowych wektorów prędkości, którch \n
 * sumy w danej osi decydują o zwrocie ruchu. Wektory określone są przez typ bool, czyli mogą mieć \n
 * tylko dwie wartości, ale ważne przy ich użyciu jest tylko to CZY aktor ma się w jakiś sposób poruszać, \n
 * nie jak. Schemat prezentuje poglądowe określenie wektorów w płaszczyźnie ekranu: 
 * \n
 *          | vy[0] \n
 *          | \n
 * vx[0]----0---> vx[1] \n
 *          | \n
 *          \/ vy[1] \n
 * \n
 * Aktor może mieć daną ilość żyć, lecz na razie wspierane jest tylko to, czy ma ich więcej niż 1. \n
 * Aktor posiada prostokąt kolizji, który określa jaki obszar bitmapy jest podatny na kolizję z otoczeniem. \n
 * Aktor w zależności od kierunku i zbiegiem czasu zmienia klatkę animacji.
 */
typedef struct S_Actor
{
    float x, y; /**< Współrzędne pikselowe położenia */
    bool vx[2]; /**< Wektory składowe prędkości w osi X */
    bool vy[2]; /**< Wektory składowe prędkości w osi Y */
    float speed; /**< Szybkość */
    float cx; /**< Punkt początkowy prostokąta kolizji na bitmapie aktora w osi X */
    float cy; /**< Punkt początkowy prostokąta kolizji na bitmapie aktora w osi Y */
    float cw; /**< Szerokość prostokąta kolizji */
    float ch; /**< Wysokość prostokąta kolizji  */
    bool enabled_collision; /**< Czy aktor ma właczoną kolizję */
    int lives; /**< Ilość żyć aktora */
    Direction dir; /**< Kierunek aktora w przestrzeni */
    int anim_frame; /**< Numer klatki animacji */
    ALLEGRO_BITMAP *bmp; /**< Bitmapa aktora */
    
} Actor; 


// ======================== actor_essentials.c =========================

/** @brief Tworzy aktora */
Actor *createActor( float x, float y, float speed, ALLEGRO_BITMAP *bmp );
/** @brief Zwalnia pamięć z aktora */
void destroyActor( Actor **actor );
/** @brief Zwalnia pamięć z talbicy aktorów */
void destroyActorArray( Actor ** *actors, int actors_num );


// ======================== actor_handling.c ===========================

/** @brief Ustawia kolizję dla aktora */
void applyCollisionToActor( Actor *actor, float cx, float cy, float cw, float ch );
/** @brief Ustawia tę samą kolizję dla tablicy aktorów */
void applyCollisionToActorArray( Actor * *actors, int actor_num, float cx, float cy, float cw, float ch );
/** @brief Odejmuje punkty życia aktorowi */
void damageActor( Actor *actor );
/** @brief Sprawdza, czy aktor jest żywy */
bool isActorAlive( Actor *actor );
/** @brief Aktualizuje klatkę animacji dla aktora */
void updateAnimFrameForActor( Actor *actor );

#endif
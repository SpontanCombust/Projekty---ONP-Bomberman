/** @file logic.c
 * 
 * @brief Plik zawiera deklaracje funkcji obsługi systemu poruszania się i kolizji
 * 
 * @author  Przemysław Cedro
 * @date    2020.05.29
*/


#ifndef LOGIC_HANDLERS_H
#define LOGIC_HANDLERS_H

#include "direction.h"
#include "actor.h"
#include "level_map.h"
#include <stdbool.h>

// ================================== movement_handler.c ==================================

/** @brief Aktualizuje składowe wektory prędkości aktora w osi X */
void updateVelocityX( Actor *actor, bool vx0, bool vx1 );
/** @brief Aktualizuje wektory prędkości aktora w osi Y */
void updateVelocityY( Actor *actor, bool vy0, bool vy1 );
/** @brief Resetuje wektory prędkości aktora */
void resetVelocity( Actor *actor );
/** @brief Sprawdza, czy aktor się porusza */
bool isActorMoving( Actor *actor );
/** @brief Aktualizuje zmienną kierunku aktora */
void resolveDirection( Actor *actor );
/** @brief Aktualizuje pozycję aktora w osi X */
void updatePositionX( Actor *actor );
/** @brief Aktualizuje pozycję aktora w osi Y */
void updatePositionY( Actor *actor );


// ================================== collision_handler.c ==================================

/** @brief Wykrywa, czy aktor jest poza obrębem mapy */
bool isOutOfBounds( Actor *actor, LevelMap *level_map, Direction *cdir );
/** @brief Koryguje pozycję aktora po wyjściu za obszar mapy */
void handleOutOfBounds( Actor *actor, LevelMap *level_map, Direction cdir );
/** @brief Wykrywa, czy aktor wchodzi w kolizję z elementami mapy w osi X */
bool isTerrainCollisionX( Actor *actor, LevelMap *level_map, Direction *cdir );
/** @brief Wykrywa, czy aktor wchodzi w kolizję z elementami mapy w osi Y */
bool isTerrainCollisionY( Actor *actor, LevelMap *level_map, Direction *cdir );
/** @brief Koryguje pozycję aktora po kolizji z elementami mapy */
void handleTerrainCollision( Actor *actor, Direction cdir );
/** @brief Wykrywa, czy zaistaniała kolizja między dwoma aktorami */
bool isActorCollision( Actor *actor1, Actor *actor2 );

#endif

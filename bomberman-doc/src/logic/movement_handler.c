/** @file movement_handler.c
 * 
 * @brief Plik zawiera funkcje do obsługi ruchu aktorów po mapie
 * 
 * Plik zawiera funckje aktualizowania wektorów prędkości aktora, jego pozycji oraz kierunku.
 * 
 * @author  Przemysław Cedro
 * @date    2020.05.21
*/


#include "../../headers/logic.h"

#include "../../headers/_game_rules.h"
#include <allegro5/allegro.h>

/** @brief Aktualizuje składowe wektory prędkości aktora w osi X
 *
 * @param actor wskaźnik na aktora
 * @param vx0   docelowy wektor składowy na wartościach ujemnych
 * @param vx1   docelowy wektor składowy na wartościach dodatnich
*/
void updateVelocityX( Actor *actor, bool vx0, bool vx1 )
{
    actor -> vx[0] = vx0;
    actor -> vx[1] = vx1;
}

/** @brief Aktualizuje wektory prędkości aktora w osi Y
 *
 * @param actor wskaźnik na aktora
 * @param vy0   docelowy wektor składowy na wartościach ujemnych
 * @param vy1   docelowy wektor składowy na wartościach dodatnich
*/
void updateVelocityY( Actor *actor, bool vy0, bool vy1 )
{
    actor -> vy[0] = vy0;
    actor -> vy[1] = vy1;
}

/** @brief Resetuje wektory prędkości aktora
 * 
 * Przywraca wartości na wektorach u aktora do stanu biernego (zerowego)
 *
 * @param actor wskaźnik na aktora
*/
void resetVelocity( Actor *actor )
{
    actor -> vx[0] = false;
    actor -> vx[1] = false;
    actor -> vy[0] = false;
    actor -> vy[1] = false;
}

/** @brief Sprawdza, czy aktor się porusza
 * 
 * Jeśli jakikolwiek z wektorów składowych prędkości jest niezerowy, aktor jest w ruchu.
 * 
 * @param actor wskaźnik na aktora
 * 
 * @return true jeśli aktor się porusza, false w przeciwnym wypadku
*/
bool isActorMoving( Actor *actor ) {
    return actor->vx[0] || actor->vx[1] || actor->vy[0] || actor->vy[1];
}

/** @brief Aktualizuje zmienną kierunku aktora
 * 
 * Bazując na wektorach składowych prędkości ocenia, w którą wstronę powinien być skierowany aktor.
 *
 * @param actor wskaźnik na aktora
*/
void resolveDirection( Actor *actor )
{
    if( actor->vy[0] & !( actor->vx[0] ) & !( actor->vx[1] ) )
        actor -> dir = UP;
    else if( actor->vy[1] & !( actor->vx[0] ) & !( actor->vx[1] ) )
        actor -> dir = DOWN;        
    else if( actor->vx[0] & !( actor->vy[0] ) & !( actor->vy[1] ) )
        actor -> dir = LEFT;
    else if( actor->vx[1] & !( actor->vy[0] ) & !( actor->vy[1] ) )
        actor -> dir = RIGHT;
}

/** @brief Aktualizuje pozycję aktora w osi X
 * 
 * Mnoży szybkość aktora i sumę wektorów składowych w osi X, biorąc pod uwagę że wartość wektora\n
 * składowego na wartościach ujemnych musi zostać zanegowana, by był on rzeczywiście przeciwny\n
 * wartością do wektora na wartościach dodatnich, bo jest to typ bool. Otrzymany wynik dodawany\n
 * jest do obecnej pozycji aktora. 
 *
 * @param actor wskaźnik na aktora
*/
void updatePositionX( Actor *actor )
{
    actor -> x += actor->speed * ( -( actor->vx[0] ) + actor->vx[1] );
}

/** @brief Aktualizuje pozycję aktora w osi Y
 * 
 * Mnoży szybkość aktora i sumę wektorów składowych w osi Y, biorąc pod uwagę że wartość wektora\n
 * składowego na wartościach ujemnych musi zostać zanegowana, by był on rzeczywiście przeciwny\n
 * wartością do wektora na wartościach dodatnich, bo jest to typ bool. Otrzymany wynik dodawany\n
 * jest do obecnej pozycji aktora. 
 *
 * @param actor wskaźnik na aktora
*/
void updatePositionY( Actor *actor )
{   
    actor -> y += actor->speed * ( -( actor->vy[0] ) + actor->vy[1] ); 
}
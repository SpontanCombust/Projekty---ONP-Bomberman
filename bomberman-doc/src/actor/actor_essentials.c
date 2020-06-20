/** @file actor_essentials.c
 * 
 * @brief Plik zawiera podstawowe funkcje dla aktora
 * 
 * Zawiera funkcje alokowania i zwalniania pamięci dla zmiennej typu Actor oraz tablicy zmiennych.
 * 
 * @author  Przemysław Cedro
 * @date    2020.05.26
*/


#include "../headers/actor.h"

#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Tworzy aktora
 * 
 * Alokuje pamięć na dynamiczną zmienną typu Actor i przydziela jej odpowiednie cechy oraz inicjuje \n
 * niektóre zmienne.
 * 
 * @param x     początkowa pozycja w osi X aktora
 * @param y     początkowa pozycja w osi Y aktora
 * @param speed szybkość ruchu aktora
 * @param bmp   bitmapa, którą ma uzywać aktor
 * 
 * @return utworzony aktor
 */
Actor *createActor( float x, float y, float speed, ALLEGRO_BITMAP *bmp )
{
    Actor *actor = (Actor *)malloc( sizeof( Actor ) );

    if( actor ){
        actor -> x = x;
        actor -> y = y;
        actor -> vx[0] = false;
        actor -> vx[1] = false;
        actor -> vy[0] = false;
        actor -> vy[1] = false;
        actor -> speed = speed;
        actor -> cx = 0;
        actor -> cy = 0;
        actor -> cw = 0;
        actor -> ch = 0;
        actor -> enabled_collision = false;
        actor -> lives = 1;
        actor -> dir = DOWN;
        actor -> anim_frame = 0;
        actor -> bmp = bmp;
    } 
    else
    {
        puts("Failed to allocate actor!");
        return NULL;
    }
    
    
    return actor;
}

/**
 * @brief Zwalnia pamięć z aktora
 * 
 * Zwalnia pamięć z dynamicznie alokowanej zmiennej typu Actor.
 * 
 * @param actor podwójny wskaźnik na aktora
 */
void destroyActor( Actor **actor )
{
    free( *actor );
    *actor = NULL;
}

/**
 * @brief Zwalnia pamięć z talbicy aktorów
 * 
 * Zwalnia pamięć z dynamicznie alokowanej tablicy dynamicznych zmiennych typu Actor.
 * 
 * @param actors    podwójny wskaźnik na tablicę wskaźników na aktorów
 * @param actor_num ilość aktorów
 */
void destroyActorArray( Actor ** *actors, int actor_num )
{
    for (int i = 0; i < actor_num; i++)
        destroyActor( &(*actors)[i] );
    free( *actors );
    *actors = NULL;
}
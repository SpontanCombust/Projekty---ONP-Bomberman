/** @file actor_handler.c
 * 
 * @brief Plik zawiera funkcje obsługi zmiennej Actor
 * 
 * Zawiera funkcje ustawiania kolizji dla aktora, sprawdzania, czy jest żywy, odejmowania jego \n
 * punktów życia oraz aktualizowania jego klatek animacji.
 * 
 * @author  Przemysław Cedro
 * @date    2020.05.26
*/


#include "../../headers/actor.h"

#include "../../headers/_game_rules.h"
#include "../../headers/logic.h"

/**
 * @brief Ustawia kolizję dla aktora
 * 
 * Ustawia zmienne kolizji dla zmiennej typu Actor, reprezentujące jego prostokąt kolizji.
 * 
 * @param actor wskaźnik na aktora
 * @param cx    lewy górny róg prostokąta kolizji w osi X w pikselach
 * @param cy    lewy górny róg prostokąta kolizji w osi Y w pikselach
 * @param cw    szerokość prostokąta kolizji w pikselach
 * @param ch    wysokość prostokąta kolizji w pikselach
 */
void applyCollisionToActor( Actor *actor, float cx, float cy, float cw, float ch )
{
    actor -> enabled_collision = true;
    actor -> cx = cx;
    actor -> cy = cy;
    actor -> cw = cw;
    actor -> ch = ch;
}

/**
 * @brief Ustawia tę samą kolizję dla tablicy aktorów
 * 
 * @param actors    tablica wskaźników na aktorów
 * @param actor_num ilość aktorów
 * @param cx        lewy górny róg prostokąta kolizji w osi X w pikselach
 * @param cy        lewy górny róg prostokąta kolizji w osi Y w pikselach
 * @param cw        szerokość prostokąta kolizji w pikselach
 * @param ch        wysokość prostokąta kolizji w pikselach
 */
void applyCollisionToActorArray( Actor * *actors, int actor_num, float cx, float cy, float cw, float ch )
{
    for (int i = 0; i < actor_num; i++)
        applyCollisionToActor( actors[i], cx, cy, cw, ch );
}

/**
 * @brief Sprawdza, czy aktor jest żywy
 * 
 * Sprawdza, czy ilość punktów życia aktora jest większa od zera
 * 
 * @param actor wskaźnik na aktora
 * 
 * @return true jeśli aktor jest żywy, false w przeciwnym wypadku
 */
bool isActorAlive( Actor *actor ) {
    return actor->lives > 0;
}

/**
 * @brief Odejmuje punkty życia aktorowi
 * 
 * @param actor wskaźnik na aktora
 */
void damageActor( Actor *actor ) {
    actor -> lives--;
}

/**
 * @brief Aktualizuje klatkę animacji dla aktora
 * 
 * Aktualizuje zmienną anim_frame dla aktora. Jeśli ten się nie porusza, klatka zostaje ustawiona \n
 * na pcozątkową.
 * 
 * @param actor wskaźnik na aktora
 */
void updateAnimFrameForActor( Actor *actor )
{
    if( !isActorMoving( actor ) )
        actor -> anim_frame = 0;
    else
    {
        actor -> anim_frame++;
        if( actor->anim_frame > ACTOR_ANIM_FRAMES - 1 )
            actor->anim_frame = 0;
    }
}
/** @file ai_module_handler.c
 * 
 * @brief Plik zawiera funkcje obsługi modułu AI 
 * 
 * Zawiera funkcję sprawdzania, czy aktor zaaplikowany do modułu osiągnął swój obecny cel oraz funkcję, \n
 * która ustawia mu kolejny cel.
 * 
 * @author  Przemysław Cedro
 * @date    2020.05.26
*/


#include "../../headers/ai.h"

/** @brief Sprawdza, czy aktor zaaplikowany do modułu osiągnął swój cel
 * 
 * Porównuje obecną pozycję aktora i determinuje, czy doszedł wystarczająco blisko do miejsca, \n
 * w którym kończy się obecny krok ścieżki, a zaczyna się następny.
 *
 * @param module wskaźnik na moduł AI
 * 
 * @return true jeśli aktor osiągnąl cel, false w przeciwnym wypadku
*/
bool reachedDestination( AIModule *module )
{
    if( abs( module->actor->x - module->current_step.dest_x ) < 1 && abs( module->actor->y - module->current_step.dest_y ) <  1 )
        return true;
    return false;
}

/** @brief Ustawia kolejny cel w module AI 
 * 
 * Dla aktora zaaplikowanego do modułu AI ustawia kolejny krok ścieżki, do którego miejsca ma się \n
 * poruszać. Wybierany jest kolejny krok w tablicy kroków w ścieżce. Aktualizuje wektory prędkości \n
 * aktora w zależności od relacji jego pozycji do pozycji jego celu. Wspierane są w pełni tylko \n
 * ścieżki, dla których przemieszczenie między kolejnymi krokami odbywa się równolegle do jednej \n
 * z osi współrzędnych.
 *
 * @param module wskaźnik na moduł AI
*/
void doNextStep( AIModule *module )
{
    PathStep prev_step = module->current_step;

    if( module->reversed_path == false )
        module -> step_index++;
    else
        module -> step_index--;

    PathStep next_step = module->path.steps[ module->step_index ];

    resetVelocity( module->actor );

    if( next_step.dest_x - prev_step.dest_x < 0 )
        updateVelocityX( module->actor, true, false );
    else if( next_step.dest_x - prev_step.dest_x > 0 )
        updateVelocityX( module->actor, false, true );

    if( next_step.dest_y - prev_step.dest_y < 0 )
        updateVelocityY( module->actor, true, false );
    else if( next_step.dest_y - prev_step.dest_y > 0 )
        updateVelocityY( module->actor, false, true );

    if( module->step_index == 0 )
        module -> reversed_path = false;
    else if( module->step_index == module->path.step_num - 1 )
        module -> reversed_path = true;

    module -> current_step = next_step;
}
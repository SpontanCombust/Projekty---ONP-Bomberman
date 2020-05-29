/** @file ai_essentials.c
 * 
 * @brief Plik zawiera podstawowe funkcje dla modułu AI
 * 
 * Zawiera funkcje alokowania i zwalniania pamięci z dynamicznie alokowanych  zmiennych typu AIModule.
 * 
 * @author  Przemysław Cedro
 * @date    2020.05.25
*/


#include "../../headers/ai.h"

#include <stdio.h>

/** @brief Tworzy moduł AI zaaplikowany do danego aktora i danej ścieżki ruchu
 * 
 * Alokuje pamięć na zmienną typu AIModule i przydziela jej docelowego aktora i ścieżkę ruchu.
 *
 * @param actor wskaźnik na docelowego aktora
 * @param path  wskaźnik na docelową scieżkę ruchu
 * 
 * @return utworzony moduł AI
*/
AIModule *createAIModule( Actor *actor, Path path )
{
    AIModule *module = ( AIModule *)malloc( sizeof( AIModule ) );

    module -> actor = actor;
    module -> path = path;
    module -> current_step = path.steps[0];
    module -> step_index = 0;
    module -> reversed_path = false;

    return module; 
}

/** @brief Zwalnia pamięć z modułu AI
 * 
 * Zwalnia pamięć z dynamicznie alokowanej zmiennej typu AIModule
 *
 * @param module podwójny wskaźnik na moduł AI
*/
void destroyAIModule( AIModule **module )
{
    free( *module );
    *module = NULL;
}

/** @brief Zwalnia pamięć z tablicy modułów AI
 * 
 * Zwalnia pamięć z dynamicznej tablicy dynamicznie alokowanych zmiennych typu AIModule
 *
 * @param modules       podwójny wskaźnik na tablicę wskaźników na moduły AI
 * @param module_num    ilość modułów
*/
void destroyAIModuleArray( AIModule ** *modules, int module_num )
{
    for (int i = 0; i < module_num; i++)
        destroyAIModule( &(*modules)[i] );
    free( *modules );
    *modules = NULL;
}

/** @brief Tworzy aktora w miejscu początku ścieżki
 * 
 * Tworzy aktora, który zostaje ustawiony w miejscu ustalony przez pierwszy krok ścieżki podanej \n
 * w parametrze.
 *
 * @param path  ścieżka
 * @param speed szybkość aktora
 * @param bmp   bitmapa aktora
 * 
 * @return utworzony aktor
*/
Actor *createAIActor( Path path, float speed, ALLEGRO_BITMAP *bmp )
{
    return createActor( path.steps[0].dest_x, path.steps[0].dest_y, speed, bmp );
}

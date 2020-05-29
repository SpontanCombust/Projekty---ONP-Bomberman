/** @file ai.h
 * 
 * @brief Plik zawiera definicje typów PathStep, Path, AIModule oraz deklaracje funkcji dla nich stworzonych
 * 
 * @author  Przemysław Cedro
 * @date    2020.05.29
*/


#ifndef AI_H
#define AI_H

#include "actor.h"
#include "logic.h"

/**
 * @brief Struktura Kroku na Ścieżce, PathStep
 * 
 * Służy do przechowywania współrzędnych informujących o punkcie, na którym kończy się etap Ścieżki
 */
typedef struct S_PathStep
{
    float dest_x, dest_y; /**< Współrzędne pikselowe punktu dla Kroku */

} PathStep;

/**
 * @brief Struktura Ścieżki, Path
 * 
 * Struktura przechowująca tablicę Kroków i ich liczbę.
 */
typedef struct S_Path
{
    int step_num; /**< ilość kroków */
    PathStep * steps; /**< tablica kroków */

} Path;

/**
 * @brief Struktura modułu AI dla wrogów, AIModule
 * 
 * Struktura stworzona na potrzeby jednostki potrafiącej kontrolować aktorów, którzy nie są aktorami \n
 * graczy. Struktura posiada Ścieżkę, według której przydziela zaaplikowanemu do niej aktorowi \n
 * (wrogowi) kolejne docelowe miejsce, do którego powinien podążać.  Przy dotarciu do danego punktu \n
 * (kroku) moduł wybiera kolejny krok. Jeśli moduł dojdzie do końca ścieżki, idzie dalej w odwrotną stronę.
 */
typedef struct S_AIModule
{
    Actor *actor; /**< aktor wroga, do którego ma być zaaplikowany moduł */
    Path path; /**< ścieżka dla modułu */
    PathStep current_step; /**< obecny krok */
    int step_index; /**< indeks kroku w tablicy kroków w Ścieżce */
    bool reversed_path; /**< czy wybór kroków ma się odbywać w odwrotnej kolejności */

} AIModule;


// =========================== path_array_creator.c =============================

/** @brief Tworzy tablicę kroków PathStep dla ścieżki Path */
PathStep * createPathStepArray( char *line, int *step_num );
/** @brief Tworzy tablicę ścieżek Path z pliku */
Path * createPathArray( char *enemies_file_path, int *paths_num );
/** @brief Zwalnia pamięć z tablicy ścieżek */
void destroyPathArray( Path ** array );
/** @brief Wypisuje do konsoli treść ścieżki Path */
void printPath( Path path );


// ======================== ai_movement_module_handler.c ========================

/** @brief Sprawdza, czy aktor zaaplikowany do modułu osiągnął swój cel */
bool reachedDestination( AIModule *module );
/** @brief Ustawia kolejny cel w module AI  */
void doNextStep( AIModule *module );


// =============================== ai_essentials.c ==============================

/** @brief Tworzy moduł AI zaaplikowany do danego aktora i danej ścieżki ruchu */
AIModule *createAIModule( Actor *actor, Path path );
/** @brief Zwalnia pamięć z modułu AI */
void destroyAIModule( AIModule **module );
/** @brief Zwalnia pamięć z tablicy modułów AI */
void destroyAIModuleArray( AIModule ** *modules, int module_num );
/** @brief Tworzy aktora w miejscu początku ścieżki */
Actor *createAIActor( Path path, float speed, ALLEGRO_BITMAP *bmp );

#endif
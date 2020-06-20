/** @file level.h
 * 
 * @brief Plik zawiera definicję typu Level, enum LevelClearCondition oraz deklaracje funkcji stworzonych dla typu Level
 * 
 * @author  Przemysław Cedro
 * @date    2020.05.29
*/


#ifndef LEVEL_H
#define LEVEL_H

#include "level_map.h"
#include "ai.h"

#include <allegro5/allegro_font.h>

/**
 * @brief Struktura poziomu, Level
 * 
 * Struktura przechowująca informacje o mapie poziomu, ścieżkach wrogów, aktorach wrogów \n
 * oraz modułach AI wrogów. Stworzona dla potrzeby zbiórczego ładowania tych wszystkich \n
 * składników na raz.
 */
typedef struct S_Level
{
    LevelMap *level_map; /**< wskaźnik na Mapę Poziomu */
    Path * enemy_paths; /**< wskaźnik na Ścieżki wrogów */
    int enemy_intit_count; /**< Początkowa ilość wrogów /nieużywane/ */
    Actor ** enemies; /**< Tablica wskaźników na Aktorów wrogów */
    AIModule ** ai_modules; /**< Tablica wskaźników na Moduły AI wrogów */

} Level;

/** Enum informujące o warunku przejścia danego poziomu. Dostępne warunki to DESTROY_ALL_BLOCKS (nieużywane), KILL_ALL_ENEMIES i KILL OPPONENT */
typedef enum E_LevelClearCondition { DESTROY_ALL_BLOCKS, KILL_ALL_ENEMIES, KILL_OPPONENT } LevelClearCondition;


// ======================== level_essentials.c ===========================

/** @brief Wyświetla kartę tytułową przy rozpoczęciu rozgrywki w poziomie gry  */
void doTitleScreen( ALLEGRO_FONT *font_big, ALLEGRO_FONT *font_small, float x, float y, char *level_id, LevelClearCondition condition );
/** @brief Wyświetla kartę końcową przy ukończeniu rozgrywki w poziomie gry  */
void doEndScreen( ALLEGRO_FONT *font, float x, float y, bool won, char player_id, LevelClearCondition condition );
/** @brief Zwalnia pamięć z poziomu gry */
void destroyLevel( Level **level );

// ========================== level_creator.c ============================

/** @brief Tworzy poziom gry */
Level *createLevel( char *level_id, ALLEGRO_BITMAP *enemy_bmp );

#endif
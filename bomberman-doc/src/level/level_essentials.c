/** @file level_essentials.c
 * 
 * @brief Plik zawiera funkcje zwalniania pamięci z poziomu oraz wyświetlania kart tytułowych
 * 
 * Zawiera funkcję zwalniania pamięci z dynamicznie alokowanej zmiennej typu Level, ale też funkcje \n
 * do wyświetlania kart tytułowych pojawiających się podczas rozpoczynania i kończenia rozgrywki \n
 * w poziomie gry.
 * 
 * @author  Przemysław Cedro
 * @date    2020.05.24
*/


#include "../../headers/level.h"

#include "../../headers/_game_rules.h"

/** @brief Wyświetla kartę tytułową przy rozpoczęciu rozgrywki w poziomie gry 
 * 
 * Wyświetla czarny ekran z napisem "LEVEL X", gdzie 'X' to tytuł poziomu, a następnie napis z warunkiem \n
 * ukończenia poziomu.
 *
 * @param font_big      wskaźnik na główną, dużą czcionkę
 * @param font_small    wskaźnik na poboczną, mniejszą czcionkę
 * @param x             współrzędna pikselowa X do wyświetlenia napisu 
 * @param y             współrzędna pikselowa Y do wyświetlenia napisu 
 * @param level_id      nazwa (ID) poziomu
 * @param condition     warunek wygranej w poziomie gry
 * 
 * @return 
*/
void doTitleScreen( ALLEGRO_FONT *font_big, ALLEGRO_FONT *font_small, float x, float y, char *level_id, LevelClearCondition condition )
{
    al_clear_to_color( COLOR_BLACK );
    al_draw_textf( font_big, COLOR_WHITE, x, y, ALLEGRO_ALIGN_CENTER, "LEVEL %s", level_id );
    al_flip_display();
    al_rest( 2 );

    al_clear_to_color( COLOR_BLACK );
    if( condition == KILL_ALL_ENEMIES )
        al_draw_text( font_small, COLOR_WHITE, x, y + 10, ALLEGRO_ALIGN_CENTER, "KILL ALL ENEMIES!!!" );
    else if( condition == KILL_OPPONENT )
        al_draw_text( font_small, COLOR_WHITE, x, y + 10, ALLEGRO_ALIGN_CENTER, "KILL YOUR OPPONENT!!!" );

    al_flip_display();
    al_rest( 2 );
}

/** @brief Wyświetla kartę końcową przy ukończeniu rozgrywki w poziomie gry 
 * 
 * Wyświetla czarny ekran z odpowiednim napisem w zależności od końcowego wyniku rozgrywki w danym trybie gry, 
 *
 * @param font          wskaźnik na czcionkę
 * @param x             współrzędna pikselowa X do wyświetlenia napisu 
 * @param y             współrzędna pikselowa Y do wyświetlenia napisu 
 * @param won           czy poziom został ukończony pomyślnie
 * @param played_id     (opcjonalny) numer zwycięskiego gracza
 * @param condition     warunek wygranej w poziomie gry
 * 
 * @return 
*/
void doEndScreen( ALLEGRO_FONT *font, float x, float y, bool won, char player_id, LevelClearCondition condition )
{
    al_clear_to_color( COLOR_BLACK );

    if( won )
        if( condition != KILL_OPPONENT )
            al_draw_text( font, COLOR_WHITE, x, y, ALLEGRO_ALIGN_CENTER, "YOU'VE WON!" );
        else
            al_draw_textf( font, COLOR_WHITE, x, y, ALLEGRO_ALIGN_CENTER, "PLAYER %c WON!", player_id );
    else
        if( condition != KILL_OPPONENT )
            al_draw_text( font, COLOR_WHITE, x, y, ALLEGRO_ALIGN_CENTER, "GAME OVER!" );
        else
            al_draw_text( font, COLOR_WHITE, x, y, ALLEGRO_ALIGN_CENTER, "DRAW!" );

    al_flip_display();
    al_rest( 3 );
}

/** @brief Zwalnia pamięć z poziomu gry
 * 
 * Zwalniania pamięć z dynamicznie alokowanej zmiennej typu Level.
 *
 * @param level podwójny wskaźnik na poziom gry
*/
void destroyLevel( Level **level )
{
    free( *level );
    *level = NULL;
}
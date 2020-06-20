/** @file _game_rules.h
 * 
 * @brief Plik zawiera stałe określone dla różnych apektów programu
 * 
 * @author  Przemysław Cedro
 * @date    2020.05.29
*/


#ifndef GAME_RULES_H
#define GAME_RULES_H

#define SCREEN_HEIGHT 600 /** Wysokość wyświetlacza */
#define SCREEN_WIDTH 720 /** Szerokość wyświetlacza */
#define GAME_WINDOW_Y_OFFSET 60 /** Przesunięcie ekranu gry w osi Y */

#define MAX_LOADED_LEVELS 10 /** Maksymalna liczba załadowanych poziomów */

#define CAMERA_SCALE 2 /** Skala przybliżenia kamery */

#define FPS 60.0 /** Częstotliwość czasomierza Allegro odświeżania gry */
#define SECOND_TIMER 1.0 /** Częstotliwość czasomierza Allegro do liczenia sekund */
#define ANIM_TIMER 10.0 /** Częstotliwość czasomierza Allegro do odświerzania klatek animacji */

#define ACTOR_ANIM_FRAMES 8 /** Ilość klatek animacji, jakie posiada aktor */
#define EXPLOSION_ANIM_FRAMES 2 /** Ilość klatek animacji, jakie posiada eksplozja */
#define BOMB_ANIM_FRAMES 3 /** Ilość klatek animacji, jakie posiada bomba */

#define BOMB_BUDGET 5 /** Maksymalna ilość istniejących na raz bomb (wielkość tablicy bomb ) */
#define SFX_BUDGET 50 /** Maksymalna ilość istniejących na raz SFX (wielkość tablicy SFX )*/

#define EXPLOSION_LIFESPAN 2 /** Długość życia SFX eksplozji */
#define CORPSE_LIFESPAN 2 /** Długość życia SFX zwłok */

#define PLAYER_SPEED 1.3 /** Szybkość graczy */
#define ENEMY_SPEED 1.2 /** Szybkość wrogów */

#define COLOR_BLACK al_map_rgb( 0, 0, 0 ) /** Kolor czarny Allegro */
#define COLOR_WHITE al_map_rgb( 255, 255, 255 ) /** Kolor biały Allegro */
#define COLOR_YELLOW al_map_rgb( 255, 255, 0 ) /** Kolor żółty Allegro */
#define COLOR_RED al_map_rgb( 255, 0, 0 ) /** Kolor czerwony Allegro */
#define COLOR_GRAY al_map_rgb( 170, 170, 170 ) /** Kolor szary Allegro */

#define FONT_SRC "./fonts/PixelFJVerdana12pt.ttf" /** Ścieżka do czcionki */
#define LEVELS_FOLDER "./levels" /** Ścieżka do folderu z poziomami */
#define SOLID_BLOCK_SPRITES_SRC "./sprites/solid_block.png" /** Ścieżka do pliku z bitmapą bloku twardego */
#define BRITTLE_BLOCK_SPRITES_SRC "./sprites/brittle_block.png" /** Ścieżka do pliku z bitmapą bloku kruchego */
#define BOMB_SPRITES_SRC "./sprites/bomb.png" /** Ścieżka do pliku z bitmapą bomby */
#define EXPLOSION_SPRITES_SRC "./sprites/explosion.png" /** Ścieżka do pliku z bitmapą eksplozji */
#define PLAYER_SPRITES_ORIG_SRC "./sprites/player_sheet_orig.png" /** Ścieżka do pliku z bitmapą oryginalnej skórki gracza */
#define PLAYER_SPRITES_ALT1_SRC "./sprites/player_sheet_alt1.png" /** Ścieżka do pliku z bitmapą 1. alternatywnej skórki gracza */
#define PLAYER_SPRITES_ALT2_SRC "./sprites/player_sheet_alt2.png" /** Ścieżka do pliku z bitmapą 2. alternatywnej skórki gracza */
#define ENEMY1_SPRITES_SRC "./sprites/enemy1_sheet.png" /** Ścieżka do pliku z bitmapą wrogów */

#endif
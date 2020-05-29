/** @file _game.h
 * 
 * @brief Główny plik nagłówkowy programu 
 * 
 * Zawiera importy wszystkich potrzebnych zasobów programu, deklaracje niezbędnych zmiennych globalnych \n
 * oraz deklaracje funkcji używanych w konkretnych menu lub szczególnie w czasie rozgrywki.
 * 
 * @author  Przemysław Cedro
 * @date    2020.05.29
*/

#ifndef GAME_H
#define GAME_H

#include "_game_rules.h"
#include "_game_state.h"
#include "actor.h"
#include "bomb.h"
#include "camera.h"
#include "direction.h"
#include "level.h"
#include "logic.h"
#include "menus.h"
#include "player_input.h"
#include "rendering.h"
#include "sfx.h"
#include "sprite_properties.h"
#include "level_tile_matrix_tools.h"
#include "level.h"

#include <stdio.h>
#include <stdbool.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>

extern ALLEGRO_DISPLAY *display; /** Zmienna globalna wskaźnika na wyświetlacz Allegro */
extern ALLEGRO_BITMAP *game_window; /** Zmienna globalna wskaźnika na bitmapę, na której rysowany jest obraz rozgrywki */

extern ALLEGRO_FONT *font_big; /** Zmienna globalna wskaźnika na "dużą czcionkę" */
extern ALLEGRO_FONT *font_small; /** Zmienna globalna wskaźnika na "małą czcionkę" */
extern ALLEGRO_FONT *font_vsmall; /** Zmienna globalna wskaźnika na "bardzo małą czcionkę" */

extern ALLEGRO_BITMAP *solid_block_sprite; /** Zmienna globalna wskaźnika na bitmapę bloku twardego */
extern ALLEGRO_BITMAP *brittle_block_sprite; /** Zmienna globalna wskaźnika na bitmapę bloku kruchego */
extern ALLEGRO_BITMAP *bomb_sprite; /** Zmienna globalna wskaźnika na bitmapę bomby */
extern ALLEGRO_BITMAP *explosion_sprite; /** Zmienna globalna wskaźnika na bitmapę eksplozji */
extern ALLEGRO_BITMAP *player1_sprites; /** Zmienna globalna wskaźnika na bitmapę pierwszego gracza */
extern ALLEGRO_BITMAP *player2_sprites; /** Zmienna globalna wskaźnika na bitmapę drugiego gracza */
extern ALLEGRO_BITMAP *enemy1_sprites; /** Zmienna globalna wskaźnika na bitmapę wrogów */

extern GameState gs; /** Zmienna globalna Stanu Gry  */


// ========================================================= game_essentials.c =======================================================================

/** @brief Inicjuje bibliotekę Allegro oraz podstawowe właściwości używane podczas działania programu */
int initAllegro( void );
/** @brief Bada poprawność załadowanych zasobów */
int validateAssets( void );
/** @brief Załadowuje zasoby gry */
int initAssets( void );
/** @brief Uprząta zasoby programu przy zakończeniu jego działania */
void clearUp( void );


// =========================================================== game_funtions.c =======================================================================

/** @brief Aktualizuje stan zmiennej wpisu wybranego poziomu na podstawie Stanu Gry */
void updateSelectedLevelVar( Menu *ls_menu );
/** @brief Aktualizuje stan zmiennej wpisu wybranych skórek dla postaci na podstawie Stanu Gry */
void updateSelectedSkinVars( Menu *opt_menu );
/** @brief Ładuje aktualne skórki dla każdego z graczy */
int loadSelectedSkins( void );
/** @brief Zmienia aktualnie uczęszczanie Menu */
void switchMenu( Menu **current, Menu *goal );
/** @brief Aktualizuje stan tablic na Bomby i SFX */
void updateContainers( Bomb *bomb_container[], SFX *sfx_container[], LevelMap *level_map, Actor **enemies, int enemy_num, ALLEGRO_BITMAP *explosion_bmp, bool *map_update );
/** @brief Sprawdza, czy tablice Bomb i SFX są puste */
bool areContainersEmpty( Bomb *bomb_container[], SFX *sfx_container[] );
/** @brief Aktualizuje ogólny stan Aktora danego gracza */
void updatePlayer( Actor *player, LevelMap *level_map, Actor * *enemies, int enemy_num, SFX *sfx_container[] );
/** @brief Aktualizuje ogólny stan Aktorów i Modułów wrogów */
void updateEnemies( AIModule * *enemy_modules, int enemy_num, SFX *sfx_container[] );
/** @brief Zajmuje się rysowaniem wszystkiego w czasie rozgrywki */
void updateGFX( Camera *camera, Actor *player1, Actor *player2, Actor * *enemies, int enemy_num, LevelMap *level_map, Bomb *bomb_container[], SFX *sfx_container[] );
/** @brief Zajmuje się rysowaniem wszystkiego w czasie pauzy w grze */
void updateGFXOnPause( ALLEGRO_BITMAP *game_stop_frame, Menu *pause_menu );
/** @brief Sprawdza, czy Aktorzy wszystkich wrogów są martwi */
bool areAllEnemiesDead( Actor ** enemies, int enemy_num );
/** @brief Obsługuje działanie kamery przy śmierci jednego z graczy */
void handleCameraOnPlayerDeath( Camera *camera, MultiPlayerCameraModule *mpcm, Actor *player1, Actor *player2 );
/** @brief Bierze stopklatkę obecnego momentu w grze */
void handleTakingGameStopFrame( ALLEGRO_BITMAP **gsf, Camera *camera, Actor *player1, Actor *player2, ALLEGRO_EVENT_QUEUE *eq );
/** @brief Sprawdza, czy oboje Aktorów graczy jest martwych */
bool areAllPlayersDead( Actor *player1, Actor *player2 );
/** @brief Aktualizuje klatki animacji dla obu Aktorów graczy */
void updateAnimFrameForPlayers( Actor *player1, Actor *player2 );
/** @brief Aktualizuje klatki animacji dla Aktorów wrogów */
void updateAnimFrameForEnemies( Actor * *enemies, int enemy_num );

#endif
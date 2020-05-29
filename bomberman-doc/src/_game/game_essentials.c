/** @file game_essentials.c
 * 
 * @brief Plik zawiera funkcje używane przy uruchamianiu i zamykaniu programu.
 * 
 * Zawiera funkcje inicjalizacji biblioteki Allegro, ładowania i sprawdzania zasobów gry oraz \n
 * uprzątania pamięci przy wychodzeniu z programu.
 * 
 * @author  Przemysław Cedro
 * @date    2020.05.26
*/


#include "../../headers/_game.h"

/**
 * @brief Inicjuje bibliotekę Allegro oraz podstawowe właściwości używane podczas działania programu
 * 
 * Inicjuje bibliotekę, tworzy wyświetlacz i ustawia jego właściwości, a następnie włącza \n
 * wychwytywanie sygnałów z klawiatury oraz załącza wtyczki rysowania prostych figur, wyświetlania \n
 * okien dialogowych, przetwarzania obrazów oraz wypisywania tekstu.
 * 
 * @return kod zwrotny wykonania funkcji - zwraca 0 przy prawidłowym wykonaniu 
 */
int initAllegro( void )
{
    if( !al_init() )
    {
        fprintf( stderr, "Failed to initialize allegro!\n" );
        return -1;
    }

    al_set_new_display_flags( ALLEGRO_WINDOWED );
    display = al_create_display( SCREEN_WIDTH, SCREEN_HEIGHT );
    game_window = al_create_bitmap( SCREEN_WIDTH, SCREEN_HEIGHT - GAME_WINDOW_Y_OFFSET );

    if( !display )
    {
        fprintf( stderr, "Failed to create display!\n" );
        return -2;
    }

    al_set_window_title( display, "BOMBERMAN" );
    al_set_window_position( display, 600, 300 );

    al_install_keyboard();
    al_init_primitives_addon();
    al_init_native_dialog_addon();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    return 0;
}

/**
 * @brief Załadowuje zasoby gry
 * 
 * Ładuje czcionki oraz bitmapy z plików i na koniec zwraca wynik poprawności tego załadowania.
 * 
 * @return wynik sprawdzenia poprawności zasobów - 0 w przypadku powodzenia
 */
int initAssets( void )
{
    font_big = al_load_font( FONT_SRC, 40, 0 );
    font_small = al_load_font( FONT_SRC, 30, 0 );
    font_vsmall = al_load_font( FONT_SRC, 12, 0 );

    solid_block_sprite = al_load_bitmap( SOLID_BLOCK_SPRITES_SRC );
    brittle_block_sprite = al_load_bitmap( BRITTLE_BLOCK_SPRITES_SRC );    
    bomb_sprite = al_load_bitmap( BOMB_SPRITES_SRC );
    explosion_sprite = al_load_bitmap( EXPLOSION_SPRITES_SRC );
    player1_sprites = al_load_bitmap( PLAYER_SPRITES_ORIG_SRC );
    player2_sprites = al_load_bitmap( PLAYER_SPRITES_ALT1_SRC );
    enemy1_sprites = al_load_bitmap( ENEMY1_SPRITES_SRC );

    return validateAssets();
}

/**
 * @brief Bada poprawność załadowanych zasobów
 * 
 * Sprawdza, czy wszystkie czcionki i bitmapy zostały załadowane prawidłowo.
 * 
 * @return kod zwrotny wykonania funkcji - zwraca 0 przy prawidłowym wykonaiu
 */
int validateAssets( void )
{
    if( font_big == NULL || font_small == NULL || font_vsmall == NULL ){
        fprintf(stderr, "Failed to load font!\n");
        return -3;
    }
    else if( solid_block_sprite == NULL ){
        fprintf(stderr, "Failed to load solid block bitmap!\n");
        return -4;
    }
    else if( brittle_block_sprite == NULL ){
        fprintf(stderr, "Failed to load brittle block bitmap!\n");
        return -5;
    }
    else if( bomb_sprite == NULL ){
        fprintf(stderr, "Failed to load bomb bitmap!\n");
        return -6;
    }
    else if( explosion_sprite == NULL ){
        fprintf(stderr, "Failed to load explosion bitmap!\n");
        return -7;
    }
    else if( player1_sprites == NULL ){
        fprintf(stderr, "Failed to load player bitmap!\n");
        return -8;
    }
    else if( player2_sprites == NULL ){
        fprintf(stderr, "Failed to load player bitmap!\n");
        return -9;
    }
    else if( enemy1_sprites == NULL ){
        fprintf(stderr, "Failed to load enemy1 bitmap!\n");
        return -10;
    }
    return 0;
}

/**
 * @brief Uprząta zasoby programu przy zakończeniu jego działania
 * 
 * Zwalnia pamięć ze wszystkich czcionek oraz bitmap, jak i dezaktywuje wszystkie wtyczki biblioteki.
 */
void clearUp( void )
{
    al_destroy_bitmap( solid_block_sprite );
    al_destroy_bitmap( brittle_block_sprite );
    al_destroy_bitmap( bomb_sprite );
    al_destroy_bitmap( explosion_sprite );
    al_destroy_bitmap( player1_sprites );
    al_destroy_bitmap( player2_sprites );
    al_destroy_bitmap( enemy1_sprites );
    al_destroy_font( font_big );
    al_destroy_font( font_small );
    al_destroy_font( font_vsmall );
    al_destroy_bitmap( game_window );
    al_destroy_display( display ); 

    al_uninstall_keyboard();
    al_shutdown_native_dialog_addon();
    al_shutdown_image_addon();
    al_shutdown_font_addon();
    al_shutdown_ttf_addon();
}
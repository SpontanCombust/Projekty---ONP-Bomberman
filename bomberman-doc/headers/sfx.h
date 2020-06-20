/** @file sfx.h
 * 
 * @brief Plik zawiera definicję typu SFX, jego enumów pomocniczych oraz deklaracje funkcji dla SFX
 * 
 * @author  Przemysław Cedro
 * @date    2020.05.29
*/


#ifndef SFX_H
#define SFX_H

#include <allegro5/allegro.h>
#include <stdbool.h>

/** Enum informujące o typie SFX. Dostępne typy: EXPLOSION, CORPSE. */
typedef enum E_SFX_Type { EXPLOSION, CORPSE } SFX_Type;
/** Enum informujące o orientacji SFX t.j. w jaki sposób jego bitmapa powinna zostać obrócona. Używane do eksplozji. \n
 * Dostępne orientacje: CENTRE, VERTICAL, HEAD_DOWN, HEAD_UP, HORIZONTAL, HEAD_LEFT, HEAD_RIGHT.
*/
typedef enum E_SFX_Orientation { CENTRE, VERTICAL, HEAD_DOWN, HEAD_UP, HORIZONTAL, HEAD_LEFT, HEAD_RIGHT } SFX_Orientation;

/**
 * @brief Struktura Efektów Specjalnych SFX
 * 
 * Struktura stworzona, by wyświetlać nieruchome bitmapy o z góry określonym czasie egzystencji. \n
 * 
 */
typedef struct S_SFX
{
    float x, y; /**< Koordynaty pikselowe, na których znajduje się SFX */
    int lifespan; /**< Czas życia SFX */
    SFX_Type type; /**< Typ */
    SFX_Orientation orientation; /**< Orientacja */
    int anim_frame; /**< Zmienna klatki animacji */
    ALLEGRO_BITMAP *bmp; /**< Bitmapa SFX */
    
} SFX;


//========== sfx_essentials.c ===========

/** @brief Tworzy i zwraca SFX o danej zawartosci */
SFX *createSFX( float x, float y, int lifespan, SFX_Type type, SFX_Orientation orientation, ALLEGRO_BITMAP *bmp );
/** @brief Zwalnia pamięć z SFX */
void destroySFX( SFX **sfx );


// ========= sfx_handling.c =============

/** @brief Aktualizuje klatkę animacji dla SFX */
void updateAnimFrameForSFX( SFX *sfx );


//======================= sfx_container_manager.c ===========================

/** @brief Zwraca, czy tablica SFX jest pusta */
bool isSFXContainerEmpty( SFX * container[] );
/** @brief Dodaje SFX do tablicy SFX */
void addSFXToContainer(SFX **sfx, SFX * container[] );
/** @brief Sprawdza, czy na danych koordynatach mapy poziomu znajduje się SFX danego typu */
bool isSFXAtTile( int tile_x, int tile_y, SFX *sfx_container[], SFX_Type type );
/** @brief Aktualizuje klatkę animacji elementów tablicy SFX */
void updateAnimFrameForSFXContainer( SFX *sfx_container[] );


#endif
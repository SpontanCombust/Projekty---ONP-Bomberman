/** @file bomb.h
 * 
 * @brief Plik zawiera definicję typu Bomb i deklaracje funkcji stworzonych dla tego typu
 * 
 * @author  Przemysław Cedro
 * @date    2020.05.29
*/


#ifndef BOMB_H
#define BOMB_H

#include "actor.h"
#include "level_map.h"
#include "sfx.h"
#include <allegro5/allegro.h>

/**
 * @brief Struktura bomby, Bomb
 * 
 * Bomba stawiana jest na danym polu mapy. Ma określony czas do wybuchu (długość lontu) i zasięg eksplozji.
 */
typedef struct S_Bomb
{
    int tile_x, tile_y; /**< współrzędne pola mapy */
    int fuse; /**< czas do wybuchu (lont) */
    int blast_range; /**< zasieg wybuchu */
    int anim_frame; /**< numer obecnej klatki animacji */
    ALLEGRO_BITMAP *bmp; /**< bitmapa */

} Bomb;

#define DEFAULT_FUSE 3 /** Stała domyślnej długości lontu (czasu do wybuchu)*/
#define DEFAULT_BLAST_RANGE 1 /** Stała domyślnego zasięgu wybuchu bomby */


// =============================== bomb_essentials.c ==================================

/** @brief Tworzy bombę */
Bomb *createBomb( int tile_x, int tile_y, int fuse, int blast_range, ALLEGRO_BITMAP *bmp );
/** @brief Zwalnia pamięć z bomby */
void destroyBomb( Bomb **bomb );


// ================================ bomb_placing.c ====================================

/** @brief Tworzy bombę na tej samej pozycji co aktor */
Bomb *createEmptyBombAtActor( Actor *actor );
/** @brief Ustawia konkretne cechy bomby */
void setBombProperties( Bomb *bomb, int fuse, int blast_range, ALLEGRO_BITMAP *bmp );


// ============================ bomb_container_manager.c ==============================

/** @brief Sprawdza, czy tablica bomb jest pusta */
bool isBombContainerEmpty( Bomb * container[] );
/** @brief Dodaje bombę do tablicy bomb */
void addBombToContainer( Bomb **bomb, Bomb *container[] );


// ================================= bomb_action.c ====================================

/** @brief Egzekwuje eksplozję bomby */
void explodeBomb( Bomb *bomb, LevelMap *level_map, SFX * sfx_container[], ALLEGRO_BITMAP *explosion_bmp );
/** @brief Aktualizuje klatkę animacji dla bomby */
void updateAnimFrameForBomb( Bomb *bomb );

#endif
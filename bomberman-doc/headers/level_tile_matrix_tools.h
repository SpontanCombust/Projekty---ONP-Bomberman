/** @file level_tile_matrix_tools.h
 * 
 * @brief Plik zawiera deklaracje funkcji wczytywania mapy poziomu z pliku oraz zamiany koordynatów na odpowiednie systemu.
 * 
 * @author  Przemysław Cedro
 * @date    2020.05.29
*/


#ifndef TILE_MATRIX_H
#define TILE_MATRIX_H

#include "../libs/matrix.h"
#include <stdio.h>
#include <stdbool.h>

// ======================== tile_matrix_creator.c =======================

/** @brief Odczytuje mapę poziomu z pliku */
int **createLevelTileMatrix( FILE *map_file, int *rows, int *collumns, unsigned char *r, unsigned char *g, unsigned char *b );


// ===================================== coordinate_translator.c =================================

/** @brief Zamienia współrzędne pola mapy na pikselowe */
float pixelFromTile( int t );
/** @brief Zamienia współrzędne pikselowe na te pola mapy */
int tileFromPixel( float p );

#endif
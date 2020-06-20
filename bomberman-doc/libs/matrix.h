/** @file matrix.h
 * 
 * @brief Plik nagłówkowy dla tablicy dwuwymiarowej
 * 
 * Zawiera deklaracje funkcji dla tablicy dwuwymiarowej.
 * 
 * @author  Przemysław Cedro
 * @date    2020.05.26
*/


#ifndef MATRIX_H
#define MATRIX_H

#include <stdbool.h>

// ================================ matrix.c ==================================

/** Alokuje pamięć na tablicę dwuwymiarową typu int */
int **allocateMatrix( int rows, int collumns );

/** Zwraca zawartość komórki tablicy dwuwymiarowej */
int getTileContent( int **tile_matrix, int tile_x, int tile_y );

/** Ustawia zawartość komórki tablicy dwuwymiarowej */
void setTileContent( int **tile_matrix, int tile_x, int tile_y, int content );

/** Sprawdza, czy komórka o podanych indeksach wykracza poza zasięg tablicy dwuwymiarowej */
bool areCoordsOutOfBounds( int tile_x, int tile_y, int rows, int collumns );

/** Zlicza ilość komórek w tablicy o danej zawartości */
int countContentInMatrix( int **tile_matrix, int rows, int collumns, int content );

/** Wypisuje do konsoli zawartość tablicy dwuwymiarowej */
void printMatrix( int **matrix, int rows, int colls );

/** Zwalnia pamięć z tablicy dwuwymiarowej */
void freeMatrix( int **matrix, int rows );

#endif
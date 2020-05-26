/** @file matrix.c
 * 
 * @brief Plik zawiera funkcje dla tablicy dwuwymiarowej
 * 
 * Zawiera funkcje alokowania tablicy dwuwymiarowej danych typu int o danej wielkości, sprawdzania\n
 * i ustawiania zawartości komórek tablicy, wypisywania tej tablicy oraz zwalniania z niej pamięci.
 * 
 * @author  Przemysław Cedro
 * @date    2020.05.26
*/


#include "../matrix.h"

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Alokuje pamięć na tablicę dwuwymiarową typu int
 * 
 * @param rows      ilość rzędów
 * @param collumns  ilość kolumn
 * 
 * @return utworzona tablica lub NULL jeśli nie udało się na nią przydzielić pamięci
 */
int **allocateMatrix( int rows, int collumns )
{
    int **matrix = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++)
        matrix[i] = (int *)malloc(collumns * sizeof(int));

    if( !matrix )
    {
        puts("Failed to allocate matrix!");
        return NULL;
    }

    return matrix;
}

/**
 * @brief Zwraca zawartość komórki tablicy dwuwymiarowej
 * 
 * @param tile_matrix   tablica dwuwymiarowa
 * @param tile_x        indeks w osi X
 * @param tile_y        indeks w osi Y
 * 
 * @return zawartość komórki tablicy
 */
int getTileContent( int **tile_matrix, int tile_x, int tile_y )
{
    return tile_matrix[ tile_y ][ tile_x ];
}

/**
 * @brief Ustawia zawartość komórki tablicy dwuwymiarowej
 * 
 * @param tile_matrix   tablica dwuwymiarowa
 * @param tile_x        indeks w osi X
 * @param tile_y        indeks w osi Y
 * @param content       zawartość komórki
 */
void setTileContent( int **tile_matrix, int tile_x, int tile_y, int content )
{
    tile_matrix[tile_y][tile_x] = content;
}

/**
 * @brief Sprawdza, czy komórka o podanych indeksach wykracza poza zasięg tablicy dwuwymiarowej
 * 
 * @param tile_x    indeks w osi X
 * @param tile_y    indeks w osi Y
 * @param rows      ilość rzędów tablicy
 * @param collumns  ilość kolumn tablicy
 * 
 * @return true jeśli wykryto wykroczenie poza zasięg tablicy
 */
bool areCoordsOutOfBounds( int tile_x, int tile_y, int rows, int collumns )
{
    if( tile_x < 0 || tile_x >= collumns || tile_y < 0 || tile_y >= rows )
        return true;
    return false;
}

/**
 * @brief Zlicza ilość komórek w tablicy o danej zawartości
 * 
 * @param tile_matrix   tablica dwuwymiarowa
 * @param rows          ilość rzędów tablicy
 * @param collumns      ilość kolumn tablicy
 * @param content       zliczana zawartość
 * 
 * @return liczba komórek o danej zawartości 
 */
int countContentInMatrix( int **tile_matrix, int rows, int collumns, int content )
{
    int count = 0;

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < collumns; j++)
            if( tile_matrix[i][j] == content )
                count++;
    
    return count;
}

/**
 * @brief Wypisuje do konsoli zawartość tablicy dwuwymiarowej
 * 
 * @param matrix    tablica dwuwymiarowa
 * @param rows      ilość rzędów
 * @param colls     ilość kolumn
 */
void printMatrix( int **matrix, int rows, int colls )
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < colls; j++)
        {
            printf("%d ", matrix[i][j] );
        }
        puts("");
    }
    
}

/**
 * @brief Zwalnia pamięć z tablicy dwuwymiarowej
 * 
 * @param matrix    tablica dwuwymiarowa 
 * @param rows      ilość rzędów tablicy
 */
void freeMatrix( int **matrix, int rows )
{
    for (int i = 0; i < rows; i++)
        free( matrix[i] );

    free( matrix );
    matrix = NULL;
}
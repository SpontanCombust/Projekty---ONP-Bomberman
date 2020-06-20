/** @file coordinate_translator.c
 * 
 * @brief Plik zawiera funkcje pomocnicze do zmiany koordynatów z pikselowych na te pól mapy i na odwrót
 * 
 * @author  Przemysław Cedro
 * @date    2020.05.24
*/


#include "../../headers/level_tile_matrix_tools.h"
#include "../../headers/sprite_properties.h"

/** @brief Zamienia współrzędne pola mapy na pikselowe
 *
 * Współrzędna pikselowa to iloczyn współrzędnej pola mapy i wielkości pola.
 * 
 * @param t współrzędna pola mapy
 * 
 * @return współrzędna pikselowa
*/
float pixelFromTile( int t )
{
    return (float) (t * TILE_SIZE);
}

/** @brief Zamienia współrzędne pikselowe na te pola mapy
 *
 * Współrzędna pola mapy to zaokrąglony w dół iloraz współrzędnej pikselowej i wielkości pola mapy.
 * 
 * @param p współrzędna pikselowa
 * 
 * @return współrzędna pola mapy
*/
int tileFromPixel( float p )
{
    return (int) (p / TILE_SIZE);
}
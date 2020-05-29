/** @file level_tile_matrix_creator.c
 * 
 * @brief Plik zawiera funkcję do odczytywania mapy poziomu z pliku
 * 
 * @author  Przemysław Cedro
 * @date    2020.05.24
*/


#include "../../headers/level_tile_matrix_tools.h"

#include <stdlib.h>
#include <string.h>

/** @brief Odczytuje mapę poziomu z pliku
 * 
 * Czyta dane pliku w zależności od napotkanych nagłówków. \n
 * 
 * Jeśli napotka nagłówek [background] odczytuje wartości RGB dla tła mapy i zapisuje \n
 * ich wartości do zmiennych spod wskaźników r, g i b. W pliku każda z tych składowych podana \n
 * jest jako "x=y", gdzie 'x' to składowa, a 'y' to wartość, jaka ma być zapisana do tej składowej. \n
 * Dostępne składowe to: 'r' - czerowny, 'g' - zielony i 'b' - niebieski. \n
 * \n
 * Jeśli napotka nagłówek [dimensions] odczytuje wartości wymiarów macierzy tego poziomu. \n
 * W pliku każdy z tych wymiarów podany jest jako "x=y", gdzie 'x' to wymiar, a 'y' to wielkość tego wymiaru. \n
 * Dostępne wymiary to: 'r' - ilość rzędów, 'c' - ilość kolumn. \n
 * Na koniec alokuje pamięć na macierz, do której będą zapisane wartości macierzy w pliku. \n
 * \n
 * Jeśli napotka nagłówek [data] odczytuje zawartość macierzy poziomu. \n
 * Wymiary macierzy są domyślnie są równe zero, więcej zmienna macierzy jest zabezpieczona tutaj \n
 * przed zapisywaniem do niej wartości jeśli wcześniej nie wymiary nie zostały określone pod \n
 * nagłówkiem [dimensions] i nie została zalokowana pamięć na macierz. Kolejne wartości napotkane \n
 * w danej kolumnie i danym rzędzie macierzy z pliku zapisuje do utworzonej w programie macierzy. \n
 * \n
 * Z początku pliku i między zawartościami nagłówków jeśli linia zaczyna się od ';' zostaje ona \n
 * automatycznie ignorowana.
 *
 * @param map_file  wskaźnik na plik z mapą poziomu
 * @param rows      wskaźnik na zmienną ilości rzędów w macierzy
 * @param collumns  wskaźnik na zmienną ilości kolumn w macierzy
 * @param r         wskaźnik na zmienną wartości kanału czerwonego koloru tła mapy
 * @param g         wskaźnik na zmienną wartości kanału zielonego koloru tła mapy
 * @param b         wskaźnik na zmienną wartości kanału niebieskiego koloru tła mapy
 * 
 * @return macierz mapy poziomu
*/
int **createLevelTileMatrix( FILE *map_file, int *rows, int *collumns, unsigned char *r, unsigned char *g, unsigned char *b )
{
    *rows = *collumns = 0;
    *r = *g = *b = 0;
    int **tile_matrix = NULL;

    char buffer[100];
    char subbuf[100];
    while ( fgets( buffer, 100, map_file ) != NULL )
    {
        if( buffer[0] == ';' )
            continue;
        else if( strcmp( buffer, "[background]\n" ) == 0 )
        {
            for (int i = 0; i < 3; i++)
            {
                if( fgets( buffer, 100, map_file ) != NULL )
                {
                    strncpy( subbuf, buffer + 2, strlen( buffer ) - 3);
                    subbuf[ strlen( subbuf ) ] = '\0';

                    if( buffer[0] == 'r' && buffer[1] == '=' )
                        *r = atoi( subbuf );
                    else if( buffer[0] == 'g' && buffer[1] == '=' )
                        *g = atoi( subbuf );
                    else if( buffer[0] == 'b' && buffer[1] == '=' )
                        *b = atoi( subbuf );

                    memset( subbuf, '\0', 100 );
                }
            } 
        }
        else if( strcmp( buffer, "[dimensions]\n" ) == 0 )
        {
            for (int i = 0; i < 2; i++)
            {
                if( fgets( buffer, 100, map_file ) != NULL )
                {
                    strncpy( subbuf, buffer + 2, strlen( buffer ) - 3);
                    subbuf[ strlen( subbuf ) ] = '\0';

                    if( buffer[0] == 'r' && buffer[1] == '=' )
                        *rows = atoi( subbuf );
                    else if( buffer[0] == 'c' && buffer[1] == '=' )
                        *collumns = atoi( subbuf );

                    memset( subbuf, '\0', 100 );     
                }
            }

            tile_matrix = allocateMatrix(*rows, *collumns);
        }

        else if( strcmp( buffer, "[data]\n" ) == 0 )
        {
            for (int i = 0; i < *rows; i++)
            {
                if( fgets( buffer, 100, map_file ) != NULL )
                    for (int j = 0; j < *collumns; j++)
                        setTileContent( tile_matrix, j, i, buffer[j] - '0' ); 
            }   
        }
    }

    return tile_matrix;
}

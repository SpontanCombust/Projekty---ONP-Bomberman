/** @file path_array_creator.c
 * 
 * @brief Plik zawiera funkcje tworzenia i pomocnicze dla ścieżek ruchu Path.
 * 
 * Zawiera funkcje tworzenia tablic ścieżek ruchu Path z pliku, wypisywania ścieżki do konsoli oraz\n
 * zwalniania pamięci z tablicy ścieżek.
 * 
 * @author  Przemysław Cedro
 * @date    2020.05.26
*/


#include "../../headers/ai.h"

#include "../../headers/level_tile_matrix_tools.h"
#include <stdio.h>

/**
 * @brief Ustawia koordynaty dla elementu tablicy kroków PathStep przy odczytywaniu ich z pliku
 * 
 * Bierze tekst w formie "x,y", gdzie 'x' to koordynat X dla kroku PathStep, a 'y' to koordynat Y dla kroku\n
 * w ścieżce i przekształca go w liczby ustawiane jako koordynaty celu dla danego kroku w tablicy kroków.
 * 
 * @param steps tablica kroków
 * @param i     indeks tablicy
 * @param point tekst kroku z pliku
 */
static void handlePoint( PathStep * steps, int i, char *point )
{
    char *tok = strtok( point, "," );
    steps[i].dest_x = pixelFromTile( atoi( tok ) );

    tok = strtok( NULL, "," );
    steps[i].dest_y = pixelFromTile( atoi( tok ) );
    tok = NULL;
}

/**
 * @brief Tworzy tablicę kroków PathStep dla ścieżki Path
 * 
 * Dzieli ciąg znaków z pliku reprezentujący ciąg kroków i tworzy na jego podstawie tablicę kroków\n
 * dla ścieżki ruchu.
 * Ciąg znaków wygląda następująco: "n x1 x2 x3 ... xn", gdzie n to ilość kroków, a kolejne xi\n
 * to kroki o formie "x,y".
 * @see handlePoint()
 * 
 * @param line      linia tekstu z pliku
 * @param step_num  wskaźnik na ilość kroków
 * 
 * @return utowrzona tablica kroków 
 */
PathStep * createPathStepArray( char *line, int *step_num )
{
    PathStep * steps;

    char *tok = strtok( line, " " );
    *step_num = atoi( tok );

    steps = (PathStep *)calloc( *step_num, sizeof( PathStep ) );

    char * tokens[ *step_num ];
    int i = 0;

    tok = strtok( NULL, " " );
    while ( tok != NULL )
    {
        tokens[i++] = tok;
        tok = strtok( NULL, " " );
    }
    
    for (i = 0; i < *step_num; i++)
        handlePoint( steps, i, tokens[i] );
    
    return steps;
}

/**
 * @brief Tworzy tablicę ścieżek Path z pliku
 * 
 * Czyta dane z pliku w zależności od napotkanych nagłówków.\n
 * 
 * Jeśli napotka nagłówek [quantity] szuka linii o treści "n=x",
 * gdzie x to ilość ścieżek Path jakie będą dalej wypisane.
 * 
 * Jeśli napotka nagłówek [paths] szuka linii ze ścieżkami Path. Każda z tych linii przetwarzana jest\n
 * na tablicę kroków PathStep, która zostaje ustawiana wraz z ilością kroków jakie posiada do elementu\n
 * tablicy ścieżek.
 * 
 * Jeśli z początku pliku lub pomiędzy zawartością nagłówków napotka linię zaczynającą się od ";",\n
 * automatycznie ją pominie. 
 * 
 * @param enemies_file_path ścieżka do pliku z tablicą ścieżek Path
 * @param paths_num         wskaźnik na ilość ścieżek Path
 * 
 * @return utworzona z pliku tablica ścieżek Path 
 */
Path * createPathArray( char *enemies_file_path, int *paths_num )
{
    *paths_num = 0;
    Path * paths_array = NULL;

    FILE *enemies_file = fopen( enemies_file_path, "r" );

    if( enemies_file != NULL )
    {
        char buffer[100];
        char subbuf[100];

        while ( fgets( buffer, 100, enemies_file ) != NULL )
        {
            if( buffer[0] == ';' )
                continue;

            else if( strcmp( buffer, "[quantity]\n" ) == 0 )
            {
                if( fgets( buffer, 100, enemies_file ) != NULL )
                {
                    strncpy( subbuf, buffer + 2, strlen( buffer ) - 3);
                    subbuf[ strlen( subbuf ) ] = '\0';

                    if( buffer[0] == 'n' && buffer[1] == '=' )
                        *paths_num = atoi( subbuf );
                }

                paths_array = (Path *)calloc( *paths_num, sizeof( Path ) );
                memset( subbuf, '\0', 100 );
            }

            else if( strcmp( buffer, "[paths]\n" ) == 0 )
            {
                for (int i = 0; i < *paths_num; i++)
                {
                    if( fgets( buffer, 100, enemies_file ) != NULL )
                    {
                        int step_num = 0;
                        PathStep * steps = createPathStepArray( buffer, &step_num );

                        paths_array[i].step_num = step_num;
                        paths_array[i].steps = steps;
                    }
                }
            }
        }

        if( fclose( enemies_file ) == EOF )
            printf("Failed to close file %s !", enemies_file_path );

        return paths_array;
    }
    else
    {
        printf("Failed to open file %s !", enemies_file_path );
        return NULL;
    }
}

/**
 * @brief Wypisuje do konsoli treść ścieżki Path
 * 
 * @param path ścieżka
 */
void printPath( Path path )
{
    for (int i = 0; i < path.step_num; i++)
    {
        printf("(%lf, %lf) ", path.steps[i].dest_x, path.steps[i].dest_y );
    }
    puts("");
}

/**
 * @brief Zwalnia pamięć z tablicy ścieżek
 * 
 * Zwalnia pamięć z dynamicznie alokowanej tablicy dynamicznych zmiennych typu Path oraz zwalnia\n
 * pamięć z tablic kroków PathStep dla każdej z tych ścieżek. 
 * 
 * @param array podwójny wskaźnik na tablicę ścieżek Path
 */
void destroyPathArray( Path ** array )
{
    free( (* array)->steps );
    free( * array );
    * array = NULL;
}
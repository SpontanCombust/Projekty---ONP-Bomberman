/** @file level_scanner.c
 * 
 * @brief Plik zawiera funkcje skanowania w poszukiwaniu poziomów gry
 * 
 * @author  Przemysław Cedro
 * @date    2020.05.24
*/


#include "../../headers/level_scan_tools.h"

#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro_native_dialog.h>

/** @brief Odwraca kolejność nazw poziomów w tablicy.
 * 
 * Domyślnie na systemie linux biblioteka dirent odczytuje nazwy katalogów w odwrotnej kolejności \n
 * alfabetycznej, więc przy nazwach z numerami poziomy byłyby wyświetlane odwrotnie. Stąd odwracanie \n
 * kolejności nazw.
 *
 * @param level_name    tablica nazw poziomów
 * @param level_num     ilość poziomów
*/
static void reverseArray( char levels_names[MAX_LOADED_LEVELS][10], int level_num )
{
    for (int i = 0; i < level_num/2; i++)
    {
        char tmp[10];
        strcpy( tmp, levels_names[i] );
        strcpy( levels_names[i], levels_names[level_num-i-1] );
        strcpy( levels_names[level_num-i-1], tmp );
    }
    
}

/** @brief Skanuje w poszukiwaniu katalogów poziomów
 * 
 * Sprawdza katalog 'levels' w poszukiwaniu katalogów zaczynających się na 'level'. Nazwa poziomu to \n
 * wszystko zapisane po tym słowie. Maksymalna długość nazwy poziomu to maksymalnie 10 znaków. Reszta \n
 * znaków zostaje unicana. Jeśli sam katalog poziomów nie zostanie znaleziony, wyświetlany jest błąd.
 *
 * @param levels_names  tablica nazw poziomów
 * @param level_num     wskaźnik na zmienną ilości poziomów
*/
void scanForLevels( char levels_names[MAX_LOADED_LEVELS][10], int *level_num )
{
    *level_num = 0;

    DIR *dir;
    struct dirent *entry;

    dir = opendir( LEVELS_FOLDER );
    int i = 0;
    if( dir != NULL )
    {
        while ( ( entry = readdir( dir ) ) != NULL )
        {
            char buffer[15];
            strncpy( buffer, entry->d_name, 15 );
            if( strncmp( buffer, "level", 5 ) == 0 ) {
                strncpy( levels_names[i], buffer + 5, 10 );
                i++;
            }

            if( i == 10 ) break;
        }
    } 
    else
    {
        al_show_native_message_box( NULL, "ERROR", "Level directory error", "Failed to load level directory!", NULL, ALLEGRO_MESSAGEBOX_ERROR );
        return;
    } 
    
    *level_num = i;
    reverseArray( levels_names, *level_num );
}

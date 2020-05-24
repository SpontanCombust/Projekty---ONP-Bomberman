/** @file level_map_essentials.c
 * 
 * @brief Plik zawiera podstawowe funckje dla mapy poziomu
 * 
 * Zawiera funkcje tworzenia mapy poziomu i zwalniania z niej pamięci
 * 
 * @author  Przemysław Cedro
 * @date    2020.05.24
*/


#include "../../headers/level_map.h"

#include "../../headers/sprite_properties.h"
#include "../../headers/level_tile_matrix_tools.h"
#include <allegro5/allegro.h>
#include <stdio.h>

/** @brief Tworzy mapę poziomu
 * 
 * Otwiera plik o danej ścieżce i odczytuje z niego przy pomocy funkcji createLevelTileMatrix()\n
 * dane mapy poziomu. Tworzy zmienną typu LevelMap (Mapa Poziomu) i zapisuje do niego odczytane wartości. 
 *
 * @param map_file_path ścieżka do pliku z mapą poziomu
 * 
 * @return wskaźnik na mapę poziomu
*/
LevelMap *createLevelMap( char *map_file_path )
{
    LevelMap *level_map = (LevelMap *)malloc( sizeof( LevelMap ) );

    if( level_map )
    {   
        FILE *map_file = fopen( map_file_path, "r" );

        if( map_file == NULL)
        {
            printf("Failed to open file %s !", map_file_path );
            return NULL;
        }

        int rows, collumns;
        unsigned char r, g, b;
        int **tile_matrix = createLevelTileMatrix( map_file, &rows, &collumns, &r, &g, &b );

        if( fclose( map_file ) == EOF )
            printf("Failed to close file %s !", map_file_path );

        level_map -> rows = rows;
        level_map -> collumns = collumns;
        level_map -> tile_matrix = tile_matrix;
        level_map -> bg = al_map_rgb( r, g, b );
        level_map -> bmp = al_create_bitmap( collumns * TILE_SIZE, rows * TILE_SIZE );
    } 
    else
    {
        puts("Failed to allcoate level map!");
        return NULL;
    }    

    return level_map;
}

/** @brief Zwalnia pamięć z mapy poziomu
 * 
 * Zwalnia pamięć z dynamicznie alokowanej zmiennej typu LevelMap, jej macierzy poziomu oraz bitmapy.
 *
 * @param level_map podwójny wskaźnik na mapę poziomu
*/
void destroyLevelMap( LevelMap **level_map )
{
    freeMatrix( (*level_map)->tile_matrix , (*level_map)->rows );
    al_destroy_bitmap( (*level_map)->bmp );

    free( *level_map );
    *level_map = NULL;
}
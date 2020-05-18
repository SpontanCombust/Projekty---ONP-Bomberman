#include "../../headers/level_scan_tools.h"

#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro_native_dialog.h>

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

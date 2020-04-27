#include "../../headers/level.h"

#include "../../libs/matrix.h"
#include "../../headers/block_type.h"
#include "../../headers/_game_rules.h"
#include <allegro5/allegro_native_dialog.h>
#include <stdio.h>
#include <string.h>

Level *createLevel( char *level_id, ALLEGRO_BITMAP *enemy_bmp )
{
    Level *level = ( Level * )malloc( sizeof( Level ) );

    char level_subfolder[10] = "";
    sprintf( level_subfolder, "/level%s", level_id );
    char map_file_name[20] = "";
    sprintf( map_file_name, "/level%s_map.txt", level_id );
    char enemies_file_name[20] = "";
    sprintf( enemies_file_name, "/level%s_enemies.txt", level_id );

    char file_path[40] = LEVELS_FOLDER;
    strcat( file_path, level_subfolder );
    strcat( file_path, map_file_name );
    LevelMap *level_map = createLevelMap( file_path );

    int enemy_num;
    strcpy( file_path, LEVELS_FOLDER );
    strcat( file_path, level_subfolder );
    strcat( file_path, enemies_file_name );
    Path * enemy_paths = createPathArray( file_path, &enemy_num );

    if( level_map == NULL || enemy_paths == NULL ) {
        al_show_native_message_box( NULL, "ERROR", "Level load error!", "Level failed to load properly!", NULL, ALLEGRO_MESSAGEBOX_WARN );
        return NULL;
    }

    Actor * *enemies = (Actor **)malloc( enemy_num * sizeof( Actor * ) );
    AIModule * *ai_modules = (AIModule **)malloc( enemy_num * sizeof( AIModule * ) );

    for (int i = 0; i < enemy_num; i++)
    {
        enemies[i] = createAIActor( enemy_paths[i], ENEMY_SPEED, enemy_bmp );
        ai_modules[i] = createAIModule( enemies[i], enemy_paths[i] );
    }

    level -> level_map = level_map;
    level -> enemy_paths = enemy_paths;
    level -> enemy_intit_count = enemy_num;
    level -> enemies = enemies;
    level -> ai_modules = ai_modules;

    return level;
}

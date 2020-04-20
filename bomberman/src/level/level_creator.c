#include "../../headers/level.h"

#include "../../libs/matrix.h"
#include "../../headers/block_type.h"
#include "../../headers/_game_rules.h"
#include <stdio.h>
#include <string.h>

Level *createLevel( int level_number, ALLEGRO_BITMAP *enemy_bmp )
{
    if( level_number < 0 || level_number > LEVELS_MADE )
    {
        puts("This level foes not exist!");
        return NULL;
    }

    Level *level = ( Level * )malloc( sizeof( Level ) );

    char level_subfolder[10] = "";
    sprintf( level_subfolder, "/level%d", level_number );
    char map_file_name[20] = "";
    sprintf( map_file_name, "/level%d_map.txt", level_number );
    char enemies_file_name[20] = "";
    sprintf( enemies_file_name, "/level%d_enemies.txt", level_number );

    char file_path[40] = LEVELS_FOLDER;
    strcat( file_path, level_subfolder );
    strcat( file_path, map_file_name );
    LevelMap *level_map = createLevelMap( file_path );

    int enemy_num;
    strcpy( file_path, LEVELS_FOLDER );
    strcat( file_path, level_subfolder );
    strcat( file_path, enemies_file_name );
    Path * enemy_paths = createPathArray( file_path, &enemy_num );

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
    // level -> block_count = countContentInMatrix( level_map->tile_matrix, level_map->rows, level_map->collumns, BRITTLE_BLOCK );
    // level -> enemy_count = enemy_num;

    return level;
}

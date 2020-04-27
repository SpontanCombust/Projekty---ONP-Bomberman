#ifndef AI_H
#define AI_H

#include "actor.h"
#include "logic.h"

typedef struct
{
    float dest_x, dest_y;

} PathStep;

typedef struct S_Path
{
    int step_num;
    PathStep * steps;

} Path;

typedef struct S_AIModule
{
    Actor *actor;
    Path path;
    PathStep current_step;
    int step_index;
    bool reversed_path;

} AIModule;


// =========================== path_array_creator.c =============================

PathStep * createPathStepArray( char *line, int *step_num );
Path * createPathArray( char *enemies_file_path, int *paths_num );
void destroyPathArray( Path ** array );
void printPath( Path path );


// ======================== ai_movement_module_handler.c ========================

bool reachedDestination( AIModule *module );
void doNextStep( AIModule *module );


// =============================== ai_essentials.c ==============================

AIModule *createAIModule( Actor *actor, Path path );
void destroyAIModule( AIModule **module );
void destroyAIModuleArray( AIModule ** *modules, int module_num );
Actor *createAIActor( Path path, float speed, ALLEGRO_BITMAP *bmp );

#endif
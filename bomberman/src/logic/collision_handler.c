#include "../../headers/logic.h"

#include "../../headers/sprite_properties.h"
#include "../../headers/level_tile_matrix_tools.h"
#include <stdio.h>
#include <math.h>

bool isOutOfBounds( Actor *actor, LevelMap *level_map, enum Direction *cdir )
{
    bool outOfBounds = false;

    if( actor->y + actor->cy + actor->ch > level_map->rows * TILE_SIZE )
    {
        outOfBounds = true;
        *cdir = DOWN;
    }
    else if( actor->y + actor->cy < 0 )
    {
        outOfBounds = true;
        *cdir = UP;
    }
    else if( actor->x + actor->cx < 0 )
    {
        outOfBounds = true;
        *cdir = LEFT;
    }
    else if( actor->x + actor->cx + actor->cw > level_map->collumns * TILE_SIZE )
    {
        outOfBounds = true;
        *cdir = RIGHT;
    }

    return outOfBounds;
}

void handleOutOfBounds( Actor *actor, LevelMap *level_map, enum Direction cdir )
{
    switch ( cdir )
    {
        case DOWN:
            actor -> y = level_map->rows * TILE_SIZE - actor->cy - actor->ch;
            break;
        case UP:
            actor -> y = - actor->cy;
            break;
        case LEFT:
            actor -> x = - actor->cx;
            break;
        case RIGHT:
            actor -> x = level_map->collumns * TILE_SIZE - actor->cx - actor->cw;
            break;
    }
}

static bool isCollidedVertexOnTerrain( float vertex_x, float vertex_y, LevelMap *level_map )
{
    if( getTileContent( level_map->tile_matrix, tileFromPixel( vertex_x ), tileFromPixel( vertex_y ) ) > 0 )
        return true;
    return false;
}

bool isTerrainCollisionX( Actor *actor, LevelMap *level_map, enum Direction *cdir )
{
    bool terrainCollision = false;

    if( isCollidedVertexOnTerrain( actor->x + actor->cx, actor->y + actor->cy,                  level_map ) ||        // lewy gorny wierzcholek
        isCollidedVertexOnTerrain( actor->x + actor->cx, actor->y + actor->cy + actor->ch - 1,  level_map ) )         // lewy dolny wierzcholek
    {
        terrainCollision = true;
        *cdir = LEFT;
    }
    else if( isCollidedVertexOnTerrain( actor->x + actor->cx + actor->cw - 1,  actor->y + actor->cy,                    level_map ) ||   // prawy gorny wierzcholek
             isCollidedVertexOnTerrain( actor->x + actor->cx + actor->cw - 1,  actor->y + actor->cy + actor->ch - 1,    level_map ) )    // prawy dolny wierzcholek
    {
        terrainCollision = true;
        *cdir = RIGHT;
    }

    return terrainCollision;
}

bool isTerrainCollisionY( Actor *actor, LevelMap *level_map, enum Direction *cdir )
{
    bool terrainCollision = false;

    if( isCollidedVertexOnTerrain( actor->x + actor->cx,                    actor->y + actor->cy + actor->ch - 1, level_map ) ||   // lewy dolny wierzcholek
        isCollidedVertexOnTerrain( actor->x + actor->cx + actor->cw - 1,    actor->y + actor->cy + actor->ch - 1, level_map ) )    // prawy dolny wierzcholek
    {
        terrainCollision = true;
        *cdir = DOWN;
    }
    else if( isCollidedVertexOnTerrain( actor->x + actor->cx,                   actor->y + actor->cy, level_map ) ||       // lewy gorny wierzcholek
             isCollidedVertexOnTerrain( actor->x + actor->cx + actor->cw - 1,   actor->y + actor->cy, level_map ) )        // prawy gorny wierzcholek
    {
        terrainCollision = true;
        *cdir = UP;
    }

    return terrainCollision;
}

void handleTerrainCollision( Actor *actor, enum Direction cdir )
{
    int head_coord;
    switch( cdir )
    {
        case DOWN:
            head_coord = actor->y + actor->cy + actor->ch - 1;
            actor -> y = pixelFromTile( tileFromPixel( head_coord ) - 1 );
            break;
        case UP:
            head_coord = actor->y + actor->cy;
            actor -> y = pixelFromTile( tileFromPixel( head_coord ) + 1 ) - actor->cy;
            break;
        case LEFT:
            head_coord = actor->x + actor->cx;
            actor -> x = pixelFromTile( tileFromPixel( head_coord ) + 1 ) - actor->cx;
            break;
        case RIGHT:
            head_coord = actor->x + actor->cx + actor->cw - 1;
            actor -> x = pixelFromTile( tileFromPixel( head_coord ) - 1 ) + actor->cx;
            break;
    }
}

static float getActorsDistance( Actor *actor1, Actor *actor2 )
{
    return sqrt( pow( actor1->x - actor2->x, 2 ) + pow( actor1->y - actor2->y, 2 ) );
}

static bool isCollidedVertexOnActor( float vertex_x, float vertex_y, Actor *actor )
{
    if( vertex_x > actor->x + actor->cx && vertex_x < actor->x + actor->cx + actor->cw - 1 &&
        vertex_y > actor->y + actor->cy && vertex_y < actor->y + actor->cy + actor->ch - 1 )
    {
        return true;
    }
    return false;
}

bool isActorCollision( Actor *actor1, Actor *actor2 )
{
    if( getActorsDistance( actor1, actor2 ) > TILE_SIZE * 1.41 )
        return false;
    else if( actor2->alive && ( isCollidedVertexOnActor( actor1->x + actor1->cx,                    actor1->y + actor1->cy,                     actor2 ) ||     // lewy gorny wierzcholek 
                                isCollidedVertexOnActor( actor1->x + actor1->cx + actor1->cw - 1,   actor1->y + actor1->cy,                     actor2 ) ||     // prawy gorny wierzcholek
                                isCollidedVertexOnActor( actor1->x + actor1->cx,                    actor1->y + actor1->cy + actor1->ch - 1,    actor2 ) ||     // lewy dolny wierzcholek
                                isCollidedVertexOnActor( actor1->x + actor1->cx + actor1->cw - 1,   actor1->y + actor1->cy + actor1->ch - 1,    actor2 ) ) )    // prawy dolny wierzcholek
    {
        return true;
    }
    return false; 
}
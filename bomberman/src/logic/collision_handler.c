#include "../../headers/logic.h"

#include "../../headers/sprite_properties.h"
#include "../../headers/level_tile_matrix_tools.h"
#include <stdio.h>

bool isOutOfBounds( Actor *actor, LevelMap *level_map, enum Direction *cdir, float cx, float cy, float cw, float ch )
{
    bool outOfBounds = false;

    if( actor->y + cy + ch > level_map->rows * TILE_SIZE )
    {
        outOfBounds = true;
        *cdir = DOWN;
    }
    else if( actor->y + cy < 0 )
    {
        outOfBounds = true;
        *cdir = UP;
    }
    else if( actor->x + cx < 0 )
    {
        outOfBounds = true;
        *cdir = LEFT;
    }
    else if( actor->x + cx + cw > level_map->collumns * TILE_SIZE )
    {
        outOfBounds = true;
        *cdir = RIGHT;
    }

    return outOfBounds;
}

void handleOutOfBounds( Actor *actor, LevelMap *level_map, enum Direction cdir, float cx, float cy, float cw, float ch )
{
    switch ( cdir )
    {
        case DOWN:
            actor -> y = level_map->rows * TILE_SIZE - cy - ch;
            break;
        case UP:
            actor -> y = -cy;
            break;
        case LEFT:
            actor -> x = -cx;
            break;
        case RIGHT:
            actor -> x = level_map->collumns * TILE_SIZE - cx - cw;
            break;
    }
}

bool isCollidedVertex( LevelMap *level_map, float vertex_x, float vertex_y )
{
    if( getTileContent( level_map->tile_matrix, tileFromPixel( vertex_x ), tileFromPixel( vertex_y ) ) > 0 )
        return true;
    return false;
}

bool isTerrainCollisionX( Actor *actor, LevelMap *level_map, enum Direction *cdir, float cx, float cy, float cw, float ch )
{
    bool terrainCollision = false;

    if( isCollidedVertex( level_map, actor->x + cx, actor->y + cy          ) ||        // lewy gorny wierzcholek
        isCollidedVertex( level_map, actor->x + cx, actor->y + cy + ch - 1 ) )         // lewy dolny wierzcholek
    {
        terrainCollision = true;
        *cdir = LEFT;
    }
    else if( isCollidedVertex( level_map, actor->x + cx + cw - 1,  actor->y + cy          ) ||   // prawy gorny wierzcholek
             isCollidedVertex( level_map, actor->x + cx + cw - 1,  actor->y + cy + ch - 1 ) )    // prawy dolny wierzcholek
    {
        terrainCollision = true;
        *cdir = RIGHT;
    }

    return terrainCollision;
}

bool isTerrainCollisionY( Actor *actor, LevelMap *level_map, enum Direction *cdir, float cx, float cy, float cw, float ch )
{
    bool terrainCollision = false;

    if( isCollidedVertex( level_map, actor->x + cx,           actor->y + cy + ch - 1 ) ||   // lewy dolny wierzcholek
        isCollidedVertex( level_map, actor->x + cx + cw - 1,  actor->y + cy + ch - 1 ) )    // prawy dolny wierzcholek
    {
        terrainCollision = true;
        *cdir = DOWN;
    }
    else if( isCollidedVertex( level_map, actor->x + cx,           actor->y + cy ) ||       // lewy gorny wierzcholek
             isCollidedVertex( level_map, actor->x + cx + cw - 1,  actor->y + cy ) )        // prawy gorny wierzcholek
    {
        terrainCollision = true;
        *cdir = UP;
    }

    return terrainCollision;
}

void handleTerrainCollision(Actor *actor, enum Direction cdir, float cx, float cy, float cw, float ch )
{
    int head_coord;
    switch( cdir )
    {
        case DOWN:
            head_coord = actor->y + cy + ch - 1;
            actor -> y = pixelFromTile( tileFromPixel( head_coord ) - 1 );
            break;
        case UP:
            head_coord = actor->y + cy;
            actor -> y = pixelFromTile( tileFromPixel( head_coord ) + 1 ) - cy;
            break;
        case LEFT:
            head_coord = actor->x + cx;
            actor -> x = pixelFromTile( tileFromPixel( head_coord ) + 1 ) - cx;
            break;
        case RIGHT:
            head_coord = actor->x + cx + cw - 1;
            actor -> x = pixelFromTile( tileFromPixel( head_coord ) - 1 ) + cx;
            break;
    }
}

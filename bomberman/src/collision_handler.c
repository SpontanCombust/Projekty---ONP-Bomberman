#include "../headers/logic_handlers.h"
#include "../headers/level_utilities.h"

bool isOutOfBounds( Actor *actor, int screen_w, int screen_h, enum Direction *cdir, int cx, int cy, int cw, int ch )
{
    bool outOfBounds = false;

    if( actor->y + cy + ch > screen_h )
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
    else if( actor->x + cx + cw > screen_w )
    {
        outOfBounds = true;
        *cdir = RIGHT;
    }

    return outOfBounds;
}

void handleOutOfBounds( Actor *actor, int screen_w, int screen_h, enum Direction cdir, int cx, int cy, int cw, int ch )
{
    switch ( cdir )
    {
        case DOWN:
            actor -> y = screen_h - cy - ch;
            break;
        case UP:
            actor -> y = -cy;
            break;
        case LEFT:
            actor -> x = -cx;
            break;
        case RIGHT:
            actor -> x = screen_w - cx - cw;
            break;
    }
}

bool isCollidedVertex( int vertex_x, int vertex_y, int **map )
{
    if( map[ tileFromPixel( vertex_y ) ][ tileFromPixel( vertex_x ) ] != 0 )
        return true;
    return false;
}

bool isTerrainCollisionX( Actor *actor, int **map, enum Direction *cdir, int cx, int cy, int cw, int ch )
{
    bool terrainCollision = false;

    if( isCollidedVertex( actor->x + cx, actor->y + cy,          map ) ||        // lewy gorny wierzcholek
        isCollidedVertex( actor->x + cx, actor->y + cy + ch - 1, map ) )         // lewy dolny wierzcholek
    {
        terrainCollision = true;
        *cdir = LEFT;
    }
    else if( isCollidedVertex( actor->x + cx + cw - 1,  actor->y + cy,          map ) ||   // prawy gorny wierzcholek
             isCollidedVertex( actor->x + cx + cw - 1,  actor->y + cy + ch - 1, map ) )    // prawy dolny wierzcholek
    {
        terrainCollision = true;
        *cdir = RIGHT;
    }

    return terrainCollision;
}

bool isTerrainCollisionY( Actor *actor, int **map, enum Direction *cdir, int cx, int cy, int cw, int ch )
{
    bool terrainCollision = false;

    if( isCollidedVertex( actor->x + cx,           actor->y + cy + ch - 1, map ) ||   // lewy dolny wierzcholek
        isCollidedVertex( actor->x + cx + cw - 1,  actor->y + cy + ch - 1, map ) )    // prawy dolny wierzcholek
    {
        terrainCollision = true;
        *cdir = DOWN;
    }
    else if( isCollidedVertex( actor->x + cx,           actor->y + cy, map ) ||       // lewy gorny wierzcholek
             isCollidedVertex( actor->x + cx + cw - 1,  actor->y + cy, map ) )        // prawy gorny wierzcholek
    {
        terrainCollision = true;
        *cdir = UP;
    }

    return terrainCollision;
}

void handleTerrainCollision(Actor *actor, int **map, enum Direction cdir, int cx, int cy, int cw, int ch)
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

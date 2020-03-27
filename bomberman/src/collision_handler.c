#include "../headers/logic_handlers.h"
#include "../headers/level_utilities.h"

bool isOutOfBounds( Entity *player, enum Direction *cdir, int screen_w, int screen_h, int cx, int cy, int cw, int ch )
{
    bool outOfBounds = false;

    if( player->y + cy + ch > screen_h )
    {
        outOfBounds = true;
        *cdir = DOWN;
    }
    else if( player->y + cy < 0 )
    {
        outOfBounds = true;
        *cdir = UP;
    }
    else if( player->x + cx < 0 )
    {
        outOfBounds = true;
        *cdir = LEFT;
    }
    else if( player->x + cx + cw > screen_w )
    {
        outOfBounds = true;
        *cdir = RIGHT;
    }

    return outOfBounds;
}

void handleOutOfBounds( Entity *player, enum Direction cdir, int screen_w, int screen_h, int cx, int cy, int cw, int ch )
{
    switch ( cdir )
    {
        case DOWN:
            player -> y = screen_h - cy - ch;
            break;
        case UP:
            player -> y = -cy;
            break;
        case LEFT:
            player -> x = -cx;
            break;
        case RIGHT:
            player -> x = screen_w - cx - cw;
            break;
    }
}

bool isCollidedVertex( int vertex_x, int vertex_y, int **map )
{
    if( map[ tileFromPixel( vertex_y ) ][ tileFromPixel( vertex_x ) ] != 0 )
        return true;
    return false;
}

bool isTerrainCollisionX( Entity *player, enum Direction *cdir, int **map, int cx, int cy, int cw, int ch )
{
    bool terrainCollision = false;

    if( isCollidedVertex( player->x + cx, player->y + cy,          map ) ||        // lewy gorny wierzcholek
        isCollidedVertex( player->x + cx, player->y + cy + ch - 1, map ) )         // lewy dolny wierzcholek
    {
        terrainCollision = true;
        *cdir = LEFT;
    }
    else if( isCollidedVertex( player->x + cx + cw - 1,  player->y + cy,          map ) ||   // prawy gorny wierzcholek
             isCollidedVertex( player->x + cx + cw - 1,  player->y + cy + ch - 1, map ) )    // prawy dolny wierzcholek
    {
        terrainCollision = true;
        *cdir = RIGHT;
    }

    return terrainCollision;
}

bool isTerrainCollisionY( Entity *player, enum Direction *cdir, int **map, int cx, int cy, int cw, int ch )
{
    bool terrainCollision = false;

    if( isCollidedVertex( player->x + cx,           player->y + cy + ch - 1, map ) ||   // lewy dolny wierzcholek
        isCollidedVertex( player->x + cx + cw - 1,  player->y + cy + ch - 1, map ) )    // prawy dolny wierzcholek
    {
        terrainCollision = true;
        *cdir = DOWN;
    }
    else if( isCollidedVertex( player->x + cx,           player->y + cy, map ) ||       // lewy gorny wierzcholek
             isCollidedVertex( player->x + cx + cw - 1,  player->y + cy, map ) )        // prawy gorny wierzcholek
    {
        terrainCollision = true;
        *cdir = UP;
    }

    return terrainCollision;
}

void handleTerrainCollision(Entity *player, enum Direction cdir, int **map, int cx, int cy, int cw, int ch)
{
    int head_coord;
    switch( cdir )
    {
        case DOWN:
            head_coord = player->y + cy + ch - 1;
            player -> y = pixelFromTile( tileFromPixel( head_coord ) - 1 );
            break;
        case UP:
            head_coord = player->y + cy;
            player -> y = pixelFromTile( tileFromPixel( head_coord ) + 1 ) - cy;
            break;
        case LEFT:
            head_coord = player->x + cx;
            player -> x = pixelFromTile( tileFromPixel( head_coord ) + 1 ) - cx;
            break;
        case RIGHT:
            head_coord = player->x + cx + cw - 1;
            player -> x = pixelFromTile( tileFromPixel( head_coord ) - 1 ) + cx;
            break;
    }
}

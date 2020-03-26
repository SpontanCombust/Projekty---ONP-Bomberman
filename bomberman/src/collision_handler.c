#include "../headers/logic_handlers.h"

bool isOutOfBounds(Entity *player, int screen_w, int screen_h, int cx, int cy, int cw, int ch)
{
    if( player->x + cx < 0 || player->y + cy < 0 || player->x + cx + cw > screen_w || player->y +cy +ch > screen_h )
        return true;
    return false;
}

bool isCollidedVertex(int vertex_x, int vertex_y, int **map)
{
    if( map[ tileFromPixel( vertex_y ) ][ tileFromPixel( vertex_x ) ] != 0 )
        return true;
    return false;
}

bool isTerrainCollision(Entity *player, int **map, int cx, int cy, int cw, int ch)
{
    if( isCollidedVertex( player->x + cx, player->y + cy, map ) ||              // lewy gorny wierzcholek
        isCollidedVertex( player->x + cx, player->y + cy + ch, map ) ||         // lewy dolny wierzcholek
        isCollidedVertex( player->x + cx + cw, player->y + cy, map ) ||         // prawy gorny wierzcholek
        isCollidedVertex( player->x + cx + cw, player->y + cy + ch, map ) )     // prawy dolny wierzcholek
    {
        return true;
    }

    return false;
}

bool isCollision(Entity *player, int **map, int screen_w, int screen_h, int cx, int cy, int cw, int ch)
{
    if( isOutOfBounds( player, screen_w, screen_h, cx, cy, cw, ch ) ||
        isTerrainCollision( player, map, cx, cy, cw, ch ) )
    {
        return true;
    }

    return false;
}
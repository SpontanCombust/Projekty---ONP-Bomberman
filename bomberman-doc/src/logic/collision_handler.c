/** @file collision_handler.c
 * 
 * @brief Plik zawiera funkcje detekcji i obsługi kolizji.
 * 
 * Plik zawiera funkcje wykrywania kolizji avatara gracza z otoczeniem oraz z innymi aktorami. \n
 * Zawiera też funkcje obsługi kolizji z otoczeniem.
 * 
 * @author  Przemysław Cedro
 * @date    2020.05.24
*/

#include "../../headers/logic.h"

#include "../../headers/sprite_properties.h"
#include "../../headers/level_tile_matrix_tools.h"
#include <stdio.h>
#include <math.h>

/** @brief Wykrywa, czy aktor jest poza obrębem mapy
 * 
 * Na podstawie wymiarów przekazanej mapy ocenia, czy aktor znajduje się poza zakresem koordynatów \n
 * wewnątrz mapy opierając się o prostokąt kolizji aktora. Jeśli wyjście poza mapę zostanie wykryte, \n
 * poza potwierdzeniem, zmiennej cdir zostanie nadana wartość odpowiadająca, z której strony względem \n
 * aktora wykryte zostało to zdarzenie.
 *
 * @param actor     wskaźnik na aktora
 * @param level_map wskaźnik na mapę poziomu
 * @param cdir      wskaźnik na zmienną kierunku, w którym ewentualnie zostanie wykryta kolizja
 * 
 * @return true jeśli aktor wyszedł poza mapę, false w przeciwnym wypadku
*/
bool isOutOfBounds( Actor *actor, LevelMap *level_map, Direction *cdir )
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

/** @brief Koryguje pozycję aktora po wyjściu za obszar mapy
 * 
 * Na podstawie wymiarów mapy i kierunku, w którym nastąpiło przekroczenie mapy, ustawia postać \n
 * gracza tak by jego prostokąt kolizji stykał się z granicą mapy po jej wewnętrznej stronie. \n
 * Dzięki danemu kierunkowi możlwie jest szybkie ocenienie od strony której ściany mapy nastąpiło \n
 * przejście i przenieść gracza z powrotem tuż przed tę ścianę.
 *
 * @param actor     wskaźnik na aktora
 * @param level_map wskaźnik na mapę poziomu
 * @param cdir      kierunek, w którym nastąpiło przekroczenie mapy
*/
void handleOutOfBounds( Actor *actor, LevelMap *level_map, Direction cdir )
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

/** @brief Wykrywa, czy dany wierzchołek prostokąta kolizji koliduje z elementami mapy
 * 
 * Wykrywa, czy dany punkt znajduje się w tym samym miejscu, gdzie jest również element mapy uznawany \n
 * jako mogący fizycznie kolidować z aktorem. Do tych elementów zaliczają się twarde i kruche bloki na mapie.
 *
 * @param vertex_x  współrzędna pikselowa punktu w osi x
 * @param vertex_y  współrzędna pikselowa punktu w osi y
 * @param level_map wskaźnik na mapę poziomu
 * 
 * @return true jeśli wierzchołek koliduje z elementami mapy, false w przeciwnym wypadku
*/
static bool isCollidedVertexOnTerrain( float vertex_x, float vertex_y, LevelMap *level_map )
{
    if( getTileContent( level_map->tile_matrix, tileFromPixel( vertex_x ), tileFromPixel( vertex_y ) ) > 0 )
        return true;
    return false;
}

/** @brief Wykrywa, czy aktor wchodzi w kolizję z elementami mapy w osi X
 * 
 * Sprawdza każdy wierzchołek prostokąta kolizji aktora i ocenia w ten sposób, czy wchodzi on w kolizję \n
 * z elementami mapy w osi X. Nadaje następnie odpowiednią wartosć zmiennej cdir odpowiadającą kierunkowi, \n
 * w którym zaistniała kolizja. 
 *
 * @param actor     wskaźnik na aktora
 * @param level_map wskaźnik na mapę poziomu
 * @param cdir      wskaźnik na zmienną kierunku, w którym ewentualnie zostanie wykryta kolizja
 * 
 * @return true jeśli aktor wszedł w kolizję z elementem mapy, false w przeciwnym wypadku
*/
bool isTerrainCollisionX( Actor *actor, LevelMap *level_map, Direction *cdir )
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

/** @brief Wykrywa, czy aktor wchodzi w kolizję z elementami mapy w osi Y
 * 
 * Sprawdza każdy wierzchołek prostokąta kolizji aktora i ocenia w ten sposób, czy wchodzi on w kolizję \n
 * z elementami mapy w osi Y. Nadaje następnie odpowiednią wartosć zmiennej cdir odpowiadającą kierunkowi, \n
 * w którym zaistniała kolizja. 
 *
 * @param actor     wskaźnik na aktora
 * @param level_map wskaźnik na mapę poziomu
 * @param cdir      wskaźnik na zmienną kierunku, w którym ewentualnie zostanie wykryta kolizja
 * 
 * @return true jeśli aktor wszedł w kolizję z elementem mapy, false w przeciwnym wypadku
*/
bool isTerrainCollisionY( Actor *actor, LevelMap *level_map, Direction *cdir )
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

/** @brief Koryguje pozycję aktora po kolizji z elementami mapy
 * 
 * Na podstawie kierunku, w którym nastąpiła kolizja, ustawia postać gracza tak by jego prostokąt \n
 * kolizji stykał się z ze ścianą najbliższego poprzedniego elementu mapy w zależności od kierunku \n
 * w którym nastąpiła kolizja np. jeśli kierunek to góra ("UP") koryguje pozycję o jedno pole \n
 * na mapie w dół i przysuwa aktora do górnej krawędzi tak, by stykał się prostokątem kolizji \n
 * z elementem mapy, z którym wszedł w kolizję.
 *
 * @param actor     wskaźnik na aktora
 * @param cdir      kierunek, w którym nastąpiła kolizja
*/
void handleTerrainCollision( Actor *actor, Direction cdir )
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

/** @brief Podaje dokładny dystans jaki dzieli dwóch aktorów 
 * 
 * @param actor1 wskaźnik na pierwszego aktora
 * @param actor2 wskaźnik na drugiego aktora
 * 
 * @return dystans między aktorami
*/
static float getActorsDistance( Actor *actor1, Actor *actor2 )
{
    return sqrt( pow( actor1->x - actor2->x, 2 ) + pow( actor1->y - actor2->y, 2 ) );
}

/** @brief Wykrywa, czy dany wierzchołek prostokąta kolizji koliduje z aktorem
 * 
 * Wykrywa, czy dany punkt znajduje się w tym samym miejscu, gdzie jest również dany aktor, \n
 * a konkretnie obszar jego prostokąta kolizji.
 *
 * @param vertex_x  współrzędna pikselowa punktu w osi x
 * @param vertex_y  współrzędna pikselowa punktu w osi y
 * @param actor     wskaźnik na aktora
 * 
 * @return true jeśli wierzchołek koliduje z aktorem, false w przeciwnym wypadku
*/
static bool isCollidedVertexOnActor( float vertex_x, float vertex_y, Actor *actor )
{
    if( vertex_x > actor->x + actor->cx && vertex_x < actor->x + actor->cx + actor->cw - 1 &&
        vertex_y > actor->y + actor->cy && vertex_y < actor->y + actor->cy + actor->ch - 1 )
    {
        return true;
    }
    return false;
}

/** @brief Wykrywa, czy zaistaniała kolizja między dwoma aktorami
 * 
 * Jeśli wykryje, że aktorzy są dostatecznie blisko siebie (lewe górne wierzchołki są w odległości \n
 * mniejszej niż przekątna bitmapy) sprawdza każdy wierzchołek prostokąta kolizji pierwszego aktora \n
 * i jeśli któryś z tych punktów natknie się na prostokąt kolziji drugiego aktora, wykryta zostanie \n
 * kolizja między nimi.
 *
 * @param actor1 wskaźnik na pierwszego aktora
 * @param actor2 wskaźnik na drugiego aktora
 * 
 * @return true jeśli wykryto kolizję, false w przeciwynm wypadku
*/
bool isActorCollision( Actor *actor1, Actor *actor2 )
{
    if( getActorsDistance( actor1, actor2 ) > TILE_SIZE * 1.41 ) // sqrt(2) ~= 1.41
        return false;
    else if( isActorAlive( actor2 ) && 
            ( isCollidedVertexOnActor( actor1->x + actor1->cx,                    actor1->y + actor1->cy,                     actor2 ) ||   // lewy gorny wierzcholek 
              isCollidedVertexOnActor( actor1->x + actor1->cx + actor1->cw - 1,   actor1->y + actor1->cy,                     actor2 ) ||   // prawy gorny wierzcholek
              isCollidedVertexOnActor( actor1->x + actor1->cx,                    actor1->y + actor1->cy + actor1->ch - 1,    actor2 ) ||   // lewy dolny wierzcholek
              isCollidedVertexOnActor( actor1->x + actor1->cx + actor1->cw - 1,   actor1->y + actor1->cy + actor1->ch - 1,    actor2 )      // prawy dolny wierzcholek
            ) )    
    {
        return true;
    }
    return false; 
}
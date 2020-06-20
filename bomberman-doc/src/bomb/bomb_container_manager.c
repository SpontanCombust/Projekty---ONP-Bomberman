/** @file bomb_container_manager.c
 * 
 * @brief Plik zawiera funkcje obsługi tablicy wksaźników na bomby
 * 
 * Zawiera funkcje sprawdzania pola mapy w poszukiwaniu innej, już istniejącej bomby, sprawdzania, \n
 * czy tablica jest pusta i dodawania bomb do tej tablicy.
 * 
 * @author  Przemysław Cedro
 * @date    2020.05.25
*/


#include "../../headers/bomb.h"

#include "../../headers/_game_rules.h"

/** @brief Sprawdza, czy tablica bomb jest pusta
 * 
 * Iteruje po tablicy wskaźników na zmienne typu Bomb o stałej wielkości określonej przez BOMB_BUDGET \n
 * w _game_rules.h i sprawdza, czy wszystkie jej wskaźniki są NULLowe  
 *
 * @param container tablica wskaźników na bomby
 * 
 * @return true jeśli tablica jest pusta, false w przeciwnym wypadku
*/
bool isBombContainerEmpty( Bomb * container[] )
{
    for (int i = 0; i < BOMB_BUDGET; i++)
        if( container[i] != NULL )
            return false;

    return true;
}

/** @brief Sprawdza, czy dane pole mapy jest już zajęte przez inną bombę
 * 
 * Iteruje po tablicy wskaźników na bomby i sprawdza, czy któraś z bomb już nie jest istnieje \n
 * na polu, na którym podana bomba ma być postawiona.
 *
 * @param container tablica wskaźników na bomby
 * @param bomb      wskaźnik na badaną bombę
 * 
 * @return true jeśli pole mapy jest już zajęte przez inną bombę, false w przeciwnym wypadku 
*/
static bool isTileTaken( Bomb * container[], Bomb *bomb )
{
    for (int i = 0; i < BOMB_BUDGET; i++)
    {
        if( container[i] != NULL  && container[i]->tile_x == bomb->tile_x && container[i]->tile_y == bomb->tile_y)
            return true;
    }

    return false;
}

/** @brief Dodaje bombę do tablicy bomb
 * 
 * Jeżeli pole mapy, na którym bomba ma być postawiona nie jest już zajęte przez inną bombę, ustawia \n
 * pierwszy napotkany NULLowy wskaźnik tablicy na wskaźnik na podaną bombę. W przeciwnym wypadku \n
 * zwalnia pamięć z podanej bomby.
 *
 * @param bomb      podwójny wskaźnik na bombę
 * @param container tablica wskaźników na bomby
*/
void addBombToContainer( Bomb **bomb, Bomb * container[] )
{
    bool valid = false;
    if( !isTileTaken( container, *bomb ) )
    {
        for (int i = 0; i < BOMB_BUDGET; i++)
        {
            if( container[i] == NULL )
            {
                valid = true;
                container[i] = *bomb;
                break;
            }
        }
    }
    
    if( !valid )
        destroyBomb( bomb );
}
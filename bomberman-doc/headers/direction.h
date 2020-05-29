/** @file direction.h
 * 
 * @brief Plik zawiera definicję typu Kierunku głównie używanego przez Aktorów
 * 
 * @author  Przemysław Cedro
 * @date    2020.05.29
*/


#ifndef DIRECTION_H
#define DIRECTION_H

/** Enum kierunku, głównie używany do ustalenia w którą stronę powinien być skierowany Aktor. Dostępne kierunki to DOWN, UP, LEFT i RIGHT. */
typedef enum E_Direction { DOWN, UP, LEFT, RIGHT } Direction;

#endif
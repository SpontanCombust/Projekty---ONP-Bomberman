/** @file sprite_properties.h
 * 
 * @brief Plik zawiera stałe dotyczące wielkości pól na mapie i prostokątów kolizji Aktorów
 * 
 * @author  Przemysław Cedro
 * @date    2020.05.29
*/


#ifndef BOUNDING_BOXES_H
#define BOUNDING_BOXES_H

#define TILE_SIZE 32

// nalezy ustawiac koordynaty dokladnie, by uniknac naruszenia ochrony pamieci przy sprawdzaniu kolizji, bo moze np. sprawdzac pole, ktore nie istnieje
#define CBX_PLAYER 7    /** Punkt początkowy prostokąta kolizji gracza w osi X */
#define CBY_PLAYER 11   /** Punkt początkowy prostokąta kolizji gracza w osi Y */
#define CBW_PLAYER 18   /** Szerokość prostokąta kolizji gracza */
#define CBH_PLAYER 21   /** Wysokość prostokąta kolizji gracza */

#define CBX_ENEMY1 3    /** Punkt początkowy prostokąta kolizji wroga w osi X */
#define CBY_ENEMY1 0    /** Punkt początkowy prostokąta kolizji wroga w osi Y */
#define CBW_ENEMY1 26   /** Szerokość prostokąta kolizji wroga */
#define CBH_ENEMY1 32   /** Wysokość prostokąta kolizji wroga */

#endif
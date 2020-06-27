/** @file rpn_app.hpp
 * 
 * @brief Plik zawiera stałe i deklaracje funkcji obsługi programu nCurses demonstrującego działanie ONP
 * 
 * @author  Przemysław Cedro
 * @date    2020.06.26
*/


#ifndef __RPN_GUI_APP
#define __RPN_GUI_APP

#include <ncurses.h>

#define MAIN_WIN_H      30 /**< Wysokość głównego okna w programie nCurses */
#define MAIN_WIN_W      100 /**< Szerokość głównego okna w programie nCurses */

#define SUB_WIN_H       20 /**< Wysokość podokna w programie nCurses */
#define SUB_WIN_W       60  /**< Szerokość podokna w programie nCurses */
#define SUB_WIN_Y       6 /**< Pozycja Y podokna w programie nCurses */
#define SUB_WIN_X       4 /**< Pozycja X podokna w programie nCurses */

#define STACK_BASE_H    4 /**< Wysokość podstawki wizualizacji stosu */
#define STACK_BASE_W    30 /**< Szerokość podstawki wizualizacji stosu */
#define STACK_ELEMENT_H 3 /**< Wysokość elementów stosu w wizualizacji stosu */
#define STACK_ELEMENT_W 20 /**< Szerokość elementów stosu w wizualizacji stosu */
#define STACK_Y         24 /**< Pozycja Y lewego górnego rogu podstawki stosu w wizualizacji stosu */
#define STACK_X         65 /**< Pozycja X lewego górnego rogu podstawki stosu w wizualizacji stosu */

/** Głowna funkcja inicjująca potrzebne moduły biblioteki nCurses */
void RunRPNDemo();

#endif
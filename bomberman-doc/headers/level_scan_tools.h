/** @file level_scan_tools.h
 * 
 * @brief Plik zawiera deklarację funkcji skanowania katalogu poziomów w celu szukania poziomów do wczytania
 * 
 * @author  Przemysław Cedro
 * @date    2020.05.29
*/


#ifndef LEVEL_SCAN_TOOLS_H
#define LEVEL_SCAN_TOOLS_H

#include "_game_rules.h"


// =========================== level_scanner.c ===========================

/** @brief Skanuje w poszukiwaniu katalogów poziomów */
void scanForLevels( char levels[MAX_LOADED_LEVELS][10], int *level_num );

#endif
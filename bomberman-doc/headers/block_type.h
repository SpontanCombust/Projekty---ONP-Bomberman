/** @file block_type.h
 * 
 * @brief Plik zawiera enum typu bloków na mapie
 * 
 * @author  Przemysław Cedro
 * @date    2020.05.29
*/


#ifndef BLOCK_TYPE_H
#define BLOCK_TYPE_H

/** Enum informujące o typie bloku znajdującego się na danym polu mapy poziomu. Dostępne bloki to EMPTY_BLOCK, SOLID_BLOCK i BRITTLE_BLOCK. */
typedef enum E_BlockTypes { EMPTY_BLOCK, SOLID_BLOCK, BRITTLE_BLOCK } BlockTypes; // kolejnosc jest wazna

#endif
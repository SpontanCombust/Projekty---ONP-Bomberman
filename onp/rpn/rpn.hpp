/** @file rpn.hpp
 * 
 * @brief Plik zawiera stałe i deklaracje funckji obsługujących ciąg elementów ONP oraz sprawdzających wydajność działania
 * 
 * @author  Przemysław Cedro
 * @date    2020.06.26
*/


#ifndef __RPN_HPP
#define __RPN_HPP

#include "../stack/stack.hpp"
#include <vector>
#include <string>
#include <ncurses.h>


// ----------- rpn_parser.cpp ------------

/** Stwierdza, czy dany element ciągu ONP jest poprawny */
bool isRPNElementValid( std::string rpnElement );
/** Sprawdza, czy kontener elementów ciągu ONP zawiera same poprawne elementy */
bool isRPNVectorValid( std::vector< std::string > rpnVector );
/** Sprawdza, czy dany element ciągu ONP to operator matematyczny */
bool isBasicMathOperator( std::string rpnElement );
/** Przetwarza łańcuch znaków ciągu liczb w ONP na kontener pojedynczych elementów  */
std::vector< std::string > parseRawRPNString( std::string rawRPNString, std::string delim );


// ----------- rpn_counter.cpp ------------

/** Obsługuje dany wejściowy element ciągu ONP i odpowiednio modyfikuje dany stos */
int handleRPNElementOnStack( std::string rpnElement, CStack &stack, bool logActions = false, WINDOW *logWin = NULL, int winY = 0, int winX = 0 );
/** Zwraca wynik danego działania w formie ONP  */
float getRPNResult( std::string rawRPNString, bool *success );


// --------- rpn_performance.cpp ----------

/** Przeprowadza serię testów wydajności wykonywania działań przez ONP */
void runRPNPerfTests( unsigned int numberWeight, unsigned int mathOperatorWeight, bool writeToFiles = true, std::string fileNamePrefix = "" );

#define RPN_DEFAULT_SAMPLE_SIZE             50 /**< Domyślna ilość próbek brana z pojedynczej serii testów */
#define RPN_DEFAULT_NUMBER_QUANTITY         10000 /**< Domyślna ilość liczb losowanych w pojedynczym teście */
#define RPN_DEFAULT_NUMBER_WEIGHT           50 /**< Domyślna waga losowania liczby w czasie testu */
#define RPN_DEFAULT_MATH_OPERATOR_WEIGHT    50 /**< Domyślna waga losowania operatora matematycznego w czasie testu */
#define RPN_DEFAULT_VALUE_MIN               -100 /**< Domyślna minimalna wartość losowanej liczby w czasie testu */
#define RPN_DEFAULT_VALUE_MAX               100 /**< Domyślna maksymalna wartość losowanej liczby w czasie testu */

#define RPN_NUMBER_QUANTITY_0 100 /**< Początkowa ilość losowanych liczb w serii testów */
#define RPN_NUMBER_QUANTITY_1 1000000 /**< Końcowa ilość losowanych liczb w serii testów */

#define RPN_VAL_MIN_0      0 /**< Początkowa wartość minimalnej wartości losowanych liczb w czasie serii testów */
#define RPN_VAL_MIN_1      100000000 /**< Końcowa wartość minimalnej wartości losowanych liczb w czasie serii testów */
#define RPN_VAL_MAX_0      100 /**< Początkowa wartość maksymalnej wartości losowanych liczb w czasie serii testów */
#define RPN_VAL_MAX_1      99999900 /**< Końcowa wartość maksymalnej wartości losowanych liczb w czasie serii testów */

#endif

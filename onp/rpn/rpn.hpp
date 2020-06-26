#ifndef __RPN_HPP
#define __RPN_HPP

#include "../stack/stack.hpp"
#include <vector>
#include <string>
#include <ncurses.h>


// ----------- rpn_parser.cpp ------------

bool isRPNElementValid( std::string rpnElement );
bool isRPNVectorValid( std::vector< std::string > rpnVector );
bool isBasicMathOperator( std::string rpnElement );
std::vector< std::string > parseRawRPNString( std::string rawRPNString, std::string delim );


// ----------- rpn_counter.cpp ------------

int handleRPNElementOnStack( std::string rpnElement, CStack &stack, bool logActions = false, WINDOW *logWin = NULL, int winY = 0, int winX = 0 );
float getRPNResult( std::string rawRPNString, bool *success );


// --------- rpn_performance.cpp ----------

void runRPNPerfTests( unsigned int numberWeight, unsigned int mathOperatorWeight, bool writeToFiles = true, std::string fileNamePrefix = "" );

#define RPN_DEFAULT_SAMPLE_SIZE             50
#define RPN_DEFAULT_NUMBER_QUANTITY         10000
#define RPN_DEFAULT_NUMBER_WEIGHT           50
#define RPN_DEFAULT_MATH_OPERATOR_WEIGHT    50
#define RPN_DEFAULT_VALUE_MIN               -100
#define RPN_DEFAULT_VALUE_MAX               100

#define RPN_NUMBER_QUANTITY_0 100
#define RPN_NUMBER_QUANTITY_1 1000000

#define RPN_VAL_MIN_0     -100
#define RPN_VAL_MIN_1     -100000000
#define RPN_VAL_MAX_0      100
#define RPN_VAL_MAX_1      100000000

#endif

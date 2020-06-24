#ifndef __RPN_HPP
#define __RPN_HPP

#include "../stack/stack.hpp"
#include <vector>
#include <string>
#include <ncurses.h>

std::vector< std::string > parseRawRPNString( std::string rawRPNString, std::string delim );
bool isRPNElementValid( std::string rpnElement );
bool isRPNVectorValid( std::vector< std::string > rpnVector );
bool isBasicMathOperator( std::string rpnElement );
int handleRPNElementOnStack( std::string rpnElement, CStack &stack, WINDOW *logWin = NULL, int winY = 0, int winX = 0 );
float getRPNResult( std::string rawRPNString, bool *success );

#endif

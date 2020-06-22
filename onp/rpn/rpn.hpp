#ifndef __RPN_HPP
#define __RPN_HPP

#include "../stack/stack.hpp"
#include <vector>
#include <string>

std::vector< std::string > parseRawRPNString( std::string rawRPNString, std::string delim );
bool isRPNVectorValid( std::vector< std::string > rpnVector );
bool isBasicMathOperator( std::string rpnElement );
int handleRPNElementOnStack( std::string rpnElement, CStack *stack );
float getRPNResult( std::string rawRPNString, bool *success );

#endif

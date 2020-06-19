#ifndef __ONP_HPP
#define __ONP_HPP

#include "../stack/stack.hpp"
#include <vector>
#include <string>

std::vector< std::string > parseRawRPNString( std::string rawRPNString, std::string delim );
bool isRPNVectorValid( std::vector< std::string > rpnVector );
bool isBasicMathOperator( std::string rpnElement );
float getRPNResult( std::string rawRPNString );

#endif

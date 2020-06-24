#include "rpn.hpp"
#include <iostream>

std::vector< std::string > parseRawRPNString( std::string rawRPNString, std::string delim )
{
    std::vector< std::string > rpnElements;
    std::string searchedString;
    std::string token;
    size_t pos;

    searchedString = rawRPNString;
    pos = 0;
    while( (pos = searchedString.find( delim )) != std::string::npos )
    {
        token = searchedString.substr( 0, pos );
        rpnElements.push_back( token );
        searchedString.erase( 0, pos + delim.length() );
    }
    rpnElements.push_back( searchedString );

    return rpnElements;
}



bool isNumChar( char c )
{
    return c >= '0' && c <= '9';
}

bool isBasicMathOperator( std::string rpnElement )
{
    if( rpnElement.size() != 1 )
        return false;
    else if( rpnElement == "+" || rpnElement == "-" || rpnElement == "*" || rpnElement == "/" || rpnElement == "=" )
        return true;
    
    return false;
}

bool isPointValid( std::string rpnElement )
{
    size_t pos = rpnElement.find( '.' );

    if( pos == std::string::npos )
        return true;
    else if( pos == 0 )
        return false;

    rpnElement.erase( 0, pos + 1 );
    pos = rpnElement.find( '.' );

    if( pos != std::string::npos )
        return false;

    return true;
}



bool isRPNElementValid( std::string rpnElement )
{
    if( isBasicMathOperator( rpnElement ) )
        return true;
    else if( rpnElement.empty() || !(rpnElement[0] == '-' || isNumChar( rpnElement[0] )) || !isPointValid( rpnElement ) )
        return false;

    if( rpnElement[0] == '-' )
        rpnElement.erase( 0 );
    
    for( char c : rpnElement )
    {
        if( !(isNumChar( c ) || c == '.') ) return false;
    }
    return true;
}

bool isRPNVectorValid( std::vector< std::string > rpnVector )
{
    for( std::string rpnElement : rpnVector )
    {
        if( !isRPNElementValid( rpnElement ) )
        {
            std::cout << "RPN element not valid: " << rpnElement << std::endl;
            return false;
        }
    }
    return true;
}
#include "rpn.hpp"
#include <iostream>

/**
 * @brief Przetwarza łańcuch znaków ciągu liczb w ONP na kontener pojedynczych elementów 
 * 
 * Bierze ciąg znaków składających się z liczb i operatorów oddzielonych separatorem, które razem
 * tworzą ciąg równania w Odwrotnej Notacji Polskiej, i przetwarza go na kontener pojedynczych elementów.
 * 
 * @param rawRPNString surowy ciąg znaków reprezentujący ciąg ONP
 * @param delim separator elementów ciągu
 * @return kontener pojedynczych elementów ciągu
 */
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


/**
 * @brief Sprawdza, czy dany znak to cyfra
 * 
 * @param c znak
 * @return true jeśli znak to cyfra
 * @return false jeśli znak to nie cyfra
 */
bool isNumChar( char c )
{
    return c >= '0' && c <= '9';
}

/**
 * @brief Sprawdza, czy dany element ciągu ONP to operator matematyczny
 * 
 * Sprawdza, czy dany ciąg znaków to kolejno +, -, *, / lub =.
 * 
 * @param rpnElement element ciągu ONP
 * @return true jeśli ciąg znaków to podstawowy operator matematyczny
 * @return false jeśli ciąg znaków to nie jest podstawowy operator matematyczny
 */
bool isBasicMathOperator( std::string rpnElement )
{
    if( rpnElement.size() != 1 )
        return false;
    else if( rpnElement == "+" || rpnElement == "-" || rpnElement == "*" || rpnElement == "/" || rpnElement == "=" )
        return true;
    
    return false;
}

/**
 * @brief Sprawdza, czy przecinek w elemencie ciągu ONP jest poprawny
 * 
 * Sprawdza, czy w danym elemencie ciągu ONP reprezentowanego przez string przecinek oddzielający
 * część całkowitą od części ułamkowej jest poprawny tj. czy nie jest go za dużo lub czy nie jest
 * w nieodpowiednim miejscu.
 * 
 * @param rpnElement element ciągu ONP
 * @return true jeśli element ciągu ma poprawny przecinek
 * @return false jeśli element ciągu nie ma poprawnego przecinka
 */
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


/**
 * @brief Stwierdza, czy dany element ciągu ONP jest poprawny
 * 
 * Sprawdza czy dany ciąg znaków, który reprezentuje element ciągu ONP jest poprawną liczbą
 * lub operatorem matematycznym.
 * 
 * @param rpnElement element ciągu ONP
 * @return true jeśli element jest poprawny
 * @return false jeśli element jest niepoprawny
 */
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

/**
 * @brief Sprawdza, czy kontener elementów ciągu ONP zawiera same poprawne elementy
 * 
 * @param rpnVector kontener elementów ciągu ONP
 * @return true jeśli kontener zawiera same poprawne elementy
 * @return false jeśli kontener zawiera niepoprawny element
 */
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
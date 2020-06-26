#include "rpn.hpp"
#include <iostream>
#include <sstream>

bool isMathOperationValid( float x1, float x2, std::string mathOperator )
{
    if( x2 == 0.f && mathOperator == "/" )
        return false;
    return true;
}

float getOperationResult( float x1, float x2, std::string mathOperator )
{
    float outcome = 0;
    if      ( mathOperator == "+" ) outcome = x1 + x2;
    else if ( mathOperator == "-" ) outcome = x1 - x2; 
    else if ( mathOperator == "*" ) outcome = x1 * x2; 
    else if ( mathOperator == "/" ) outcome = x1 / x2; 
    else {
        printf("Invalid operator!\n");
        return -1;
    }

    return outcome;
}

void log( std::string str, WINDOW *logWin, int winY, int winX )
{
    if( logWin == NULL )
        std::cout << str << std::endl;
    else
        mvwprintw( logWin, winY, winX, str.c_str() );
}

int handleRPNElementOnStack( std::string rpnElement, CStack &stack, bool logActions, WINDOW *logWin, int winY, int winX )
{
    std::ostringstream strStream;
    
    if( rpnElement == "=" )
    {
        float x;
        if( stack.pop( &x ) )
        {
            if(logActions) log( "Popped " + std::to_string(x) + " as the equation result.", logWin, winY, winX );
            return 0;
        }
        else
        {
            if(logActions) log( "Unable to pop element from stack. Probable cause: stack is empty.", logWin, winY, winX );
            return -1;
        }
    }
    else if( isBasicMathOperator( rpnElement ) )
    {
        float x1, x2;
        bool b1, b2;

        b2 = stack.pop( &x2 );
        if( !b2 )
        {
            if(logActions) log( "Unable to pop element from stack. Probable cause: stack is empty.", logWin, winY, winX );
            return -2;
        }

        if(logActions) log( "Popped " + std::to_string(x2) + " from stack.", logWin, winY, winX );

        b1 = stack.pop( &x1 );
        if( !b1 )
        {
            if(logActions) log( "Unable to pop element from stack. Probable cause: stack is empty. Reversing the previous pop operation!", logWin, winY, winX );
            stack.push( x2 );
            return -3;
        }

        if(logActions) log( "Popped " + std::to_string(x1) + " from stack.", logWin, winY + 1, winX );

        if( isMathOperationValid( x1, x2, rpnElement ) )
        {
            float result = getOperationResult( x1, x2, rpnElement );
            stack.push( result );

            if(logActions) log( "Pushed " + std::to_string(result) + " onto stack.", logWin, winY + 2, winX );
            return 0;
        }
        else
        {
            if(logActions) log( "Unable to perform math operation. Probable cause: division by zero.", logWin, winY, winX );            
            return -4;
        }
    }
    else
    {
        if( stack.push( stof( rpnElement ) ) )
        {
            if(logActions) log( "Pushed " + rpnElement + " onto stack.", logWin, winY, winX );
            return 0;
        }
        else
        {
            if(logActions) log( "Unable to push element onto stack. Probable cause: unknown.", logWin, winY, winX );
            return -5;
        }
    }

    return 0;
}


float getRPNResult( std::string rawRPNString, bool *success )
{
    CStack stack;
    std::vector< std::string > rpnVec;
    float result;

    *success = true;
    stack = CStack();
    rpnVec = parseRawRPNString( rawRPNString, " " );
    result = 0;

    if( isRPNVectorValid( rpnVec ) )
    {
        for( std::string rpnElement : rpnVec )
        {
            if( handleRPNElementOnStack( rpnElement, stack ) != 0 )
            {
                *success = false;
                break;
            }
        }

        stack.pop( &result );
    }
    else
    {
        std::cout << "RPN sequence not valid: " << rawRPNString << std::endl;
        *success = false;
    }
    
    return result;
}

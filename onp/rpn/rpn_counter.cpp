#include "rpn.hpp"
#include <iostream>

bool isMathOperationValid( float x1, float x2, std::string mathOperator )
{
    if( x2 == 0 && mathOperator == "/" )
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


int handleRPNElementOnStack( std::string rpnElement, CStack &stack, WINDOW *w, int y, int x )
{
    if( isBasicMathOperator( rpnElement ) )
    {
        float x1, x2;
        bool b1, b2;

        b2 = stack.pop( &x2 );
        if( !b2 )
        {
            if( w == NULL )
                std::cout << "Unable to pop element from stack. Probable cause: stack is empty." << std::endl;
            else
                mvwprintw( w, y, x, "Unable to pop element from stack. Probable cause: stack is empty." );

            return -1;
        }
        if( w == NULL )
            std::cout << "Popped " << x2 << " from stack." << std::endl;
        else
            mvwprintw( w, y, x, "Popped %f from stack.", x2 );

        b1 = stack.pop( &x1 );
        if( !b1 )
        {
            if( w == NULL )
                std::cout << "Unable to pop element from stack. Probable cause: stack is empty. Reversing the previous pop operation!" << std::endl;
            else
                mvwprintw( w, y, x, "Unable to pop element from stack. Probable cause: stack is empty. Reversing the previous pop operation!" );

            stack.push( x2 );
            return -2;
        }

        if( w == NULL )
            std::cout << "Popped " << x1 << " from stack." << std::endl;
        else
            mvwprintw( w, y, x, "Popped %f from stack.", x1 );


        if( isMathOperationValid( x1, x2, rpnElement ) )
        {
            float result = getOperationResult( x1, x2, rpnElement );
            stack.push( result );

            if( w == NULL )
                std::cout << "Pushed " << result << " onto stack." << std::endl;
            else
                mvwprintw( w, y, x, "Pushed %f onto stack.", result );

            return 0;
        }
        else
        {
            if( w == NULL)
                std::cout << "Unable to perform math operation. Probable cause: division by zero." << std::endl;
            else
                mvwprintw( w, y, x, "Unable to perform math operation. Probable cause: division by zero.", rpnElement.c_str() );
            
            return -3;
        }
    }
    else
    {
        if( stack.push( stof( rpnElement ) ) )
        {
            if( w == NULL )
                std::cout << "Pushed " << rpnElement << " onto stack." << std::endl;
            else
                mvwprintw( w, y, x, "Pushed %s onto stack.", rpnElement.c_str() );

            return 0;
        }
        else
        {
            if( w == NULL )
                std::cout << "Unable to push element onto stack. Probable cause: unknown." << std::endl;
            else
                mvwprintw( w, y, x, "Unable to push element onto stack. Probable cause: unknown." );

            return -4;
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

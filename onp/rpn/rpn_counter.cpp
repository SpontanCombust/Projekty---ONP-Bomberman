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


bool handleRPNElementOnStack( std::string rpnElement, CStack *stack )
{
    if( isBasicMathOperator( rpnElement ) )
    {
        float x1, x2;
        bool b1, b2;

        b2 = stack->pop( &x2 );
        b1 = stack->pop( &x1 );

        if( !b2 || !b1 )
        {
            std::cout << "Element not taken from stack correctly!" << std::endl;
            return false;
        }

        std::cout << "Popped " << x1 << " and " << x2 << " from stack." << std::endl;

        if( isMathOperationValid( x1, x2, rpnElement ) )
        {
            float result = getOperationResult( x1, x2, rpnElement );
            stack->push( result );
            std::cout << "Pushed " << rpnElement << " onto stack." << std::endl;

            return true;
        }
        else
            return false;
    }
    else
    {
        std::cout << "Pushed " << rpnElement << " onto stack." << std::endl;

        return stack->push( stof( rpnElement ) );
    }

    return true;
}


float getRPNResult( std::string rawRPNString, bool *success )
{
    CStack *stack;
    std::vector< std::string > rpnVec;
    float result;

    *success = true;
    stack = new CStack();
    rpnVec = parseRawRPNString( rawRPNString, " " );
    result = 0;

    if( isRPNVectorValid( rpnVec ) )
    {
        for( std::string rpnElement : rpnVec )
        {
            if( !handleRPNElementOnStack( rpnElement, stack ) )
            {
                *success = false;
                break;
            }
        }

        stack->pop( &result );
    }
    else
    {
        std::cout << "RPN sequence not valid: " << rawRPNString << std::endl;
        *success = false;
    }
    
    return result;
}


// bool show_steps( void )
// {
// char input;
// puts("Do you want to see steps of RPN? [Y/N]");
// while (1)
//     {
//     scanf("%c",&input);
//     switch (input)
//         {
//         case ('Y'): return true;
//         case ('y'): return true;

//         case ('N'): return false;
//         case ('n'): return false;

//         default : continue;
//         }
//     }
// }

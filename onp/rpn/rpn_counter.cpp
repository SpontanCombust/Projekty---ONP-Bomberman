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


int handleRPNElementOnStack( std::string rpnElement, CStack *stack )
{
    if( isBasicMathOperator( rpnElement ) )
    {
        float x1, x2;
        bool b1, b2;

        b2 = stack->pop( &x2 );
        if( !b2 )
        {
            std::cout << "Unable to pop element from stack. Probable cause: stack is empty." << std::endl;
            return -1;
        }

        b1 = stack->pop( &x1 );
        if( !b1 )
        {
            std::cout << "Unable to pop element from stack. Probable cause: stack is empty. Reversing the previous pop operation!" << std::endl;
            stack->push( x2 );
            return -2;
        }

        std::cout << "Popped " << x1 << " and " << x2 << " from stack." << std::endl;

        if( isMathOperationValid( x1, x2, rpnElement ) )
        {
            float result = getOperationResult( x1, x2, rpnElement );
            stack->push( result );
            std::cout << "Pushed " << rpnElement << " onto stack." << std::endl;

            return 0;
        }
        else
        {
            std::cout << "Unable to perform math operation. Probable cause: division by zero." << std::endl;
            return -3;
        }
    }
    else
    {
        if( stack->push( stof( rpnElement ) ) )
        {
            std::cout << "Pushed " << rpnElement << " onto stack." << std::endl;
            return 0;
        }
        else
        {
            std::cout << "Unable to push element onto stack. Probable cause: unknown." << std::endl;
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
            if( handleRPNElementOnStack( rpnElement, &stack ) != 0 )
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

#include "rpn.hpp"

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
        
    // if(steps==true){
    //     printf("Executed operation %f %c %f\n",x1 , operator , x2);
    //     printf("Placed %f at the top of the stack \n", outcome );}

    return outcome;
}


bool handleRPNElementOnStack( std::string rpnElement, CStack *stack )
{
    if( isBasicMathOperator( rpnElement ) )
    {
        float x1, x2;

        if( !stack->pop( &x2 ) || !stack->pop( &x1 ) )
            return false;

        // if(steps==true)
        //     printf("Removed %f and %f from the stack. ", n2, n1);

        if( isMathOperationValid( x1, x2, rpnElement ) )
            stack->push( getOperationResult( x1, x2, rpnElement ) );
        else
            return false;
    }
    else
    {
        // if(steps==true)
        //    printf("Placed %lf at the top of the stack \n",atof( e ));}
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
    
    // if(steps==true)
    //     printf("Returning top of the stack as a result\n");

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
    }
    stack->pop( &result );

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

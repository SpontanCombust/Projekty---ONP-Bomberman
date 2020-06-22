#include "rpn.hpp"

#include <chrono>
#include <fstream>
#include <cstdlib>
#include <ctime>

std::string getRandFloatString( float valMin, float valMax )
{
    float r = valMin + static_cast<float>( rand() ) / ( static_cast<float>( RAND_MAX / ( valMax - valMin ) ) );
    
    return std::to_string(r);
}

std::string getRandMathOperatorString( bool cantBeDevide = false )
{
    std::string s;
    char r = rand() % 4;
    if( cantBeDevide ) r--;

    switch(r)
    {
        case 0:     s = "+"; break;
        case 1:     s = "-"; break;
        case 2:     s = "*"; break;
        case 3:     s = "/"; break;
        default:    s = "+"; 
    }

    return s;
}

void performRPNPerformanceTest( int numberQuantity, int numberWeight, int mathOperatorWeight, float valMin, float valMax, std::string mathOperator = "", std::ofstream *statFile = NULL )
{
    CStack          stack;
    std::string     element;
    int             whichElement;
    bool            isNum;
    int             retcode;
    int             i;

    srand( time(0) );
    stack = CStack();
    // if( writeResultsToFile ) 
    // {
    //     auto t = time(0);
    //     auto tm = *std::localtime( &t );
    //     std::ostringstream date;
    //     date << "RPN-Performance-Test-" << std::put_time( &tm, "%Y-%m-%d-%H-%M-%S" ) << ".csv";
    //     statFile.open( date.str() );
    // }
    auto start = std::chrono::steady_clock::now();

    while( i < numberQuantity )
    {
        whichElement = rand() % ( numberWeight + mathOperatorWeight );
        isNum = whichElement < numberWeight ? true : false;

        if( isNum )
        {
            element = getRandFloatString( valMin, valMax );
            i++;
        }
        else
        {
            if( mathOperator != "" )
                element = getRandMathOperatorString();
            else
                element = mathOperator;
        }
        
        retcode = handleRPNElementOnStack( element, stack, NULL, 0, 0 );

        if( retcode != 0 ) continue;

        i++;
        // if( retcode == -1 )
        // {   
            // std::string tmp1 = getRandFloatString( valMin, valMax );
            // std::string tmp2 = getRandFloatString( valMin, valMax );

            // if( tmp2 == std::to_string(0.f) && element == "/" )
            //     element = getRandMathOperatorString( true );
            
            // handleRPNElementOnStack( tmp1, &stack );
            // handleRPNElementOnStack( tmp2, &stack );
            // handleRPNElementOnStack( element, &stack );
        // }
    }

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> perf_time = end - start;

    if( statFile != NULL )
    {
        *statFile   << numberQuantity       << ";" 
                    << numberWeight         << ";" 
                    << mathOperatorWeight   << ";" 
                    << valMin               << ";" 
                    << valMax               << ";" 
                    << perf_time.count()    << "\n";
    }
}

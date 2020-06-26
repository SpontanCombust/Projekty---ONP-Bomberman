#include "rpn.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <chrono>
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

void performRPNPerformanceTest( unsigned int numberQuantity = RPN_DEFAULT_NUMBER_QUANTITY,
                                unsigned int numberWeight = RPN_DEFAULT_NUMBER_WEIGHT,
                                unsigned int mathOperatorWeight = RPN_DEFAULT_MATH_OPERATOR_WEIGHT,
                                float valMin = RPN_DEFAULT_VALUE_MIN,
                                float valMax = RPN_DEFAULT_VALUE_MAX,
                                std::string mathOperator = "", std::ofstream *statFile = NULL )
{
    CStack          stack;
    std::string     element;
    unsigned int    whichElement;
    bool            isNum;
    int             i;
    long            size;
    std::chrono::duration<double> perf_time;
    
    srand( time(0) );
    stack = CStack();
    i = 0;
    size = 0;

    auto start = std::chrono::steady_clock::now();

    while( i < numberQuantity )
    {
        if( size < 2 )
        {
            element = getRandFloatString( valMin, valMax );
            size++;
            i++;
        }
        else
        {
            /*
             * < 0; numberWeight-1 >                   - number
             * < numberWeight; mathOperatorWeight-1 >  - operator            
            */
            whichElement = rand() % ( numberWeight + mathOperatorWeight );
            isNum = (whichElement < numberWeight) ? true : false;

            if( isNum )
            {
                element = getRandFloatString( valMin, valMax );
                size++;
                i++;
            }
            else
            {
                if( mathOperator == "" )
                    element = getRandMathOperatorString();
                else
                    element = mathOperator;
                size--;
            }    
        }

        handleRPNElementOnStack( element, stack );
    }

    while( size > 1 )
    {
        if( mathOperator == "" )
            element = getRandMathOperatorString();
        else
            element = mathOperator;
        
        handleRPNElementOnStack( element, stack );
        size--;
    }

    auto end = std::chrono::steady_clock::now();
    perf_time = end - start;

    std::cout << "Time elapsed: " << perf_time.count() << std::endl;

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

void runRPNPerfTests( unsigned int numberWeight, unsigned int mathOperatorWeight, bool writeToFiles, std::string fileNamePrefix )
{
    std::ofstream quantityTestFile;
    std::ofstream numValueTestFile;
    
    int numQuantity;
    int numQuanityDelta;
    float valMin;
    float valMinDelta;
    float valMax;
    float valMaxDelta;

    auto t = time(0);
    auto tm = *std::localtime( &t );
    std::ostringstream date;
    date << std::put_time( &tm, "%Y-%m-%d-%H-%M-%S" );

    if( writeToFiles )
    {
        quantityTestFile.open( fileNamePrefix + "-Quantity-Test-" + date.str() + ".csv" );
        quantityTestFile << "numberQuantity;numberWeight;mathOperatorWeight;valMin;valMax;timeElapsed\n";
        numValueTestFile.open( fileNamePrefix + "-Value-Test-" + date.str() + ".csv" );
        numValueTestFile << "numberQuantity;numberWeight;mathOperatorWeight;valMin;valMax;timeElapsed\n";
    }

    numQuantity = RPN_NUMBER_QUANTITY_0;
    numQuanityDelta = (RPN_NUMBER_QUANTITY_1 - RPN_NUMBER_QUANTITY_0) / RPN_DEFAULT_SAMPLE_SIZE;
    valMin = RPN_VAL_MIN_0;
    valMinDelta = (RPN_VAL_MIN_1 - RPN_VAL_MIN_0) / RPN_DEFAULT_SAMPLE_SIZE;
    valMax = RPN_VAL_MAX_0;
    valMaxDelta = (RPN_VAL_MAX_1 - RPN_VAL_MAX_0) / RPN_DEFAULT_SAMPLE_SIZE;

    for (int i = 0; i < RPN_DEFAULT_SAMPLE_SIZE; i++)
    {
        if( writeToFiles )
        {
            std::cout << i << "-quantity: ";
            performRPNPerformanceTest( numQuantity, numberWeight, mathOperatorWeight, RPN_DEFAULT_VALUE_MIN, RPN_DEFAULT_VALUE_MAX, "", &quantityTestFile );
            std::cout << i << "-value: ";
            performRPNPerformanceTest( RPN_DEFAULT_NUMBER_QUANTITY, numberWeight, mathOperatorWeight, valMin, valMax, "", &numValueTestFile );
        }
        else
        {
            std::cout << i << ": ";
            performRPNPerformanceTest( numQuantity, numberWeight, mathOperatorWeight, RPN_DEFAULT_VALUE_MIN, RPN_DEFAULT_VALUE_MAX );
            std::cout << i << ": ";
            performRPNPerformanceTest( RPN_DEFAULT_NUMBER_QUANTITY, numberWeight, mathOperatorWeight, valMin, valMax );
        }
        
        numQuantity += numQuanityDelta;
        valMin += valMinDelta;
        valMax += valMaxDelta;
    }
    
    if( quantityTestFile.is_open() && numValueTestFile.is_open() )
    {
        quantityTestFile.close();
        numValueTestFile.close();
    }
}
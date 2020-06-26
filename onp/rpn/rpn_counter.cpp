#include "rpn.hpp"
#include <iostream>
#include <sstream>

/**
 * @brief Sprawdza, czy operacja matematyczna może zostać wykonana
 * 
 * Sprawdza, czy operację matematyczną da się poprawnie wykonać. W tym przypadku na razie,
 * czy odbywa się dzielenie przez zero.
 * 
 * @param x1 argument 1.
 * @param x2 argument 2.
 * @param mathOperator operator matematyczny
 * @return true jeśli operacja jest poprawna
 * @return false jeśli operacja jest niepoprawna
 */
bool isMathOperationValid( float x1, float x2, std::string mathOperator )
{
    if( x2 == 0.f && mathOperator == "/" )
        return false;
    return true;
}

/**
 * @brief Zwraca wynik operacji matematycznej
 * 
 * Zwraca wynik działania dla danych dwóch argumentów i jednego operatora matematycznego.
 * 
 * @param x1 argument 1.
 * @param x2 argument 2.
 * @param mathOperator operator matematyczny
 * @return wynik działania matematycznego
 */
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

/**
 * @brief Wysyła komunikat na ekran w nCurses
 * 
 * @param str tekst do wyświetlenia
 * @param logWin wskaźnik na okno nCurses
 * @param winY pozycja Y wg. okna nCurses
 * @param winX pozycja X wg. okna nCurses
 */
void log( std::string str, WINDOW *logWin, int winY, int winX )
{
    if( logWin == NULL )
        std::cout << str << std::endl;
    else
        mvwprintw( logWin, winY, winX, str.c_str() );
}

/**
 * @brief Obsługuje dany wejściowy element ciągu ONP i odpowiednio modyfikuje dany stos
 * 
 * Odpowiednio wykonuje akcję na stosie w zależności od podanego elementu ciągu ONP. Jeśli element
 * to liczba, dodaje ją do stosu; jeśli jest to operator, pobiera dwie liczby ze stosu i wykonuje
 * na nich działanie przy pomocy tego operatora, a następnie dodaje wynik działania do stosu.
 * Jeśli element to znak równania, pobiera szczytowy element stosu. Wszelkie akcje mogą być
 * wyświetlane do konsoli lub do okna nCurses.
 * 
 * @param rpnElement element ciągu ONP
 * @param stack referencja stosu
 * @param logActions czy akcje powinny zostać wyświetlone w konsoli
 * @param logWin wskaźnik na okno nCurses
 * @param winY pozycja Y wg. okna nCurses
 * @param winX pozycja X wg. okna nCurses
 * @return kod zwrotny działania funkcji
 */
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

/**
 * @brief Zwraca wynik danego działania w formie ONP 
 * 
 * Bierze surowy ciąg znaków będący działaniem w formie ONP, przetwarza go na pojedyncze elementy,
 * a następnie wykonuje na nich odpowiednie działania. Mówi, czy działanie jest prawidłowe.
 * @see handleRPNElementOnStack
 * 
 * @param rawRPNString surowy ciąg elementów ONP
 * @param success wskaźnik na bool informujący czy działanie się powiodło
 * @return wynik działania 
 */
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

        if( stack.size() != 1 )
            *success = false;
        else
            stack.pop( &result );
    }
    else *success = false;
    
    if( !(*success) )    
        std::cout << "RPN sequence not valid: " << rawRPNString << std::endl;
    
    return result;
}

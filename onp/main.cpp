/** @file main.cpp
 * 
 * @brief Plik zawiera funkcję main() programu. 
 * 
 * Plik może wywołać funkcję wywołania podprogramu domonstacyjnego lub funkcji testowania wydajności algorytmu.
 * 
 * @author  Przemysław Cedro
 * @date    2020.06.26
*/

#include "./rpn/rpn.hpp"
#include "./gui_ncurses/rpn_app.hpp"

#include <iostream>

/**
 * @brief Główna funkcja programu
 * 
 * W funkcji można wywołać podprogram demostacyjny w nCurses lub funkcje testowania wydajności działania ONP
 * 
 * @return kod zwrotny działania funkcji
 */
int main()
{
    // runRPNPerfTests( 80, 20, true, "MoreNums" );
    // runRPNPerfTests( 50, 50, true, "EvenOdds" );
    // runRPNPerfTests( 20, 80, true, "MoreOperators" );

    // bool success;
    // float result = getRPNResult( "9 2 + 7 7 7 * / -", &success );
    // if( success ) std::cout << "Result: " << result << std::endl;

    RunRPNDemo();
    
    return 0;
}


/** @file rpn_app.cpp
 * 
 * @brief Plik zawiera definicje funkcji obsługi programu w nCurses demonstrującego działanie ONP
 * 
 * @author  Przemysław Cedro
 * @date    2020.06.26
*/


#include "rpn_app.hpp" 

#include <iostream>
#include <string>
#include "../rpn/rpn.hpp"

void gotoMainMenu();
void gotoRPNDemo();
void resetStackElementWindows( WINDOW *stackElWins[6], bool baseToo = false );
void drawStackBase( WINDOW *stackElWins[6], int baseY, int baseX );
void drawStackElements( WINDOW *stackElWins[6], CStack &stack, int baseY, int baseX );

/**
 * @brief Głowna funkcja inicjująca potrzebne moduły biblioteki nCurses
 * 
 * Funkcja inicjuje podstawowe właściwości okna terminalu nCurses. Tworzy okno główne i wzywa 
 * funkcję przejścia do menu głównego. Po wszystkim zamyka program.
 * @see gotoMainMenu()
 */
void RunRPNDemo()
{
    initscr();
    resize_term( MAIN_WIN_H, MAIN_WIN_W );
    cbreak();
    noecho();
    curs_set(0);

    WINDOW *mainWin = newwin( MAIN_WIN_H, MAIN_WIN_W, 0, 0 );
    WINDOW *headerWin = newwin( 3, MAIN_WIN_W * 0.8, 2, MAIN_WIN_W/2 - MAIN_WIN_W * 0.8 / 2 );
    refresh();

    wborder( mainWin, '#', '#', '#', '#', '#', '#', '#', '#' );
    wrefresh( mainWin );

    wborder( headerWin, '*', '*', '*', '*', '*', '*', '*', '*' );
    std::string headerText = "Reverse Polish Notation Demo Program";
    mvwprintw( headerWin, 1, MAIN_WIN_W * 0.8/2 - headerText.size()/2, headerText.c_str() );
    wrefresh( headerWin );

    gotoMainMenu();

    echo();
    curs_set(1);

    endwin();
}




// -------------- MENUS ----------------

/**
 * @brief Obsługuje przebywanie w menu głównym 
 * 
 * Tworzy okno menu i rysuje linie z tekstem dla niego. Linie można zmieniać strzałkami w górę
 * i w dół. Wybranie linii odbiera się przez naciśnięcię przycisku Enter.
 * Obecnie dostępne opcje:
 * - "Manual RPN Test"  - przechodzi do okna testowania działania ONP 
 * - "Exit"             - wychodzi z programu
 * Wyjść z programu można również przez naciśnięcie przycisku 'q'.
 * 
 * @see gotoRPNDemo()
 */
void gotoMainMenu()
{
    WINDOW *mainMenuWin = newwin( SUB_WIN_H, SUB_WIN_W,  SUB_WIN_Y, SUB_WIN_X );
    keypad( mainMenuWin, true );
    std::string choices[2] = { "Manual RPN test", "Exit" };

    int highlight = 0;
    int action;
    bool done = false;
    bool selected = false;
    while( !done )
    {
        for (int i = 0; i < 2; i++)
        {
            if( i == highlight )
                wattron( mainMenuWin, A_REVERSE );
            mvwprintw( mainMenuWin, i + 1, 1, choices[i].c_str() );
            wattroff( mainMenuWin, A_REVERSE );
        }
        wrefresh( mainMenuWin );
        
        action = wgetch( mainMenuWin );
        switch( action )
        {
            case KEY_UP:    highlight--;        break;
            case KEY_DOWN:  highlight++;        break;
            case 10:        selected = true;    break; //ENTER
            case 'q':       done = true;        break;
            default:        break;
        }

        if      ( highlight < 0 )   highlight = 0;
        else if ( highlight > 1 )   highlight = 1;

        if ( selected && highlight == 0 ) 
        { 
            wclear( mainMenuWin ); 
            refresh(); 
            gotoRPNDemo(); 
        }
        else if ( selected && highlight == 1 ) 
        {
            done = true;
        }
    
        selected = false;
    }

    delwin( mainMenuWin );
}

/**
 * @brief Obsługuje przebywanie w menu demonstracyjnym działania ONP
 * 
 * Tworzy okno programu demonstracyjnego ONP i wczytuje wejście z klawiatury. Wejście jest
 * interpretowane jako kolejne elementy dla stosu ONP. Elementem może być liczba (część ułamkowa
 * powinna być oddzielona kropką '.') lub operator matematyczny ('+', '-', '*', '/', '=').
 * Przy każdej akcji wyświetlany jest na ekranie komentarz do tej akcji wyjaśniający działanie
 * algorytmu oraz rysowana jest wizualizacja stosu ONP. Aby wyjść z dema należy w dowolnym momencie
 * nacisnąć 'q'.
 */
void gotoRPNDemo()
{
    echo();
    curs_set(1);

    CStack stack = CStack();
    WINDOW *demoWin = newwin( SUB_WIN_H, SUB_WIN_W,  SUB_WIN_Y, SUB_WIN_X );
    WINDOW *stackElWins[6] = {NULL};

    drawStackBase( stackElWins, STACK_Y, STACK_X );

    int input;
    std::string sequence = "";
    bool done = false;
    while( !done )
    { 
        wmove( demoWin, 0, 0 );
        wrefresh( demoWin );
        
        input = wgetch( demoWin );    
        while( input != ' ' && input != '\n' )
        {
            if( input == 'q' )
            {
                done = true;
                break;
            }
            sequence += input;

            input = wgetch( demoWin );
        }

        werase( demoWin );
        wrefresh( demoWin );

        if( isRPNElementValid( sequence ) && handleRPNElementOnStack( sequence, stack, true, demoWin, 5, 10 ) == 0 )
        {
            wrefresh( demoWin );
            drawStackElements( stackElWins, stack, STACK_Y, STACK_X );
        }
        else
        {
            mvwprintw( demoWin, 5, 10, "Incorrect input!");
            wrefresh( demoWin );
        }
        
        sequence = "";     
    }

    resetStackElementWindows( stackElWins, true );
    delwin( demoWin );
    
    noecho();
    curs_set(0);
}




// ------------- DRAWING ---------------

/**
 * @brief Resetuje okna nCurses dla wizualizacji stosu
 * 
 * @param stackElWins tablica okien nCurses dla wizualizacji stosu
 * @param baseToo czy zresetować również podstawkę stosu
 */
void resetStackElementWindows( WINDOW *stackElWins[6], bool baseToo )
{
    int lim = baseToo ? 6 : 5;
    for (int i = 0; i < lim; i++)
    {
        if( stackElWins[i] != NULL )
        {
            werase( stackElWins[i] );
            wrefresh( stackElWins[i] );
            delwin( stackElWins[i] );
        }
        stackElWins[i] = NULL;
    }
    refresh();
}

/**
 * @brief Tworzy i rysuje podstawkę wizualizacji stosu
 * 
 * @param stackElWins tablica okien nCurses dla wizualizacji stosu
 * @param baseY koordynat Y podstawki wizualizacji stosu
 * @param baseX koordynat X podstawki wizualizacji stosu
 */
void drawStackBase( WINDOW *stackElWins[6], int baseY, int baseX )
{
    if( stackElWins[5] == NULL )
    {
        stackElWins[5] = newwin( STACK_BASE_H, STACK_BASE_W, baseY, baseX );
        refresh();
        box( stackElWins[5], '/', '/' );
    } 
    wrefresh( stackElWins[5] );
}

/**
 * @brief Tworzy i rysuje wizualizację elementów stosu
 * 
 * Na bazie stosu programu demonstacyjnego tworzy wizualizację stosu ONP. Wizualizacja stosu
 * na wysokość najwyżej 5 elementów - jeśli stos ma wysokość większą niż 5, najniższy element
 * w wizualizacji jest oznaczony przez "...". Elementy stosu stoją na widzialnej cały czas podstawce. 
 * @see drawStackBase()
 * 
 * @param stackElWins tablica okien nCurses dla wizualizacji stosu
 * @param stack referencja stosu używanego przez program
 * @param baseY koordynat Y podstawki wizualizacji stosu
 * @param baseX koordynat X podstawki wizualizacji stosu
 */
void drawStackElements( WINDOW *stackElWins[6], CStack &stack, int baseY, int baseX )
{
    resetStackElementWindows( stackElWins );

    CStack localStack;
    bool isStackElPresent[5] = {false};
    std::string stackElContentStrings[5];    
    float currContent;
    int i, j;

    localStack = stack;

    baseX += (STACK_BASE_W - STACK_ELEMENT_W)/2;
    baseY -= STACK_ELEMENT_H;

    i = 0;
    while( localStack.pop(&currContent) && i < 5 )
    {
        isStackElPresent[i] = true;
        stackElContentStrings[i] = std::to_string( currContent );
        i++;
    }

    for(j = 4; j > -1; j--)
    {
        if( isStackElPresent[j] )
        {
            stackElWins[j] = newwin( STACK_ELEMENT_H, STACK_ELEMENT_W, baseY, baseX );
            refresh();
            box( stackElWins[j], 0, 0 );
            wrefresh( stackElWins[j] );

            if( j == 4 && stack.size() > 5 )
                mvwprintw( stackElWins[j], 1, STACK_ELEMENT_W/2 - 2, "..." );
            else
                mvwprintw( stackElWins[j], 1, STACK_ELEMENT_W/2 - stackElContentStrings[j].size()/2, stackElContentStrings[j].c_str() );

            wrefresh( stackElWins[j] );
        
            baseY -= STACK_ELEMENT_H;
        }
    }
}
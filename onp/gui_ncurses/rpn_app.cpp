#include "rpn_app.hpp" 

#include <iostream>
#include <string>
#include "../rpn/rpn.hpp"

void gotoMainMenu();
void gotoRPNDemo();

void RunRPN()
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

    endwin();
}

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

        if      ( selected && highlight == 0 ) { wclear( mainMenuWin ); refresh(); gotoRPNDemo(); }
        else if ( selected && highlight == 1 ) done = true;
    
        selected = false;
    }

    delwin( mainMenuWin );
}

void drawStack( WINDOW *win, CStack stack, int y, int x )
{
    WINDOW *stackElementWins[6] = { NULL };
    long size = stack.size();
    int currLevel = 1;
    float elementContent;
    for( int i = 0; i < size; i++ )
    {
        stack.pop( &elementContent );
        if( i < 2 || i > size - 3 )
        {
            stackElementWins[currLevel] = newwin( STACK_ELEMENT_H, STACK_ELEMENT_W, currLevel * y, x );
            refresh();

            box( stackElementWins[currLevel], 0, 0 );
            mvwprintw( stackElementWins[currLevel], currLevel * y + 1, x + 5, std::to_string( elementContent ).c_str() );
            wrefresh( stackElementWins[currLevel] );

            currLevel++;
        }
        else if( i == 2 )
        {
            
            stackElementWins[currLevel] = newwin( STACK_ELEMENT_H, STACK_ELEMENT_W, currLevel * y, x );
            refresh();

            box( stackElementWins[currLevel], 0, 0 );
            if( size < 6 )
            {
                mvwprintw( stackElementWins[currLevel], currLevel * y + 1, x + 5, std::to_string( elementContent ).c_str() );
            }
            else
            {
                mvwprintw( stackElementWins[currLevel], currLevel * y + 1, x + 5, "..." );
            }
            wrefresh( stackElementWins[currLevel] );

            currLevel++;
        }               
    }
    stackElementWins[currLevel] = newwin( STACK_BASE_H, STACK_BASE_W, currLevel * y, x - (STACK_BASE_W - STACK_ELEMENT_W)/2 );
    refresh();

    box( stackElementWins[currLevel], '/', '/' );
    wrefresh( stackElementWins[currLevel] );

    for (int j = 0; j < 6; j++)
    {
        if( stackElementWins[j] != NULL ) delwin( stackElementWins[j] );
    }
    
}

void gotoRPNDemo()
{
    echo();
    curs_set(1);

    CStack stack = CStack();
    WINDOW *demoWin = newwin( SUB_WIN_H, SUB_WIN_W,  SUB_WIN_Y, SUB_WIN_X );

    int input;
    std::string sequence = "";
    bool done = false;
    while( !done )
    { 
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

        if( isRPNElementValid( sequence ) && handleRPNElementOnStack( sequence, stack, demoWin, 10, 60 ) == 0 )
        {
            wrefresh( demoWin );
            drawStack( demoWin, stack, 0, 0 );
        }
        else
        {
            wrefresh( demoWin );            
            mvwprintw( demoWin, 20, 20, "WTF?!?!!!!?");
        }
        

        sequence = "";
        getch();
        werase( demoWin );
        wrefresh( demoWin );
    }

    delwin( demoWin );

    noecho();
    curs_set(0);
}
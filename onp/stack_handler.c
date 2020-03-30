#include "onp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// TODO: modul dokladnego sprawdzenia poprawnosci zapisu ciagu
// Funkcje tutaj sa funkcjami wyzszego stopnia i wymagaja juz wstepnie obsluzonych/obrobionych danych

// Zajmuje sie liczeniem rownania; obsluga operatorow
float get_operation_result(float x1, float x2,char operator)
{
    switch (operator)
    {
        case '+':
            return x1 + x2;

        case '-':
            return x1 - x2;

        case '*':
            return x1 * x2;

        case '/':

            if (x2 == 0){
                printf("Can't divide by zero!\n");
                return -1;}

            return x1 / x2;

        default:
            printf("Invalid operator!\n");
            return -2;
    }
}

// Obsluguje dany jej (funkcji) element wyrazenia ONP
void handle_element( char *e, stack_node **top )
{
    if ( e[0] >= '0' && e[0] <= '9' || e[0] == '-' & e[1] >= '0' && e[1] <= '9' )
        *top = push( *top, atof( e ) );
    else
    {
        float n2 = pop( top );
        float n1 = pop( top );
        *top = push( *top, get_operation_result( n1, n2, *e ) );
    }
}

float get_ONP_result( char *string )
{
    stack_node *top = NULL;

    // Do funkcji strtok wprowadzany jest lancuch string oraz miejsca w ktorych ciag nalezy podzielic (znak spacji)
    char *result = strtok( string, " " );

    do
    {
        handle_element( result, &top );
        result = strtok( NULL, " " );

    } while( result != NULL ); //Zwrocenie wartosci NULL oznacza ze funkcja sprawdzila wszystkie znaki lancucha

    return pop( &top );
}
#include "onp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Funkcje tutaj sa funkcjami wyzszego stopnia i wymagaja juz wstepnie obsluzonych/obrobionych danych

// Zajmuje sie liczeniem rownania; obsluga operatorow
float get_operation_result( float x1, float x2, char operator, bool steps)
{
    float outcome;
    switch (operator)
    {
        case '+':
            outcome = x1 + x2;
            break;

        case '-':
            outcome = x1 - x2;
            break;

        case '*':
            outcome = x1 * x2;
            break;

        case '/':

            if (x2 == 0){
                printf("Can't divide by zero!\n");
                return -1;}

            outcome = x1 / x2;
            break;

        default:
            printf("Invalid operator!\n");
            return -2;
    }
    //Wypisanie krokow dzialania funkcji jesli uzytkownik wybral taka mozliwosc
    if(steps==true){
        printf("Executed operation %f %c %f\n",x1 , operator , x2);
        printf("Placed %f at the top of the stack \n", outcome );}

    return outcome;
}

// Obsluguje dany jej (funkcji) element wyrazenia ONP
void handle_element( char *e, stack_node **top , bool steps )
{

    if ( e[0] >= '0' && e[0] <= '9' || e[0] == '-' & e[1] >= '0' && e[1] <= '9' ){
        *top = push( *top, atof( e ) );

    //Wypisanie krokow dzialania funkcji jesli uzytkownik wybral taka mozliwosc
        if(steps==true)
           printf("Placed %lf at the top of the stack \n",atof( e ));}
    else
    {
        float n2 = pop( top );
        float n1 = pop( top );

    //Wypisanie krokow dzialania funkcji jesli uzytkownik wybral taka mozliwosc
        if(steps==true)
            printf("Removed %f and %f from the stack. ", n2, n1);

        *top = push( *top, get_operation_result( n1, n2, *e , steps ) );

    }
}

float get_ONP_result( char *string , bool steps )
{
    stack_node *top = NULL;

    // Do funkcji strtok wprowadzany jest lancuch string oraz miejsca w ktorych ciag nalezy podzielic (znak spacji)
    char *result = strtok( string, " " );
    do
    {
        handle_element( result, &top , steps );
        result = strtok( NULL, " " );

    } while( result != NULL ); //Zwrocenie wartosci NULL oznacza ze funkcja sprawdzila wszystkie znaki lancucha

    //
    if(steps==true)
        printf("Returning top of the stack as a result\n");
    return pop( &top );
}

// Decyduje czy w trakcie trwania programu zostana pokazane poszczegolne kroki wykonanych dzialan
bool show_steps( void )
{
char input;
puts("Do you want to see steps of ONP? [Y/N]");
while (input!='Y'||'N')
    {
    scanf("%c",&input);
    switch (input)
        {
        case 'Y': return true;
                    break;
        case 'N': return false;
                    break;
        default : continue;
        }
    }
}

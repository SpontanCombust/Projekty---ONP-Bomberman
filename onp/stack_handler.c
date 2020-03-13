#include <stdio.h>
// #include <stdlib.h>
#include <string.h>
#include "stack.h"


// TODO: modul dokladnego sprawdzenia poprawnosci zapisu ciagu
// Funkcje tutaj sa funkcjami wyzszego stopnia i wymagaja juz wstepnie obsluzonych/obrobionych danych

// Obsluguje dany jej (funkcji) element wyrazenia ONP
void handle_element(Tstack_node *top, char *e)
{
    // > 1, czyli nie jest pojedynczym znakiem (operatorem)
    if (strlen(e) > 1)
        push(top, atof(e));
    else {
        float n2 = pop(&top);
        float n1 = pop(&top);
        push(top, get_operation_result(n1, n2, e[0]));
    }
}


// Zajmuje sie liczeniem rownania; obsluga operatorow
float get_operation_result(float x1, float x2, char operator)
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
        
            if (x2 == 0)
                printf("Can't divide by zero!");
                return -1;

            return x1 / x2;

        default:
            printf("Invalid operator!");
            return -2;
    }
}
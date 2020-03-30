#include <stdio.h>
// #include <stdlib.h>
#include <string.h>
#include "stack.h"


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
void handle_element(char *e)
{
    Tstack_node *top = NULL;
// Do funkcji strtok wprowadzany jest lancuch string oraz miejsca w ktorych ciag nalezy podzielic (znak spacji)
    char *result = strtok(e," ");
do{
if(result)
// Sprawdzanie czy pierwszy wprowadzany znak jest cyfra
if (result[0]>='0'&&result[0]<='9')
    top = push(top,atof(result));
    else{
    float n2 = pop(&top);
    float n1 = pop(&top);
    top = push(top,get_operation_result(n1,n2,*result));}
result=strtok(NULL," ");

//Zwrocenie wartosci NULL oznacza ze funkcja sprawdzila wszystkie znaki lancucha
}while(result!=NULL);

printf("The result is: %f",pop(&top));
}


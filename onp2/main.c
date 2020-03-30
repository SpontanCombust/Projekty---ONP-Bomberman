#include "stack.h"
#include "stack.c"
#include <stdlib.h>
#include <stdio.h>
#include "stack_handler.c"

int main(){

    char input[22]={'\0'};
    puts("Enter Reverse Polish Notation:");
    scanf("%21[^\n]s",input);
    //Sprawdzenie czy wprowadzany ciag ma powyzej 20 znakow
    if(strlen(input)>20){printf("Given input is too long!!!"); return -1;}
    handle_element(input);
    return 0;
}


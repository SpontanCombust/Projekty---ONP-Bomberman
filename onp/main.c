#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

float get_operation_result(float x1, float x2, char operation)
{
    switch (operation)
    {
        case '+':
            return x1 + x2;

        case '-':
            return x1 - x2;

        case '*':
            return x1 * x2;

        case '/':
            if (x2 == 0)
                puts("Can't divide by zero!");
                return -1;
            return x1 / x2;

        default:
            puts("Invalid operator!");
            return -2;
    }
}

float get_calculated(char onp[100][1000000])
{
    for(int i = 0; i < sizeof(onp)/sizeof(char); i++)
    {


    }

}

int main()
{

    return 0;
}

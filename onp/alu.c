#include <stdio.h>


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
                printf(stderr, "Can't divide by zero!");
                return -1;

            return x1 / x2;

        default:
            printf(stderr, "Invalid operator!");
            return -2;
    }
}
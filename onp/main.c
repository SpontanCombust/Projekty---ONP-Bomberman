#include "onp.h"
#include <string.h>
#include <stdio.h>

int main(){

    char input[22];

    puts( "Enter Reverse Polish Notation of max. length of 20:" );
    scanf("%21[^\n]s", input );

    //Sprawdzenie czy wprowadzany ciag ma powyzej 20 znakow
    if( strlen( input ) > 20 )
    {
        printf( "Given input is too long!!!" );
        return -1;
    }

    printf("The result is: %f", get_ONP_result( input ) );

    return 0;
}


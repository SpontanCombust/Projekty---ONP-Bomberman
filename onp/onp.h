#ifndef ONP_H
#define ONP_H

#include "stdbool.h"
#include "stack.h"

float get_operation_result( float, float, char, bool );
void handle_element( char *, stack_node ** , bool);
float get_ONP_result( char * , bool );
bool show_steps();

#endif

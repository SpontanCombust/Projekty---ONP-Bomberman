#ifndef __ONP_H
#define __ONP_H

#include "stack.h"
#include "stdbool.h"

float get_operation_result( float, float, char, bool );
void handle_element( char *, stack_node ** , bool);
float get_ONP_result( char * , bool );
bool show_steps();

#endif

#include "stack.hpp"
#include <stdlib.h>

Stack::Stack()
{
    top = NULL;
}

bool Stack::push( float content )
{
    TStackNode *newNode = ( TStackNode * )malloc( sizeof( TStackNode ) );
    
    if ( newNode )
    {       
        newNode->content = content;
        
        if( top == NULL )
        {
            newNode->next = NULL;
            top = newNode;
        }
        else
        {
            newNode->next = top;
            top = newNode;
        }
        
        return true;
    }
    return false;
}

bool Stack::pop( float *content )
{
    if( top == NULL )
        return false;

    *content = top->content;
    TStackNode *tmp = top->next;
    free( top );
    top = tmp;

    return true;
}

bool Stack::peek( float *content )
{
    if( top == NULL )
        return false;

    *content = top->content;

    return true;
}
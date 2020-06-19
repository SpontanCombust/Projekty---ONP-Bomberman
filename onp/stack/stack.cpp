#include "stack.hpp"
#include <stdlib.h>

CStack::CStack()
{
    top = NULL;
}

bool CStack::push( float content )
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

bool CStack::pop( float *content )
{
    if( top == NULL )
        return false;

    *content = top->content;
    TStackNode *tmp = top->next;
    free( top );
    top = tmp;

    return true;
}

bool CStack::peek( float *content )
{
    if( top == NULL )
        return false;

    *content = top->content;

    return true;
}
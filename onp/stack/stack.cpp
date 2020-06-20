#include "stack.hpp"
#include <stdlib.h>

CStack::CStack()
{
    top = NULL;
}

bool CStack::push( float content )
{
    SStackNode *newNode = ( SStackNode * )malloc( sizeof( SStackNode ) );
    
    if ( newNode == NULL )
        return false;

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

bool CStack::pop( float *content )
{
    if( top == NULL )
        return false;

    *content = top->content;
    SStackNode *tmp = top->next;
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
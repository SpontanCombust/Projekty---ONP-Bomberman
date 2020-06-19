#ifndef __STACK_HPP
#define __STACK_HPP

typedef struct SStackNode
{
    float content;
    struct SStackNode *next;

} TStackNode;

class CStack
{
    protected:
        TStackNode *top;

    public:
        CStack();
        bool push( float content );
        bool pop( float *content );
        bool peek( float *content );
};

#endif

#ifndef __STACK_H
#define __STACK_H

//Struktura rekurencyjna "stack_node" pelniaca role elementu stosu.
struct s_stack_node
{
    //Pole "content" typ float, ktore bedzie przechowywac  liczbe
    float content;

    //Wskaznik na kolejny (nizszy) element stosu; ma ten sam typ co struktura, w ktorej sie znajduje (stad "struktura rekurencyjna").
    struct s_stack_node *next;
};

//Definicja typu Tstack_node w celu pozniejszego uproszczenia kodu
typedef struct s_stack_node stack_node;

stack_node *push( stack_node *, float );
float pop( stack_node ** );
float peek( stack_node * );

#endif

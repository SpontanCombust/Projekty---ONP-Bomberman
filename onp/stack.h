#ifndef STACK_H
#define STACK_H

//Plik naglowkowy zawierajacy deklaracje stosu i funkcji, ktore beda go obslugiwac.

static struct stack_node;
typedef struct stack_node Tstack_node;
Tstack_node *push(Tstack_node *, float);
float pop(Tstack_node **);

#endif 

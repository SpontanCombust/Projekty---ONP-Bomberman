#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

//Plik naglowkowy zawierajacy deklaracje stosu i funkcji, ktore beda go obslugiwac.

extern Tstack_node;
extern Tstack_node *push(Tstack_node *, char);
extern char pop(Tstack_node **);

#endif // STACK_H_INCLUDED

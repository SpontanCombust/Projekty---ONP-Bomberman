#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

//Funkcja "push" dodajaca element do stosu. Zwraca wskaznik na nowy wierzcholek stosu.
stack_node *push( stack_node *top, float content )
{
    //Deklaracja i inicjalizacja nowego elementu stosu - "new_node"; dynamiczne przydzielenie pamieci do niego.
    stack_node *new_node = ( stack_node * )malloc( sizeof( stack_node ) );

    //Jesli pamiec dla nowego elementu stosu zostala przydzielonaS pomyslnie to:
    if (new_node)
    {
        //Przypisanie polu "content" nowego elementu stosu wartosc parametru 'content'.
        new_node -> content = content;

        //Ustawienie obecnego wierzcholka stosu ("top") jako nastepny element stosu dla elementu "new_node".
        new_node -> next = top;

        //Ustawienie "new_node" jako nowego wierzcholka stosu.
        top = new_node;
    }

    //Zwrocenie wskaznika na nowy wierzcholek stosu
    return top;
}


//Funkcja "pop" zwracajaca zawartosc pola "content" z najwyzszego elementu stosu i usuwajaca ten element ze stosu tzn. zdejmuje element ze stosu.
float pop(stack_node **top)
{
    //Deklaracja i inicjalizacja zmiennej "result", ktorej poczatkowo przypisywana jest wartosc -1
    float result = -1;

    //Sprawdzenie czy stos jest niepusty. Jesli stos posiada jeden lub wiecej elementow, to:
    if (*top)
    {
        //Przypisz zmiennej "result" wartosc pola "content", ktore posiada wierzcholek stosu.
        result = (*top) -> content;

        //Deklaracja i inicjalizacja tymczasowej zmiennej wskaznikowej "tmp", ktora przechowuje wskaznik na drugi element stosu, tj. element pod wierzchozkiem stosu
        stack_node *tmp = (*top) -> next;

        //Zwolnienie pamieci, ktora zajmowal obecny wierzcholek stosu.
        free(*top);

        //Przypisanie do wskaznika na wierzcholek stosu wartosci wskaznika "tmp". Ustawienie drugiego elementu stosu jako nowego wierzcholka stosu.
        *top = tmp;
    }
    else
    {
        puts("Stack is empty!");
    }
    

    //Zwrocenie: wartosci -1 jesli stos byc pusty; wartosci pola "content" najwyzszego elementu stosu, jesli ten stos byc niepusty
    return result;
}

float peek( stack_node *top)
{
    float result = -1;

    if( top )
        result = top -> content;
    else
        puts("Stack is empty!");
    
    return result;
}



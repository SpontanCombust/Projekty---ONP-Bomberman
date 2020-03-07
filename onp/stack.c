#include "stack.h"
#include <stdlib.h>

//Struktura rekurencyjna "stack_node" pełniaca rolę elementu stosu.
struct stack_node
{
    //Pole "content" typ char, które będzie przechowywać  nieprzetworzoną jeszcze na typ liczbowy liczbę lub operator.
    char content;

    //Wskaźnik na kolejny (niższy) element stosu; ma ten sam typ co struktura, w której się znajduje (stąd "struktura rekurencyjna").
    struct stack_node *next;
};


//Funkcja "push" dodająca element do stosu. Zwraca wskaźnik na nowy wierzchołek stosu.
struct stack_node *push(struct stack_node *top, char content)
{
    //Deklaracja i inicjalizacja nowego elementu stosu - "new_node"; dynamiczne przydzielenie pamięci do niego.
    struct stack_node *new_node = (struct stack_node *)malloc(sizeof(stack_node));

    //Jeśli pamięc dla nowego elementu stosu została przydzielona pomyślnie to:
    if (new_node)
    {
        //Przypisanie polu "content" nowego elementu stosu wartość parametru 'content'.
        new_node -> content = content;

        //Ustawienie obecnego wierzchołka stosu ("top") jako natępny element stosu dla elementu "new_node".
        new_node -> next = top;

        //Ustawienie "new_node" jako nowego wierzchołka stosu.
        top = new_node;
    }

    //Zwrócenie wskaźnika na nowy wierzchołek stosu
    return top;
}


//Funkcja "pop" zwracająca zawartość pola "content" z najwyższego elementu stosu i usuwająca ten element ze stosu tzn. zdejmuje element ze stosu.
char pop(struct stack_node **top)
{
    //Deklaracja i inicjalizacja zmiennej "result", której początkowo przypisywana jest wartość -1
    char result = -1;

    //Sprawdzenie czy stos jest niepusty. Jeśli stos posiada jeden lub więcej elementów, to:
    if (*top)
    {
        //Przypisz zmiennej "result" wartość pola "content", które posiada wierzchołek stosu.
        result = (*top) -> content;

        //Deklaracja i inicjalizacja tymczasowej zmiennej wskaźnikowej "tmp", która przechowuje wskaźnik na drugi element stosu, tj. element pod wierzchołkiem stosu
        struct stack_node *tmp = (*top) -> next;

        //Zwolnienie pamięci, którą zajmował obecny wierzchołek stosu.
        free(*top);

        //Przypisanie do wskaźnika na wierzchołek stosu wartości wskaźnika "tmp". Ustawienie drugiego elementu stosu jako nowego wierzchołka stosu.
        *top = tmp;
    }

    //Zwrócenie: wartości -1 jeśli stos był pusty; wartości pola "content" najwyższego elementu stosu, jeśli ten stos był niepusty
    return result;
}

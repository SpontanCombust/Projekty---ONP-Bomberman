#include "stack.h"
#include <stdlib.h>

//Struktura rekurencyjna "stack_node" pe�niaca rol� elementu stosu.
struct stack_node
{
    //Pole "content" typ char, kt�re b�dzie przechowywa�  nieprzetworzon� jeszcze na typ liczbowy liczb� lub operator.
    char content;

    //Wska�nik na kolejny (ni�szy) element stosu; ma ten sam typ co struktura, w kt�rej si� znajduje (st�d "struktura rekurencyjna").
    struct stack_node *next;
};


//Funkcja "push" dodaj�ca element do stosu. Zwraca wska�nik na nowy wierzcho�ek stosu.
struct stack_node *push(struct stack_node *top, char content)
{
    //Deklaracja i inicjalizacja nowego elementu stosu - "new_node"; dynamiczne przydzielenie pami�ci do niego.
    struct stack_node *new_node = (struct stack_node *)malloc(sizeof(stack_node));

    //Je�li pami�c dla nowego elementu stosu zosta�a przydzielona pomy�lnie to:
    if (new_node)
    {
        //Przypisanie polu "content" nowego elementu stosu warto�� parametru 'content'.
        new_node -> content = content;

        //Ustawienie obecnego wierzcho�ka stosu ("top") jako nat�pny element stosu dla elementu "new_node".
        new_node -> next = top;

        //Ustawienie "new_node" jako nowego wierzcho�ka stosu.
        top = new_node;
    }

    //Zwr�cenie wska�nika na nowy wierzcho�ek stosu
    return top;
}


//Funkcja "pop" zwracaj�ca zawarto�� pola "content" z najwy�szego elementu stosu i usuwaj�ca ten element ze stosu tzn. zdejmuje element ze stosu.
char pop(struct stack_node **top)
{
    //Deklaracja i inicjalizacja zmiennej "result", kt�rej pocz�tkowo przypisywana jest warto�� -1
    char result = -1;

    //Sprawdzenie czy stos jest niepusty. Je�li stos posiada jeden lub wi�cej element�w, to:
    if (*top)
    {
        //Przypisz zmiennej "result" warto�� pola "content", kt�re posiada wierzcho�ek stosu.
        result = (*top) -> content;

        //Deklaracja i inicjalizacja tymczasowej zmiennej wska�nikowej "tmp", kt�ra przechowuje wska�nik na drugi element stosu, tj. element pod wierzcho�kiem stosu
        struct stack_node *tmp = (*top) -> next;

        //Zwolnienie pami�ci, kt�r� zajmowa� obecny wierzcho�ek stosu.
        free(*top);

        //Przypisanie do wska�nika na wierzcho�ek stosu warto�ci wska�nika "tmp". Ustawienie drugiego elementu stosu jako nowego wierzcho�ka stosu.
        *top = tmp;
    }

    //Zwr�cenie: warto�ci -1 je�li stos by� pusty; warto�ci pola "content" najwy�szego elementu stosu, je�li ten stos by� niepusty
    return result;
}

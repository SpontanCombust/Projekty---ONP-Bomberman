#include "stack.h"
#include <stdlib.h>

//Struktura rekurencyjna "stack_node" pe³niaca rolê elementu stosu.
struct stack_node
{
    //Pole "content" typ char, które bêdzie przechowywaæ  nieprzetworzon¹ jeszcze na typ liczbowy liczbê lub operator.
    char content;

    //WskaŸnik na kolejny (ni¿szy) element stosu; ma ten sam typ co struktura, w której siê znajduje (st¹d "struktura rekurencyjna").
    struct stack_node *next;
};


//Funkcja "push" dodaj¹ca element do stosu. Zwraca wskaŸnik na nowy wierzcho³ek stosu.
struct stack_node *push(struct stack_node *top, char content)
{
    //Deklaracja i inicjalizacja nowego elementu stosu - "new_node"; dynamiczne przydzielenie pamiêci do niego.
    struct stack_node *new_node = (struct stack_node *)malloc(sizeof(stack_node));

    //Jeœli pamiêc dla nowego elementu stosu zosta³a przydzielona pomyœlnie to:
    if (new_node)
    {
        //Przypisanie polu "content" nowego elementu stosu wartoœæ parametru 'content'.
        new_node -> content = content;

        //Ustawienie obecnego wierzcho³ka stosu ("top") jako natêpny element stosu dla elementu "new_node".
        new_node -> next = top;

        //Ustawienie "new_node" jako nowego wierzcho³ka stosu.
        top = new_node;
    }

    //Zwrócenie wskaŸnika na nowy wierzcho³ek stosu
    return top;
}


//Funkcja "pop" zwracaj¹ca zawartoœæ pola "content" z najwy¿szego elementu stosu i usuwaj¹ca ten element ze stosu tzn. zdejmuje element ze stosu.
char pop(struct stack_node **top)
{
    //Deklaracja i inicjalizacja zmiennej "result", której pocz¹tkowo przypisywana jest wartoœæ -1
    char result = -1;

    //Sprawdzenie czy stos jest niepusty. Jeœli stos posiada jeden lub wiêcej elementów, to:
    if (*top)
    {
        //Przypisz zmiennej "result" wartoœæ pola "content", które posiada wierzcho³ek stosu.
        result = (*top) -> content;

        //Deklaracja i inicjalizacja tymczasowej zmiennej wskaŸnikowej "tmp", która przechowuje wskaŸnik na drugi element stosu, tj. element pod wierzcho³kiem stosu
        struct stack_node *tmp = (*top) -> next;

        //Zwolnienie pamiêci, któr¹ zajmowa³ obecny wierzcho³ek stosu.
        free(*top);

        //Przypisanie do wskaŸnika na wierzcho³ek stosu wartoœci wskaŸnika "tmp". Ustawienie drugiego elementu stosu jako nowego wierzcho³ka stosu.
        *top = tmp;
    }

    //Zwrócenie: wartoœci -1 jeœli stos by³ pusty; wartoœci pola "content" najwy¿szego elementu stosu, jeœli ten stos by³ niepusty
    return result;
}

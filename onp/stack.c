#include "stack.h"
#include <stdlib.h>

//Struktura rekurencyjna "stack_node" pelniaca role elementu stosu.
struct stack_node

    //Pole "content" typ char, ktore bedzie przechowywac  nieprzetworzona jeszcze na typ liczbowy liczbe lub operator.
    char content[20];

    //Wskaznik na kolejny (nizszy) element stosu; ma ten sam typ co struktura, w ktorej sie znajduje (stad "struktura rekurencyjna").
    struct stack_node *next;
};

//Definicja typu Tstack_node w celu pozniejszego uproszczenia kodu
typedef struct stack_node Tstack_node;

//Funkcja "push" dodajaca element do stosu. Zwraca wskaznik na nowy wierzcholek stosu.
Tstack_node *push(Tstack_node *top, char content)
{
    //Deklaracja i inicjalizacja nowego elementu stosu - "new_node"; dynamiczne przydzielenie pamieci do niego.
    Tstack_node *new_node = (Tstack_node *)malloc(sizeof(Tstack_node));

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
char pop(Tstack_node **top)
{
    //Deklaracja i inicjalizacja zmiennej "result", ktorej poczatkowo przypisywana jest wartosc -1
    char result = -1;

    //Sprawdzenie czy stos jest niepusty. Jesli stos posiada jeden lub wiecej elementow, to:
    if (*top)
    {
        //Przypisz zmiennej "result" wartosc pola "content", ktore posiada wierzcholek stosu.
        result = (*top) -> content;

        //Deklaracja i inicjalizacja tymczasowej zmiennej wskaznikowej "tmp", ktora przechowuje wskaznik na drugi element stosu, tj. element pod wierzchozkiem stosu
        Tstack_node *tmp = (*top) -> next;

        //Zwolnienie pamieci, ktora zajmowal obecny wierzcholek stosu.
        free(*top);

        //Przypisanie do wskaznika na wierzcholek stosu wartosci wskaznika "tmp". Ustawienie drugiego elementu stosu jako nowego wierzcholka stosu.
        *top = tmp;
    }

    //Zwrocenie: wartosci -1 jesli stos byc pusty; wartosci pola "content" najwyzszego elementu stosu, jesli ten stos byc niepusty
    return result;
}

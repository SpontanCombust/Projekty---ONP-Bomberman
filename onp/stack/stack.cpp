/** @file stack.cpp
 * 
 * @brief Plik zawiera definicje metod klasy stos.
 * 
 * @author  Przemysław Cedro
 * @date    2020.06.22
*/


#include "stack.hpp"
#include <stdlib.h>

/**
 * @brief Konstruktor stosu. Zeruje wartość jego szczytu.
 * 
 */
CStack::CStack()
{
    top = NULL;
}

/**
 * @brief Destruktor stosu. Zwalnia pamięć z pozostałych elemenyów stosu.
 * 
 */
CStack::~CStack()
{
    clear();
}

/**
 * @brief Dodaje element do stosu
 * 
 * Jeśli stos jest pusty to ustawia nowo utworzony element jako szczyt.
 * W przeciwnym wypadku dodaje element na sam szczyt stosu.
 * 
 * @param content zawartość elementu stosu
 * @return true jeśli element został dodany pomyślnie
 * @return false jeśli element nie został dodany pomyślnie
 */
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

/**
 * @brief Zdejmuje element ze szczytu stosu
 * 
 * Usuwa szczytowy element stosu i przypisuje wartość jego zawartości do zmiennej content
 * (o ile ta zawartość istnieje)
 * 
 * @param content wskaźnik na zmienną do przypisania jej wartości zawartości szczytu stosu
 * @return true jeśli element został zdjęty pomyślnie
 * @return false jeśli element nie został zdjęty pomyślnie
 */
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

/**
 * @brief Pozwala na zajrzenie do szczytu stosu
 * 
 * Przypisuje wartość zawartości szczytu stosu zmiennej content (o ile ta zawartość istnieje)
 * 
 * @param content 
 * @return true jeśli udało się zajrzeć do szczytu stosu
 * @return false jeśli nie udało się zajrzeć do szczytu stosu
 */
bool CStack::peek( float *content )
{
    if( top == NULL )
        return false;

    *content = top->content;

    return true;
}

/**
 * @brief Zwraca wielkość stosu (ilość jego elementów)
 * 
 * @return long rozmiar stosu
 */
long CStack::size()
{
    long ss = 0;
    SStackNode *node = top;
    while( node != NULL )
    {
        ss++;
        node = node->next;
    }
    return ss;
}

/**
 * @brief Zwalnia pamięć z ustawionych elementów stosu
 * 
 */
void CStack::clear()
{
    float dummy;
    while( top != NULL )
        pop( &dummy );
}
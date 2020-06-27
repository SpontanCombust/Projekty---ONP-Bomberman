/** @file stack.hpp
 * 
 * @brief Plik zawiera definicję struktury elementu stosu i klasy stosu oraz deklaracje metod dla klasy stosu.
 * 
 * @author  Przemysław Cedro
 * @date    2020.06.22
*/


#ifndef __STACK_HPP
#define __STACK_HPP

/**
 * @brief Struktura reprezentująca element stosu
 * 
 * Przechowuje zmienną typu float i wskaźnik na kolejny (niższy) element stosu.
 */
typedef struct SStackNode
{
    float content; /**< Zawartość elementu */
    struct SStackNode *next; /**< Wskaźnik na kolejny element stosu */

} SStackNode;

/**
 * @brief Klasowa implementacja stosu
 * 
 * Zawiera metody dodawania elementów, zdejmowania, zaglądania, sprawdzania wielkości stosu i zwalniania
 * pamięci ze wszystkich elementów.
 */
class CStack
{
    protected:
        SStackNode *top; /**< Wskaźnik na szczyt stosu */

    public:
        /** Konstruktor stosu. Zeruje wartość jego szczytu */
        CStack(); 
        /** Destruktor stosu. Zwalnia pamięć z pozostałych elemenyów stosu */
        ~CStack(); 
        /** Przeciążony operator przypisania jednego stosu do drugiego */
        CStack& operator= ( const CStack &stack );
        /** Dodaje element do stosu */
        bool push( float content ); 
        /** Zdejmuje element ze szczytu stosu */
        bool pop( float *content );
        /** Pozwala na zajrzenie do szczytu stosu */
        bool peek( float *content );
        /** Zwraca wielkość stosu (ilość jego elementów) */
        long size();
        /** Zwalnia pamięć z ustawionych elementów stosu */
        void clear();
};

#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TAB_MAX 500

//struktura statystyk
typedef struct
{
    //statystyki porownan
    int bubble;
    int heap;
    int quick;
    int merge;
    //statystyki czasowe
    int bubble_t;
    int heap_t;
    int quick_t;
    int merge_t;
    
}statistics;

//predefinicje funkcji
void fillTab(int tab[]);
//funkcje sortowania zwracaja ilosc porownan
void bubbleSort(int tab[],statistics *s);
void heapSort(int tab[],statistics *s); //pamietac o ->
void quickSort(int tab[],statistics *s);
void mergeSort(int tab[],statistics *s);


void getStatistics(statistics s);

int main() {
    int tab[TAB_MAX];
    fillTab(tab);
    statistics stat;
    //bubbleSort(tab,stat);
    
}

void fillTab(int tab[])
{
    srand(time(NULL));
    for(int i=0; i<TAB_MAX; i++)
        tab[i] = (rand() % 1201) - 600; //losuje liczby z przedzialu <-600;600>
    return;
}

void getStatistics(statistics s)
{
    printf("\nLiczba porownan:");
    printf("\nSortowanie babelkowe:\t%d",s.bubble);
    printf("\nSortowanie przez kopcowanie:\t%d",s.heap);
    printf("\nSortowanie szybkie:\t%d",s.quick);
    printf("\nSortowanie przez scalanie:\t%d",s.merge);
    
    printf("\n\nCzas wykonywania:");
    printf("\nSortowanie babelkowe:\t%d",s.bubble_t);
    printf("\nSortowanie przez kopcowanie:\t%d",s.heap_t);
    printf("\nSortowanie szybkie:\t%d",s.quick_t);
    printf("\nSortowanie przez scalanie:\t%d",s.merge_t);
    
    return;
}

bubbleSort(int tab[],statistics *s);

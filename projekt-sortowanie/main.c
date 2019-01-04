#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TAB_MAX 2000
#define TIME_MULT 1000000
//struktura statystyk
typedef struct
{
    //statystyki porownan
    int bubble;
    int heap;
    int quick;
    int merge;
    //statystyki czasowe
    float bubble_t;
    float heap_t;
    float quick_t;
    float merge_t;
    
}statistics;

//predefinicje funkcji
void fillTab(int tab[]);
void deleteStats(statistics *s);
//funkcje sortowania zwracaja ilosc porownan
void bubbleSort(int tab[],statistics *s);
void heapSort(int tab[],statistics *s); //pamietac o ->
void quickSort(int tab[],statistics *s);
void mergeSort(int tab[],statistics *s);


void getStatistics(statistics *s);

int main() {
    int tab[TAB_MAX];
    fillTab(tab);
    statistics s = {
        .bubble= 0,
        .bubble_t =  0.0,
        .heap =  0,
        .heap_t =  0.0,
        .quick =  0,
        .quick_t =  0.0,
        .merge =  0,
        .merge_t =  0.0
    };
    statistics *stat = &s;
    
    //deleteStats(stat);
    bubbleSort(tab,stat);
    
    getStatistics(stat);
    
}

void fillTab(int tab[])
{
    srand(time(NULL));
    for(int i=0; i<TAB_MAX; i++)
        tab[i] = (rand() % (4*TAB_MAX+1)) - 2*TAB_MAX; //losuje liczby z przedzialu <-2TAB_MAX;2TAB_MAX>
    return;
}
void deleteStats(statistics *s)
{
    s->bubble = 0;
    s->bubble_t = 0.0;
    s->heap = 0;
    s->heap_t = 0.0;
    s->merge = 0;
    s->merge_t = 0.0;
    s->quick = 0;
    s->quick_t = 0.0;
    
}
void getStatistics(statistics *s)
{
    printf("\nLiczba porownan:");
    printf("\nSortowanie babelkowe:\t%d",s->bubble);
    printf("\nSortowanie przez kopcowanie:\t%d",s->heap);
    printf("\nSortowanie szybkie:\t%d",s->quick);
    printf("\nSortowanie przez scalanie:\t%d",s->merge);
    
    printf("\n\nCzas wykonywania:");
    printf("\nSortowanie babelkowe:\t%.2fus",s->bubble_t);
    printf("\nSortowanie przez kopcowanie:\t%.2fus",s->heap_t);
    printf("\nSortowanie szybkie:\t%.2fus",s->quick_t);
    printf("\nSortowanie przez scalanie:\t%.2fus\n\n",s->merge_t);
    
    return;
}

void bubbleSort(int tab[],statistics *s)
{
    int max_idx; //indeks najwiekszego elementu
    int comp = 0; //zlicza porownania
    clock_t start, stop;
    float time;
    
    start = clock();
    for(int i=0; i < TAB_MAX; i++)
    {
        max_idx = 0;
        for(int j=0; j< TAB_MAX - i; j++)
        {
            if (tab[max_idx]<tab[j])
                max_idx = j;
            comp++; //porownuje elementy
            
        }
        //zamiana wartosci
        int z = tab[max_idx];
        tab[max_idx] = tab[TAB_MAX-i-1];
        tab[TAB_MAX-i-1] = z;
    }
    stop = clock();
    time = TIME_MULT*(stop-start)/CLOCKS_PER_SEC;
    
    s->bubble = comp;
    s->bubble_t = time;
    
    return;
}

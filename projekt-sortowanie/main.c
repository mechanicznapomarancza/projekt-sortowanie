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
void heapSort(int tab[],statistics *s);
void quickSort(int tab[],int first,int last,statistics *s);
void mergeSort(int tab[], int l, int r,statistics *s);
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
    heapSort(tab, stat);
    quickSort(tab, 0, TAB_MAX-1, stat);
    mergeSort(tab, 0, TAB_MAX-1, stat);
    
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
            s->bubble++; //porownuje elementy
            
        }
        //zamiana wartosci
        int z = tab[max_idx];
        tab[max_idx] = tab[TAB_MAX-i-1];
        tab[TAB_MAX-i-1] = z;
    }
    stop = clock();
    time = TIME_MULT*(stop-start)/CLOCKS_PER_SEC;
    
    s->bubble_t = time;
    
    return;
}

//metody pomocnicze do kopca
int max (int tab[],int n, int i, int j, int k, statistics *s) {
    int m = i;
    if (j < n && tab[j] > tab[m]) {
        m = j;
    }
    if (k < n && tab[k] > tab[m]) {
        m = k;
    }
    s->heap+=2;
    return m;
}
void downheap (int tab[], int n, int i, statistics *s) {
    while (1) {
        int j = max(tab, n, i, 2 * i + 1, 2 * i + 2,s);
        
        if (j == i) {
            break;
        }
        int t = tab[i];
        tab[i] = tab[j];
        tab[j] = t;
        i = j;
    }
    return;
}

void heapSort (int tab[], statistics *s) {
    int i;
    clock_t start, stop;
    float time;
    start = clock();
    for (i = (TAB_MAX - 2) / 2; i >= 0; i--) {
        downheap(tab, TAB_MAX, i,s);
    }
    for (i = 0; i < TAB_MAX; i++) {
        int t = tab[TAB_MAX - i - 1];
        tab[TAB_MAX - i - 1] = tab[0];
        tab[0] = t;
        downheap(tab, TAB_MAX - i - 1, 0,s);
    }
    stop = clock();
    time = TIME_MULT*(stop-start)/CLOCKS_PER_SEC;
    
    s->heap_t = time;
    return;
}

void quickSort(int tab[],int first,int last,statistics *s){
    int i, j, pivot, temp;
    clock_t start, stop;
    float time;
    start = clock();
    if(first<last){
        pivot=first;
        i=first;
        j=last;
        
        while(i<j){
            while(tab[i]<=tab[pivot]&&i<last)
                {
                    i++;
                    s->quick++;
                }
            while(tab[j]>tab[pivot])
                {
                    j--;
                    s->quick++;
                }
           
            if(i<j){
                temp=tab[i];
                tab[i]=tab[j];
                tab[j]=temp;
            }
            
        }
        
        temp=tab[pivot];
        tab[pivot]=tab[j];
        tab[j]=temp;
        quickSort(tab,first,j-1,s);
        quickSort(tab,j+1,last,s);
        
    }
    stop = clock();
    time = TIME_MULT*(stop-start)/CLOCKS_PER_SEC;
    
    s->quick_t = time;
    return;
}



void merge(int arr[], int l, int m, int r, statistics *s)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
    
    // tymczasowe tablice L i R o rozmiarach n1 i n2
    int L[n1], R[n2];
    
    // kopiowanie danych do podtablic
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
    
    // scalanie tablic
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
        s->merge++;
    }
    
    // kopiowanie pozostalych elementow lewej tablicy L (jesli zostaly)
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    // kopiowanie pozostalych elementow prawej tablicy R (jesli zostaly)
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
    return;
}

//l - lewy kraniec sortowanego przedzialu
//p - prawy kraniec sortowanego przedzialu
void mergeSort(int tab[], int l, int r, statistics *s)
{
    clock_t start, stop;
    float time;
    start = clock();
    if (l < r)
    {
        // miejsce podzialu tablic na polowy
        int m = l+(r-l)/2;
        
        // Sortowanie polowek
        mergeSort(tab, l, m, s);
        mergeSort(tab, m+1, r, s);
        
        merge(tab, l, m, r, s);
    }
    stop = clock();
    time = TIME_MULT*(stop-start)/CLOCKS_PER_SEC;
    
    s->merge_t = time;
    return;
}

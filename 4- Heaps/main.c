#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct
{

    int *array;
    int count;
    int capacity;
    int heap_type;

}*Heap;

int isEmpty_Heap(Heap h)
{

    return ( h->count == 0 );
}

int isFull_Heap(Heap h)
{

    return ( h->count == h->capacity );
}

Heap Create_Heap(int capacity,int heap_type)
{

    Heap h = (Heap)malloc(sizeof(Heap));
    if(!h) return NULL;
    h->heap_type = heap_type;
    h->count = 0;
    h->capacity = capacity;
    h->array = (int *)malloc((sizeof(int))*(h->capacity));
    if(! h->array) return NULL;
    return h;
}

int Parent(Heap h,int i)
{

    if( i<= 0 || i>= h->count ) return -1;
    return ((i-1)/2);
}

int Left_Child(Heap h,int i)
{

    int left = 2*i+1;
    if( left >= h->count ) return -1;
    return left;
}

int Right_Child(Heap h,int i)
{

    int right = 2*i+2;
    if( right >= h->count ) return -1;
    return right;
}

int Max_Heap(Heap h)
{

    if( h->count == 0 ) return -1;
    return h->array[0];
}

void Percolate_Down(Heap *h,int i)
{

    int l,r,max,temp;
    l = Left_Child(*h,i);
    r = Right_Child(*h,i);
    if( l != -1 && (*h)->array[l] > (*h)->array[i] ) max = l;
    else max = i;
    if( r != -1 && (*h)->array[r] > (*h)->array[max] ) max = r;
    if( max != i )
    {
        temp = (*h)->array[i];
        (*h)->array[i] = (*h)->array[max];
        (*h)->array[max] = temp;
        Percolate_Down(h,max);
    }
}

int Delete_Max(Heap *h)
{

    int data;
    if( (*h)->count == 0 ) return -1;
    data = (*h)->array[0];
    (*h)->array[0] = (*h)->array[(*h)->count-1];
    (*h)->count--;
    Percolate_Down(h,0);
    return data;
}

void Resize_Heap(Heap *h)
{

    int i;
    int *array_old = (*h)->array;
    (*h)->array = (int *)malloc(sizeof(int)*(*h)->capacity*2);
    if(! (*h)->array) return;
    for( i = 0 ; i <= (*h)->capacity ; i++ )
        (*h)->array[i] = array_old[i];
    (*h)->capacity *= 2;
    free(array_old);
}

int Insert(Heap *h,int data)
{

    int i;
    if( (*h)->count == (*h)->capacity ) Resize_Heap(h);
    (*h)->count++;
    i = (*h)->count - 1;
    while( i > 0 && data > (*h)->array[(i-1)/2] )
    {
        (*h)->array[i] = (*h)->array[(i-1)/2];
        i = (i-1)/2;
    }
    (*h)->array[i] = data;
}

void Destroy_Heap(Heap *h)
{

    if( h == NULL ) return;
    free( (*h)->array );
    free(h);
    h = NULL;
}

void Build_Heap(Heap *h,int A[],int n)
{

    int i;
    if( h == NULL ) return;
    while( n > (*h)->capacity ) Resize_Heap(h);
    for( i = 0 ; i < n ; i++ ) (*h)->array[i] = A[i];
    (*h)->count = n;
    for( i = (n-1)/2 ; i >= 0 ; i-- ) Percolate_Down(h,i);
}

void Print_Heap( Heap root )
{

    int i,level = 2,count = 2,l=0,etap = 1,temp = 0,one = 0;
    int d = root->count/2,r = root->count%2;
    one = d+r;
    for( i = 0 ; i < root->count ; i++ )
    {
        temp = etap;
        l = (root->count/2)+1;
        if( i == 0 )
        {
            while(one--) printf("   ");
            printf("%d",root->array[i]);
            putchar('\n');
            putchar('\n');
        }
        else
        {
            while(temp--) l /=1.5 ;
            while(l--) printf("   ");
            printf("%d",root->array[i]);
            if( i == count )
            {
                putchar('\n');
                putchar('\n');
                level *= 2;
                count += level;
                etap++;
            }
        }
    }
}

/*----------------------------------------------*/

void Heap_Sort(int A[],int n)
{

    Heap h = Create_Heap(n,1);
    int old_size,i,temp;
    Build_Heap(&h,A,n);
    old_size = h->count;
    for( i = n-1 ; i >= 0 ; i-- )
    {
        temp = h->array[0];
        h->array[0] = h->array[h->count-1];
        h->array[h->count-1] = temp;
        h->count--;
        Percolate_Down(&h,0);
    }
    h->count = old_size;
    for( i = 0 ; i < h->count ; i++ )
        A[i] = h->array[i];
}

/*----------------------------------------------*/

void Print_Development(Heap B)
{

    int i,j = -1,count = 1,first = 1;
    while(1)
    {
        i = Max_Heap(B);
        if(i==-1)
        {
            if(count > 1) printf("^%d",count);
            break;
        }
        Delete_Max(&B);
        if(first == 1) printf("%d",i);
        first++;
        if(first > 2)
        {
            if( i == j ) count++;
            else
            {
                if(count > 1)
                {
                    printf("^%d",count);
                    printf(" x %d",i);
                    count = 1;
                }
                else printf(" x %d",i);
            }
        }
        j = i;
    }
}

/*----------------------------------------------*/

// Question 1 :

double log2(double x){

    return log10(x)/log10(2);
}

int IsOnMinLevel(Heap H,int i){

    int level = 0;
    double x = i;
    if( i < 0 || i > H->count ) return 0;
    level = (int)log2(x+1);
    if(level%2) return 0;
    return 1;
}

// Question 2 :

void PercolateDownMin(Heap *h,int i){

    if( !(*h) || i < 0 || i > (*h)->count ) return;
    int m,l,l1,l2,r,r1,r2,min,temp,grand = 0;
    l = Left_Child(*h,i);
    r = Right_Child(*h,i);
    if( l == -1 ) return;
    if( r == -1 ){
        l1 = Left_Child(*h,l);
        r1 = Right_Child(*h,l);
        if( l1 != -1 && (*h)->array[l1] < (*h)->array[l] ) {
                min = l1;
                grand = 1;
        }
        else min = l;
        if( r1 != -1 && (*h)->array[r1] < (*h)->array[min] ) {
                min = r1;
                grand = 1;
        }
    }
    else{
        l1 = Left_Child(*h,l);
        r1 = Right_Child(*h,l);
        l2 = Left_Child(*h,r);
        r2 = Right_Child(*h,r);
        if( (*h)->array[l] < (*h)->array[r] ) min = l;
        else min = r;
        if( l1 != -1 && (*h)->array[l1] < (*h)->array[min] ){
                min = l1;
                grand = 1;
        }
        if( r1 != -1 && (*h)->array[r1] < (*h)->array[min] ){
                min = r1;
                grand = 1;
        }
        if( l2 != -1 && (*h)->array[l2] < (*h)->array[min] ){
                min = l2;
                grand = 1;
        }
        if( r2 != -1 && (*h)->array[r2] < (*h)->array[min] ){
                min = r2;
                grand = 1;
        }
    }
    m = min;
    if( (*h)->array[m] < (*h)->array[i] ){
        temp = (*h)->array[m];
        (*h)->array[m] = (*h)->array[i];
        (*h)->array[i] = temp;
    }
    if(grand){
        if( (*h)->array[m] > (*h)->array[Parent(*h,m)] ){
            temp = (*h)->array[m];
            (*h)->array[m] = (*h)->array[Parent(*h,m)];
            (*h)->array[Parent(*h,m)] = temp;
        }
    }
    PercolateDownMin(h,m);
}

void PercolateDownMax(Heap *h,int i){

    if( !(*h) || i < 0 || i > (*h)->count ) return;
    int m,l,l1,l2,r,r1,r2,max,temp,grand = 0;
    l = Left_Child(*h,i);
    r = Right_Child(*h,i);
    if( l == -1 ) return;
    if( r == -1 ){
        l1 = Left_Child(*h,l);
        r1 = Right_Child(*h,l);
        if( l1 != -1 && (*h)->array[l1] > (*h)->array[l] ) {
                max = l1;
                grand = 1;
        }
        else max = l;
        if( r1 != -1 && (*h)->array[r1] > (*h)->array[max] ) {
                max = r1;
                grand = 1;
        }
    }
    else{
        l1 = Left_Child(*h,l);
        r1 = Right_Child(*h,l);
        l2 = Left_Child(*h,r);
        r2 = Right_Child(*h,r);
        if( (*h)->array[l] > (*h)->array[r] ) max = l;
        else max = r;
        if( l1 != -1 && (*h)->array[l1] > (*h)->array[max] ){
                max = l1;
                grand = 1;
        }
        if( r1 != -1 && (*h)->array[r1] > (*h)->array[max] ){
                max = r1;
                grand = 1;
        }
        if( l2 != -1 && (*h)->array[l2] > (*h)->array[max] ){
                max = l2;
                grand = 1;
        }
        if( r2 != -1 && (*h)->array[r2] > (*h)->array[max] ){
                max = r2;
                grand = 1;
        }
    }
    m = max;
    if( (*h)->array[m] > (*h)->array[i] ){
        temp = (*h)->array[m];
        (*h)->array[m] = (*h)->array[i];
        (*h)->array[i] = temp;
    }
    if(grand){
        if( (*h)->array[m] < (*h)->array[Parent(*h,m)] ){
            temp = (*h)->array[m];
            (*h)->array[m] = (*h)->array[Parent(*h,m)];
            (*h)->array[Parent(*h,m)] = temp;
        }
    }
    PercolateDownMax(h,m);
}

void PercolateDown(Heap *h,int i){

    if(IsOnMinLevel(*h,i)) PercolateDownMin(h,i);
    else PercolateDownMax(h,i);
}

// Question 3 :

void BuildHeap(Heap *h,int A[],int n){

    int i;
    if( !(*h) ) return;
    while( n > (*h)->capacity ) Resize_Heap(h);
    for( i = 0 ; i < n ; i++ ) (*h)->array[i] = A[i];
    (*h)->count = n;
    for( i = (n-1)/2 ; i >= 0 ; i-- ) PercolateDown(h,i);
}

// Question 4 :

int DeleteMax(Heap *h){

    int data,l,r,max = 0;
    if( !(*h) ) return -1;
    l = Left_Child(*h,0);
    r = Right_Child(*h,0);
    if( l != -1 ) max = l;
    if( r != -1 && (*h)->array[r] > (*h)->array[l] ) max = r;
    data = (*h)->array[max];
    (*h)->array[max] = (*h)->array[(*h)->count-1];
    (*h)->count--;
    Percolate_Down(h,max);
    return data;
}

// Question 5 :

int DeleteMin(Heap *h){

    int data;
    if( !(*h)) return -1;
    data = (*h)->array[0];
    (*h)->array[0] = (*h)->array[(*h)->count-1];
    (*h)->count--;
    PercolateDown(h,0);
    return data;
}

// Question 6 :

void HeapSort(int A[],int n){

    Heap h = Create_Heap(n,1);
    int old_size,i,temp;
    BuildHeap(&h,A,n);
    old_size = h->count;
    for( i = n-1 ; i >= 0 ; i-- )
    {
        temp = h->array[0];
        h->array[0] = h->array[h->count-1];
        h->array[h->count-1] = temp;
        h->count--;
        PercolateDown(&h,0);
    }
    h->count = old_size;
    for( i = 0 ; i < h->count ; i++ )
        A[i] = h->array[h->count-1-i];
}

int main()
{
    printf("Hello world!\n");
    return 0;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void Bubble_Sort(int A[],int n)
{

    int pass,i,temp,swapped = 1;
    for( pass = n-1 ; pass >= 0 && swapped ; pass-- )
    {

        swapped = 0;
        for( i = 0 ; i < pass ; i++ )
            if( A[i] > A[i+1] )
            {
                temp = A[i];
                A[i] = A[i+1];
                A[i+1] = temp;
                swapped = 1;
            }
    }
}

/*----------------------------------------------*/

void Selection_Sort(int A[],int n)
{

    int i,j,min,temp;
    for( i = 0 ; i < n-1 ; i++ )
    {

        min = i;
        for( j = i+1 ; j < n ; j++ )
            if( A[j] < A[min] )
                min = j;

        if( min != i )
        {
            temp = A[i];
            A[i] = A[min];
            A[min] = temp;
        }
    }
}

/*----------------------------------------------*/

void Insertion_Sort(int A[],int n)
{

    int i,j,v;
    for( i = 1 ; i <= n-1 ; i++ )
    {

        v = A[i];
        j = i;
        while( A[j-1] > v && j > 0 )
        {
            A[j] = A[j-1];
            j--;
        }
        A[j] = v;
    }
}

/*----------------------------------------------*/

int Partition(int A[],int low,int high)
{

    int left,right,pivot_item = A[low],temp;
    left = low + 1;
    right = high;
    while( left <= right )
    {
        while( A[left] <= pivot_item && left <= right ) left++;
        while( A[right] > pivot_item && left <= right ) right--;
        if( left < right )
        {
            temp = A[left];
            A[left] = A[right];
            A[right] = temp;
            left++;
            right--;
        }
    }
    A[low] = A[right];
    A[right] = pivot_item;
    return right;
}

void Sort1(int A[],int low,int high)
{

    int pivot;
    if( high > low )
    {
        pivot = Partition(A,low,high);
        Sort1(A,low,pivot-1);
        Sort1(A,pivot+1,high);
    }
}

void Quick_Sort(int A[],int n)
{

    Sort1(A,0,n-1);
}

/*----------------------------------------------*/

void Fusion(int A[],int lower,int upper,int middle)
{

    int i = lower,j = middle+1,k = 0,c[upper-lower+1];
    while( i <= middle && j <= upper )
    {
        if( A[i] < A[j] ) c[k++] = A[i++];
        else c[k++] = A[j++];
    }
    while( i <= middle ) c[k++] = A[i++];
    while( j <= upper ) c[k++] = A[j++];
    for( i = lower, j = 0 ; j < k ; i++, j++ ) A[i] = c[j];
}

void Sort2(int A[],int lower,int upper)
{

    int middle;
    if( lower < upper )
    {
        middle = ( lower + upper )/2;
        Sort2(A,lower,middle);
        Sort2(A,middle+1,upper);
        Fusion(A,lower,upper,middle);
    }
}

void Merge_Sort(int A[],int n)
{

    Sort2(A,0,n-1);
}

int main()
{
    printf("Hello world!\n");
    return 0;
}

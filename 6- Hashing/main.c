#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef int element;

typedef element Hash[13];

int HF(  int k , int N ){

    return ( k % N );
}

int insert( Hash h , element val , int N ){

    int index = HF( val , N ),result = 0,temp;
    if( N < 1 ) return 0;
    if( h[index] == -1 ) h[index] = val;
    else{
        for( int i = index ; i < N ; i++ ){
            if( h[i] == -1 ){
                    h[i] = val;
                    result = 1;
                    break;
            }
            if( h[i] > val && HF(h[i],N) == index ){
                temp = h[i];
                h[i] = val;
                result = 1;
                insert(h,temp,N);
                break;
            }
        }
        if( result == 0 ){
                for( int i = 0 ; i < index ; i++ ){
                    if( h[i] == -1 ){
                        h[i] = val;
                        break;
                    }
                    if( h[i] > val && HF(h[i],N) == index ){
                        temp = h[i];
                        h[i] = val;
                        insert(h,temp,N);
                        break;
                    }
                }
        }
    }
    return 1;
}

int deleteHash( Hash h , element val , int N ){

    int index = HF(val,N),pos,i,comp = -1;
    if( N < 1 ) return 0;
    if( h[index] == val ){
            h[index] = -1;
            pos = index;
    }
    else {
            pos = index+1;
            while(1){
                if( HF(h[pos],N) < index ) return;
                if( h[pos] == val ){
                        h[pos] = -1;
                        break;
                }
                pos = (pos+1)%N;
            }
    }
    i = pos + 1;
    while( h[i] != -1 ){
        if( HF(h[i],N) == i ) comp = i;
        if( HF(h[i],N) != i && HF(h[i],N) != comp ){
            h[pos] = h[i];
            h[i] = -1;
            pos = i;
        }
        i = (i+1)%N;
    }
}

int main(){

    Hash H;
    for( int i = 0 ; i < 13 ; i++ )
            H[i] = -1;
    insert(H,5,13);
    insert(H,6,13);
    insert(H,9,13);
    insert(H,35,13);
    insert(H,22,13);
    insert(H,14,13);
    insert(H,1,13);
    insert(H,11,13);
    insert(H,48,13);
    insert(H,10,13);
    printf("\n  ******* HASH TABLE *******\n");
    for( int i = 0 ; i < 13 ; i++ ){
        printf("  %d",i);
        if( H[i] != -1 ) printf(" : data = %d , HF = %d",H[i],HF(H[i],13));
        putchar('\n');
    }
    printf("\nAfter Delete : 1");
    printf("\n  *******  END HASH TABLE *******\n");
    deleteHash(H,1,13);
    printf("\n  ******* HASH TABLE *******\n");
    printf("\nAfter Delete : 9 \n\n");
    deleteHash(H,9,13);
    for( int i = 0 ; i < 13 ; i++ ){
        printf("  %d",i);
        if( H[i] != -1 ) printf(" : data = %d",H[i]);
        putchar('\n');
    }
    printf("\n\n  *******  END HASH TABLE *******\n\n");
    return 0;
}

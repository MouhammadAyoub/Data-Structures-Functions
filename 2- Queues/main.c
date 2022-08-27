#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define N 50


typedef struct
{
    element data[N];
    int front,rear;
} queue;

int isEmptyQueue(queue q)
{

    return (q.front == (q.rear + 1)%N);
}

int isFullQueue(queue q)
{

    return (q.front == (q.rear + 2)%N);
}

queue CreateQueue()
{

    queue q;
    q.front = 1;
    q.rear = 0;
    return q;
}

int EnQueue(queue *q,element e)
{

    if(isFullQueue(*q)) return 0;
    q->rear = (q->rear + 1) % N;
    q->data[q->rear] = e;
    return 1;
}

int DeQueue(queue *q)
{

    if(isEmptyQueue(*q)) return 0;
    q->front = (q->front + 1) % N;
    return 1;
}

int Front(queue q,element *e)
{

    if(isEmptyQueue(q)) return 0;
    *e = q.data[q.front];
    return 1;
}

void Display_Queue(queue q)
{

    element e;
    while(Front(q,&e))
    {
        printf("%d\t",e);
        DeQueue(&q);
    }
}

void Sort_Queue(queue *q){

    element e;
    stack s = CreateStack();
    queue aux = CreateQueue();
    while(Front(*q,&e)){
        DeQueue(q);
        if(e%2)Push(&s,e);
        else EnQueue(&aux,e);
    }
    while(Front(aux,&e)){
        DeQueue(&aux);
        EnQueue(q,e);
    }
    while(Top(s,&e)){
        Pop(&s);
        EnQueue(q,e);
    }
}

void Reverse_Queue(queue *q){

    element e;
    stack s = CreateStack();
    while(Front(*q,&e)){
        DeQueue(q);
        Push(&s,e);
    }
    while(Top(s,&e)){
        Pop(&s);
        EnQueue(q,e);
    }
}

void Add_From_Stack(queue *q,stack s){

    element e;
    while(Top(s,&e)){
        Pop(&s);
        EnQueue(q,e);
    }
}

void Add_From_Queue(stack *s,queue q){

    element e;
    while(Front(q,&e)){
        DeQueue(&q);
        Push(s,e);
    }
}

void Add_Reverse_Stack(stack *s1,stack s2){

    element e;
    queue q = CreateQueue();
    while(Top(*s1,&e)){
        Pop(s1);
        EnQueue(&q,e);
    }
    while(Front(q,&e)){
        DeQueue(&q);
        Push(s1,e);
    }
    while(Top(s2,&e)){
        Pop(&s2);
        Push(s1,e);
    }
}

void Reverse_Stack(stack *s1){

    element e;
    queue q = CreateQueue();
    while(Top(*s1,&e)){
        Pop(s1);
        EnQueue(&q,e);
    }
    while(Front(q,&e)){
        DeQueue(&q);
        Push(s1,e);
    }
}

void insert(stack *s, int x) {

    element e;
    if (Top(*s,&e)){

        int y = e;
        if (x > y){
            Pop(s);
            insert(s,x);
            Push(s, y);
        }
        else Push(s,x);
    }
    else Push(s,x);
}

void sort(stack *s) {

    element e;
    if (Top(*s,&e)){
        Pop(s);
        int x = e ;
        sort(s);
        insert(s,x);
    }
}

void Sort_Queue1(queue *q){

    element e;
    stack s = CreateStack();
    while(Front(*q,&e)){
        DeQueue(q);
        Push(&s,e);
    }
    sort(&s);
    while(Top(s,&e)){
        Pop(&s);
        EnQueue(q,e);
    }
}

int main(){

    queue s = CreateQueue();
    EnQueue(&s,6);
    EnQueue(&s,9);
    EnQueue(&s,1);
    EnQueue(&s,4);
    EnQueue(&s,7);
    EnQueue(&s,11);
    EnQueue(&s,5);
    EnQueue(&s,8);
    printf("\n Avant :  ");
    Display_Queue(s);
    printf("\n\n Apres :  ");
    Sort_Queue1(&s);
    Display_Queue(s);
    putchar('\n');
    putchar('\n');
    return 0;
}

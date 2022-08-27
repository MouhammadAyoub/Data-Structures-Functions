#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define N 20

typedef int element;

// Static implementation of Stack :

typedef struct{

    element data[N];
    int top;
}Stack;

Stack CreateStack(){

    Stack p;
    p.top = -1;
    return p;
}

int isEmptyStack(Stack p){

    return (p.top == -1);
}

int isFullStack(Stack p){

    return (p.top == N-1);
}

int Push(Stack *p,element e){

    if( isFullStack(*p) ) return 0;
    p->data[++p->top] = e;
    return 1;
}

int Pop(Stack *p){

    if( isFullStack(*p) ) return 0;
    p->top--;
    return 1;
}

int Top(Stack p,element *e){

    if( isEmptyStack(p) ) return 0;
    *e = p.data[p.top];
    return 1;
}

// Print a Stack :

void PrintStack(Stack P){

    element e;
    int max = 0;
    Stack P1 = CreateStack();
    if(isEmptyStack(P)) return;
    while(Top(P,&e)){
        if( max < e ) max = e;
        Push(&P1,e);
        Pop(&P);
    }
    if(max/10) max = 1;
    else max = 0;
    while(Top(P1,&e)){
        Push(&P,e);
        Pop(&P1);
    }
    putchar('\n');
    while(Top(P,&e)){
        if(max) {
                if(e/10) printf("                   | %d |\n",e);
                else printf("                   | %d  |\n",e);
        }
        else printf("                   | %d |\n",e);
        Pop(&P);
    }
    if(max) printf("                   |____|\n\n\n");
    else printf("                   |___|\n\n\n");
    return;
}

/*----------------------------------------------------*/

// Static implementation of Queue :

typedef struct{

    element data[N];
    int front,rear;
} Queue;


int isEmptyQueue(Queue q){

    return (q.front == (q.rear + 1)%N);
}

int isFullQueue(Queue q){

    return (q.front == (q.rear + 2)%N);
}

Queue CreateQueue(){

    Queue q;
    q.front = 1;
    q.rear = 0;
    return q;
}

int EnQueue(Queue *q,element e){

    if(isFullQueue(*q)) return 0;
    q->rear = (q->rear + 1) % N;
    q->data[q->rear] = e;
    return 1;
}

int DeQueue(Queue *q){

    if(isEmptyQueue(*q)) return 0;
    q->front = (q->front + 1) % N;
    return 1;
}

int Front(Queue q,element *e){

    if(isEmptyQueue(q)) return 0;
    *e = q.data[q.front];
    return 1;
}

// Print a Queue :

void PrintQueue(Queue Q){

    element e;
    Queue Q1 = CreateQueue();
    int count1 = 0,count2 = 0;
    while(Front(Q,&e)){
        count1++;
        EnQueue(&Q1,e);
        DeQueue(&Q);
    }
    count2 = count1;
    printf("\n        ");
    while(count1--) printf("-----");
    printf("\n       ");
    while(Front(Q1,&e)){
        printf("   %d ",e);
        DeQueue(&Q1);
    }
    printf("\n        ");
    while(count2--) printf("-----");
    putchar('\n');
    return;
}

/*----------------------------------------------------*/

// Implementation of Graph :

// Adjacency Matrix :

typedef struct {

    int V;
    int E;
    int **Adj;
} Graph;

Graph* adjacencyMatrix(){

    int i,u,v;
    Graph* G = (Graph *)malloc(sizeof(Graph));
    printf("\nEntre the numbre of Vertices : ");
    scanf("%d",&G->V);
    printf("\nEntre the numbre of Edges : ");
    scanf("%d",&G->E);
    G->Adj = (int **)malloc(G->V * sizeof(int*));
    for( u = 0 ; u < G->V ; u++ )
        G->Adj[u] = (int *)malloc(G->V * sizeof(int));
    for( u = 0 ; u < G->V ; u++ )
        for( v = 0 ; v < G->V ; v++ )
            G->Adj[u][v] = 0;
    for( i = 0 ; i < G->E ; i++ ){
        printf("\nEntre the edge : ");
        scanf("%d %d",&u,&v);
        G->Adj[u][v] = 1;
    }
    return G;
}

//Recursive DFS Matrix :

void DFSTraversal(Graph *G,int index,int Visited[]){

    int v;
    printf("%d ",index);;
    for( v = 0 ; v < G->V ; v++ )
        if( !Visited[v] && G->Adj[index][v] ){
            Visited[v] = 1;
            DFSTraversal(G,v,Visited);
        }
}

void DFS(Graph *G){

    int i,*Visited = (int *)malloc(sizeof(int)*G->V);
    for( i = 0 ; i < G->V ; i++ )
        Visited[i] = 0;
    for( i = 0 ; i < G->V ; i++ )
        if(!Visited[i]){
            Visited[i] = 1;
            DFSTraversal(G,i,Visited);
        }
}

//Iterative BFS Matrix :

void BFSTraversal(Graph *G,int u,int Visited[]){

    Queue q = CreateQueue();
    int v,w;
    EnQueue(&q,u);
    Visited[u] = 1;
    while(Front(q,&v)){
        DeQueue(&q);
        printf("%d ",v);
        for( w = 0 ; w < G->V ; w++ ){
            if(!Visited[w] && G->Adj[v][w]){
                Visited[w] = 1;
                EnQueue(&q,w);
            }
        }
    }
}

void BFS(Graph *G){

    int i,*Visited = (int *)malloc(sizeof(int)*G->V);
    for( i = 0 ; i < G->V ; i++ )
        Visited[i] = 0;
    for( i = 0 ; i < G->V ; i++ )
        if(!Visited[i])
            BFSTraversal(G,i,Visited);

}

// Adjacency List :

typedef struct node {

    int vertexNumber;
    struct node *next;
} node;

typedef struct {

    int V;
    int E;
    node **Adj;
} Graph1;

Graph1* adjacencyList(){

    int i,x,y;
    node *temp,*temp2;
    Graph1* G = (Graph1 *)malloc(sizeof(Graph1));
    printf("\nEntre the numbre of Vertices : ");
    scanf("%d",&G->V);
    printf("\nEntre the numbre of Edges : ");
    scanf("%d",&G->E);
    G->Adj = (node **)malloc(G->V * sizeof(node *));
    for( i = 0 ; i < G->V ; i++ ){
        G->Adj[i] = (node *)malloc(G->V * sizeof(node));
        G->Adj[i]->vertexNumber = i;
        G->Adj[i]->next = NULL;
    }
    for( i = 0 ; i < G->E ; i++ ){
        printf("\nEntre the edge : ");
        scanf("%d %d",&x,&y);
        temp = (node *)malloc(sizeof(node));
        temp->vertexNumber = y;
        temp->next = NULL;
        temp2 = G->Adj[x];
        while(temp2->next)
            temp2 = temp2->next;
        temp2->next = temp;
    }
    return G;
}

//Recursive DFS List :

void DFSTraversal1(Graph1 *G,int index,int Visited[]){

    node *head = G->Adj[index]->next;
    printf("%d ",index);
    while(head){
        if(!Visited[head->vertexNumber]){
            Visited[head->vertexNumber] = 1;
            DFSTraversal1(G,head->vertexNumber,Visited);
        }
        head = head->next;
    }
}

void DFS1(Graph1 *G){

    int i,*Visited = (int *)malloc(sizeof(int)*G->V);
    for( i = 0 ; i < G->V ; i++ )
        Visited[i] = 0;
    for( i = 0 ; i < G->V ; i++ )
        if(!Visited[i]){
            Visited[i] = 1;
            DFSTraversal1(G,i,Visited);
        }
}

//Iterative DFS List :

void DFSTraversal2(Graph1 *G,int index,int Visited[]){

    Stack s = CreateStack();
    element e;
    node *head;
    Push(&s,index);
    Visited[index] = 1;
    while(Top(s,&e)){
        Pop(&s);
        printf("%d ",e);
        head = G->Adj[e]->next;
        while(head){
            if(!Visited[head->vertexNumber]){
                Visited[head->vertexNumber] = 1;
                Push(&s,head->vertexNumber);
            }
            head = head->next;
        }
    }
}

void DFS2(Graph1 *G){

    int i,*Visited = (int *)malloc(sizeof(int)*G->V);
    for( i = 0 ; i < G->V ; i++ )
        Visited[i] = 0;
    for( i = 0 ; i < G->V ; i++ )
        if(!Visited[i])
            DFSTraversal2(G,i,Visited);

}

//Iterative BFS List :

void BFSTraversal1(Graph1 *G,int index,int Visited[]){

    Queue q = CreateQueue();
    element e;
    node *head;
    EnQueue(&q,index);
    Visited[index] = 1;
    while(Front(q,&e)){
        DeQueue(&q);
        printf("%d ",e);
        head = G->Adj[e]->next;
        while(head){
            if(!Visited[head->vertexNumber]){
                Visited[head->vertexNumber] = 1;
                EnQueue(&q,head->vertexNumber);
            }
            head = head->next;
        }
    }
}

void BFS1(Graph1 *G){

    int i,*Visited = (int *)malloc(sizeof(int)*G->V);
    for( i = 0 ; i < G->V ; i++ )
        Visited[i] = 0;
    for( i = 0 ; i < G->V ; i++ )
        if(!Visited[i])
            BFSTraversal1(G,i,Visited);

}

/*---------------------------------------------------------*/

//Exercices :

int path(Graph *G,int source,int destination){

    int i,*Visited = (int *)malloc(G->V*sizeof(int));
    for( i = 0 ; i < G->V ; i++ )
        Visited[i] = 0;
    Visited[source] = 1;
    DFSTraversal(G,source,Visited);
    return Visited[destination];
}

int connected(Graph *G){

    int i,*Visited = (int *)malloc(sizeof(int)*G->V);
    for( i = 0 ; i < G->V ; i++ )
        Visited[i] = 0;
    Visited[0] = 1;
    DFSTraversal(G,0,Visited);
    for( i = 0 ; i < G->V ; i++ )
        if(!Visited[i]) return 0;
    return 1;
}

void topologicalSort(Graph *G){ //Matrix BFS

    Queue q = CreateQueue(),topologicalorder = CreateQueue();
    int counter = 0,v, w, *indegree = (int *)malloc(sizeof(int)*G->V);
    for( v = 0 ; v < G->V ; v++ )
        indegree[v] = 0;
    for( v = 0 ; v < G->V ; v++ )
        for( w = 0 ; w < G->V ; w++ )
            if(G->Adj[v][w] == 1)
                indegree++;
    for( v = 0 ; v < G->V ; v++ )
        if(indegree[v] == 0) EnQueue(&q,v);
    while(Front(q,&v)){
        DeQueue(&q);
        counter++;
        EnQueue(&topologicalorder,v);
        for( w = 0 ; w < G->V ; w++ )
            if( G->Adj[v][w] == 1)
                if(--indegree == 0) EnQueue(&q,w);
    }
    if(counter != G->V) printf("\n Graph has cycle !\n");
    while(Front(topologicalorder,&v) && DeQueue(&topologicalorder))
            printf("%d ",v);
}


void topologicalSort1(Graph1 *G){ //List BFS

    Queue q = CreateQueue(),topologicalorder = CreateQueue();
    int counter = 0,v, w, *indegree = (int *)malloc(sizeof(int)*G->V);
    node *head;
    for( v = 0 ; v < G->V ; v++ )
        indegree[v] = 0;
    for( v = 0 ; v < G->V ; v++ ){
        head = G->Adj[v]->next;
        while(head){
            indegree[head->vertexNumber]++;
            head = head->next;
        }
    }
    for( v = 0 ; v < G->V ; v++ )
        if(indegree[v] == 0) EnQueue(&q,v);
    while(Front(q,&v)){
        DeQueue(&q);
        counter++;
        EnQueue(&topologicalorder,v);
        head = G->Adj[v]->next;
        while(head){
            if(--indegree[head->vertexNumber]==0)
                EnQueue(&q,head->vertexNumber);
            head = head->next;
        }
    }
    if(counter != G->V) printf("\n Graph has cycle !\n");
    while(Front(topologicalorder,&v) && DeQueue(&topologicalorder))
            printf("%d ",v);
}

void topological_helper(Graph1 *G,int index,int Visited[],Stack *s){ //List DFS

    node *head = G->Adj[index]->next;
    while(head){
        if(!Visited[head->vertexNumber]){
            Visited[head->vertexNumber] = 1;
            topological_helper(G,head->vertexNumber,Visited,s);
        }
        head = head->next;
    }
    Push(s,index);
}

void topological(Graph1 *G){

    Stack s = CreateStack();
    int i,*Visited = (int *)malloc(G->V*sizeof(int));
    element e;
    for( i = 0 ; i < G->V ; i++ )
        Visited[i] = 0;
    for( i = 0 ; i < G->V ; i++ )
        if(!Visited[i])
            topological_helper(G,i,Visited,&s);
    while(Top(s,&e) && Pop(&s) && printf("%d ",e) );
}

// Algorithm :

void BellmanFord(Graph *G,int s){

    Queue q = CreateQueue();
    int *distance,*Path,*inqueue,i,v,w,dist;

    Path = (int*)malloc(sizeof(int)*G->V);
    inqueue = (int*)malloc(sizeof(int)*G->V);
    distance = (int*)malloc(sizeof(int)*G->V);

    for( i = 0 ; i < G->V ; i++ ){
        inqueue[i] = 0;
        distance[i] = INT_MAX;
    }

    EnQueue(&q,s);
    distance[s] = 0;
    inqueue[s] = 0;

    while(Front(q,&v)){

        DeQueue(&q);
        for( w = 0 ; w < G->V ; w++ )
            if(G->Adj[v][w] != 0){
                dist = distance[v]+G->Adj[v][w];
                if( dist < distance[w]){
                    distance[w] = dist;
                    Path[w] = v;
                    if(!inqueue[w]){
                        inqueue[w] = 1;
                        EnQueue(&q,w);
                    }
                }
            }

    }
    for( v = 0 ; v < G->V ; v++ )
        printf("%d shoud be reached from %d of total weight %d \n",v,Path[v],distance[v]);
}

void Dijkstra(Graph *G,int s){

    Queue q = CreateQueue();
    int *distance,*Path,i,v,w,dist;

    Path = (int*)malloc(sizeof(int)*G->V);
    distance = (int*)malloc(sizeof(int)*G->V);

    for( i = 0 ; i < G->V ; i++ )
        distance[i] = -1;


    //EnQueue(&q,s,0);
    distance[s] = 0;

    while(Front(q,&v)){

        DeQueue(&q);
        for( w = 0 ; w < G->V ; w++ )
            if(G->Adj[v][w]){
                dist = distance[v] + G->Adj[v][w];
                if( distance[w] == -1){
                    distance[w] = dist;
                    //EnQueue(&q,w,dist);
                    Path[w] = v;
                }
                else
                if(dist < distance[w]){
                    distance[w] = dist;
                    //update_priority(&q,w,dist);
                    Path[w] = v;
                }
            }

    }
    for( v = 0 ; v < G->V ; v++ )
        printf("%d shoud be reached from %d of total weight %d \n",v,Path[v],distance[v]);
}

/*
typedef struct{

    int u,v,w;
}edge;

typedef edge element;

*/

void Prim(Graph *G,int s){

    Queue q = CreateQueue();
    int *U,i,j;
    element *T,v;

    U = (int*)malloc(sizeof(int)*G->V);
    T = (element *)malloc(sizeof(element)*(G->V -1));

    for( i = 0 ; i < G->V ; i++ ){
        U[i] = 0;
        for( j = 0 ; j < G->V ; j++ )
            if(G->Adj[i][j])
            //EnQueue(&q,(element){i,j,G->Adj[i][j]},G->Adj[i][j]);
    }
    U[s] = 1;
    j = 0;
    for( i = 0 ; i < G->V - 1 ; i++ ){
        while(Front(q,&v) && DeQueue(&q))
            if(U[v.u] && !U[v.v]){
                U[v.v] = 1;
                T[j++] = v;
                break;
            }
    }

     for( i = 0 ; i < G->V - 1 ; i++ )
        printf("Edge: %d - %d weight %d\n",T[i].u,T[i].v,T[i].w);
}

// Short Path :

void UnweightedShortestPath(Graph *G,int s){ //Matrix

    Queue q = CreateQueue();
    int v,w,*distance = (int *)malloc(G->V*sizeof(int));
    int *Path = (int *)malloc(G->V*sizeof(int));
    for( v = 0 ; v < G->V ; v++ )
        distance[v] = -1;
    EnQueue(&q,s);
    distance[s] = 0;
    while(Front(q,&v)){
        DeQueue(&q);
        for( w = 0 ; w < G->V ; w++ )
            if(G->Adj[v][w] == 1)
                if(distance[w] == -1){
                    distance[w] = distance[v] + 1;
                    Path[w] = v;
                    EnQueue(&q,w);
                }
        for( v = 0 ; v < G->V ; v++ )
            printf("%d should pass by %d\n",v,Path[v]);
    }
}

void UnweightedShortestPath1(Graph1 *G,int s){ //List

    Queue q = CreateQueue();
    int v,w,*distance = (int *)malloc(G->V*sizeof(int));
    int *Path = (int *)malloc(G->V*sizeof(int));
    node *head;
    for( v = 0 ; v < G->V ; v++ )
        distance[v] = -1;
    EnQueue(&q,s);
    distance[s] = 0;
    while(Front(q,&v)){
        DeQueue(&q);
        head = G->Adj[v]->next;
        while(head){
            if(distance[head->vertexNumber] == -1){
                distance[head->vertexNumber] = distance[v] + 1;
                Path[head->vertexNumber] = v;
                EnQueue(&q,head->vertexNumber);
            }
            head = head->next;
        }
        for( v = 0 ; v < G->V ; v++ )
            printf("%d should pass by %d\n",v,Path[v]);
    }
}

int main(){

    Graph *G = adjacencyMatrix();
    DFS(G);
    return 0;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define N 50

int max(int x,int y)
{

    if(x>y) return x;
    return y;
}

//Implementation Stack :

typedef int element;
typedef struct
{
    element donnee[N];
    int tete;
} stack;


int isEmptyStack(stack p)
{

    return (p.tete == -1);
}

int isFullStack(stack p)
{

    return (p.tete == (N-1));
}

stack CreateStack()
{

    stack p;
    p.tete = -1;
    return p;
}

int Push(stack *p,element e)
{

    if(isFullStack(*p)) return 0;
    p->donnee[++p->tete] = e;
    return 1;
}

int Pop(stack *p)
{

    if(isEmptyStack(*p)) return 0;
    p->tete--;
    return 1;
}

int Top(stack p,element *e)
{

    if(isEmptyStack(p)) return 0;
    *e = p.donnee[p.tete];
    return 1;
}

void Print_Stack(stack p)
{

    element e;
    while(Top(p,&e))
    {
        Pop(&p);
        printf("%d\t",e);
    }
}

//Implementation Queue :

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

//Implementation BTree :

typedef struct node
{

    element data;
    struct node *left, *right;
} *Btree;

int isEmpty_Btree(Btree B)
{

    return (B == NULL);
}

Btree Create_Btree()
{

    return NULL;
}

Btree Construct (element e, Btree G, Btree D)
{

    Btree temp;
    temp = (Btree)malloc(sizeof(struct node));
    if(!temp) return 0;
    temp->data = e;
    temp->left = G;
    temp->right = D;
    return temp;
}

int Root(Btree B,element *e)
{

    if(isEmpty_Btree(B)) return 0;
    *e = B->data;
    return 1;
}

int Right(Btree B,element *R)
{

    if(isEmpty_Btree(B)) return 0;
    *R = B->right;
    return 1;
}

int Left(Btree B,element *L)
{

    if(isEmpty_Btree(B)) return 0;
    *L = B->left;
    return 1;
}

void Print_BTree( struct node *root, int level )
{

    if ( root == NULL )
    {
        for (int i = 0; i < level; i++ ) putchar('\t');
        puts("~");
    }
    else
    {
        Print_BTree(root->right,level+1);
        for (int i = 0; i < level; i++ ) putchar('\t');
        printf("%d\n",root->data);
        Print_BTree(root->left,level+1);
    }
}

void PreorderR(Btree B)
{

    if(B)
    {
        printf("%d ",B->data);
        PreorderR(B->left);
        PreorderR(B->right);
    }
}

void InorderR(Btree B)
{

    if(B)
    {
        InorderR(B->left);
        printf("%d ",B->data);
        InorderR(B->right);
    }
}

void PostorderR(Btree B)
{

    if(B)
    {
        PostorderR(B->left);
        PostorderR(B->right);
        printf("%d ",B->data);
    }
}

void Preorder(Btree B)
{

    stack s = CreateStack();

    while(1)
    {

        while(B)
        {

            printf("%d ",B->data);
            Push(&s,B);
            B = B->left;
        }
        if(Top(s,&B))
        {

            Pop(&s);
            B = B->right;
        }
        else return;
    }

}

void Inorder(Btree B)
{

    stack s = CreateStack();

    while(1)
    {

        while(B)
        {

            Push(&s,B);
            B = B->left;
        }
        if(Top(s,&B))
        {

            Pop(&s);
            printf("%d ",B->data);
            B = B->right;
        }
        else return;
    }

}

void Postorder(Btree B)
{

    stack s = CreateStack();
    Btree previous = NULL;

    while(1)
    {

        while(B)
        {

            Push(&s,B);
            B = B->left;
        }
        if(Top(s,&B))
        {

            if(!B->right || B->right == previous)
            {

                printf("%d ",B->data);
                previous = B;
                B = NULL;
                Pop(&s);
            }
            else B = B->right;
        }
        else return;
    }

}

void Levelorder(Btree B)
{

    queue q;
    Btree temp;
    if(!B) return;

    q = CreateQueue();
    EnQueue(&q,B);

    while(Front(q,&temp))
    {

        DeQueue(&q);
        printf("%d ",temp->data);
        if(temp->left) EnQueue(&q,temp->left);
        if(temp->right) EnQueue(&q,temp->right);
    }
}

int Found(Btree B,element e)
{

    if(!B) return 0;
    if(B->data == e) return 1;
    return Found(B->left,e) || Found(B->right,e);
}

Btree Lca(Btree B,int one,int two)
{

    if(!B || !Found(B,one) || !Found(B,two)) return NULL;
    if( Found(B->left,one) && Found(B->left,two) )
        return Lca(B->left,one,two);
    if( Found(B->right,one) && Found(B->right,two) )
        return Lca(B->right,one,two);
    return B;
}

int Height_Btree(Btree t)
{

    int hleft,hright;
    if(!t) return 0;
    else
    {
        hleft = Height_Btree(t->left);
        hright = Height_Btree(t->right);
        if( hleft > hright ) return (hleft+1);
        else return (hright+1);
    }
}

////////////////////////////////////////////////

//Exercices_BTree :

int max_BtreeR(Btree B)
{

    if(!B) return 0;
    return max(max(max_BtreeR(B->left),max_BtreeR(B->right)),B->data);
}

int max_Btree_Queue(Btree B)
{

    queue q = CreateQueue();
    Btree temp;
    int max = -1;
    if(!B) return max;
    EnQueue(&q,B);

    while(Front(q,&temp))
    {

        DeQueue(&q);
        if(temp->data > max) max = temp->data;
        if(temp->left) EnQueue(&q,temp->left);
        if(temp->right) EnQueue(&q,temp->right);
    }
    return max;
}

int max_Btree_Stack(Btree B)
{

    stack s = CreateStack();
    int max = -1;
    if(!B) return max;

    while(1)
    {

        while(B)
        {

            Push(&s,B);
            B = B->left;
        }
        if(Top(s,&B))
        {

            Pop(&s);
            if(B->data > max) max = B->data;
            B = B->right;
        }
        else break;
    }
    return max;
}

int sum_BtreeR(Btree B)
{

    if(!B) return 0;
    return B->data + sum_BtreeR(B->left) + sum_BtreeR(B->right);
}

int NbNode_BtreeR(Btree B)
{

    if(!B) return 0;
    return 1 + NbNode_BtreeR(B->left) + NbNode_BtreeR(B->right);
}

int NbLeafNode_BtreeR(Btree B)
{

    if(!B) return 0;
    if(!B->left && !B->right) return 1;
    return NbLeafNode_BtreeR(B->left) + NbLeafNode_BtreeR(B->right);
}

int NonLeafNode_BtreeR(Btree B)
{

    if(!B) return 0;
    if(!B->left && !B->right) return 0;
    return 1+ NonLeafNode_BtreeR(B->left) + NonLeafNode_BtreeR(B->right);
}

void Insert_Level(Btree *B,element e)
{

    queue f = CreateQueue();
    Btree pc = *B,n = (Btree)malloc(sizeof(struct node));

    if(!n) return 0;
    n->data = e;
    n->left = n->right = NULL;

    if(pc == NULL)
    {
        *B = n;
        return 1;
    }

    while(pc)
    {

        if(pc->left == NULL)
        {
            pc->left = n;
            return 1;
        }
        else EnQueue(&f,pc->left);

        if(pc->right == NULL)
        {
            pc->right = n;
            return 1;
        }
        else EnQueue(&f,pc->right);

        Front(f,&pc);
        DeQueue(&f);
    }
}

void deletDeepest(Btree racine,Btree d_node)
{

    if(!racine) return;
    if(racine == d_node)
    {
        racine = NULL;
        free(d_node);
        return;
    }
    if(racine->left == d_node)
    {
        racine->left = NULL;
        free(d_node);
        return;
    }
    if(racine->right == d_node)
    {
        racine->right = NULL;
        free(d_node);
        return;
    }
    deletDeepest(racine->left,d_node);
    deletDeepest(racine->right,d_node);
}

void deletion(Btree racine, int cle)
{

    queue f = CreateQueue();
    if(!racine) return;
    EnQueue(&f,racine);
    Btree temp,cle_noeud = NULL;

    while(Front(f,&temp))
    {

        DeQueue(&f);

        if(temp->data == cle) cle_noeud = temp;
        if(temp->left) EnQueue(&f,temp->left);
        if(temp->right) EnQueue(&f,temp->right);
    }

    int x = temp->data;
    cle_noeud->data = x;
    deletDeepest(racine,temp);
}

void Affiche_Inverse_Level(Btree B)
{

    queue q;
    stack s;
    Btree temp;
    if(!B) return;

    q = CreateQueue();
    s = CreateStack();
    EnQueue(&q,B);

    while(Front(q,&temp))
    {

        DeQueue(&q);
        if(temp->right) EnQueue(&q,temp->right);
        if(temp->left) EnQueue(&q,temp->left);
        Push(&s,temp);
    }

    while(Top(s,&temp))
    {
        Pop(&s);
        printf("%d ",temp->data);
    }
}

/////////////////////////////////////////////////////////

// BST :

Btree Min_BST(Btree B)
{

    if(!B) return NULL;
    else if(B->left == NULL) return B;
    else return Min_BST(B->left);
}

Btree Max_BST(Btree B)
{

    if(!B) return NULL;
    else if(B->right == NULL) return B;
    else return Min_BST(B->right);
}

void Insert_BST(Btree *B,element e)
{

    if(!(*B))
    {
        *B = (Btree)malloc(sizeof(struct node));
        (*B)->data = e;
        (*B)->left = (*B)->right = NULL;
        return;
    }
    else
    {
        if((*B)->data < e) Insert_BST(&((*B)->right),e);
        else Insert_BST(&((*B)->left),e);
    }
}
/*
Btree Delete_BST(Btree B,int val){

    if (!B) return B;
    if (val < B->data) B->left = Delete_BST(B->left,val);
    else if (val > B->data) B->right = Delete_BST(B->right,val);
    else{
        if (B->left == NULL){
        Btree temp = B->right;
        free(B);
        return temp;
        }
        else if (B->right == NULL){
        Btree temp = B->left;
        free(B);
        return temp;
        }
        Btree temp = Min_BST(B->right);
        B->data = temp->data;
        B->right = Delete_BST(B->right,temp->data);
    }
    return B;
}
*/
void Delete_BST(Btree *B,int val)
{

    if (!B) return *B;
    if (val < (*B)->data)  Delete_BST(&((*B)->left),val);
    else if (val > (*B)->data)  Delete_BST(&((*B)->right),val);
    else
    {
        if (! (*B)->left)
        {
            (*B) = (*B)->right;
            return;
        }
        else if (! (*B)->right)
        {
            (*B) = (*B)->left;
            return;
        }
        Btree temp = Min_BST((*B)->right);
        (*B)->data = temp->data;
        Delete_BST(&((*B)->right),temp->data);
    }
}

int Trouver_BST(Btree root,int val)
{

    if(!root) return 0;
    if(val < root->data) return Trouver_BST(root->left,val);
    else if(val > root->data) return Trouver_BST(root->right,val);
    else return 1;
}

void Table_To_BST(Btree *B,int tab[],int debut,int fin)
{

    if(debut > fin) return;
    int med=(debut+fin)/2;
    Insert_BST(B,tab[med]);
    Table_To_BST(B,tab,debut,med-1);
    Table_To_BST(B,tab,med+1,fin);
}

int Is_BST(Btree B,int min,int max)
{

    if(!B) return 1;
    return (B->data > min && B->data < max && Is_BST(B->left,min,B->data) && Is_BST(B->right,B->data,max));
}

int main()
{
    printf("Hello world!\n");
    return 0;
}

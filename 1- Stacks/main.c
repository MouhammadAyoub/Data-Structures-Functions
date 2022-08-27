#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 50

typedef int element;
typedef struct {
    element donnee[N];
    int tete;
}stack;


int isEmptyStack(stack p){

    return (p.tete == -1);
}

int isFullStack(stack p){

    return (p.tete == (N-1));
}

stack CreateStack(){

    stack p;
    p.tete = -1;
    return p;
}

int Push(stack *p,element e){

    if(isFullStack(*p)) return 0;
    p->donnee[++p->tete] = e;
    return 1;
}

int Pop(stack *p){

    if(isEmptyStack(*p)) return 0;
    p->tete--;
    return 1;
}

int Top(stack p,element *e){

    if(isEmptyStack(p)) return 0;
    *e = p.donnee[p.tete];
    return 1;
}

void printstack(stack p){

  element e;
  putchar('\n');
  while(Top(p,&e)){
    Pop(&p);
    printf("%d\t",e);
  }
  putchar('\n');
}

//EXERCICE 1 :

element Chercher(stack s,int index){

    if(isEmptyStack(s) || index < 1) return -1;
    element e;
    int count = 1;
    while(Top(s,&e) && count < index){
        Pop(&s);
        count++;
    }
    if(count == index) return e;
    else return -1;

}

//EXERCICE 2 :

void Ajouter(stack *s,int index,element val){

    if(isEmptyStack(*s) || index < 1) return;
    element e;
    int i = 1;
    stack aux = CreateStack();
    while( Top(*s,&e) && i < index ){
        Pop(s);
        Push(&aux,e);
        i++;
    }
    if(Push(s,val)){
        while( Top(aux,&e) ){
        Pop(&aux);
        Push(s,e);
        }
        return;
    }
    else return;
}

//EXERCICE 3 :

void Supprime(stack *s,int index){

    if(isEmptyStack(*s) || index < 1) return;
    element e;
    int i = 1;
    stack aux = CreateStack();
    while( Top(*s,&e) && i < index ){
        Pop(s);
        Push(&aux,e);
        i++;
    }
    if(Pop(s)){
        while( Top(aux,&e) ){
        Pop(&aux);
        Push(s,e);
        }
        return;
    }
    else return;
}

//EXERCICE 4 :

void Echanger(stack *s){

    if( isEmptyStack(*s) || s->tete < 1 ) return;
    element e1,e2;
    Top(*s,&e1);
    Pop(s);
    Top(*s,&e2);
    Pop(s);
    Push(s,e1);
    Push(s,e2);
}

//EXERCICE 5 :

int Som_Pile(stack s){

    if( isEmptyStack(s) ) return 0;
    element e;
    int som = 0;
    while(Top(s,&e)){
        Pop(&s);
        som += e;
    }
    return som;
}

//EXERCICE 6 :

double Moyenne_Pile(stack s){

    if( isEmptyStack(s) ) return 0;
    element e;
    int som = 0,i = 0;
    double avg = 0.0;
    while(Top(s,&e)){
        Pop(&s);
        som += e;
        i++;
    }
    avg = (som*1.0)/i;
    return avg;
}

//EXERCICE 7 :

void Inverser(stack *s){

    if( isEmptyStack(*s) || s->tete < 1 ) return;
    element e;
    stack aux1 = CreateStack(),aux2 = CreateStack();
    while(Top(*s,&e)){
        Pop(s);
        Push(&aux1,e);
    }
    while(Top(aux1,&e)){
        Pop(&aux1);
        Push(&aux2,e);
    }
    while(Top(aux2,&e)){
        Pop(&aux2);
        Push(s,e);
    }
}

//EXERCICE 8 :

void Palindrome(char mot[]){

    int taille = strlen(mot);
    if(taille < 2) return;
    int i = 0;
    element e;
    stack s = CreateStack();
    while( i < taille/2 ){
        Push(&s,mot[i]);
        i++;
    }
    if( taille%2 != 0 ) i++;
    while( i < taille && Top(s,&e)){
        if( mot[i] != e ){
            printf("No");
            return;
        }
        Pop(&s);
        i++;
    }
    printf("YES");
}

//EXERCICE 9 :

void Som_Int(char str1[],char str2[],char str3[]){

    stack aux1 = CreateStack();
    stack aux2 = CreateStack();
    stack aux3 = CreateStack();
    int taille1 = strlen(str1),taille2 = strlen(str2);
    int i = 0,som = 0,stocke = 0;
    element e1,e2;
    while( i < taille1 ){
        Push(&aux1,str1[i]-'0');
        i++;
    }
    i = 0;
    while( i < taille2 ){
        Push(&aux2,str2[i]-'0');
        i++;
    }
    while( !isEmptyStack(aux1) || !isEmptyStack(aux2) ){

        if(Top(aux1,&e1)) Pop(&aux1);
        if(Top(aux2,&e2)) Pop(&aux2);
        som = e1 + e2 + stocke ;
        if( som > 9 ){
            Push(&aux3,som%10);
            stocke = 1;
        }
        else {
            Push(&aux3,som);
            stocke = 0;
        }
        e1 = 0;
        e2 = 0;
    }
    if( stocke == 1 ) Push(&aux3,1);
    i = 0;
    while(Top(aux3,&e1)){
            str3[i] = e1+'0';
            Pop(&aux3);
            i++;
    }
}

//EXERCICE 10 :

void Remove_Negative(stack *s){

    if( isEmptyStack(*s) ) return;
    stack aux = CreateStack();
    element e;
    while(Top(*s,&e)){
        if(e >= 0)Push(&aux,e);
        Pop(s);
    }
    while(Top(aux,&e)){
        Push(s,e);
        Pop(&aux);
    }
}

//EXERCICE 11 :

typedef struct {
    element donnee[N];
    int tete1,tete2;
}stackN;

int isEmptyStackN(stackN p,int i){

    if(i == 1) return (p.tete1 == -1);
    if(i == 2) return (p.tete2 == N);
}

int isFullStackN(stackN p){

   return (p.tete1+1 == p.tete2);
}

stackN CreateStackN(){

    stackN p;
    p.tete1 = -1;
    p.tete2 = N;
    return p;
}

int PushN(stackN *p,element e,int n){

    if(isFullStackN(*p)) return 0;
    if( n == 1 ) p->donnee[++p->tete1] = e;
    else p->donnee[p->tete2--] = e;
    return 1;
}

int PopN(stackN *p,int n){

    if(isEmptyStackN(*p,n)) return 0;
    if( n == 1 ) p->tete1--;
    else ++p->tete2;
    return 1;
}

int TopN(stackN p,element *e,int n){

    if(isEmptyStackN(p,n)) return 0;
    if( n == 1 ) *e = p.donnee[p.tete1];
    else  *e = p.donnee[p.tete2];
    return 1;
}

//EXERCICE 12 :

typedef struct {
    element donnee[N];
    int tete1,tete2;
    int tete3,tail3;
}NstackN;

int NisEmptyStackN(NstackN p,int i){

    if(i == 1) return (p.tete1 == -1);
    if(i == 2) return (p.tete2 == N);
    if(i == 3) return (p.tete3 < p.tail3);
}

int NisFullStackN(NstackN p){

   return (p.tete1+1 == p.tail3 && p.tete3 == p.tete2-1);
}

NstackN NCreateStackN(){

    NstackN p;
    p.tete1 = -1;
    p.tete2 = N;
    p.tete3 = N/2;
    p.tail3 = N/2+1;
    return p;
}

int NPushN(NstackN *p,element e,int n){

    if(NisFullStackN(*p)) return 0;
    if( n == 1 ) p->donnee[++p->tete1] = e;
    if( n == 2 )p->donnee[p->tete2--] = e;
    else {
        ....................
    }
    return 1;
}

int NPopN(NstackN *p,int n){

    if(NisEmptyStackN(*p,n)) return 0;
    if( n == 1 ) p->tete1--;
    if( n == 2 ) ++p->tete2;
    else p->tete3--;
    return 1;
}

int NTopN(NstackN p,element *e,int n){

    if(NisEmptyStackN(p,n)) return 0;
    if( n == 1 ) *e = p.donnee[p.tete1];
    if( n == 2 )  *e = p.donnee[p.tete2];
    else *e = p.donnee[p.tete3];
    return 1;
}

int main()
{
    stack p = CreateStack();
    Push(&p,-1);
    Push(&p,23);
    Push(&p,-2);
    Push(&p,53);
    Push(&p,21);
    Push(&p,-9);
    printstack(p);
    putchar('\n');
    Remove_Negative(&p);
    printstack(p);
    getchar();
    return 0;
}

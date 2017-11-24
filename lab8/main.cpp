#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <SFML/Graphics.hpp>

int N = 10; // Размер дерева
int H; // Высота
int CHH; // Высота локальной ветки
int CS; // Контрольная сумма
int S; // Размер
int MIDH; // Cредняя высота
int BR; // Номер ветки
int** AW; //Вес поддерева
int** AP; //Взвешеная высота поддерева
int** AR; //ДОП матрица
int Wes = 0;

struct tree{
    int wes;
    int data;
    tree *l;
    tree *r;
};

void InsertSort (int *a, int *w, int n);
void ClearTree(tree *S);
void middleHeight (tree *m);
void CreateTree(int L, int R, int* A, int* W, tree *&head);
void matrixAPAR(int** AP, int** AR, int** AW);
void matrixAW(int** AW, int* W);
void print_struct (tree *m);
void Add (int data, int wes, tree *&head);
void TreeA2(int L, int R, int* A, int* W, tree *&head);
void TreeA1 (int *A, int *W, tree *&head);



int main(){
    srand (time(NULL));
    int key;
    int *A = new int [N+1];
    int *W = new int [N+1];
    tree *h = NULL;
    tree *see = NULL;
    int i,j;

    AW = new int* [N+1];
    for (i=0; i<N+1; i++){
        AW[i] = new int [N+1];
    }
    AP = new int* [N+1];
    for (i=0; i<N+1; i++){
        AP[i] = new int [N+1];
    }
    AR = new int* [N+1];
    for (i=0; i<N+1; i++){
        AR[i] = new int [N+1];
    }

    std::cout<<"Lab 7 - DOP";
    for (i=1; i<=N; i++){
        A[i] = rand() % (N*2) + 10;
        W[i] = rand() % 100;
        CS += A[i];
        for(j=0;j<i;j++){
            if (A[j] == A[i]) break;
        }
        if (j < i) {CS -= A[i]; i--;}
    }
    InsertSort (A, W, N+1);
    printf(" \nSorted array: \n");
    for (i=1;i<=N;i++){
        printf("%4d (%d)",A[i], W[i]);
    }
    std::cout<<std::endl<<"DOP control summ: "<<CS;

    for (i=0; i<=N; i++) {
        for (j=0; j<=N; j++) {
            AW[i][j] = AR[i][j] = AP[i][j] = 0;
        }
    }
    matrixAW(AW, W);
    matrixAPAR(AP, AR, AW);
    Wes = CS = H = S = MIDH = BR = 0;
    CHH = 1;

    CreateTree(0, N, A, W, h);
    middleHeight (h);
    std::cout<<std::endl<<"COMPLETE";
    print_struct (h);
    std::cout<<std::endl<<"DOP control summ: "<<CS<<" ";
    std::cout<<"Height: "<<H<<" ";
    std::cout<<"Size: "<<S<<" ";
    std::cout<<"Mid: "<<((double)MIDH/Wes)<<" ";
    ClearTree (h);
    h = NULL;

    std::cout<<std::endl<<"ALG A1";
    puts("\n");
    InsertSort (W, A, N+1);
    printf(" \nSorted array: \n");
    for (i=1;i<=N;i++){
        printf("%4d (%d)",A[i], W[i]);
    }
    printf("\nCS - %d", CS);

    Wes = CS = H = S = MIDH = BR = 0;
    CHH = 1;

    TreeA1(A, W, h);
    middleHeight (h);
    std::cout<<std::endl<<"COMPLETE";
    print_struct (h);
    std::cout<<std::endl<<"DOP control summ: "<<CS<<" ";
    std::cout<<"Height: "<<H<<" ";
    std::cout<<"Size: "<<S<<" ";
    std::cout<<"Mid: "<<((double)MIDH/Wes)<<" ";
    ClearTree (h);
    h = NULL;

    std::cout<<std::endl<<"ALG A2";
    puts("\n");
    InsertSort (A, W, N);
    printf(" \nSorted array: \n");
    for (i=1;i<=N;i++){
        printf("%4d (%d)",A[i], W[i]);
    }
    printf("\nCS - %d", CS);

    Wes = CS = H = S = MIDH = BR = 0;
    CHH = 1;

    TreeA2(1, N, A, W, h);
    middleHeight (h);
    std::cout<<std::endl<<"COMPLETE";
    print_struct (h);
    std::cout<<std::endl<<"DOP control summ: "<<CS<<" ";
    std::cout<<"Height: "<<H<<" ";
    std::cout<<"Size: "<<S<<" ";
    std::cout<<"Mid: "<<((double)MIDH/Wes)<<" ";
    ClearTree (h);
    h = NULL;

    delete A;
    system ("PAUSE");
}

void print_struct (tree *m){
    if ( !m ) return;
    print_struct (m->l);
    printf("%4d",m->data);
    CS += m->data;
    print_struct (m->r);
}

void Add (int data, int wes, tree *&head){
    if (head == NULL){
        head = new tree;
        head->data = data;
        head->wes = wes;
        head->l = head->r = NULL;
        S++;
        Wes += head->wes;
    }
    if (data > head->data) {
        Add (data, wes, head->r);
    } else {
        if (data < head->data) {
            Add (data, wes, head->l);
        } else {
            if (data == head->data) {
                return;
            }
        }
    }
}

void TreeA1 (int *A, int *W, tree *&head){
    for (int i = 1; i<=N; i++){
        Add(A[i], W[i], head);
    }
}

void TreeA2(int L, int R, int* A, int* W, tree *&head){
    int wes, sum, i;
    wes = sum = 0;
    if (L <= R){
        for (i = L; i <= R; i++) {
            wes += W[i];
        }
        for (i = L; i < R; i++) {
            if ((sum < wes/2)&&((sum + W[i]) >= wes/2)) break;
            sum += W[i];
        }
        Add (A[i], W[i], head);
        TreeA2(L, i-1, A, W, head);
        TreeA2(i+1, R, A, W, head);
    }
}

void matrixAW(int** AW, int* W){
    for (int i=0; i<=N; i++){
        for (int j=i+1; j<=N; j++){
            AW[i][j] = AW[i][j-1] + W[j];
        }
    }
}

void matrixAPAR(int** AP, int** AR, int** AW){
    int i,j,h,k,m,min;
    for (i=0; i<N; i++) {
        j = i+1;
        AP[i][j] = AW[i][j];
        AR[i][j] = j;
    }
    for (h=2; h<=N; h++){
        for (i=0; i<=N-h; i++){
            j = i+h;
            m = AR[i][j-1];
            min = AP[i][m-1] + AP[m][j];
            for (k=m+1; k<=AR[i+1][j]; k++){
                int x = AP[i][k-1] + AP[k][j];
                if (x < min) {
                    m = k;
                    min = x;
                }
            }
            AP[i][j] = min + AW[i][j];
            AR[i][j] = m;
        }
    }
}

void CreateTree(int L, int R, int* A, int* W, tree *&head){
    if (L < R){
        int k = AR[L][R];
        Add (A[k], W[k], head);
        CreateTree(L, k-1, A, W, head);
        CreateTree(k, R, A, W, head);
    }
}

void middleHeight (tree *m){
    MIDH += m->wes*CHH;
    if ( m->l ) {
        CHH++;
        middleHeight (m->l);
    }
    if ( m->r ) {
        CHH++;
        middleHeight (m->r);
    }
    if ((!m->l) && (!m->r)){
        BR++;
        if (H < CHH)
            H = CHH;
    }
    CHH--;
    return;
}

void ClearTree(tree *S){
    if ( S->l )
        ClearTree ( S->l );
    if ( S->r )
        ClearTree ( S->r );
    delete S;
}
void InsertSort (int *a, int *w, int n){
    int i,j,key,keyW;
    for (j=2;j<n;j++){
        key=a[j];
        keyW=w[j];
        i=j-1;
        while(i>=1 && a[i]>key){
            a[i+1]=a[i];
            w[i+1]=w[i];
            i--;
        }
        a[i+1]=key;
        w[i+1]=keyW;
    }
}

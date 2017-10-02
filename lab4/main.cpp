#include <iostream>
#include <stdlib.h>
#include <ctime>

using namespace std;

struct Vertex{
    int Data;
    Vertex *Left;
    Vertex *Right;
};Vertex *ROOT;

int summ(Vertex* p); //Определение контрольной суммы для дерева
int height(Vertex* p); //Определение высоты дерева
int sizetree (Vertex *p); //Определение размера дерева
void outputtree(Vertex *p); //Вывод дерева(Обход дерева слева направо)
void searchkeyx(Vertex *p, int x); //Поиск по ключу
void randAddDouble (int d, Vertex *&ROOT); //Добавление в СДП двойноей косвенностью
void RandAddRecursion(int d,Vertex *p); //Добавление в СДП рекурсией
int heightMid(Vertex* p,int L); //Определение средней высоты дерева
void dellVertex(Vertex *&ROOT,int X); //Удаление вершины дерева


int main() {

    srand(time(0));
    int woodSize= 100; //Размер дерева
    int searchkey = 10; //Ключ поиска
    int dellvertex = 10;//Колличество удаляемых элементов
    int key;
    for (int i = 0; i < woodSize; ++i) {
        randAddDouble(1 + rand() % 100,ROOT);

    }
    outputtree(ROOT);
    searchkeyx(ROOT,searchkey);
    cout << "Size: "<< sizetree(ROOT)<<endl;
    cout << "Height: "<<height(ROOT)<<endl;
    cout << "HeightMid: "<<heightMid(ROOT,1)/sizetree(ROOT)<<endl;
    cout << "Mid: "<<summ(ROOT)<<endl;
    for(int i=0;i<dellvertex;i++){
        cout<<"input number to delete:";
        cin>>key;
        cout<<endl;
        dellVertex(ROOT, key);
        outputtree(ROOT);};
    system("pause");
    return 0;
}
int summ(Vertex* p){
    if(!(p)){ return 0;}
    else return (p->Data+summ(p->Left)+summ(p->Right));
}
int height(Vertex* p){
    int l, r, h = 0;
    if(!(p)){ return 0;}else{
        l = height(p->Left);
        r = height(p->Right);
        h = ((l > r) ? l : r) + 1;
    }
    return h;
}
int heightMid(Vertex* p,int L){
    if(!(p)){ return 0;}
    else { return (L+heightMid(p->Left,L+1)+heightMid(p->Right,L+1));};
}

void outputtree(Vertex *p){
    if(p){
        outputtree(p->Left);
        cout<< p->Data<<endl;
        outputtree(p->Right);
    }
};

int sizetree (Vertex *p){
    int size;
    if (!(p)) return 0;
    else return(1 + sizetree(p->Left) + sizetree(p->Right));
};

void searchkeyx(Vertex *p, int x){
    if(p){
        searchkeyx (p->Left,x);
        if (p->Data == x){cout<<" found "<<x<<endl;}
        searchkeyx (p->Right,x);
    };
};
void randAddDouble (int d, Vertex *&ROOT){
    Vertex **p = &ROOT;
    while(*p) {
        if (d < (*p)->Data) p = &(*p)->Left;
        else if (d > (*p)->Data) p = &(*p)->Right;
        else if (d == (*p)->Data) p = &(*p)->Right;
    }
    if(!(*p)) {
        (*p) = new Vertex,
        (*p)->Data = d,
        (*p)->Right = (*p)->Left = NULL;
    }
}
void RandAddRecursion(int d,Vertex *p){
    if (!(p));
};
void dellVertex(Vertex *&ROOT,int X) {
    Vertex **p = &ROOT;
    Vertex *r, *s, *q;
    while (*p) {
        if ((*p)->Data < X) p = &(*p)->Right;
        else if ((*p)->Data > X) p = &(*p)->Left;
        else break;
    };
    if (*p) {
        q = *p;
        if (q->Left == NULL) *p = q->Right;
        else if (q->Right == NULL) *p = q->Left;
        else {
            r = q->Left;
            s = q;
            if (r->Right == NULL) {
                r->Right = q->Right;
                *p = r;
            } else {
                while (r->Right != NULL) {
                    s = r;
                    r = r->Right;
                };
                s->Right = r->Left;
                r->Left = q->Left;
                r->Right = q->Right;
                *p = r;
            };
            delete (q);
        }
    }
}
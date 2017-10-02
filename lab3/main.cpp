#include <iostream>
#include <stdlib.h>
#include <ctime>

using namespace std;

struct Vertex{
    int Data;
    Vertex *Left;
    Vertex *Right;
};Vertex *ROOT;

int summ(Vertex* p);
int height(Vertex* p);
int sizetree (Vertex *p);
void outputtree(Vertex *p);
void searchkeyx(Vertex *p, int x);
void randAddDouble (int d, Vertex *&ROOT);
void RandAddRecursion(int d,Vertex *p);
int heightMid(Vertex* p,int L);

int main() {
    srand(time(0));
    int woodSize= 10;
    int searchkey = 10;
    for (int i = 0; i < woodSize; ++i) {
        randAddDouble(1 + rand() % 10,ROOT);

    }
    outputtree(ROOT);
    searchkeyx(ROOT,11);
    cout << "Size: "<< sizetree(ROOT)<<endl;
    cout << "Height: "<<height(ROOT)<<endl;
    cout << "HeightMid: "<<heightMid(ROOT,1)/sizetree(ROOT)<<endl;
    cout << "Mid: "<<summ(ROOT)<<endl;
    sizetree(ROOT);
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
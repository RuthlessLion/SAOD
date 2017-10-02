#include <iostream>
#include <stdlib.h>
#include <ctime>

using namespace std;

struct Vertex{
    int Data;
    Vertex *Left;
    Vertex *Right;
};Vertex *ROOT;

void output_tree(Vertex *p);
void searchkeyx(Vertex *p, int x, int countt);
void random_tree_search_double_indirection(int d, Vertex *&ROOT);
void randAddDouble (int d, Vertex *&ROOT);
void RandAddRecursion(int d,Vertex *p);

int main() {
    srand(time(0));
    int countt;
    int woodSize = 10;
    int randd[woodSize];
    for (int j = 0; j < woodSize; ++j) {
        randd[j] = 1 + rand() % 10;
        cout<<randd[j];
    }
    for (int i = 0; i < woodSize; ++i) {
        cout<<" HUI ";
        randAddDouble(randd[i],ROOT);

    }
    output_tree(ROOT);
    searchkeyx(ROOT,2,countt);
    system("pause");
    return 0;
}


void output_tree(Vertex *p){
    if(p != NULL){
        output_tree(p->Left);
        cout<< p->Data<<endl;
        output_tree(p->Right);
    }
};

void searchkeyx(Vertex *p, int x, int count){
    if(p != NULL){
        searchkeyx (p->Left,x,count);
        if (p->Data == x){cout <<"count = "<<count<<" found "<<x<<endl;}
        count += 1;
        searchkeyx (p->Right,x,count);
    } else {
        cout << "hello";
    }
};

void random_tree_search_double_indirection(int d, Vertex *&ROOT){
    Vertex **p = &ROOT;
    while(*p){
        if(d < (*p)->Data){
            p = &(*p)->Left;
        } else if(d > (*p)->Data){
            p = &(*p)->Right;
        }else if (d == (*p)->Data) {
            return;};
    }
    if(!(*p)){
        if(d == (*p)->Data){
            p = &(*p)->Right;
        (*p) = new Vertex;
        (*p)->Data = d;
        (*p)->Left = NULL;
        (*p)->Right = NULL;
    }
};
}
void randAddDouble (int d, Vertex *&ROOT){
    Vertex **p = &ROOT;
    while(*p) {
        if (d < (*p)->Data) p = &(*p)->Left;
        else if (d > (*p)->Data) p = &(*p)->Right;
    }
    if(!(*p)) {
        (*p) = new Vertex,
        (*p)->Data = d,
        (*p)->Right = (*p)->Left = NULL;
    }
}
void RandAddRecursion(int d,Vertex *p){
    if (p == NULL);
};
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <stdio.h>
#include "include/json.h"

using namespace std;

bool VR; // VerticalRost
bool HR; // HorizontalRost

int summ(tree* p){
    if(!(p)){ return 0;}
    else return (p->data+summ(p->l)+summ(p->r));
}
int sizetree (tree *p){
    if (!(p)) return 0;
    else return(1 + sizetree(p->l) + sizetree(p->r));
};
int height(tree* p){
    int l, r, h = 0;
    if(!(p)){ return 0;}else{
        l = height(p->l);
        r = height(p->r);
        h = ((l > r) ? l : r) + 1;
    }
    return h;
}
int heightMid(tree* p,int L){
    if(!(p)){ return 0;}
    else { return (L+heightMid(p->l,L+1)+heightMid(p->r,L+1));};
}
void print_struct (tree *m){
    if ( !m ) return;
    print_struct (m->l);
    printf("%4d",m->data);
    print_struct (m->r);
}

void B2INSERT (int data, tree *&p) {
    tree *q;
    if (p == NULL) {
        p = new tree;
        p->data = data;
        p->l = p->r = NULL;
        p->bal = 0;
        VR = true;
    } else {
        if (p->data > data) {
            B2INSERT(data, p->l);
            if (VR) {
                if (p->bal == 0) {
                    q = p->l;
                    p->l = q->r;
                    q->r = p;
                    p = q;
                    q->bal = 1;
                    VR = false;
                    HR = true;
                } else {
                    p->bal = 0;
                    VR = true;
                    HR = false;
                }
            } else {
                HR = false;
            }
        } else {
            if (p->data < data) {
                B2INSERT(data, p->r);
                if (VR) {
                    p->bal = 1;
                    VR = false;
                    HR = true;
                } else {
                    if (HR) {
                        if (p->bal == 1) {
                            q = p->r;
                            p->bal = 0;
                            q->bal = 0;
                            p->r = q->l;
                            q->l = p;
                            p = q;
                            VR = true;
                            HR = false;
                        } else {
                            HR = false;
                        }
                    }
                }
            }
        }
    }
}
void ClearTree(tree *S){
    if ( S->l )
        ClearTree ( S->l );
    if ( S->r )
        ClearTree ( S->r );
    delete S;
}

int main(){
    int n = 1000,numb;
    srand (time(NULL));
    tree *h = NULL;
    VR = HR = true;
    for(int i = 0; i < n; i++){
        numb = rand()%1000;
        cout << numb << " ";
        B2INSERT (numb, h);
    }
    cout << endl << "Sort:";
    print_struct (h);
    cout << endl << "Size: "<< sizetree(h)<<endl;
    cout << "Height: "<< height(h)<<endl;
    cout << "HeightMid: "<< (float)heightMid(h,1)/sizetree(h) << endl;
    cout << "Mid: " << summ(h) << endl;
    GraphBintree(h);
}
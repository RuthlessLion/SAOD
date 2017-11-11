#ifndef TREE_JSON_GRAPH
#define TREE_JSON_GRAPH

#include <iostream>
#include <string>
#include <sstream>
#include "JsonBox.h"

struct tree{
    int bal;
    int data;
    tree *l;
    tree *r;
};
void GraphBintreeRecure(tree *tr, JsonBox::Object &obj, int &i, int x, int y, int size_x, int size_y);
void GraphBintree(tree *tr);

#endif
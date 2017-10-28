//
// Created by windo on 21.10.2017.
//

#ifndef SIAOD_PROJECT_INIT_H
#define SIAOD_PROJECT_INIT_H

class init {
private:
    static void siftDown(int *numbers, int root, int bottom);
    static void heapSort(int *numbers, int array_size);
    static void sortDB();
    static void freeDB();
    static void readDB();
    static void printDB();
    static void sort(int col);
    static void sortDBname();
    static int searchkey(int key);
    static int curr(int a, int b);
public:
    static void menu();
};


#endif //SIAOD_PROJECT_INIT_H

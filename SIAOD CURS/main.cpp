
#include <cstdio>
#include <iostream>
#include <cstdlib>

#define DBSize 4000

using namespace std;

struct record {
    char fullname[30];
    short int dept;
    char post[22];
    char dob[10];
};

record* database = NULL;
record** index = NULL;

void siftDown(int *numbers, int root, int bottom);
void heapSort(int *numbers, int array_size);
void sortDB();
void freeDB();
void readDB();
void printDB();
void sort(int col);
void menu();
void sortDBname();
int searchkey(int key);
int curr(int a,int b);



int main() {
    menu();
    return 0;
}

void menu() {
    int selector = 0;
    int key = 0;
    while(1){
        cin >> selector;
            if (selector == 1){
                readDB();
            }
            if(selector == 2){
                printDB();
                break;
            }
            if(selector == 3){
                sortDB();
                break;
            }
            if(selector == 4){
                sortDBname();
            }
            if(selector == 5){
                cin>>key;
                searchkey(key);
            }else {
                cout << "Wrong key" << endl;
        }
    }
}

void readDB() {
    freeDB();

    FILE *pF;
    pF = fopen("testBase2.dat","rb");
    database = new record [DBSize];
    int count = fread((record*)database, sizeof(record), DBSize, pF);
    if (count != DBSize) {
        puts("\nERROR! Something unexpected caused a problem! Database wastn't readed!\n");
        system("PAUSE");
        exit(1);
    }

    index = new record* [DBSize];
    for (int i=0; i<DBSize; i++)
        index[i] = &database[i];
    fclose(pF);
}
void freeDB() {
    if (database!=NULL){
        delete[] database;
        delete[] index;
        database = NULL;
        index = NULL;
    }
}
void printDB() {
    if (database==NULL){
        system("CLS");
        puts("Database hasn't readed yet!\n");
        system("PAUSE");
        return;
    }
    int ch;
    int i;
    int first = 0;
    int last = 20;
        while (1) {
        system("CLS");
        for (i=first; i<last; i++) {
            cout << i+1<<" "<<index[i]->fullname<<" ",
                    cout << index[i]->dept<<" ",
                    cout << index[i]->post<<" ",
                    cout << index[i]->dob<<endl;
        }
        cout << "Enter 1 to next or 2 to down";
        cin>>ch;
        if(ch == 1){
        if ((last+20)<=DBSize) {
            first += 20;
            last += 20;
            }
        }
        if(ch == 2){
            if ((first-20)>=0) {
                first -= 20;
                last -= 20;
            }
        }
        if(ch == 0 ){
            menu();
            return;
        }
    }
}
void sortDB(){
    readDB();
    int dob[DBSize];
    for (int i=0; i<DBSize; i++){
        dob[i] = atoi(index[i]->dob);
        cout << dob[i] << " ";
    }
    cout << endl;
    heapSort(dob,DBSize);
        for (int i=0; i<DBSize; i++){
        cout << dob[i]<< " ";
    }
    printDB();
    system("PAUSE");
}

void siftDown(int *numbers, int root, int bottom) {
    int maxChild;
    int done = 0;
    record* buf;
    while ((root * 2 <= bottom) && (!done)) {
        if (root * 2 == bottom)
            maxChild = root * 2;
        else if (numbers[root * 2] > numbers[root * 2 + 1])
            maxChild = root * 2;
        else
            maxChild = root * 2 + 1;
        if (numbers[root] < numbers[maxChild]) {
            int temp = numbers[root];
            buf = index[root];
            numbers[root] = numbers[maxChild];
            index[root] = index[maxChild];
            numbers[maxChild] = temp;
            index[maxChild] = buf;
            root = maxChild;
        }
        else
            done = 1;
    }
}
void heapSort(int *numbers, int array_size) {
    record* buf;
    for (int i = (array_size / 2) - 1; i >= 0; i--)
        siftDown(numbers, i, array_size);
    for (int i = array_size - 1; i >= 1; i--) {
        int temp = numbers[0];
        buf = index[0];
        numbers[0] = numbers[i];
        index[0] = index[i];
        numbers[i] = temp;
        index[i] = buf;
        siftDown(numbers, 0, i - 1);
    }
}
void sort(int col) {
    record *buf;
    for( int i = 0; i < col; i++)
        for( int j = 0; j < col - 1; j++){
            if (curr(j , j+1)){
                    buf = index[j];
                    index[j] = index[j + 1];
                    index[j + 1] = buf;
                }else{
                }
            }
        }

void sortDBname(){
    readDB();
    record *buf;
    sort(DBSize);
    printDB();
}
int curr(int a,int b){
    for (int i = 0; i<30;i++){
        if(index[a]->fullname[i] > index[b]->fullname[i]){
            return 1;
        } else if(index[a]->fullname[i] < index[b]->fullname[i]){ return 0;};
    }
    return 1;
}
int searchkey(int key) {
    readDB();
    int dob[DBSize];
    for (int i = 0; i < DBSize; i++) {
        dob[i] = atoi(index[i]->dob);
    }
    for (int j = 0; j < DBSize; j++) {
        if (key == dob[j]) {
            cout << j+1<<" "<<index[j]->fullname<<" ",
                    cout << index[j]->dept<<" ",
                    cout << index[j]->post<<" ",
                    cout << index[j]->dob<<endl;
        }
    }
}
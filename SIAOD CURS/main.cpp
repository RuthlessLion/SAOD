// Variant #41 B2 C2 S1 D2 E3
#pragma pack(push, 1)

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <conio.h>

#define DBSize 4000

using namespace std;

struct record
{
    char fullname[30];
    short int dept;
    char post[22];
    char dob[10];
};

struct chr
{
    int prob;
    unsigned char ch;
};

record* database = NULL;
record** index = NULL;
chr* alphabet = NULL;
string* CodeWord = NULL;

void freeDB();
void readDB();
void printDB();
void menu();

int main()
{
    menu();
    return 0;
}

void menu()
{
    char selector;
    while(1){
        system("CLS");
        puts("MENU:\n\
1. Load database\n\
2. Print database\n\
ESC. Exit\n");
        selector = getch();
        switch(selector)
        {
            case '1':
            {
                readDB();
            }
            case '2':
            {
                printDB();
                break;
            }
            case 27:
            {
                system("CLS");
                return;
            }
            default:
            {
                puts("\nWRONG KEY\n");
            }
        }
    }
}

void readDB()
{
    freeDB();

    FILE *pF;
    pF = fopen("testBase2.dat","rb");
    database = new record [DBSize];
    int count = fread((record*)database, sizeof(record), DBSize, pF);
    if (count != DBSize)
    {
        puts("\nERROR! Something unexpected caused a problem! Database wastn't readed!\n");
        system("PAUSE");
        exit(1);
    }

    index = new record* [DBSize];
    for (int i=0; i<DBSize; i++)
        index[i] = &database[i];
    fclose(pF);
}
void freeDB()
{
    if (database!=NULL){
        delete[] database;
        delete[] index;
        database = NULL;
        index = NULL;
    }
}
void printDB()
{
    if (database==NULL){
        system("CLS");
        puts("Database hasn't readed yet!\n");
        system("PAUSE");
        return;
    }
    char ch;
    int i;
    int first = 0;
    int last = 20;
    while (1)
    {
        system("CLS");
        for (i=first; i<last; i++) {
            printf("%04d) %30s  %03d  %22s  %10s\n",i+1,index[i]->fullname,
                   index[i]->dept,
                   index[i]->post,
                   index[i]->dob);
        }
        puts("\nNEXT 20: RIGHT\nPREVIOUS 20: LEFT\nEXIT: Esc");
        ch = getch();
        switch(ch)
        {
            case 77:
            {
                if ((last+20)<=DBSize)
                {
                    first += 20;
                    last += 20;
                }
                break;
            }
            case 75:
            {
                if ((first-20)>=0)
                {
                    first -= 20;
                    last -= 20;
                }
                break;
            }
            case 27:
            {
                system("CLS");
                return;
            }
        }
    }
    puts("\nERROR! Something unexpected caused a problem!\n");
    system("PAUSE");
    exit(1);
}
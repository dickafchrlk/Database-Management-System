#include <stdio.h>
#include <string.h>

typedef struct library
{
    char PrimaryKey[255];   // kode unik
    char ForeignKey[255];   // kode penghubung
    char Atribute1[255];    // nama
    char Atribute2[255];    // perilaku
}dataName;

// Sorting method
void swap(dataName *a, dataName *b);
int partition(dataName arr[], int low, int high);
void quicSort(dataName arr[], int low, int high);

// Read & Write file method
void readFile(int *n, dataName source[], char filename[]);
void writeFile(int n, dataName source[], char fileName[]);

// Query method
void queryAdd (char ribbon[], int n, dataName source[]);
void queryShow(dataName source[]);
void queryUpdate(char ribbon[], int n, dataName source[]);
void queryDelete(char ribbon[], int n, dataName source[]);
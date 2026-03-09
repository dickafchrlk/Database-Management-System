#include <stdio.h>
#include <string.h>

typedef struct library
{
    char primaryKey[50];
    char foreignKey[50];
    char name[100];
    char attribute[100];
}dataName;

// Abstrack Machine method
int eop(char pita[]);
void start(char pita[]);
void reset();
void inc(char pita[]);
char* getcw();
int getlen();

// Sorting method
void swap(dataName *a, dataName *b);
int partition(dataName arr[], int low, int high);
void quickSort(dataName arr[], int low, int high);

// searching method
int SequentialSearch(int n, dataName arr[], char target[]);

// Read & Write file method
void readFile(int *n, dataName source[], char filename[]);
void writeFile(int *n, dataName source[], char fileName[]);

// Query method
void queryAdd (char ribbon[], int *n, dataName source[], char fileName[]);
void queryShow(int *n, dataName source[]);
void queryUpdate(char ribbon[], int *n, dataName source[], char fileName[]);
void queryDelete(char ribbon[], int *n, dataName source[], char fileName[]);
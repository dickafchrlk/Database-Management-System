#include <stdio.h>
#include <string.h>

typedef struct library
{
    char PrimaryKey[255];
    char Atribute[255];
    char ForeignKey[255];
    char sanksi[255];
}dataName;

// Sorting method
void swap(dataName *a, dataName *b);
int partition(dataName arr[], int low, int high);
void quicSort(dataName arr[], int low, int high);
#include "library.h"


/**
 * Quick Sort prosedur
 * ada 3 prosedur yang akan digunakan. Pertama adalah swap
 * fungsinya untuk menukar posisi data depan ke belakang.
 * Kedua ada pemisahan partisi yang berguna untuk menentukan pivot
 * yang digunakan saat proses sorting. Terakhir yang ketiga
 * prosedur quickSort yang akan dilakukan secara rekursif (berulang).
 */

void swap(dataName *a, dataName *b) {
    dataName temp = *a;
    *a = *b;
    *b = temp;
}

int partition(dataName arr[], int low, int high) {
    int p = arr[low].PrimaryKey;
    int i = low;
    int j = high;

    while (i < j)
    {
        // mencari element pertama yang lebih besar dari pivot
        // pivot (di awal)
        while (arr[i].PrimaryKey <= p && i <= high -1)
        {
            i++;
        }

        // mencari element pertama yang lebih kecil dari pivot
        // pivot (di akhir)
        while (arr[j].PrimaryKey > p && j >= low + 1)
        {
            j--;
        }
        
        // jika nilai elemen pertama dari depan (i) lebih besar dari 
        // elemen pertama dari belakang (j). maka posisi akan di tukar
        if (i < j)
        {
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[low], &arr[j]);
    return j;
}

void quicSort(dataName arr[], int low, int high) {
    if (low < high)
    {
        // Gunakan prosedur partition untuk mencari pivot
        int pi = partition(&arr, low, high);

        // Gunakan pemanggilan rekursif dari prosedur quicksort
        // setengah kiri dan kanan yang di pisah menggunakan pivot
        quicSort (&arr, low, pi - 1);
        quicSort (&arr, pi + 1, high);
    }
}

/**
 * Read Data
 * Proses ini digunakan untuk membaca data yang disimpan pada
 * file.txt yang tersedia (ex: kasus.txt, sanksi.txt, etc)
 */

void readFile(int *n, dataName source[], char filename[]) {
    FILE *fTemp;
    fTemp = fopen(filename, "r");

    int returnVal = fscanf(fTemp, "%s %s %s %s",
        source[*n].PrimaryKey,
        source[*n].Atribute,
        source[*n].ForeignKey
    );

    if (strcmp(source[*n].PrimaryKey, "####") == 0)
    {
        printf("File Kosong\n");
    } else {
        while (strcmp (source[*n].PrimaryKey, "####") != 0)
        {
            *n = *n + 1;
            fscanf(fTemp, "%s %s %s %s",
            source[*n].PrimaryKey,
            source[*n].Atribute,
            source[*n].ForeignKey
            );
        }
        
    }
    fclose(fTemp);
}

/**
 * Query Show digunakan untuk menampilkan isi dari 
 * file.txt agar dapat di baca oleh pengguna dbms
 */

void queryShow(char ribbon[], int n, dataName source[]) {
    
    for (int i = 0; i < n; i++)
    {
        /* code */
    }
    
}
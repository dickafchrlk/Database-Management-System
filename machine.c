#include "library.h"


/**
 * Mesin Abstrak
 * 
 */
int idx; // index
int wlen; // panjang current word
char cw[255]; // current word

// cek eop
int eop(char pita[]){
    if(pita[idx] == ';'){ // jika ';' return 1
        return 1;
    }
    else{
        return 0; // jika bukan ';' kembalikan 0
    }
}

// nyalakan mesin
void start(char pita[]){
    // set index dan panjang kata menjadi 0
    idx = 0;
    wlen = 0;


    while (pita[idx] == ' '){ // ignore blank
        idx++;
    }


    // ambil kata masukkan dalam current word
    while ((pita[idx] != ' ') && (eop(pita) == 0)){
        cw[wlen] = pita[idx];
        wlen++;
        idx++;
    }
    cw[wlen] = '\0'; // akhiri dengan null terminator
}

// reset current word
void reset(){
    wlen = 0; // kembalikan panjang kata menjadi 0
    cw[wlen] = '\0'; // set current word menjadi null (siap diisi)
}

// pindah next kata
void inc(char pita[]){
    wlen = 0; // set panjang kata jadi 0 (memastikan)


    while (pita[idx] == ' '){ // ignore blank
        idx++;
    }


    // masukkan kata baru
    while ((pita[idx] != ' ') && (eop(pita) == 0)){
        cw[wlen] = pita[idx];
        wlen++;
        idx++;
    }
    cw[wlen] = '\0'; // akhiri lagi
}

// mengembalikan current word
char* getcw(){
    return cw;
}

// mengembalikan panjang current word
int getlen(){
    return wlen;
}

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
 * Sequential Seacrh
 * Proses pencarian data dengan membandingkan target dengan data
 * untuk menemukan nya. Digunakan untuk mencari data dari file / database
 */
int SequentialSearch(int n, dataName arr[], char target[]){
    int idx = 0; // Counter
    
    while(idx < n)
    // perulangan while sebanyak total data (n)
    {
        if(strcmp(target, arr[idx].PrimaryKey) == 0)
        // if statement untuk membandingkan target dengan data
        {
            // jika sama maka kembalikan nilai index nya
           return idx;
        }
        else
        // apabila primary key saat ini dengan index tidak sama
        {
            // Majukan counter untuk mencari target
            idx++;
        }
    }
    // kembalikan nilai
    return -1;
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
        source[*n].ForeignKey,
        source[*n].Atribute1,
        source[*n].Atribute2
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
            source[*n].ForeignKey,
            source[*n].Atribute1,
            source[*n].Atribute2
            );
        }
    }
    fclose(fTemp);
}

/**
 * Write data
 * Prosedur ini digunakan untuk mengakses dan menulis ulang
 * data dari file.txt
 */

void writeFile(int n, dataName source[], char fileName[]) {
    FILE *fTemp;
    fTemp = fopen(fileName, "w");

    for (int i = 0; i < n; i++)
    {
        fprintf(fTemp, "%s %s %s %s\n",
            source[i].PrimaryKey,
            source[i].ForeignKey,
            source[i].Atribute1,
            source[i].Atribute2
        );
    }
    fprintf(fTemp, "%s %s %s %s\n", "####", "####", "####");
    
    fclose(fTemp);
}


/**
 * Query Create / add digunakan untuk menambahkan item / objek
 * kedalam database
 */

void queryAdd (char ribbon[], int n, dataName source[]) {
    char temp_primary[255];
    char temp_foreign[255];
    char temp_atribute1[255];
    char temp_atribute2[255];

    inc(ribbon);
    if (getlen() != NULL)
    {
        strcpy(temp_primary, getcw());
    } else {
        printf("\033[91mError: PrimaryKey tidak valid.\033[0m\n");
        return;
    }
    
    inc(ribbon);
    if (getlen() != NULL)
    {
        strcpy(temp_foreign, getcw());
    } else {
        printf("\033[91mError: ForeignKey tidak valid.\033[0m\n");
        return;
    }
    
    inc(ribbon);
    if (getlen() != NULL)
    {
        strcpy(temp_atribute1, getcw());
    } else {
        printf("\033[91mError: Atribute tidak valid.\033[0m\n");
        return;
    }

    inc(ribbon);
    if (getlen() != NULL)
    {
        strcpy(temp_atribute2, getcw());
    } else {
        printf("\033[91mError: Atribute tidak valid.\033[0m\n");
        return;
    }

    // buat flag untuk pencarian data
    int found = SequentialSearch(n, source, temp_primary); 

    // if statement untuk mencari apakah ada data yang sama / tidak
    if (found == -1) // tidak ketemu / tidak ada data yang sama
    {
        // masukan data baru ke dalam source
        strcpy(source[n].PrimaryKey, temp_primary);
        strcpy(source[n].PrimaryKey, temp_foreign);
        strcpy(source[n].PrimaryKey, temp_atribute1);
        strcpy(source[n].PrimaryKey, temp_atribute2);

        //tambahkan jumlah variable pada jumlah data / file
        n++;
        printf("SUCCESS: Kasus berhasil ditambahkan.\n");
        
        // simpan data ke dalam file sanksi.txt
        writeFileKasus(n,source, "kasus.txt");
    } else {
        // Error handling...
        // Error handling Jika terdapat primary key yang sama
        printf("\033[91mError: Terdapat Code Primary Yang Sama.\033[0m\n");
    }
}

/**
 * Query Read / Show digunakan untuk menampilkan isi dari 
 * file.txt agar dapat di baca oleh pengguna dbms
 */

void queryShow(dataName source[]) {
    int n = 0;
    readFile(&n, source, "file.txt");

    for (int i = 0; i < n; i++)
    {
        printf("| %-*s | %-*s | %-*s | %-*s |\n", 
            source[i].PrimaryKey,   // Id / Kode unik
            source[i].ForeignKey,   // Kode penghubung
            source[i].Atribute1,    // Nama
            source[i].Atribute2     // Perilaku
        );
    }
}

/**
 * Query Update
 * 
 */

void queryUpdate(char ribbon[], int n, dataName source[]) {
    char primaryKey[255];
    char update[255];

    inc(ribbon);
    
    if (getlen() > 0)
    {
        strcpy(primaryKey, getcw());

    }else{
        printf("\033[91mError: Primary Key tidak Valid.\033[0m\n");
        return;
    }
    
    inc(ribbon);

    if (getlen() > 0)
    {
        strcpy(update, getcw());
    }else{
        printf("\033[91mError: Data tidak Valid.\033[0m\n");
        return;
    }

    int found = SequentialSearch(n, source, update);

    if (found != -1) // jika code id tersebut ada
    {
        strcpy(source[found].Atribute1, update);
    
        printf("SUCCESS: Data berhasil di update.\n");
    }else{
        printf("\033[91mERROR: Primary Key Tersebut Tidak DiTemukan.\033[0m\n");
    }

    writeFile(n, source, "sanksi.txt");
}


/**
 * Query Delete
 * 
 */

void queryDelete(char ribbon[], int n, dataName source[]) {
    char primaryKey[255];
    inc(ribbon);
    
    if (getlen() != NULL)
    {
        strcpy(primaryKey, getcw());
    } else {
        printf("\033[91mError: Kode delete tidak valid.\033[0m\n");   
    }

    int found = SequentialSearch(n, source, primaryKey);

    if (found != -1) // jika terdapat code tersebut dalam data
    {
        for (int i = found; i < n - 1; i++)
        {
            strcpy(source[i].PrimaryKey, source[i + 1].PrimaryKey); 
            strcpy(source[i].ForeignKey, source[i + 1].ForeignKey); 
            strcpy(source[i].Atribute1, source[i + 1].Atribute1); 
            strcpy(source[i].Atribute2, source[i + 1].Atribute2); 
            
        }
        strcpy(source[n - 1].PrimaryKey, "####");
        strcpy(source[n - 1].ForeignKey, "####");
        strcpy(source[n - 1].Atribute1, "####");
        strcpy(source[n - 1].Atribute2, "####");

        n--;

        printf("SUCCESS: Data kasus berhasil di hapus.\n");
    } else {
        // Error handling...
        printf("\033[91mError: Code Kasus Tersebut Tidak Ditemukan.\033[0m\n");
    }
}
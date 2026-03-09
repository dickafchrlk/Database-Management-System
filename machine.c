#include "library.h"


/**
 * Mesin Abstrak
 * 
 */
int idx; // index
int wlen; // panjang current word
char cw[255]; // current word

// cek eop
int eop(char pita[]) {
    if((pita[idx] == ';') || (pita[idx] == '\0')){ // jika ';' return 1
        return 1;
    }
    else{
        return 0; // jika bukan ';' kembalikan 0
    }
}

// nyalakan mesin
void start(char pita[]) {
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
void reset() {
    wlen = 0; // kembalikan panjang kata menjadi 0
    cw[wlen] = '\0'; // set current word menjadi null (siap diisi)
}

// pindah next kata
void inc(char pita[]) {
    wlen = 0; // set panjang kata jadi 0 (memastikan)


    while ((pita[idx] == ' ') && (eop(pita) == 0)){ // ignore blank
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
char* getcw() {
    return cw;
}

// mengembalikan panjang current word
int getlen() {
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
    char pivot[255];
    strcpy(pivot, arr[low].primaryKey);

    int i = low;
    int j = high;

    while (i < j)
    {
        // mencari element pertama yang lebih besar dari pivot
        // pivot (di awal)
        while (i <= high - 1 && strcmp(arr[i].primaryKey, pivot) <= 0)
        {
            i++;
        }

        // mencari element pertama yang lebih kecil dari pivot
        // pivot (di akhir)
        while (j >= low + 1 && strcmp(arr[j].primaryKey, pivot) > 0)
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

void quickSort(dataName arr[], int low, int high) {
    if (low < high)
    {
        // Gunakan prosedur partition untuk mencari pivot
        int pi = partition(arr, low, high);

        // Gunakan pemanggilan rekursif dari prosedur quicksort
        // setengah kiri dan kanan yang di pisah menggunakan pivot
        quickSort (arr, low, pi - 1);
        quickSort (arr, pi + 1, high);
    }
}

/**
 * Sequential Seacrh
 * Proses pencarian data dengan membandingkan target dengan data
 * untuk menemukan nya. Digunakan untuk mencari data dari file / database
 */
int SequentialSearch(int n, dataName arr[], char target[]) {
    int idx = 0; // Counter
    
    while(idx < n)
    // perulangan while sebanyak total data (n)
    {
        if(strcmp(target, arr[idx].primaryKey) == 0)
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

    if (fTemp == NULL) {
        printf("File tidak ditemukan\n");
        return;
    }
    
    while (fscanf(fTemp,"%s %s %s %s",
            source[*n].primaryKey,
            source[*n].foreignKey,
            source[*n].name,
            source[*n].attribute) == 4 &&
            strcmp(source[*n].primaryKey,"####") != 0)
    {
        (*n)++;
    }
    fclose(fTemp);
}

/**
 * Write data
 * Prosedur ini digunakan untuk mengakses dan menulis ulang
 * data dari file.txt
 */

void writeFile(int *n, dataName source[], char fileName[]) {
    FILE *fTemp;
    fTemp = fopen(fileName, "w");
    
    if (fTemp == NULL) {
        printf("File tidak ditemukan\n");
        return;
    }
    
    for (int i = 0; i < *n; i++)
    {
        fprintf(fTemp, "%s %s %s %s\n",
            source[i].primaryKey,
            source[i].foreignKey,
            source[i].name,
            source[i].attribute
        );
    }
    fprintf(fTemp, "%s %s %s %s\n", "####", "####", "####", "####");
    
    fclose(fTemp);
}


/**
 * Query Create / add digunakan untuk menambahkan item / objek
 * kedalam database
 */

void queryAdd (char ribbon[], int *n, dataName source[], char fileName[]) {
    char temp_primary[255];
    char temp_foreign[255];
    char temp_name[255];
    char temp_attribute[255];

    if (*n >= 50)
    {
        printf("Database penuh\n");
        return;
    }

    inc(ribbon);
    if (getlen() > 0)
    {
        strcpy(temp_primary, getcw());
    } else {
        printf("\033[91mError: PrimaryKey tidak valid.\033[0m\n");
        return;
    }
    
    inc(ribbon);
    if (getlen() > 0)
    {
        strcpy(temp_foreign, getcw());
    } else {
        printf("\033[91mError: foreignKey tidak valid.\033[0m\n");
        return;
    }
    
    inc(ribbon);
    if (getlen() > 0)
    {
        strcpy(temp_name, getcw());
    } else {
        printf("\033[91mError: name tidak valid.\033[0m\n");
        return;
    }

    inc(ribbon);
    if (getlen() > 0)
    {
        strcpy(temp_attribute, getcw());
    } else {
        printf("\033[91mError: Atribute tidak valid.\033[0m\n");
        return;
    }

    // buat flag untuk pencarian data
    int found = SequentialSearch(*n, source, temp_primary); 

    // if statement untuk mencari apakah ada data yang sama / tidak
    if (found == -1) // tidak ketemu / tidak ada data yang sama
    {
        // masukan data baru ke dalam source
        strcpy(source[*n].primaryKey, temp_primary);
        strcpy(source[*n].foreignKey, temp_foreign);
        strcpy(source[*n].name, temp_name);
        strcpy(source[*n].attribute, temp_attribute);

        //tambahkan jumlah variable pada jumlah data / file
        (*n)++;
        printf("SUCCESS: Kasus berhasil ditambahkan.\n");
        
        // simpan data ke dalam file
        writeFile(n, source, fileName);
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

void queryShow(int *n, dataName source[]) {
    if(*n > 0){
        quickSort(source, 0, *n - 1);
    

        for (int i = 0; i < *n; i++)
        {
            printf("| %-10s | %-10s | %-20s | %-20s |\n",
                source[i].primaryKey,
                source[i].foreignKey,
                source[i].name,
                source[i].attribute
            );
        }
    } else {
        // Error handling...
        // Error handling Jika database kosong
        printf("\033[91mError: Database Kosong.\033[0m\n");
    }
}

/**
 * Query Update
 * Digunakan untuk mengupdate data
 */

void queryUpdate(char ribbon[], int *n, dataName source[], char fileName[]) {
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

    int found = SequentialSearch(*n, source, primaryKey);

    if (found != -1) // jika code id tersebut ada
    {
        strcpy(source[found].name, update);
        writeFile(n, source, fileName);
        printf("SUCCESS: Data berhasil di update.\n");
    }else{
        printf("\033[91mERROR: Primary Key Tersebut Tidak DiTemukan.\033[0m\n");
    }
}

/**
 * Query Delete
 * Digunakan untuk menghapus data dari database
 */

void queryDelete(char ribbon[], int *n, dataName source[], char fileName[]) {
    char primaryKey[255];
    inc(ribbon);
    
    if (getlen() > 0)
    {
        strcpy(primaryKey, getcw());
    } else {
        printf("\033[91mError: Kode delete tidak valid.\033[0m\n");   
    }

    int found = SequentialSearch(*n, source, primaryKey);

    if (found != -1) // jika terdapat code tersebut dalam data
    {
        for (int i = found; i < *n - 1; i++)
        {
            strcpy(source[i].primaryKey, source[i + 1].primaryKey); 
            strcpy(source[i].foreignKey, source[i + 1].foreignKey); 
            strcpy(source[i].name, source[i + 1].name); 
            strcpy(source[i].attribute, source[i + 1].attribute); 
            
        }
        strcpy(source[*n - 1].primaryKey, "####");
        strcpy(source[*n - 1].foreignKey, "####");
        strcpy(source[*n - 1].name, "####");
        strcpy(source[*n - 1].attribute, "####");

        (*n)--;

        printf("SUCCESS: Data kasus berhasil di hapus.\n");
    } else {
        // Error handling...
        printf("\033[91mError: Code Kasus Tersebut Tidak Ditemukan.\033[0m\n");
        return;
    }
    writeFile(n, source, fileName);
}
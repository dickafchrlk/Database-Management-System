#include "library.h"

int main() {
    char ribbon[501];
    int exit = 0;

    dataName kasus[51];
    int indexkasus = 0;

    readFile(&indexkasus, kasus, "database.txt");

    while (exit != 1)
    {
        scanf(" %500[^\n]", ribbon);
        start(ribbon);

        if (((strcmp(getcw(), "exit") == 0) || (strcmp(getcw(), "EXIT") == 0)) && 
            eop(ribbon) == 1 )
        {
            return 0;
        }
        
        if (strcmp(getcw(), "show") == 0 || strcmp(getcw(), "SHOW") == 0)
        {
            queryShow(&indexkasus, kasus);
        } else if (strcmp(getcw(), "insert") == 0 || strcmp(getcw(), "INSERT") == 0)
        {
            queryAdd(ribbon, &indexkasus, kasus, "database.txt");
        } else if (strcmp(getcw(), "update") == 0 || strcmp(getcw(), "UPDATE") == 0)
        {
            queryUpdate(ribbon, &indexkasus, kasus, "database.txt");
        } else if (strcmp(getcw(), "delete") == 0 || strcmp(getcw(), "DELETE") == 0) 
        {
            queryDelete(ribbon, &indexkasus, kasus, "database.txt");
        } else if (eop(ribbon) == 0)
        {
            printf("\033[91mError: Perintah query harus diakhiri dengan ';'.\033[0m\n");
        } else {
            printf("\033[91mError: Perintah tidak valid. Gunakan SHOW, INSERT, UPDATE, DELETE, EXIT.\033[0m\n");
        }
    }
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "begin.h"
#include "admin.h"
#include "user.h"
#include "petugas.h"

int main()
{
    system("cls");
    user *cekuser = (user *)malloc(sizeof(user));
    
    FILE *cek_file;
    cek_file = fopen("users.txt", "r");
    
    if (cek_file == NULL){
        CreateUser(cekuser);
    }
    
    fclose(cek_file);
//    free(cekuser);

    LoginUser(cekuser);
}

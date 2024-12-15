#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "user.h"
#include "begin.h"
#include "petugas.h"

void userMenu()
{
    system("cls");
    int choice;
    buku buku;

    system("cls");
    printf("        ========================================== Menu User ==========================================\n\n");
    printf("                                            pilih hanya angka nya saja\n");
    printf("                                                [1] => Lihat buku\n");
    printf("                                                [2] => lihat buku yang dipinjam\n");
    printf("                                                [3] => logout\n");

    printf("        =================================================================================================\n\n");
    printf("                                            masukkan pilihan(1/2/3): ");
    scanf("                                                           %d", &choice);

    if (choice == 1)
    {
        system("cls");
        char filename[] = "buku.txt";
        ReadData(filename);
        printf("\ntekan tombol apa saja untuk kembali");
        getch();
        userMenu();
    }

    else if (choice == 2)
    {
        system("cls");
        char filename[] = "peminjaman.txt";
        ReadData(filename);
        printf("\ntekan tombol apa saja untuk kembali");
        getch();
        userMenu();
    }
    else if (choice == 3)
    {
        system("cls");
        user user;
        LoginUser(&user);
    }
}

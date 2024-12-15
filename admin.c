#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "admin.h"
#include "begin.h"

void adminMenu()
{
    system("cls");
    user user;
    buku buku;
    int choice = 0;

    printf("        ========================================== Admin Menu ==========================================\n\n");
    printf("                                            pilih hanya angka nya saja\n");
    printf("                                                [1] => tambahkanbuku\n");
    printf("                                                [2] => tambahkan user\n");
    printf("                                                [3] => hapus buku\n");
    printf("                                                [4] => hapus user\n");
    printf("                                                [5] => lihat user\n");
    printf("                                                [6] => update user\n\n");
    printf("                                                [7] => Logout\n\n");

    printf("        =================================================================================================\n\n");

    printf("                                            masukkan pilihan(1/2/3/4/5/6/7): ");
    scanf("                                                           %d", &choice);
    if (choice == 1)
    {
        system("cls");
        Addbuku(&buku);
        printf("tekan tombol apa saja untuk kembali");
        getch();
        adminMenu();
    }

    else if (choice == 2)
    {
        system("cls");
        AddUser(&user);
        printf("tekan tombol apa saja untuk kembali");
        getch();
        adminMenu();
    }
    else if (choice == 3)
    {
        system("cls");
        char hapus[] = "buku.txt";
        int targetId;
        printf("        ============================================== Menghapus buku ==============================================\n\n");
        printf("                                        masukkan ID buku yang ingin di hapus:\n");

        printf("                                                           ");
        scanf("%d", &targetId);
        printf("        ============================================================================================================\n\n");

        Deletebuku(hapus, targetId);
        printf("tekan tombol apa saja untuk kembali");
        getch();
        adminMenu();
    }
    else if (choice == 4)
    {
        system("cls");
        char hapus[] = "users.txt";
        int targetId;

        printf("        ============================================== Menghapus user ==============================================\n\n");
        printf("                                        masukkan ID user yang ingin di hapus:\n");

        printf("                                                           ");
        scanf("%d", &targetId);
        printf("        ============================================================================================================\n\n");

        DeleteUser(hapus, targetId);
        printf("tekan tombol apa saja untuk kembali");
        getch();
        adminMenu();
    }
    else if (choice == 5)
    {
        system("cls");
        char filename[] = "users.txt";
        ReadData(filename);
        printf("\ntekan tombol apa saja untuk kembali\n");
        getch();
        adminMenu();
    }
    else if (choice == 6)
    {
        int targetId;
        system("cls");
        printf("        ============================================== mengupdate user ==============================================\n\n");
        printf("                                        masukkan ID user yang ingin di update:\n");

        printf("                                                           ");
        scanf("%d", &targetId);
        printf("        ============================================================================================================\n\n");
        char filename[] = "users.txt";
        UpdateUser(filename,targetId);
    }
    else if (choice == 7)
    {
        system("cls");
        LoginUser(&user);
    }
}

void AddUser(user *user)
{
    printf("\n      ========================================================================================================\n");
    printf("\n      |||                                    ****** Menambah User ******                                   |||\n");
    printf("\n      ========================================================================================================\n\n");

    printf("                                                    Masukkan ID User: ");
    scanf("%d", &user->id);
    int id = user->id;

    FILE *cekuser = fopen("users.txt", "r");
    while (fscanf(cekuser, "%d %s %s %s", &user->id, user->username, user->password, user->role) != EOF)
    {
        if (id == user->id)
        {
            printf("id sudah ada");
            AddUser(user);
        }
        else
        {
            break;
        }
    }
    fclose(cekuser);

    user->id = id;
    printf("                                                    Masukkan Username: ");
    scanf("%s", user->username);

    printf("                                                    Masukkan Password: ");
    scanf("%s", user->password);

    strcpy(user->role, "user");
    SetUser(user);
}

void Addbuku(buku *buku)
{

    printf("\n      ====================================================================================================\n");
    printf("\n      |||                                   ****** Menambah Buku ******                                |||\n");
    printf("\n      ====================================================================================================\n\n");
    printf("                                                masukkan id buku: ");
    scanf("%d", &buku->id);

    printf("                                                masukkan judul buku: ");
    scanf("\n%s", &buku->judul);

    printf("                                                masukkan penulis buku: ");
    scanf("\n%s", &buku->penulis);

    printf("                                                masukkan tahun terbit buku: ");
    scanf("\n%d", &buku->tahunTerbit);

    printf("                                                masukkan jumlah buku: ");
    scanf("\n%d", &buku->jumlahBuku);
    SetBuku(buku);
}

void DeleteUser(char *filename, int targetId)
{
    FILE *file = fopen(filename, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (file == NULL || temp == NULL)
    {
        printf("Gagal membuka file!\n");
        return;
    }

    user currentUser;
    int found = 0;

    while (fscanf(file, "%d %s %s %s", &currentUser.id, &currentUser.username, &currentUser.password, &currentUser.role) != EOF)
    {
        if (currentUser.id == targetId)
        {
            found = 1;
            printf("Data dengan ID %d telah dihapus!\n", currentUser.id);
            continue;
        }
        fprintf(temp, "%d %s %s %s\n", currentUser.id, currentUser.username, currentUser.password, currentUser.role);
    }

    fclose(file);
    fclose(temp);

    if (found)
    {
        remove(filename);
        rename("temp.txt", filename);
    }
    else
    {
        remove("temp.txt");
        printf("ID tidak ditemukan!\n");
    }
}

void Deletebuku(char *filename, int targetId)
{
    FILE *filebuku = fopen(filename, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (filebuku == NULL || temp == NULL)
    {
        printf("Gagal membuka file!\n");
        return;
    }

    buku buku;
    int found = 0;

    while (fscanf(filebuku, "%d %s %s %d %d\n", &buku.id, &buku.judul, &buku.penulis, &buku.tahunTerbit, &buku.jumlahBuku) != EOF)
    {
        if (buku.id == targetId)
        {
            found = 1;
            if (buku.jumlahBuku == 1)
            {
                continue;
            }
            else
            {
                fprintf(temp, "%d %s %s %d %d\n", buku.id, buku.judul, buku.penulis, buku.tahunTerbit, buku.jumlahBuku - 1);
            }
            printf("1 buku dengan id %d telah di hapus\n", buku.id);
            continue;
        }
        fprintf(temp, "%d %s %s %d %d\n", buku.id, buku.judul, buku.penulis, buku.tahunTerbit, buku.jumlahBuku);
    }

    fclose(filebuku);
    fclose(temp);

    if (found)
    {
        remove(filename);
        rename("temp.txt", filename);
    }
    else
    {
        remove("temp.txt");
        printf("ID tidak ditemukan!\n");
    }
}

void UpdateUser(char *filename, int targetId)
{
    FILE *file = fopen(filename, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (file == NULL || temp == NULL)
    {
        printf("Gagal membuka file!\n");
        return;
    }

    user currentUser;
    int found = 0;

    while (fscanf(file, "%d %s %s %s", &currentUser.id, currentUser.username, currentUser.password, currentUser.role) != EOF)
    {
        if (currentUser.id == targetId)
        {
            found = 1;
            printf("                            Data lama: ID: %d, Username: %s, Password: %s, Role: %s\n", currentUser.id, currentUser.username, currentUser.password, currentUser.role);

            printf("                                                    Masukkan Username baru: ");
            scanf("%s", currentUser.username);
            printf("                                                    Masukkan password baru: ");
            scanf("%s", currentUser.password);
        }
        fprintf(temp, "%d %s %s %s\n", currentUser.id, currentUser.username, currentUser.password, currentUser.role);
    }

    fclose(file);
    fclose(temp);

    if (found)
    {
        remove(filename);
        rename("temp.txt", filename);
        printf("Data berhasil diperbarui!\n");
    }
    else
    {
        remove("temp.txt");
        printf("ID tidak ditemukan!\n");
    }
}

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "begin.h"
#include "admin.h"
#include "user.h"
#include "petugas.h"

void CreateUser(user *user)
{
    user->id = 11111;
    strcpy(user->username, "admin");
    strcpy(user->password, "111");
    strcpy(user->role, "admin");

    SetUser(user);

    user->id = 222222;
    strcpy(user->username, "petugas");
    strcpy(user->password, "111");
    strcpy(user->role, "petugas");

    SetUser(user);
}

void LoginUser(user *user)
{
    char usernameInput[50];
    char passwordInput[50];
    char roleInput[20];
    printf("        ===========================================================================================================\n");
    printf("                                                Selamat Datang Di Libraries                                       \n");
    printf("        ===========================================================================================================\n");

    printf("\n");
    printf("        ~ Silahkan Lakukan Login Terlebih Dahulu ~\n");
    printf("        ~ jika akun belum terdaftar silahkan login sebagai admin terlebih dahulu untuk menambahkan/registrasi user ~\n\n");

    printf("        ===========================================================================================================\n");
    printf("                                                            LOGIN\n");
    printf("        ===========================================================================================================\n");
    printf("                                                    Masukkan Username: ");
    scanf("%s", usernameInput);

    printf("                                                    Masukkan Password: ");
    scanf("%s", passwordInput);

    printf("                                                    role (admin/petugas/user): ");
    scanf("%s", roleInput);
    printf("\n      ============================================================================================================\n");

    if (ValidateUser(user, usernameInput, passwordInput, roleInput))
	{
        if (strcmp(roleInput, "admin") == 0)
        {
        	printf("Login Berhasil!\n");
            system("cls");
            adminMenu();
        }
        else if (strcmp(roleInput, "user") == 0)
        {
            system("cls");
            userMenu();
        }
        else
        {
            system("cls");
            petugasMenu();
        }
    }
    else
    {
        printf("Username atau Password Salah atau role tidak sesuai!\n");
    }
}

int ValidateUser(user *user, char *username, char *password, char *role)
{
    FILE *file;
    int found = 0;

    file = fopen("users.txt", "r");
    if (file == NULL)
    {
        printf("Gagal membuka file!\n");
        exit(1);
    }

    while (fscanf(file, "%d %99s %99s %99s", &user->id, user->username, user->password, user->role) != EOF)
    {
        if (strcmp(user->username, username) == 0 && strcmp(user->password, password) == 0 && strcmp(user->role, role) == 0)
        {
            found = 1;
            break;
        }
    }
    fclose(file);
    return found;
}

void SetUser(user *user)
{
    FILE *fileUser;

    fileUser = fopen("users.txt", "a");
    if (fileUser == NULL)
    {
        printf("Gagal membuka file!\n");
        exit(1);
    }

    fprintf(fileUser, "%d %s %s %s\n", user->id, user->username, user->password, user->role);

    printf("Data user berhasil ditambahkan ke file!\n");

    fclose(fileUser);
}


void SetBuku(buku *buku)
{
    FILE *filebuku;

    filebuku = fopen("buku.txt", "a");

    if (filebuku == NULL)
    {
        printf("Gagal membuka file!\n");
        exit(1);
    }

    fprintf(filebuku, "%d %s %s %d %d\n", buku->id, buku->judul, buku->penulis, buku->tahunTerbit, buku->jumlahBuku);
    fclose(filebuku);
    printf("buku berhasil ditambahkan\n\n");
}

/****** Authorization ******/

void ReadData(char *filename)
{
    FILE *file = fopen(filename, "r");
    int recordCount = 0;

    if (strcmp(filename, "users.txt") == 0)
    {
        user currentUser;
        if (file == NULL)
        {
            printf("Gagal membuka file pengguna!\n");
        }

        printf("=========================================================================\n");
        printf("| %-15s | %-15s | %-15s | %-15s |\n", "ID", "Username", "Password", "Role");
        printf("=========================================================================\n");

        while (fscanf(file, "%d %s %s %s", &currentUser.id, currentUser.username, currentUser.password, currentUser.role) != EOF)
        {
            printf("| %-15d | %-15s | %-15s | %-15s |\n", currentUser.id, currentUser.username, currentUser.password, currentUser.role);
            recordCount++;
        }

        if (recordCount == 0)
        {
            printf("|                   Tidak ada data!          |\n");
        }

        printf("=========================================================================\n");
    }
    else if (strcmp(filename, "buku.txt") == 0)
    {
        buku buku;
        if (file == NULL)
        {
            printf("Gagal membuka file pengguna!\n");
            return;
        }

        printf("===========================================================================================\n");
        printf("| %-15s | %-15s | %-15s | %-15s | %-15s |\n", "ID", "Judul", "Penulis", "TahunTerbit", "Jumlahbuku");
        printf("===========================================================================================\n");

        while (fscanf(file, "%d %s %s %d %d", &buku.id, &buku.judul, &buku.penulis, &buku.tahunTerbit, &buku.jumlahBuku) != EOF)
        {
            printf("| %-15d | %-15s | %-15s | %-15d | %-15d |\n", buku.id, buku.judul, buku.penulis, buku.tahunTerbit, buku.jumlahBuku);
            recordCount++;
        }

        if (recordCount == 0)
        {
            printf("|                   Tidak ada data!          |\n");
        }

        printf("===========================================================================================\n");
    }
    else if (strcmp(filename, "peminjaman.txt") == 0)
    {
        peminjaman peminjaman;
        if (file == NULL)
        {
            printf("Gagal membuka file pengguna!\n");
            return;
        }

        printf("============================================================================================================================\n");
        printf("| %-15s | %-15s | %-20s | %-20s | %-20s | %-15s |\n", "ID Peminjaman", "id user", "nama peminjam", "tanggal peminjaman", "tanggal pengembalian", "status");
        printf("============================================================================================================================\n");

        char tanggalpeminjaman[20];
        char tanggalpengembalian[20];

        while (fscanf(file, "%d %d %s %s %s %s", &peminjaman.idPeminjaman, &peminjaman.idUser, peminjaman.namaPeminjam, tanggalpeminjaman, tanggalpengembalian, peminjaman.status) != EOF)
        {
            printf("| %-15d | %-15d | %-20s | %-20s | %-20s | %-15s |\n", peminjaman.idPeminjaman, peminjaman.idUser, peminjaman.namaPeminjam, tanggalpeminjaman, tanggalpengembalian, peminjaman.status);
            recordCount++;
        }

        if (recordCount == 0)
        {
            printf("|                   Tidak ada data!          |\n");
        }

        printf("============================================================================================================================\n");
    }
    else if (strcmp(filename, "pengembalian.txt") == 0)
    {
        pengembalian pengembalian;
        if (file == NULL)
        {
            printf("Gagal membuka file pengguna!\n");
            return;
        }

        printf("===================================================================================\n");
        printf("| %-15s | %-15s | %-20s | %-20s | \n", "ID Peminjaman", "ID Pengembalian", "tanggal pengembalian", "denda");
        printf("===================================================================================\n");

        char tanggalpengembalian[20];

        while (fscanf(file, "%d %d %s %d", &pengembalian.idPengembalian, &pengembalian.idPeminjaman, tanggalpengembalian, &pengembalian.denda) != EOF)
        {
            printf("| %-15d | %-15d | %-20s | %-20d |\n", pengembalian.idPengembalian, pengembalian.idPeminjaman, tanggalpengembalian, pengembalian.denda);
            recordCount++;
        }

        if (recordCount == 0)
        {
            printf("|                   Tidak ada data!          |\n");
        }

        printf("===================================================================================\n");
    }
    fclose(file);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include "petugas.h"
#include "begin.h"

void petugasMenu()
{
    int choice;
    peminjaman peminjaman;
    pengembalian pengembalian;

    printf("        ========================================== Menu Petugas ==========================================\n\n");
    printf("                                            pilih hanya angka nya saja\n");
    printf("                                                [1] => Lihat data buku\n");
    printf("                                                [2] => Buat peminjaman\n");
    printf("                                                [3] => Lihat data peminjaman\n");
    printf("                                                [4] => Buat pengembalian\n");
    printf("                                                [5] => Lihat data pengembalian\n");
    printf("                                                [6] => Logout\n\n");

    printf("        =================================================================================================\n\n");

    printf("                                            masukkan pilihan(1/2/3/4/5/6): ");
    scanf("                                                           %d", &choice);
    if (choice == 1)
    {
    	system("cls");
        char filename[] = "buku.txt";
        ReadData(filename);
        printf("\ntekan tombol apa saja untuk kembali\n");
        getch();
        petugasMenu();
    }
    else if (choice == 2)
    {
        system("cls");
        AddPeminjaman(&peminjaman);
        petugasMenu();
    }
    else if (choice == 3)
    {
    	system("cls");
        char filename[] = "peminjaman.txt";
        ReadData(filename);
        printf("\ntekan tombol apa saja untuk kembali\n");
        getch();
        petugasMenu();
    }
    else if (choice == 4)
    {
        system("cls");
        PengembalianBuku(&pengembalian);
        petugasMenu();
    }
    else if (choice == 5)
    {
    	system("cls");
        char filename[] = "pengembalian.txt";
        ReadData(filename);
        printf("\ntekan tombol apa saja untuk kembali\n");
        getch();
        petugasMenu();
    }
    else if (choice == 6)
    {
        system("cls");
        user user;
        LoginUser(&user);
    }
}

int AmbilStokBuku(int idTarget)
{
    int idBuku, tahunTerbit, stok;
    char judul[100], pengarang[100];

    FILE *fileBuku = fopen("buku.txt", "r");
    if (fileBuku == NULL)
    {
        printf("Gagal membuka file buku!\n");
        return -1;
    }

    while (fscanf(fileBuku, "%d %99s %99s %d %d", &idBuku, judul, pengarang, &tahunTerbit, &stok) != EOF)
    {
        if (idBuku == idTarget)
        {
            fclose(fileBuku);
            return stok;
        }
    }

    fclose(fileBuku);
}

void UbahStok(int idTarget, int newStok)
{
    int idBuku1, tahunTerbit, stok, found;
    char judul[100], pengarang[100];
    found = 0;

    FILE *fileBuku = fopen("buku.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (fileBuku == NULL || temp == NULL)
    {
        printf("Gagal membuka file!\n");
    }

    while (fscanf(fileBuku, "%d %99s %99s %d %d", &idBuku1, judul, pengarang, &tahunTerbit, &stok) != EOF)
    {
        if (idBuku1 == idTarget)
        {
            found = 1;
            fprintf(temp, "%d %s %s %d %d\n", idBuku1, judul, pengarang, tahunTerbit, newStok);
        }
        else
        {
            fprintf(temp, "%d %s %s %d %d\n", idBuku1, judul, pengarang, tahunTerbit, stok);
        }
    }

    fclose(fileBuku);
    fclose(temp);

    remove("buku.txt");
    rename("temp.txt", "buku.txt");
}

int FoundBuku(int idTarget)
{
    int idBuku, tahunTerbit, stok;
    char judul[100], pengarang[100];

    FILE *fileBuku = fopen("buku.txt", "r");
    if (fileBuku == NULL)
    {
        printf("Gagal membuka file buku!\n");
        return -1;
    }

    while (fscanf(fileBuku, "%d %99s %99s %d %d", &idBuku, judul, pengarang, &tahunTerbit, &stok) != EOF)
    {
        if (idBuku == idTarget)
        {
            fclose(fileBuku);
            return 1;
        }
    }

    fclose(fileBuku);
    return -1;
}

int FoundIdUser(int idTarget)
{
    FILE *file;
    int found = 0;
    user user;

    file = fopen("users.txt", "r");
    if (file == NULL)
    {
        printf("Gagal membuka file!\n");
        exit(1);
    }

    while (fscanf(file, "%d %s %s %s", &user.id, user.username, user.password, user.role) != EOF)
    {
        if (user.id, idTarget)
        {
            found = 1;
            break;
        }
    }
    fclose(file);

    return found;
}

int FoundRoleUser(int idTarget)
{
    FILE *file;
    int found = 0;
    user user;

    file = fopen("users.txt", "r");
    if (file == NULL)
    {
        printf("Gagal membuka file!\n");
        exit(1);
    }

    while (fscanf(file, "%d %s %s %s", &user.id, user.username, user.password, user.role) != EOF)
    {
        if (user.id == idTarget && strcmp(user.role, "user") == 0)
        {
            found = 1;
            break;
        }
    }
    fclose(file);

    return found;
}

int getNextId(const char *fileName)
{
    char tanggalHariIni[15], line[200], existingDate[15], fullId[20];
    int increment, tempIncrement;

    increment = 1;
    time_t t = time(NULL);
    struct tm *waktu = localtime(&t);

    snprintf(tanggalHariIni, sizeof(tanggalHariIni), "%02d%02d%04d", waktu->tm_mday, waktu->tm_mon + 1, (waktu->tm_year + 1900));

    FILE *file = fopen(fileName, "r");
    if (file != NULL)
    {

        while (fgets(line, sizeof(line), file))
        {
            char tempNomorPesanan[20];
            sscanf(line, "%[^,]", tempNomorPesanan);
            strncpy(existingDate, tempNomorPesanan, 8);
            existingDate[8] = '\0';

            if (strcmp(existingDate, tanggalHariIni) == 0)
            {
                sscanf(tempNomorPesanan + 8, "%02d", &tempIncrement);
                if (tempIncrement >= increment)
                {
                    increment = tempIncrement + 1;
                }
            }
        }

        fclose(file);
    }

    snprintf(fullId, sizeof(fullId), "%s%02d", tanggalHariIni, increment);
    return atoi(fullId);
}

void UbahStatus(int idTarget, const char *newStatus)
{
    int found, idPeminjaman, idUser, tglPinjam, blnPinjam, thnPinjam, tglKembali, blnKembali, thnKembali;
    char namaPeminjam[100], status[20];

    found = 0;

    FILE *file = fopen("peminjaman.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (file == NULL || temp == NULL)
    {
        printf("Gagal membuka file!\n");
    }

    while (fscanf(file, "%d %d %99s %d-%d-%d %d-%d-%d %s", &idPeminjaman, &idUser, namaPeminjam, &tglPinjam, &blnPinjam, &thnPinjam, &tglKembali, &blnKembali, &thnKembali, status) != EOF)
    {
        if (idPeminjaman == idTarget)
        {
            found = 1;
            fprintf(temp, "%d %d %s %02d-%02d-%04d %02d-%02d-%04d %s\n", idPeminjaman, idUser, namaPeminjam, tglPinjam, blnPinjam, thnPinjam, tglKembali, blnKembali, thnKembali, newStatus);
        }
        else
        {
            fprintf(temp, "%d %d %s %02d-%02d-%04d %02d-%02d-%04d %s\n", idPeminjaman, idUser, namaPeminjam, tglPinjam, blnPinjam, thnPinjam, tglKembali, blnKembali, thnKembali, status);
        }
    }

    fclose(file);
    fclose(temp);

    remove("peminjaman.txt");
    rename("temp.txt", "peminjaman.txt");
}

/****** Peminjaman ******/
void AddPeminjaman(peminjaman *peminjaman)
{
    int iduser, idbuku, choice, stok;
    printf("\n      ========================================================================================================\n");
    printf("\n      |||                                    ****** peminjaman ******                                   |||\n");
    printf("\n      ========================================================================================================\n\n");

    printf("                                            Masukkan id user peminjam :");
    scanf("%d", &iduser);

    if (FoundRoleUser(iduser) == 0)
    {
        printf("\n");
        printf("                          User tidak ditemukan atau tidak memiliki hak untuk meminjam buku!\n");
    }

    printf("                                            1. Masukkan buku ke keranjang\n");
    printf("                                            2. Konfirmasi peminjaman\n\n");
    printf("                                            Masukkan pilihan (1/2): ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        while (choice == 1)
        {
            printf("\n");
            printf("                                          ------------------------------\n");
            printf("                                               Masukkan id buku :");
            scanf("%d", &idbuku);
            stok = AmbilStokBuku(idbuku);

            if (FoundBuku(idbuku) == 1 && stok != -1)
            {
                AddToKeranjang(iduser, idbuku);
                printf("                                            1. Masukkan buku ke keranjang\n");
                printf("                                            2. Konfirmasi peminjaman\n\n");
                printf("                                            Masukkan pilihan (1/2): ");
                scanf("%d", &choice);
            }
            else
            {
                printf("Stok Buku 0 atau Id Buku Tidak Ditemukan!\n");
                while (FoundBuku(idbuku) == 1 && stok != 0)
                {
                    printf("Masukkan id buku :");
                    scanf("%d", &idbuku);
                    stok = AmbilStokBuku(idbuku);
                }
            }
        }
    }

    KonfirmasiPeminjaman(iduser);
}

void AddToKeranjang(int userId, int idBuku)
{
    FILE *keranjangFile = fopen("keranjang.txt", "a");
    fprintf(keranjangFile, "%d %d\n", userId, idBuku);
    fclose(keranjangFile);
    printf("                                            Buku berhasil ditambahkan ke keranjang.\n\n");
}

void KonfirmasiPeminjaman(int userId)
{
    peminjaman peminjam;
    detailPeminjaman detailPeminjam;
    char namaPeminjam[25];
    int idBuku, stok, newStok, dd, mm, yyyy;
    char status[] = "dipinjam";

    char *fileName = "peminjaman.txt";
    FILE *keranjangFile = fopen("keranjang.txt", "r");
    FILE *peminjamanTextFile = fopen("peminjaman.txt", "a");
    FILE *detailPeminjamanFile = fopen("detailPeminjaman.txt", "a");
    if (keranjangFile == NULL || peminjamanTextFile == NULL || detailPeminjamanFile == NULL)
    {
        printf("Gagal membuka file!\n");
    }

    time_t now = time(NULL);
    struct tm *today = localtime(&now);
    peminjam.tanggalPinjam.Tgl = today->tm_mday;
    peminjam.tanggalPinjam.Bln = today->tm_mon + 1;
    peminjam.tanggalPinjam.Thn = today->tm_year + 1900;

    printf("\n");
    printf("                                       ----------------------------------------\n");
    printf("                                             Masukkan nama peminjam :");
    scanf("%s", namaPeminjam);
    strcpy(peminjam.namaPeminjam, namaPeminjam);

    peminjam.idUser = userId;
    peminjam.idPeminjaman = getNextId(fileName);
    strcpy(peminjam.status, status);

    printf("                                             Masukkan tanggal pengembalian (dd mm yyyy): ");

    scanf("%d %d %d", &dd, &mm, &yyyy);

    if (mm < 1 || mm > 12 || dd < 1 || dd > 31)
    {
        printf("Tanggal tidak valid!\n");
        return;
    }
    peminjam.tanggalKembali.Tgl = dd;
    peminjam.tanggalKembali.Bln = mm;
    peminjam.tanggalKembali.Thn = yyyy;

    char tanggalPinjam[20], tanggalKembali2[20];
    snprintf(tanggalPinjam, sizeof(tanggalPinjam), "%02d-%02d-%04d",
             peminjam.tanggalPinjam.Tgl,
             peminjam.tanggalPinjam.Bln,
             peminjam.tanggalPinjam.Thn);
    snprintf(tanggalKembali2, sizeof(tanggalKembali2), "%02d-%02d-%04d",
             peminjam.tanggalKembali.Tgl,
             peminjam.tanggalKembali.Bln,
             peminjam.tanggalKembali.Thn);
    fprintf(peminjamanTextFile, "%d %d %s %s %s %s\n", peminjam.idPeminjaman, peminjam.idUser, peminjam.namaPeminjam, tanggalPinjam, tanggalKembali2, peminjam.status);

    while (fscanf(keranjangFile, "%d %d", &userId, &idBuku) != EOF)
    {
        detailPeminjam.idPeminjaman = peminjam.idPeminjaman;
        detailPeminjam.idBuku = idBuku;
        fprintf(detailPeminjamanFile, "%d %d\n", detailPeminjam.idPeminjaman, detailPeminjam.idBuku);
        stok = AmbilStokBuku(idBuku);
        newStok = stok - 1;
        UbahStok(idBuku, newStok);
    }

    fclose(keranjangFile);
    fclose(peminjamanTextFile);
    fclose(detailPeminjamanFile);

    remove("keranjang.txt");
    printf("Peminjaman berhasil dikonfirmasi!\n");
}

/****** Pengembalian ******/
int hitungHari(int d1, int m1, int y1, int d2, int m2, int y2)
{
    int a[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((y1 % 4 == 0 && y1 % 100 != 0) || (y1 % 400 == 0))
        a[2] = 29;

    int hari1 = d1 + m1 * 30 + y1 * 365;
    int hari2 = d2 + m2 * 30 + y2 * 365;
    return hari1 - hari2;
}

void PengembalianBuku(pengembalian *pengembalianData)
{
    int inputIdPeminjaman, idPeminjaman, idPeminjamanBuku, idUser, idBuku, stok, newStok, tglPinjam, blnPinjam, thnPinjam, tglKembali, blnKembali, thnKembali, daysLate, denda;
    char namaPeminjam[100], status[20], tanggalKembali[20];
    int idDitemukan = 0;
    char *fileName = "pengembalian.txt";
    FILE *peminjamanFileTxt = fopen("peminjaman.txt", "r");
    FILE *pengembalianFileTxt = fopen("pengembalian.txt", "a");
    FILE *detailPeminjamanFile = fopen("detailPeminjaman.txt", "r");

    if (peminjamanFileTxt == NULL || pengembalianFileTxt == NULL || detailPeminjamanFile == NULL)
    {
        printf("Gagal membuka file!\n");
    }

    printf("                                    Masukkan ID peminjaman yang ingin dikembalikan: ");
    scanf("%d", &inputIdPeminjaman);

    while (fscanf(peminjamanFileTxt, "%d %d %s %d-%d-%d %d-%d-%d %s", &idPeminjaman, &idUser, namaPeminjam, &tglPinjam, &blnPinjam, &thnPinjam, &tglKembali, &blnKembali, &thnKembali, status) != EOF)
    {

        if (idPeminjaman == inputIdPeminjaman)
        {
            if (strcmp(status, "dikembalikan") == 0)
            {
                printf("Peminjaman dengan ID %d sudah dikembalikan. Masukkan ID peminjaman lain.\n", inputIdPeminjaman);
                fclose(peminjamanFileTxt);
                fclose(pengembalianFileTxt);
                fclose(detailPeminjamanFile);
            }

            idDitemukan = 1;
            printf("Nama Peminjam: %s\n", namaPeminjam);

            time_t now = time(NULL);
            struct tm *today = localtime(&now);

            daysLate = hitungHari(today->tm_mday, today->tm_mon + 1, today->tm_year + 1900, tglKembali, blnKembali, thnKembali);
            denda = 0;
            if (daysLate > 0)
            {
                denda = daysLate * 5000;
                printf("Buku terlambat dikembalikan selama %d hari.\n", daysLate);
                printf("Denda yang harus dibayar: Rp%d\n", denda);
            }

            pengembalianData->idPengembalian = getNextId(fileName);
            pengembalianData->idPeminjaman = idPeminjaman;
            pengembalianData->tanggalKembali.Tgl = today->tm_mday;
            pengembalianData->tanggalKembali.Bln = today->tm_mon + 1;
            pengembalianData->tanggalKembali.Thn = today->tm_year + 1900;
            pengembalianData->denda = denda;

            snprintf(tanggalKembali, sizeof(tanggalKembali), "%02d-%02d-%04d", pengembalianData->tanggalKembali.Tgl, pengembalianData->tanggalKembali.Bln, pengembalianData->tanggalKembali.Thn);
            fprintf(pengembalianFileTxt, "%d %d %s %d\n", pengembalianData->idPengembalian, pengembalianData->idPeminjaman, tanggalKembali, denda);

            while (fscanf(detailPeminjamanFile, "%d %d", &idPeminjamanBuku, &idBuku) != EOF)
            {
                if (idPeminjamanBuku == inputIdPeminjaman)
                {
                    stok = AmbilStokBuku(idBuku);
                    newStok = stok + 1;
                    UbahStok(idBuku, newStok);
                }
            }
            
		    fclose(peminjamanFileTxt);
		    fclose(pengembalianFileTxt);
		    fclose(detailPeminjamanFile);

            UbahStatus(inputIdPeminjaman, "dikembalikan");

            printf("Pengembalian berhasil diproses.\n");
            break;
        }
    }

    if (!idDitemukan)
    {
        printf("ID peminjaman tidak ditemukan.\n");
    }

    fclose(peminjamanFileTxt);
    fclose(pengembalianFileTxt);
    fclose(detailPeminjamanFile);
}

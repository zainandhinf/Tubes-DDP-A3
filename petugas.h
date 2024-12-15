#ifndef petugas_h
#define petugas_h
#include "begin.h"

void petugasMenu();
int AmbilStokBuku(int idTarget);
void UbahStok(int idTarget, int newStok);
int FoundBuku(int idTarget);
int FoundIdUser(int idTarget);
int FoundRoleUser(int idTarget);
void UbahStatus(int idTarget, const char *newStatus);
int getNextId(const char *fileName);
void AddPeminjaman(peminjaman *peminjaman);
void AddToKeranjang(int userId, int idBuku);
void KonfirmasiPeminjaman(int userId);
int hitungHari(int d1, int m1, int y1, int d2, int m2, int y2);
void PengembalianBuku(pengembalian *pengembalianData);

#endif

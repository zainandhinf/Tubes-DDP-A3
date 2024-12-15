#ifndef peminjaman_h
#define peminjaman_h

typedef struct { 
	int Tgl; 
	int Bln; 
	int Thn;
} tanggal;

typedef struct {
    int id;
    char username[50];
    char password[50];
    char role[50];
} user;

typedef struct {
    int id;
    char judul[100];
    char penulis[100];
    int tahunTerbit;    
    int jumlahBuku;
} buku;

typedef struct {
    int idPeminjaman;
    int idUser;
    char namaPeminjam[100];
    tanggal tanggalPinjam;
    tanggal tanggalKembali;
    char status[20];
} peminjaman;

typedef struct {
    int idPeminjaman;
    int idBuku;
} detailPeminjaman;	

typedef struct {
    int idPengembalian;
    int idPeminjaman;
    tanggal tanggalKembali;
    int denda;
} pengembalian;


void CreateUser(user *user);
void LoginUser(user *user);
int ValidateUser(user *user, char *username, char *password, char *role);
void SetUser(user *user);
void SetBuku(buku *buku);
void ReadData(char *filename);

#endif


#ifndef admin_h
#define admin_h
#include "begin.h"


void adminMenu();
void UpdateUser( char *filename, int targetId);
void AddUser(user *user);
void Addbuku(buku *buku); 
void DeleteUser(char *filename, int targetId);
void Deletebuku(char *filename, int targetId);
void UpdateUser(char *filename, int targetId);

#endif
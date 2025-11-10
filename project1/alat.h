#ifndef ALAT_H
#define ALAT_H

typedef struct {
    unsigned int id;
    char nama[50];
    char merek[30];
    char model[30];
    unsigned int tahun;
    unsigned int jumlah;
} Alat;

void tampilkanAlat();
void tambahAlat();
void hapusAlat();
void editAlat();

#endif


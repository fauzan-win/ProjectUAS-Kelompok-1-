#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alat.h"
#include "peminjaman.h"

void pinjamAlat(char *username) {
    unsigned int id;
    printf("Masukkan ID alat yang ingin dipinjam: ");
    scanf("%u", &id);

    FILE *fp = fopen("alat.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    FILE *pinjam = fopen("pinjaman.txt", "a");
    Alat alat;
    int found = 0;

    while (fscanf(fp, "%u;%[^;];%[^;];%[^;];%u;%u\n",
                  &alat.id, alat.nama, alat.merek, alat.model, &alat.tahun, &alat.jumlah) == 6) {
        if (alat.id == id && alat.jumlah > 0) {
            alat.jumlah--;
            found = 1;
            fprintf(pinjam, "%s;%u;%s\n", username, alat.id, alat.nama);
            printf("Peminjaman berhasil!\n");
        }
        fprintf(temp, "%u;%s;%s;%s;%u;%u\n",
                alat.id, alat.nama, alat.merek, alat.model, alat.tahun, alat.jumlah);
    }

    fclose(fp);
    fclose(temp);
    fclose(pinjam);
    remove("alat.txt");
    rename("temp.txt", "alat.txt");

    if (!found)
        printf("Alat tidak ditemukan atau stok habis!\n");
}

void lihatPinjaman(char *username) {
    FILE *fp = fopen("pinjaman.txt", "r");
    if (!fp) {
        printf("Belum ada data peminjaman.\n");
        return;
    }

    char user[50], nama[50];
    unsigned int id;
    int found = 0;

    printf("\n===== ALAT YANG DIPINJAM =====\n");
    while (fscanf(fp, "%[^;];%u;%[^\n]\n", user, &id, nama) == 3) {
        if (strcmp(user, username) == 0) {
            printf("ID: %u | %s\n", id, nama);
            found = 1;
        }
    }
    fclose(fp);

    if (!found)
        printf("Kamu belum meminjam alat.\n");
}

void kembalikanAlat(char *username) {
    unsigned int id;
    printf("Masukkan ID alat yang ingin dikembalikan: ");
    scanf("%u", &id);

    FILE *pinjam = fopen("pinjaman.txt", "r");
    FILE *tempPinjam = fopen("tempPinjam.txt", "w");
    FILE *alatFile = fopen("alat.txt", "r");
    FILE *tempAlat = fopen("tempAlat.txt", "w");
    Alat alat;
    char user[50], nama[50];
    unsigned int alat_id;
    int found = 0;

    while (fscanf(pinjam, "%[^;];%u;%[^\n]\n", user, &alat_id, nama) == 3) {
        if (strcmp(user, username) == 0 && alat_id == id) {
            found = 1;
        } else {
            fprintf(tempPinjam, "%s;%u;%s\n", user, alat_id, nama);
        }
    }

    while (fscanf(alatFile, "%u;%[^;];%[^;];%[^;];%u;%u\n",
                  &alat.id, alat.nama, alat.merek, alat.model, &alat.tahun, &alat.jumlah) == 6) {
        if (alat.id == id)
            alat.jumlah++;
        fprintf(tempAlat, "%u;%s;%s;%s;%u;%u\n",
                alat.id, alat.nama, alat.merek, alat.model, alat.tahun, alat.jumlah);
    }

    fclose(pinjam);
    fclose(tempPinjam);
    fclose(alatFile);
    fclose(tempAlat);

    remove("pinjaman.txt");
    rename("tempPinjam.txt", "pinjaman.txt");
    remove("alat.txt");
    rename("tempAlat.txt", "alat.txt");

    if (found)
        printf("Pengembalian berhasil!\n");
    else
        printf("Data peminjaman tidak ditemukan!\n");
}

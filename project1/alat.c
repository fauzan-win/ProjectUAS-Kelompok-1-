#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alat.h"

void tampilkanAlat() {
    FILE *fp = fopen("alat.txt", "r");
    if (!fp) {
        printf("Belum ada data alat.\n");
        return;
    }

    Alat alat;
    printf("\n===== DAFTAR ALAT LAB =====\n");
    while (fscanf(fp, "%u;%[^;];%[^;];%[^;];%u;%u\n",
                  &alat.id, alat.nama, alat.merek, alat.model, &alat.tahun, &alat.jumlah) == 6) {
        printf("ID: %u | %s | %s | %s | %u | Stok: %u\n",
               alat.id, alat.nama, alat.merek, alat.model, alat.tahun, alat.jumlah);
    }
    fclose(fp);
}

void tambahAlat() {
    FILE *fp = fopen("alat.txt", "a");
    Alat alat;

    printf("Masukkan ID alat: ");
    scanf("%u", &alat.id);
    getchar();
    printf("Masukkan nama alat: ");
    fgets(alat.nama, sizeof(alat.nama), stdin);
    strtok(alat.nama, "\n");
    printf("Masukkan merek alat: ");
    fgets(alat.merek, sizeof(alat.merek), stdin);
    strtok(alat.merek, "\n");
    printf("Masukkan model alat: ");
    fgets(alat.model, sizeof(alat.model), stdin);
    strtok(alat.model, "\n");
    printf("Masukkan tahun produksi: ");
    scanf("%u", &alat.tahun);
    printf("Masukkan jumlah unit: ");
    scanf("%u", &alat.jumlah);

    fprintf(fp, "%u;%s;%s;%s;%u;%u\n",
            alat.id, alat.nama, alat.merek, alat.model, alat.tahun, alat.jumlah);
    fclose(fp);
    printf("Data alat berhasil ditambahkan!\n");
}

void hapusAlat() {
    FILE *fp = fopen("alat.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    unsigned int id;
    int found = 0;
    Alat alat;

    printf("Masukkan ID alat yang ingin dihapus: ");
    scanf("%u", &id);

    while (fscanf(fp, "%u;%[^;];%[^;];%[^;];%u;%u\n",
                  &alat.id, alat.nama, alat.merek, alat.model, &alat.tahun, &alat.jumlah) == 6) {
        if (alat.id != id) {
            fprintf(temp, "%u;%s;%s;%s;%u;%u\n",
                    alat.id, alat.nama, alat.merek, alat.model, alat.tahun, alat.jumlah);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);
    remove("alat.txt");
    rename("temp.txt", "alat.txt");

    if (found)
        printf("Data alat berhasil dihapus!\n");
    else
        printf("Data alat tidak ditemukan!\n");
}

void editAlat() {
    FILE *fp = fopen("alat.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    unsigned int id;
    int found = 0;
    Alat alat;

    printf("Masukkan ID alat yang ingin diedit: ");
    scanf("%u", &id);
    getchar();

    while (fscanf(fp, "%u;%[^;];%[^;];%[^;];%u;%u\n",
                  &alat.id, alat.nama, alat.merek, alat.model, &alat.tahun, &alat.jumlah) == 6) {
        if (alat.id == id) {
            found = 1;
            printf("Masukkan nama baru: ");
            fgets(alat.nama, sizeof(alat.nama), stdin);
            strtok(alat.nama, "\n");
            printf("Masukkan merek baru: ");
            fgets(alat.merek, sizeof(alat.merek), stdin);
            strtok(alat.merek, "\n");
            printf("Masukkan model baru: ");
            fgets(alat.model, sizeof(alat.model), stdin);
            strtok(alat.model, "\n");
            printf("Masukkan tahun baru: ");
            scanf("%u", &alat.tahun);
            printf("Masukkan jumlah baru: ");
            scanf("%u", &alat.jumlah);
        }
        fprintf(temp, "%u;%s;%s;%s;%u;%u\n",
                alat.id, alat.nama, alat.merek, alat.model, alat.tahun, alat.jumlah);
    }

    fclose(fp);
    fclose(temp);
    remove("alat.txt");
    rename("temp.txt", "alat.txt");

    if (found)
        printf("Data alat berhasil diperbarui!\n");
    else
        printf("Data alat tidak ditemukan!\n");
}

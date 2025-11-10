#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alat.h"
#include "peminjaman.h"

void menuAdmin();
void menuUser(char *username);

int login(char *role, char *username, char *password) {
    FILE *fp = fopen("akun.txt", "r");
    if (!fp) return 0;

    char fileRole[10], fileUser[50], filePass[50];
    while (fscanf(fp, "%[^;];%[^;];%[^\n]\n", fileRole, fileUser, filePass) == 3) {
        if (strcmp(username, fileUser) == 0 && strcmp(password, filePass) == 0) {
            strcpy(role, fileRole);
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Gunakan format: ./program username password\n");
        return 1;
    }

    char role[10];
    if (login(role, argv[1], argv[2])) {
        printf("Login berhasil sebagai %s\n", role);
        if (strcmp(role, "admin") == 0)
            menuAdmin();
        else
            menuUser(argv[1]);
    } else {
        printf("Login gagal! Username atau password salah.\n");
    }

    return 0;
}

void menuAdmin() {
    int pilihan;
    do {
        printf("\n=== MENU ADMIN ===\n");
        printf("1. Lihat alat\n");
        printf("2. Tambah alat\n");
        printf("3. Edit alat\n");
        printf("4. Hapus alat\n");
        printf("0. Keluar\n");
        printf("Pilih: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1: tampilkanAlat(); break;
            case 2: tambahAlat(); break;
            case 3: editAlat(); break;
            case 4: hapusAlat(); break;
        }
    } while (pilihan != 0);
}

void menuUser(char *username) {
    int pilihan;
    do {
        printf("\n=== MENU USER ===\n");
        printf("1. Lihat alat\n");
        printf("2. Pinjam alat\n");
        printf("3. Lihat alat yang dipinjam\n");
        printf("4. Kembalikan alat\n");
        printf("0. Keluar\n");
        printf("Pilih: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1: tampilkanAlat(); break;
            case 2: pinjamAlat(username); break;
            case 3: lihatPinjaman(username); break;
            case 4: kembalikanAlat(username); break;
        }
    } while (pilihan != 0);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventaris.h"

// Menambahkan node baru di awal list
void menambah_data_awal(struct inventaris** head_ref, char* id, char* nama,
                        char* kategori, int stok, char* lokasi, char* status,
                        char* pemilik, char* pic) {
    struct inventaris* new_inventaris =
           (struct inventaris*) malloc(sizeof(struct inventaris));

    strcpy(new_inventaris->id, id);
    strcpy(new_inventaris->nama, nama);
    strcpy(new_inventaris->kategori, kategori);
    new_inventaris->stok = stok;
    strcpy(new_inventaris->lokasi, lokasi);
    strcpy(new_inventaris->status, status);
    strcpy(new_inventaris->pemilik, pemilik);
    strcpy(new_inventaris->pic, pic);

    new_inventaris->next = (*head_ref);
    (*head_ref) = new_inventaris;
}

// Menambahkan node baru setelah node tertentu
void menambah_data(struct inventaris* prev_inventaris, char* id, char* nama,
                   char* kategori, int stok, char* lokasi, char* status,
                   char* pemilik, char* pic) {
    if (prev_inventaris == NULL) {
        printf("the given previous inventaris cannot be NULL");
        return;
    }

    struct inventaris* new_inventaris =
           (struct inventaris*) malloc(sizeof(struct inventaris));

    strcpy(new_inventaris->id, id);
    strcpy(new_inventaris->nama, nama);
    strcpy(new_inventaris->kategori, kategori);
    new_inventaris->stok = stok;
    strcpy(new_inventaris->lokasi, lokasi);
    strcpy(new_inventaris->status, status);
    strcpy(new_inventaris->pemilik, pemilik);
    strcpy(new_inventaris->pic, pic);

    new_inventaris->next = prev_inventaris->next;
    prev_inventaris->next = new_inventaris;
}

// Menambahkan node baru di akhir list
void menambah_data_akhir(struct inventaris** head_ref, char* id, char* nama,
                         char* kategori, int stok, char* lokasi, char* status,
                         char* pemilik, char* pic) {
    struct inventaris* new_inventaris =
           (struct inventaris*) malloc(sizeof(struct inventaris));
    struct inventaris* last = *head_ref;

    strcpy(new_inventaris->id, id);
    strcpy(new_inventaris->nama, nama);
    strcpy(new_inventaris->kategori, kategori);
    new_inventaris->stok = stok;
    strcpy(new_inventaris->lokasi, lokasi);
    strcpy(new_inventaris->status, status);
    strcpy(new_inventaris->pemilik, pemilik);
    strcpy(new_inventaris->pic, pic);

    new_inventaris->next = NULL;

    if (*head_ref == NULL) {
        *head_ref = new_inventaris;
        return;
    }

    while (last->next != NULL)
        last = last->next;

    last->next = new_inventaris;
}

void hapus_data(struct inventaris** head, const char* target_id) {
    if (*head == NULL) {
        printf("[ERROR] Gagal menghapus! Data inventaris masih kosong.\n");
        return;
    }

    struct inventaris* node_now  = *head;
    struct inventaris* node_prev = NULL;

    if (strcmp(node_now->id, target_id) == 0) {
        *head = node_now->next;
        free(node_now);
        printf("[SUKSES] Barang dengan ID %s di posisi pertama berhasil dihapus.\n", target_id);
        return;
    }

    while (node_now != NULL && strcmp(node_now->id, target_id) != 0) {
        node_prev = node_now;
        node_now  = node_now->next;
    }

    if (node_now == NULL) {
        printf("[ERROR] Gagal menghapus! ID %s tidak ditemukan.\n", target_id);
        return;
    }

    node_prev->next = node_now->next;
    free(node_now);
    printf("[SUKSES] Barang dengan ID %s berhasil dihapus dari sistem.\n", target_id);
}

void mencari_data_berdasarkan_id(struct inventaris* cari_head, const char* id_cari) {
    if (cari_head == NULL) {
        printf("Data inventaris masih kosong!\n");
        return;
    }

    struct inventaris* cari_current = cari_head;
    int cari_ditemukan = 0;

    while (cari_current != NULL) {
        if (strcmp(cari_current->id, id_cari) == 0) {
            cari_ditemukan = 1;
            printf("\nResult untuk ID: %s\n", id_cari);
            printf("---------------------------------------------------------------------------------------------------------\n");
            printf("%-8s | %-20s | %-12s | %-5s | %-10s | %-10s | %-12s | %-12s\n",
                   "ID", "Nama Komponen", "Kategori", "Stok", "Lokasi", "Status", "Pemilik", "PIC");
            printf("---------------------------------------------------------------------------------------------------------\n");
            printf("%-8s | %-20s | %-12s | %-5d | %-10s | %-10s | %-12s | %-12s\n",
                   cari_current->id, cari_current->nama, cari_current->kategori,
                   cari_current->stok, cari_current->lokasi, cari_current->status,
                   cari_current->pemilik, cari_current->pic);
            printf("---------------------------------------------------------------------------------------------------------\n");
            break;
        }
        cari_current = cari_current->next;
    }

    if (!cari_ditemukan) {
        printf("Error! Barang dengan ID '%s' tidak ditemukan.\n", id_cari);
    }
}

void memperbarui_stok(struct inventaris* stok_head, const char* stok_id_cari, int stok_perubahan) {
    if (stok_head == NULL) {
        printf("Data inventaris masih kosong!\n");
        return;
    }

    mencari_data_berdasarkan_id(stok_head, stok_id_cari);

    struct inventaris* stok_current = stok_head;
    int stok_ditemukan = 0;

    while (stok_current != NULL) {
        if (strcmp(stok_current->id, stok_id_cari) == 0) {
            stok_ditemukan = 1;
            if (stok_current->stok + stok_perubahan < 0) {
                printf("Stok tidak mencukupi! ID %s (%s) saat ini = %d, diminta berkurang = %d.\n",
                       stok_current->id, stok_current->nama,
                       stok_current->stok, abs(stok_perubahan));
            } else {
                int stok_stokLama = stok_current->stok;
                stok_current->stok += stok_perubahan;
                printf("Update Sukses! ID %s (%s): %d menjadi %d\n",
                       stok_current->id, stok_current->nama,
                       stok_stokLama, stok_current->stok);

                if (stok_current->stok == 0) {
                    strcpy(stok_current->status, "habis");
                    printf("Status ID %s otomatis diubah menjadi 'habis'.\n", stok_current->id);
                } else if (strcmp(stok_current->status, "habis") == 0 && stok_current->stok > 0) {
                    strcpy(stok_current->status, "tersedia");
                    printf("Status ID %s otomatis diubah menjadi 'tersedia'.\n", stok_current->id);
                }
            }
            break;
        }
        stok_current = stok_current->next;
    }
}

void memperbarui_status(struct inventaris* head, char* target_id, char* status_baru) {
    if (head == NULL) {
        printf("Data inventaris masih kosong.\n");
        return;
    }

    struct inventaris* current = head;

    while (current != NULL) {
        if (strcmp(current->id, target_id) == 0) {
            strcpy(current->status, status_baru);
            return;
        }
        current = current->next;
    }
}

void menampilkan_seluruh_data(struct inventaris* head) {
    if (head == NULL) {
        printf("Data inventaris masih kosong.\n");
        return;
    }

    struct inventaris* current = head;

    printf("---------------------------------------------------------------------------------------------------------\n");
    printf("%-8s | %-20s | %-12s | %-5s | %-10s | %-10s | %-12s | %-12s\n",
           "ID", "Nama Komponen", "Kategori", "Stok", "Lokasi", "Status", "Pemilik", "PIC");
    printf("---------------------------------------------------------------------------------------------------------\n");

    while (current != NULL) {
        printf("%-8s | %-20s | %-12s | %-5d | %-10s | %-10s | %-12s | %-12s\n",
               current->id, current->nama, current->kategori, current->stok,
               current->lokasi, current->status, current->pemilik, current->pic);
        printf("---------------------------------------------------------------------------------------------------------\n");
        current = current->next;
    }
}

void menampilkan_ringkasan(struct inventaris* head) {
    if (head == NULL) {
        printf("Data inventaris masih kosong.\n");
        return;
    }

    int total    = 0;
    int tersedia = 0;
    int dipinjam = 0;
    int rusak    = 0;
    int habis    = 0;

    struct inventaris* current = head;

    while (current != NULL) {
        total++;
        if      (strcasecmp(current->status, "tersedia") == 0) tersedia++;
        else if (strcasecmp(current->status, "dipinjam") == 0) dipinjam++;
        else if (strcasecmp(current->status, "rusak")    == 0) rusak++;
        else if (strcasecmp(current->status, "habis")    == 0) habis++;
        current = current->next;
    }

    printf("\n======Rekap Ringkasan Inventaris======\n");
    printf("Total barang            : %d\n", total);
    printf("Barang yang tersedia    : %d\n", tersedia);
    printf("Barang yang dipinjam    : %d\n", dipinjam);
    printf("Barang yang rusak       : %d\n", rusak);
    printf("Barang yang habis       : %d\n", habis);
    printf("======================================\n");
}

void jalankan_sistem(struct inventaris** head_ref) {
    int pilihan;
    int c;
    char input_id[15], input_nama[30], input_kategori[20];
    char input_lokasi[20], input_status[15], input_pemilik[30], input_pic[30];
    int input_stok;

    do {
        printf("\n======================================================\n");
        printf("       SISTEM INVENTARISASI LABORATORIUM              \n");
        printf("======================================================\n");
        printf("[1] Tambah Data Barang Baru\n");
        printf("[2] Hapus Data Barang\n");
        printf("[3] Cari Barang Berdasarkan ID\n");
        printf("[4] Perbarui Status Barang\n");
        printf("[5] Tampilkan Seluruh Data\n");
        printf("[6] Tampilkan Ringkasan & Total\n");
        printf("[0] Keluar dari Program\n");
        printf("------------------------------------------------------\n");
        printf("Pilih menu (0-6): ");
        fflush(stdout);

        scanf("%d", &pilihan);
        while ((c = getchar()) != '\n' && c != EOF);

        switch (pilihan) {
            case 1:
                printf("\n--- Tambah Data Barang ---\n");

                printf("Masukkan ID Barang      : ");
                fgets(input_id, sizeof(input_id), stdin);
                input_id[strcspn(input_id, "\n")] = 0;

                printf("Masukkan Nama Barang    : ");
                fgets(input_nama, sizeof(input_nama), stdin);
                input_nama[strcspn(input_nama, "\n")] = 0;

                printf("Masukkan Kategori       : ");
                fgets(input_kategori, sizeof(input_kategori), stdin);
                input_kategori[strcspn(input_kategori, "\n")] = 0;

                printf("Masukkan Stok           : ");
                scanf("%d", &input_stok);
                while ((c = getchar()) != '\n' && c != EOF);

                printf("Masukkan Lokasi         : ");
                fgets(input_lokasi, sizeof(input_lokasi), stdin);
                input_lokasi[strcspn(input_lokasi, "\n")] = 0;

                printf("Masukkan Status         : ");
                fgets(input_status, sizeof(input_status), stdin);
                input_status[strcspn(input_status, "\n")] = 0;

                printf("Masukkan Pemilik        : ");
                fgets(input_pemilik, sizeof(input_pemilik), stdin);
                input_pemilik[strcspn(input_pemilik, "\n")] = 0;

                printf("Masukkan PIC            : ");
                fgets(input_pic, sizeof(input_pic), stdin);
                input_pic[strcspn(input_pic, "\n")] = 0;

                menambah_data_akhir(head_ref, input_id, input_nama, input_kategori,
                                    input_stok, input_lokasi, input_status,
                                    input_pemilik, input_pic);
                printf("\n[SUKSES] Data berhasil ditambahkan!\n");
                break;

            case 2:
                printf("\n--- Hapus Data Barang ---\n");
                printf("Masukkan ID yang akan dihapus: ");
                fgets(input_id, sizeof(input_id), stdin);
                input_id[strcspn(input_id, "\n")] = 0;

                // BUG FIX: 'hapusData' → 'hapus_data'
                hapus_data(head_ref, input_id);
                break;

            case 3:
                printf("\n--- Cari Data Barang ---\n");
                printf("Masukkan ID yang dicari: ");
                fgets(input_id, sizeof(input_id), stdin);
                input_id[strcspn(input_id, "\n")] = 0;

                mencari_data_berdasarkan_id(*head_ref, input_id);
                break;

            case 4:
                printf("\n--- Perbarui Status Barang ---\n");
                printf("Masukkan ID Barang   : ");
                fgets(input_id, sizeof(input_id), stdin);
                input_id[strcspn(input_id, "\n")] = 0;

                printf("Masukkan Status Baru : ");
                fgets(input_status, sizeof(input_status), stdin);
                input_status[strcspn(input_status, "\n")] = 0;

                memperbarui_status(*head_ref, input_id, input_status);
                printf("\n[INFO] Proses pembaruan status selesai dijalankan.\n");
                break;

            case 5:
                printf("\n--- Seluruh Data Inventaris ---\n");
                menampilkan_seluruh_data(*head_ref);
                break;

            case 6:
                menampilkan_ringkasan(*head_ref);
                break;

            case 0:
                printf("\nKeluar dari sistem. Terima kasih!\n");
                break;

            default:
                printf("\nPilihan tidak valid! Silakan masukkan angka 0-6.\n");
        }
    } while (pilihan != 0);
}

#include "inventaris.h"

void mencari_data_berdasarkan_id(struct inventaris* cari_head, const char* id_cari) {
    // Cek apakah daftar stok kosong
    // Menangani kondisi data kosong
    if (cari_head == NULL) {
        printf("Data inventaris masih kosong!\n");
        return;
    }
    // Pencarian data berdasarkan ID
    struct inventaris* cari_current = cari_head;
    int cari_ditemukan = 0;
    while (cari_current != NULL) {
        if (strcmp(cari_current->id, id_cari) == 0) {
            cari_ditemukan = 1;
            // Tampilkan data yang ditemukan dengan format tabel
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
    // Jika ID tidak ditemukan, tampilkan pesan error
    // Menangani kondisi ID tidak ditemukan
    if (!cari_ditemukan) {
        printf("Error! Barang dengan ID '%s' tidak ditemukan.\n", id_cari);
    }
}
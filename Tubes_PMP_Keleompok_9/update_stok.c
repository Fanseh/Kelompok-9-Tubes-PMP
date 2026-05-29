#include "inventaris.h"

void memperbarui_stok(Node* stok_head, const char* stok_id_cari, int stok_perubahan) {
    // Cek apakah daftar stok kosong
    // Menangani kondisi data kosong
    if (stok_head == NULL) {
        printf("Data inventaris masih kosong!\n");
        return;
    }
    mencari_data_berdasarkan_id(stok_head, stok_id_cari); // Tampilkan data sebelum update
    Node* stok_current = stok_head;
    int stok_ditemukan = 0;
    while (stok_current != NULL) {
        if (strcmp(stok_current->id, stok_id_cari) == 0) {
            stok_ditemukan = 1;
            // Cek apakah perubahan stok valid (tidak membuat stok negatif)
            // Menangani kondisi stok tidak mencukupi
            if (stok_current->stok + stok_perubahan < 0) {
                printf("Stok tidak mencukupi! ID %s (%s) saat ini = %d, diminta berkurang = %d.\n", stok_current->id, stok_current->nama, stok_current->stok, abs(stok_perubahan));
            } else {
                int stok_stokLama = stok_current->stok;
                stok_current->stok += stok_perubahan;
                printf("Update Sukses! ID %s (%s): %d menjadi %d\n", stok_current->id, stok_current->nama, stok_stokLama, stok_current->stok);
                // Update status 
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

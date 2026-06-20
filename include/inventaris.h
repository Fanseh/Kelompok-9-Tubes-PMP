#ifndef INVENTARIS_H
#define INVENTARIS_H

#include <stdint.h>

// 1. STRUKTUR DATA ULTRA-OPTIMIZED (Kini Hanya 32 Byte!)
struct inventaris {
    char id[4];            // 4 Byte
    char nama[16];         // 16 Byte
    
    uint8_t kategori_id;   // 1 Byte
    uint8_t lokasi_id;     // 1 Byte
    uint8_t pic_id;        // 1 Byte
    
    uint8_t tersedia;      // 1 Byte
    uint8_t dipinjam;      // 1 Byte
    uint8_t rusak;         // 1 Byte
    
    struct inventaris* next; // 2 Byte
};

// 2. DEKLARASI FUNGSI
void bacaString(char* buffer, int max_len);
void bacaAngka(int* hasil);
void cetak_header_tabel();
void cetak_baris_tabel(struct inventaris* item);
void cek_id_duplikat(struct inventaris* head, const char* id_baru, int* hasil);

// Hapus 'const char* pemilik' dari parameter fungsi ini
void menambah_data_akhir(struct inventaris** head_ref, const char* id, const char* nama, 
                         uint8_t kat_id, uint8_t lok_id, uint8_t pic_id, 
                         uint8_t tersedia, uint8_t dipinjam, uint8_t rusak);
void hapus_data(struct inventaris** head, const char* target_id);
void mencari_data_berdasarkan_id(struct inventaris* cari_head, const char* id_cari);
void memperbarui_kuantitas(struct inventaris* head, const char* id_cari);
void menampilkan_seluruh_data(struct inventaris* head);
void menampilkan_ringkasan(struct inventaris* head);
void jalankan_sistem(struct inventaris** head_ref);

#endif
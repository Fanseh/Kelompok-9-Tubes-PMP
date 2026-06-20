#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/pgmspace.h> // Pustaka Sakti untuk Akses Flash Memory
#include "inventaris.h"

// =======================================================
// LOOKUP TABLES (Dikunci Permanen di Flash / PROGMEM)
// =======================================================
const char kat_0[] PROGMEM = "-";
const char kat_1[] PROGMEM = "Elektronik";
const char kat_2[] PROGMEM = "Mekanik";
const char kat_3[] PROGMEM = "Alat Ukur";
const char kat_4[] PROGMEM = "Lainnya";
const char* const TABEL_KATEGORI[] PROGMEM = {kat_0, kat_1, kat_2, kat_3, kat_4};

const char lok_0[] PROGMEM = "-";
const char lok_1[] PROGMEM = "Lemari A";
const char lok_2[] PROGMEM = "Lemari B";
const char lok_3[] PROGMEM = "Gudang";
const char lok_4[] PROGMEM = "Meja Praktikum";
const char* const TABEL_LOKASI[] PROGMEM = {lok_0, lok_1, lok_2, lok_3, lok_4};

const char pic_0[] PROGMEM = "-";
const char pic_1[] PROGMEM = "Pak Abi";
const char pic_2[] PROGMEM = "Kak Steven";
const char pic_3[] PROGMEM = "Kak Obi";
const char pic_4[] PROGMEM = "Pak Mervin";
const char* const TABEL_PIC[] PROGMEM = {pic_0, pic_1, pic_2, pic_3, pic_4};

const char PEMILIK_GLOBAL[] PROGMEM = "Lab Embedded";

void bacaString(char* buffer, int max_len) {
    int i = 0; 
    char c;
    
    while (i < max_len - 1) {
        c = getchar();

        if (c == '\b' || c == 127) {
            if (i > 0) {
                i--;
                printf_P(PSTR("\b \b")); 
            }
            continue;
        }
        
        if (c == '\n' || c == '\r') {
            if (i == 0) continue;
            printf_P(PSTR("\n"));
            break;
        }
        
        putchar(c);
        buffer[i++] = c;
    }
    buffer[i] = '\0';
}

void bacaAngka(int* hasil) {
    char buffer[10];
    bacaString(buffer, 10);
    *hasil = atoi(buffer);
}

void cek_id_duplikat(struct inventaris* head, const char* id_baru, int* hasil) {
    *hasil = 0; 
    struct inventaris* current = head;
    while (current != NULL) {
        if (strcmp(current->id, id_baru) == 0) { *hasil = 1; return; }
        current = current->next;
    }
}


void cetak_garis_tabel() {
    printf_P(PSTR("  +----------+-----------------+-----------------+-------------+----------------+----------+----------+-------+---------+\n"));
}

void cetak_header_tabel() {
    printf_P(PSTR("\n"));
    cetak_garis_tabel();
    printf_P(PSTR("  | ID       | Nama Komponen   | Pemilik         | Kategori    | Lokasi         | Tersedia | Dipinjam | Rusak | PIC     |\n"));
    cetak_garis_tabel();
}

void cetak_baris_tabel(struct inventaris* item) {
    // Sisipkan PEMILIK_GLOBAL menggunakan %S secara statis
    printf_P(PSTR("  | %-8s | %-15s | %-15S | %-11S | %-14S | %-8d | %-8d | %-5d | %-7S |\n"),
           item->id, item->nama, 
           PEMILIK_GLOBAL, // <-- Memanggil teks "Lab Embedded" dari Flash Memory
           (const char*)pgm_read_word(&(TABEL_KATEGORI[item->kategori_id])), 
           (const char*)pgm_read_word(&(TABEL_LOKASI[item->lokasi_id])), 
           item->tersedia, item->dipinjam, item->rusak,
           (const char*)pgm_read_word(&(TABEL_PIC[item->pic_id])));
}

// =================================================================
// FUNGSI OPERASI DATA
// =================================================================
void menambah_data_akhir(struct inventaris** head_ref, const char* id, const char* nama, 
                         uint8_t kat_id, uint8_t lok_id, uint8_t pic_id, 
                         uint8_t tersedia, uint8_t dipinjam, uint8_t rusak) {
    
    int is_duplikat;
    cek_id_duplikat(*head_ref, id, &is_duplikat);
    if (is_duplikat) { printf_P(PSTR("\n[ERROR] ID '%s' sudah terdaftar.\n"), id); return; }

    struct inventaris* new_node = (struct inventaris*) malloc(sizeof(struct inventaris));
    if (new_node == NULL) { printf_P(PSTR("\n[FATAL ERROR] RAM ATmega328P Penuh!\n")); return; }

    strcpy(new_node->id, id);
    strcpy(new_node->nama, nama);
    
    // Baris strcpy(new_node->pemilik, pemilik) telah dihapus
    
    new_node->kategori_id = kat_id;
    new_node->lokasi_id = lok_id;
    new_node->pic_id = pic_id;
    
    new_node->tersedia = tersedia;
    new_node->dipinjam = dipinjam;
    new_node->rusak = rusak;
    new_node->next = NULL;

    if (*head_ref == NULL) {
        *head_ref = new_node;
    } else {
        struct inventaris* last = *head_ref;
        while (last->next != NULL) last = last->next;
        last->next = new_node;
    }
    printf_P(PSTR("\n[SUKSES] Data disimpan ke Linked List.\n"));
}

void hapus_data(struct inventaris** head, const char* target_id) {
    if (*head == NULL) { printf_P(PSTR("\nData kosong.\n")); return; }
    struct inventaris* node_now  = *head;
    struct inventaris* node_prev = NULL;

    if (strcmp(node_now->id, target_id) == 0) {
        *head = node_now->next; free(node_now);
        printf_P(PSTR("\n[SUKSES] Barang dihapus.\n")); return;
    }
    while (node_now != NULL && strcmp(node_now->id, target_id) != 0) {
        node_prev = node_now; node_now  = node_now->next;
    }
    if (node_now == NULL) { printf_P(PSTR("\n[ERROR] ID tidak ditemukan.\n")); return; }
    
    node_prev->next = node_now->next; free(node_now);
    printf_P(PSTR("\n[SUKSES] Barang dihapus.\n"));
}

void mencari_data_berdasarkan_id(struct inventaris* cari_head, const char* id_cari) {
    struct inventaris* current = cari_head;
    while (current != NULL) {
        if (strcmp(current->id, id_cari) == 0) {
            printf_P(PSTR("\nResult ID: %s"), id_cari);
            cetak_header_tabel(); 
            cetak_baris_tabel(current);
            cetak_garis_tabel(); // <-- Garis penutup bawah
            return;
        }
        current = current->next;
    }
    printf_P(PSTR("\n[ERROR] ID '%s' tidak ditemukan.\n"), id_cari);
}

void menampilkan_seluruh_data(struct inventaris* head) {
    if (head == NULL) { printf_P(PSTR("\nData kosong.\n")); return; }
    cetak_header_tabel();
    while (head != NULL) { 
        cetak_baris_tabel(head); 
        head = head->next; 
    }
    cetak_garis_tabel(); // <-- Garis penutup bawah
}

void memperbarui_kuantitas(struct inventaris* head, const char* id_cari) {
    struct inventaris* current = head;
    while (current != NULL) {
        if (strcmp(current->id, id_cari) == 0) {
            int pilihan, jumlah;
            
            // Cetak UI Tabel Menu dengan PROGMEM
            printf_P(PSTR("\n  +-------------------------------------------------------------+\n"));
            printf_P(PSTR("  | Update Kuantitas: %-41s |\n"), current->nama);
            printf_P(PSTR("  | Status Saat Ini -> Ada: %-3d | Pjm: %-3d | Rsk: %-3d          |\n"), 
                     current->tersedia, current->dipinjam, current->rusak);
            printf_P(PSTR("  +-------------------------------------------------------------+\n"));
            printf_P(PSTR("  | [1] Tambah Stok Baru      | [4] Kembalikan Barang Pinjaman  |\n"));
            printf_P(PSTR("  | [2] Buang Stok / Hilang   | [5] Catat Barang Rusak          |\n"));
            printf_P(PSTR("  | [3] Pinjam Barang         | [6] Perbaiki Barang Rusak       |\n"));
            printf_P(PSTR("  +-------------------------------------------------------------+\n"));
            printf_P(PSTR("  | [0] Batal / Kembali ke Menu Utama                           |\n"));
            printf_P(PSTR("  +-------------------------------------------------------------+\n"));
            printf_P(PSTR("  Pilih aksi (0-6): "));
            bacaAngka(&pilihan);

            if (pilihan == 0) {
                printf_P(PSTR("\n[INFO] Pembaruan dibatalkan.\n"));
                return;
            }

            if (pilihan < 1 || pilihan > 6) {
                printf_P(PSTR("\n[ERROR] Pilihan tidak valid.\n"));
                return;
            }

            printf_P(PSTR("  Masukkan jumlah barang: "));
            bacaAngka(&jumlah);

            // Fitur Keamanan: Pengguna tidak perlu (dan tidak boleh) memakai tanda minus lagi
            if (jumlah < 0) {
                printf_P(PSTR("\n[ERROR] Masukkan angka positif saja!\n"));
                return;
            }
            if (jumlah == 0) return;

            // Logika Transaksional Ganda
            switch (pilihan) {
                case 1: 
                    current->tersedia += jumlah;
                    printf_P(PSTR("\n[SUKSES] Stok baru berhasil ditambahkan.\n"));
                    break;
                case 2: 
                    if (current->tersedia < jumlah) printf_P(PSTR("\n[ERROR] Stok 'Tersedia' tidak cukup!\n"));
                    else { current->tersedia -= jumlah; printf_P(PSTR("\n[SUKSES] Stok berhasil dikurangi/dibuang.\n")); }
                    break;
                case 3: 
                    if (current->tersedia < jumlah) printf_P(PSTR("\n[ERROR] Stok 'Tersedia' tidak cukup untuk dipinjam!\n"));
                    else { current->tersedia -= jumlah; current->dipinjam += jumlah; printf_P(PSTR("\n[SUKSES] Peminjaman dicatat.\n")); }
                    break;
                case 4: 
                    if (current->dipinjam < jumlah) printf_P(PSTR("\n[ERROR] Tidak bisa mengembalikan lebih dari yang dipinjam!\n"));
                    else { current->dipinjam -= jumlah; current->tersedia += jumlah; printf_P(PSTR("\n[SUKSES] Pengembalian dicatat.\n")); }
                    break;
                case 5: 
                    if (current->tersedia < jumlah) printf_P(PSTR("\n[ERROR] Stok 'Tersedia' tidak cukup untuk dicatat rusak!\n"));
                    else { current->tersedia -= jumlah; current->rusak += jumlah; printf_P(PSTR("\n[SUKSES] Kerusakan dicatat.\n")); }
                    break;
                case 6: 
                    if (current->rusak < jumlah) printf_P(PSTR("\n[ERROR] Tidak bisa memperbaiki lebih dari yang rusak!\n"));
                    else { current->rusak -= jumlah; current->tersedia += jumlah; printf_P(PSTR("\n[SUKSES] Perbaikan selesai.\n")); }
                    break;
            }
            return;
        }
        current = current->next;
    }
    printf_P(PSTR("\n[ERROR] ID tidak ditemukan.\n"));
}

void menampilkan_ringkasan(struct inventaris* head) {
    int totalJenis = 0, totalTersedia = 0, totalDipinjam = 0, totalRusak = 0;
    
    while (head != NULL) {
        totalJenis++; // Menghitung ada berapa node/jenis barang
        totalTersedia += head->tersedia;
        totalDipinjam += head->dipinjam;
        totalRusak += head->rusak;
        head = head->next;
    }
    
    printf_P(PSTR("\n========== RINGKASAN ==========\n"));
    printf_P(PSTR("Jumlah Jenis Barang : %d\n"), totalJenis);
    printf_P(PSTR("Total Tersedia      : %d\n"), totalTersedia);
    printf_P(PSTR("Total Dipinjam      : %d\n"), totalDipinjam);
    printf_P(PSTR("Total Rusak         : %d\n"), totalRusak);
    printf_P(PSTR("===============================\n"));
}

// =================================================================
// MENU UTAMA SISTEM
// =================================================================
void jalankan_sistem(struct inventaris** head_ref) {
    int pilihan;
    char id[4], nama[16];
    int kat_id, lok_id, pic_id, ada;

    do {
        printf_P(PSTR("\n=====================================\n"));
        printf_P(PSTR(" SISTEM INVENTARISASI (BARE-METAL)   \n"));
        printf_P(PSTR("=====================================\n"));
        printf_P(PSTR("[1] Tambah Data\n[2] Hapus Data\n[3] Cari via ID\n"));
        printf_P(PSTR("[4] Update Kuantitas\n[5] Lihat Semua Data\n[6] Ringkasan\n"));
        printf_P(PSTR("[7] Uji Kapasitas (Stress Test)\n[0] Keluar\n"));
        printf_P(PSTR("Pilih menu: "));
        
        bacaAngka(&pilihan);

        switch (pilihan) {
            case 1:
                printf_P(PSTR("\nID Barang: ")); bacaString(id, sizeof(id));
                printf_P(PSTR("Nama Komponen: ")); bacaString(nama, sizeof(nama));
                
                // Prompt "Nama Pemilik:" telah dihapus sepenuhnya
                
                printf_P(PSTR("\nKategori (1.Elektronik, 2.Mekanik, 3.Bahan Habis, 4.Alat Ukur): ")); bacaAngka(&kat_id);
                printf_P(PSTR("Lokasi (1.Lemari A, 2.Lemari B, 3.Gudang, 4.Meja Praktikum): ")); bacaAngka(&lok_id);
                printf_P(PSTR("PIC (1.Budi, 2.Siti, 3.Andi, 4.Laboran): ")); bacaAngka(&pic_id);
                
                printf_P(PSTR("\nKuantitas Awal (Stok Tersedia): ")); bacaAngka(&ada);
                
                // Variabel parameter 'pemilik' tidak lagi dikirimkan ke fungsi ini
                menambah_data_akhir(head_ref, id, nama, 
                                    (uint8_t)kat_id, (uint8_t)lok_id, (uint8_t)pic_id, 
                                    (uint8_t)ada, 0, 0);
                break;
            case 2: printf_P(PSTR("\nID dihapus: ")); bacaString(id, sizeof(id)); hapus_data(head_ref, id); break;
            case 3: printf_P(PSTR("\nCari ID: ")); bacaString(id, sizeof(id)); mencari_data_berdasarkan_id(*head_ref, id); break;
            case 4: printf_P(PSTR("\nUpdate Kuantitas ID: ")); bacaString(id, sizeof(id)); memperbarui_kuantitas(*head_ref, id); break;
            case 5: menampilkan_seluruh_data(*head_ref); break;
            case 6: menampilkan_ringkasan(*head_ref); break;
            case 7: 
            {
                int limit;
                printf_P(PSTR("\n--- STRESS TEST MEMORI ---\n"));
                printf_P(PSTR("Masukkan jumlah data yang ingin disuntikkan: "));
                bacaAngka(&limit);
                
                printf_P(PSTR("\nMemulai Injeksi Hardcode...\n"));
                for (int i = 1; i <= limit; i++) {
                    char temp_id[4];
                    char temp_nama[16];
                    
                    snprintf(temp_id, sizeof(temp_id), "%d", i);
                    snprintf(temp_nama, sizeof(temp_nama), "Dummy %d", i);
                    
                    // Hilangkan parameter "AutoBot" (pemilik) dari Hardcode Stress Test
                    menambah_data_akhir(head_ref, temp_id, temp_nama, 
                                        1, 1, 1, 10, 0, 0);
                }
                printf_P(PSTR("\n[INFO] Injeksi selesai! Silakan cek menu [6] Ringkasan.\n"));
                break;
            }

            case 0: printf_P(PSTR("\nSistem Halt.\n")); break;
            default: printf_P(PSTR("\nMenu tidak valid.\n"));
        }
    } while (pilihan != 0);
}
#ifndef INVENTARIS_H
#define INVENTARIS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct inventaris {
    char id[15];        
    char nama[30];      
    char kategori[20];  
    int stok;           
    char lokasi[20];    
    char status[15];    
    char pemilik[30];   
    char pic[30];       
    struct inventaris* next;  
};

void memperbarui_status(struct inventaris* head, char* target_id, char* status_baru);
void menampilkan_seluruh_data(struct inventaris* head);
void menampilkan_ringkasan(struct inventaris* head);
void mencari_data_berdasarkan_id(struct inventaris* cari_head, const char* id_cari);
void memperbarui_stok(struct inventaris* stok_head, const char* stok_id_cari, int stok_perubahan);

#endif

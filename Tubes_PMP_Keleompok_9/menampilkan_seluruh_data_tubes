#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventaris.h"

void menampilkan_seluruh_data(struct inventaris* head){
    // cek apakah list kosong
    if(head == NULL){
        printf("Data inventaris masih kosong.\n");
        return;
    }
    // pointer sementara
    struct inventaris* current = head;
    int i = 1;
    printf("---------------------------------------------------------------------------------------------------------\n");
    printf("%-2s | %-8s | %-20s | %-12s | %-5s | %-10s | %-10s | %-12s | %-12s\n", 
           "No.", "ID", "Nama Komponen", "Kategori", "Stok", "Lokasi", "Status", "Pemilik", "PIC");
    printf("---------------------------------------------------------------------------------------------------------\n");
    // looping hingga ke akhir node
    while(current != NULL){
        // display data barang
        printf("%-2s | %-8s | %-20s | %-12s | %-5s | %-10s | %-10s | %-12s | %-12s\n",
                i, current->id, current->nama, current->kategori, current->stok, current->lokasi, current->status, current->pemilik, current->pic);
        printf("---------------------------------------------------------------------------------------------------------\n");
        // menggeser pointer ke node berikutnya
        current = current->next;
        i++;
    }
    
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventaris.h"

void menampilkan_ringkasan(struct inventaris* head){
    // inisialisasi dibuat nilai awalnya 0
    int total = 0;
    int tersedia = 0;
    int dipinjam = 0;
    int rusak = 0;
    int habis = 0;
    // cek apakah list kosong
    if(head == NULL){
        printf("Data inventaris masih kosong.\n");
        return;
    }
    // pointer sementara
    struct inventaris* current = head;
    // looping hingga ke akhir node
    while(current != NULL){
        // total bertambah setiap looping 1 kali
        total++;
        // pakai strcasecmp agar kalau ditulis dengan capslock itu tetap aman
        // dengan strcasecmp, kalau dicompare itu == 0,
        // berarti jumlah characternya sama sehingga jumlah barang pada status tersebut bertambah
        if(strcasecmp(current->status, "tersedia") == 0){
            tersedia++;
        }
        else if(strcasecmp(current->status, "dipinjam") == 0){
            dipinjam++;
        }
        else if(strcasecmp(current->status, "rusak") == 0){
            rusak++;
        }
        else if(strcasecmp(current->status, "habis") == 0){
            habis++;
        }
        // menggeser pointer ke node berikutnya
        current = current->next;
    }
    // display rekap ringkasan inventaris
    printf("\n======Rekap Ringkasan Inventaris======\n");
    printf("Total barang            : %d\n", total);
    printf("Barang yang tersedia    : %d\n", tersedia);
    printf("Barang yang dipinjam    : %d\n", dipinjam);
    printf("Barang yang rusak       : %d\n", rusak);
    printf("Barang yang habis       : %d\n", habis);
    printf("======================================\n");
}
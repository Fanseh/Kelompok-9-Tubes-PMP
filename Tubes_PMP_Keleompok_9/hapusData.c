#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "inventaris.h"

void hapusData(struct inventaris** head, const char* target_id) {
    
    if (*head == NULL) {
        printf("[ERROR] Gagal menghapus! Data inventaris masih kosong.\n");
        return; 
    }

    struct inventaris* node_now = *head; 
    struct inventaris* node_prev = NULL; 

    if (strcmp(node_now->id, target_id) == 0) {
        *head = node_now->next; 
        
        free(node_now); 
        
        printf("[SUKSES] Barang dengan ID %s di posisi pertama berhasil dihapus.\n", target_id);
        return; 
    }

    while (node_now != NULL && strcmp(node_now->id, target_id) != 0) {
        node_prev = node_now;       
        node_now = node_now->next;   
    }

    if (node_now == NULL) {
        printf("[ERROR] Gagal menghapus! ID %s tidak ditemukan.\n", target_id);
        return; 
    }

    node_prev->next = node_now->next;

    free(node_now);

    printf("[SUKSES] Barang dengan ID %s berhasil dihapus dari sistem.\n", target_id);
}
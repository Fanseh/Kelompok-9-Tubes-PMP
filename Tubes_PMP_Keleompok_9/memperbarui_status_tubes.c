#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventaris.h"

void memperbarui_status(struct inventaris* head, char* target_id, char* status_baru){
    // cek apakah list kosong
    if(head == NULL){
        printf("Data inventaris masih kosong.\n");
        return;
    }
    // pointer sementara
    struct inventaris* current = head;
    // looping hingga ke akhir node
    while(current != NULL){
        // kalau id dan targert_id sama,
        // update statusnya dengan copy string status_baru ke status
        if(strcmp(current->id, target_id) == 0){
            strcpy(current->status, status_baru);
            return;
        }
        // menggeser pointer ke node berikutnya
        current = current->next;
    }
    
}
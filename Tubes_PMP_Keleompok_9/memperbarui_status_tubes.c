#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventaris.h"

void memperbarui_status(struct Node* head, char* target_id, char* status_baru){
    if(head == NULL){
        printf("Data inventaris masih kosong.\n");
        return;
    }

    struct Node* current = head;

    while(current != NULL){
        if(strcmp(current->id, target_id) == 0){
            strcpy(current->status, status_baru);
            return;
        }
        current = current->next;
    }
    
}
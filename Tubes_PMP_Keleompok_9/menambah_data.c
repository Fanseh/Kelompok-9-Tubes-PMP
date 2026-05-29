// Fungsi keseluruhan yang digunakan dalam menambah data inventaris
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventaris.h"

// fungsi untuk menambahkan inventaris pada bagian awal list
void menambah_data_awal(struct inventaris** head_ref, char* id, char* nama, 
                        char* kategori, int stok, char* lokasi, char* status,
                        char* pemilik, char* pic) {
    // 1. Allocate inventaris 
    struct inventaris* new_inventaris = 
           (struct inventaris*) malloc(sizeof(struct inventaris));

    // 2. Put in the data  
    strcpy(new_inventaris->id, id);
    strcpy(new_inventaris->nama, nama);
    strcpy(new_inventaris->kategori, kategori);
    new_inventaris->stok = stok;
    strcpy(new_inventaris->lokasi, lokasi);
    strcpy(new_inventaris->status, status);
    strcpy(new_inventaris->pemilik, pemilik);
    strcpy(new_inventaris->pic, pic);

    // 3. Make next of new inventaris as head 
    new_inventaris->next = (*head_ref);

    // 4. move the head to point to 
    //    the new inventaris 
    (*head_ref) = new_inventaris;
}

// fungsi untuk menambahkan inventaris setelah sebuah inventaris yang telah ditetapkan
void menambah_data(struct inventaris* prev_inventaris, char* id, char* nama,
                   char* kategori, int stok, char* lokasi, char* status,
                   char* pemilik, char* pic) {
    // 1. Check if the given prev_inventaris 
    //    is NULL 
    if (prev_inventaris == NULL)
    {
      printf("the given previous inventaris cannot be NULL");
      return;
    }

    // 2. Allocate new inventaris 
    struct inventaris* new_inventaris =
           (struct inventaris*) malloc(sizeof(struct inventaris));

    // 3. Put in the data  
    strcpy(new_inventaris->id, id);
    strcpy(new_inventaris->nama, nama);
    strcpy(new_inventaris->kategori, kategori);
    new_inventaris->stok = stok;
    strcpy(new_inventaris->lokasi, lokasi);
    strcpy(new_inventaris->status, status);
    strcpy(new_inventaris->pemilik, pemilik);
    strcpy(new_inventaris->pic, pic);

    // 4. Make next of new inventaris as next 
    //    of prev_inventaris 
    new_inventaris->next = prev_inventaris->next;

    // 5. Move the next of prev_inventaris 
    //    as new_inventaris 
    prev_inventaris->next = new_inventaris;
}

// fungsi untuk menambahkan inventaris pada akhir dari list
void menambah_data_akhir(struct inventaris** head_ref, char* id, char* nama,
                         char* kategori, int stok, char* lokasi, char* status,
                         char* pemilik, char* pic) {
    // 1. Allocate inventaris 
    struct inventaris* new_inventaris = 
           (struct inventaris*) malloc(sizeof(struct inventaris));

    // Used in step 5
    struct inventaris *last = *head_ref;  

    // 2. Put in the data  
    strcpy(new_inventaris->id, id);
    strcpy(new_inventaris->nama, nama);
    strcpy(new_inventaris->kategori, kategori);
    new_inventaris->stok = stok;
    strcpy(new_inventaris->lokasi, lokasi);
    strcpy(new_inventaris->status, status);
    strcpy(new_inventaris->pemilik, pemilik);
    strcpy(new_inventaris->pic, pic);

    // 3. This new inventaris is going to be the 
    //    last inventaris, so make next of it as NULL
    new_inventaris->next = NULL;

    // 4. If the Linked List is empty, then make 
    //    the new inventaris as head 
    if (*head_ref == NULL)
    {
       *head_ref = new_inventaris;
       return;
    }

    // 5. Else traverse till the last inventaris 
    while (last->next != NULL)
        last = last->next;

    // 6. Change the next of last inventaris 
    last->next = new_inventaris;
    return;
}
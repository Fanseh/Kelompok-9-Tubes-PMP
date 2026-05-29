#ifndef INVENTARIS_H
#define INVENTARIS_H

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

#endif
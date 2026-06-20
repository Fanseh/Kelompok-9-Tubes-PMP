#include <avr/io.h>
#include <stdio.h>
#include "uart.h"
#include "inventaris.h"

FILE uart_output = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
FILE uart_input  = FDEV_SETUP_STREAM(NULL, uart_getchar, _FDEV_SETUP_READ);

// Memori Utama
struct inventaris* head_utama = NULL;

int main(void) {
    // Inisialisasi Perangkat Keras Komunikasi Serial
    uart_init();

    stdout = &uart_output;
    stdin  = &uart_input;
    
    // Panggil Fungsi Utama dari Inventaris.c
    jalankan_sistem(&head_utama);

    // Perulangan (Syarat Wajib Bare-Metal)
    while(1) {
    }
    
    return 0;
}
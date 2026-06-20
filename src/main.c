#include <avr/io.h>
#include <stdio.h>
#include "uart.h"
#include "inventaris.h"

// Makro sakti dari AVR-LIBC untuk mengikat fungsi perangkat keras 
// ke perpustakaan standar Input/Output (stdio)
FILE uart_output = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
FILE uart_input  = FDEV_SETUP_STREAM(NULL, uart_getchar, _FDEV_SETUP_READ);

// Memori Utama
struct inventaris* head_utama = NULL;

int main(void) {
    // 1. Inisialisasi Perangkat Keras Komunikasi Serial
    uart_init();
    
    // 2. Membelokkan perintah printf() dan scanf() murni 
    // agar mereka keluar-masuk melalui kabel USB Arduino
    stdout = &uart_output;
    stdin  = &uart_input;

    printf("\n=====================================\n");
    printf(" AVR C Compiler: Siap Digunakan!     \n");
    printf("=====================================\n");
    
    // 3. Panggil fungsi inti dari inventaris.c
    jalankan_sistem(&head_utama);

    // 4. Perulangan abadi tak berujung (Syarat wajib Bare-Metal)
    while(1) {
        // Sistem tertidur / Halt
    }
    
    return 0;
}
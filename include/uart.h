#ifndef UART_H
#define UART_H

#include <stdio.h>

// Deklarasi inisialisasi UART
void uart_init(void);

// Deklarasi fungsi pengiriman dan penerimaan karakter untuk printf/scanf
int uart_putchar(char c, FILE *stream);
int uart_getchar(FILE *stream);

#endif
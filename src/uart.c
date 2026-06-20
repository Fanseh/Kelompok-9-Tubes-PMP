#include <avr/io.h>
#include "uart.h"

// Arduino Uno dengan aktivasi 16 MHz
#define F_CPU 16000000UL
#define BAUD 9600
#define BRC ((F_CPU/16/BAUD) - 1)

void uart_init(void) {
    // Mengatur Baud Rate
    UBRR0H = (BRC >> 8);
    UBRR0L = BRC;
    
    // Mengaktifkan pin TX dan RX
    UCSR0B = (1 << TXEN0) | (1 << RXEN0);
    
    // Mengatur format frame data: 8 bit, 1 stop bit
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

int uart_putchar(char c, FILE *stream) {
    if (c == '\n') uart_putchar('\r', stream); 
    while (!(UCSR0A & (1 << UDRE0)));         
    UDR0 = c;                                 
    return 0;
}

int uart_getchar(FILE *stream) {
    while (!(UCSR0A & (1 << RXC0)));           
    char c = UDR0;                             
    return c;
}
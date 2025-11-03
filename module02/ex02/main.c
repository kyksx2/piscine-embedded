#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void uart_init(unsigned int ubrr) {
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;

    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void uart_tx(char c) {
    while (!( UCSR0A & (1 << UDRE0)))
        ;
    UDR0 = c;
}

char uart_rx(void) {
    while (!( UCSR0A & (1 << RXC0))) 
        ;
    //? mis a 1 quand il recois quelque chose
    //? reste a 1 tant qu'il n'a pas ete lu
    return (UDR0);
}
//! datasheet p.200.

int main() {
    uart_init(8);
    char read;
    while(1) {
        read = uart_rx();
        uart_tx(read);
    }
}
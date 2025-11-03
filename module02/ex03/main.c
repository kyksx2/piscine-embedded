#include "../header/rgb.h"

void uart_init(unsigned int ubrr) {
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;

    UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0); //? activation de l'interuption a la reception
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}
//! lire readme

void uart_tx(char c) {
    while (!( UCSR0A & (1 << UDRE0)))
        ;
    UDR0 = c;
}

ISR(USART_RX_vect) {
    char c = UDR0; //? on recupere la valeur recus par UDR0
    if (c >= 'a' && c <= 'z')
        c -= 32;
    else if (c >= 'A' && c <= 'Z')
        c += 32;
    uart_tx(c); //? renvoi de la valeur changer a UDR0
}
//! datasheet p.66

int main() {
    uart_init(8);
    sei();
    while(1) {}
}
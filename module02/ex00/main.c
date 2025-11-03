#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void uart_init(unsigned int ubrr) {
    /*Set baud rate */
    UBRR0H = (unsigned char)(ubrr >> 8); //? ici son stocker les 8 bits forts du braudrate
    UBRR0L = (unsigned char)ubrr; //? ici son stocker les 8 bits faibles du braudrate
    /* Enable receiver and transmitter */
    UCSR0B = (1 << RXEN0)|(1 << TXEN0);
    /* Set frame format: 8data, 1stop bit */
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}
//! datasheet p.185
//! datasheet p.203

void uart_tx(char c) {
    /* Wait for empty transmit buffer */
    while ( !( UCSR0A & (1 << UDRE0)) )
        ;
    /* Put data into buffer, sends the data */
    UDR0 = c;
}
//! datasheet p.189
//! datasheet p.200 / p.201
//! check readme
int main() {
    uart_init(8); //? on envoi 8 en se referant au tableau p.199
    while (1) {
        uart_tx('Z');
        _delay_ms(1000);
    }
}

//? ctrl a + k + y -> quitter le programe screen

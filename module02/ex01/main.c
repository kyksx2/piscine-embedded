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
    while ( !( UCSR0A & (1 << UDRE0)) )
        ;
    UDR0 = c;
}

void uart_printstr(const char* str) {
    for(int i = 0; str[i]; i++) {
        uart_tx(str[i]);
    }
}

ISR(TIMER1_COMPA_vect) {
    uart_printstr("mdodevsk\n");
}
//? TIMER1 COMPA -> suite a TIMSK1 (OCIE1A)
//! datasheet p.66 + arduino forum

void setup() {
    TCCR1A &= ~((1 << WGM10) | (WGM11));
    TCCR1B &= ~(1 << WGM13);
    TCCR1B |= (1 << WGM12);     //? activation CTC

    TCCR1B |= ((1 << CS12) | (1 << CS10));
    TCCR1B &= ~(1 << CS11);     //? prescaler 1024

    OCR1A = 31249; //*

    TIMSK1 |= (1 << OCIE1A);    //! datasheet p.144/145
    //? verifie au niveau des valeurs s'il y a match
    sei();      //? enable interrupts
    //! datasheet p.69
}

int main() {
    uart_init(8);
    setup();
    while(1) {}
}

//* 16 000 000 / 1024 = 15 625 (1 seconde)
//* 15 625 * 2 = 31 250 - 1 = 31 249
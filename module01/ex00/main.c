#include <avr/io.h>

void    delay() {
    volatile unsigned long i; //? mot cle volatile empeche le compilateur d'optimiser en supprimant la fontion
    for (i = 0; i < 250000UL; i++);
}

int main() {
    DDRB = DDRB | (1 << DDB1);

    while(1) {
        PORTB ^= (1 << PB1); //? change l'etat du bit grace au toggle
        delay(); // ! remplace _delay_ms()
    }
}
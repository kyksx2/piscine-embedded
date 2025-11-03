#include <avr/io.h>
#include <util/delay.h>

void setup() {
    DDRB |= (1 << PB1); //? led PB en sortie
    DDRD &= ~((1 << PD2) | (1 << PD4)); //? boutons SW en entree

    TCCR1A &= ~(1 << WGM10);
    TCCR1A |= (1 << WGM11);
    TCCR1B |= ((1 << WGM13) | (1 << WGM12));
    TCCR1A |= (1 << COM1A1);
    TCCR1B |= (1 << CS12);
    TCCR1B &= ~((1 << CS11) | (1 << CS10));
}
int main() {
    setup();
    ICR1 = 62499;
    OCR1A = 6249.9;

    int pourcentage = 1;
    uint64_t status_sw1 = 0;
    uint64_t status_sw2 = 0;
    uint64_t old_status_sw1 = 0;
    uint64_t old_status_sw2 = 0;

    while (1) {
        status_sw1 = PIND & (1 << PD2);
        status_sw2 = PIND & (1 << PD4);

        if (status_sw1 && !old_status_sw1) { //? condition utiliser pour proteger quand on reste appuyer sans bloquer l'autre boutons
            _delay_ms(150);
            if (pourcentage < 10)
                pourcentage ++;
            OCR1A = 6249.9 * pourcentage;
        }
        if (status_sw2 && !old_status_sw2) { //? idem
            _delay_ms(150);
            if (pourcentage > 1)
                pourcentage --;
            OCR1A = 6249.9 * pourcentage;
        }
        old_status_sw1 = status_sw1;
        old_status_sw2 = status_sw2;
    }
}

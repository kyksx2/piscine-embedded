#include <avr/io.h>

int main() {
    DDRB = DDRB | (1 << DDB1); //? led PB en sortie
    
    TCCR1A &= ~((1 << WGM10) | (1 << WGM11));
    TCCR1B &= ~(1 << WGM13);
    TCCR1B |= (1 << WGM12);
    //? les WGM1x decide du mode d'operation
    //! datasheet p.141 OCR1A -> mode CTC
    TCCR1A |= (1 << COM1A0);
    //? toggle OC1A/OC1B si la comparaison match (PB1 = OC1A)
    //! datasheet p.140 toggle OC1A -> led PB1
    TCCR1B |= (1 << CS12);
    TCCR1B &= ~((1 << CS11) | (1 << CS10));
    //? choisi le prescaler (ici : 256)
    //! datasheet p.143
    OCR1A = 31249;
    //? penser que le 0 compte donc retirer 1 pour etre precis
    
    while(1) {}
}

//! (DF_CPU / PRESCALER) / prediviseur
//? 16MHZ / 256 = 62 500Hz
//?  1 / 62 500 = 0,000016 secondes
//? donc 0,5 / 0,000016 = 31 250 --> compris entre 0 et 65 535 donc quand il a compter 31 250 --> 500ms

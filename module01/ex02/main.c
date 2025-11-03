#include <avr/io.h>

int main() {
    DDRB = DDRB | (1 << DDB1); //? led PB en sortie
    
    TCCR1A &= ~(1 << WGM10);
    TCCR1A |= (1 << WGM11);
    TCCR1B |= ((1 << WGM13) | (1 << WGM12));
    //? mode Fast PWM -> retournbe plus vite au bottom une fois le top atteint
    //! datasheet p.133 p.134
    TCCR1A |= (1 << COM1A1);
    //? non-inverting mode
    //! datasheet p.140
    TCCR1B |= (1 << CS12);
    TCCR1B &= ~((1 << CS11) | (1 << CS10));

    ICR1 = 62499;
    //? ici le top qui represente 1Hz (1sec)
    OCR1A = 6249;
    //? ici la comparaison pour toggle la led elle commence allumer car mode PWM non-inverting mode

    while(1) {}
}

//? BOTTOM = debut
//? TOP = limite choisie
//? MAX = limite absolue
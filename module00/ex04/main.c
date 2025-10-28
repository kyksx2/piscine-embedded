#include <avr/io.h>
#include <util/delay.h>

int main() {
    DDRB = DDRB | (1 << DDB0); //? on prepare toutes les led
    DDRB = DDRB | (1 << DDB1); 
    DDRB = DDRB | (1 << DDB2); 
    DDRB = DDRB | (1 << DDB4);
    
    DDRD = DDRD & ~(1 << PD2); //? on prepare les 2 boutons
    DDRD = DDRD & ~(1 << PD4);
    int count = 0;

    while(1) {
        if (!(PIND & (1 << PD2))) {
            _delay_ms(300);
            if (count < 15)
                count++;
        }
        else if (!(PIND & (1 << PD4))) {
            _delay_ms(300);
            if (count > 0)
                count--;
        }
        PORTB &= ~((1 << PORTB0) | (1 << PORTB1) | (1 << PORTB2) | (1 << PORTB4)); //? chaque led est etteinte avant d'afficher les suivantes
        if (count & (1 << 0))
            PORTB = PORTB | (1 << PORTB0);
        if (count & (1 << 1))
            PORTB = PORTB | (1 << PORTB1);
        if (count & (1 << 2))
            PORTB = PORTB | (1 << PORTB2);
        if (count & (1 << 3))
            PORTB = PORTB | (1 << PORTB4);
    } //? en fonction des 4 premiers bits, on sait quel led allumer
    return (0);
}
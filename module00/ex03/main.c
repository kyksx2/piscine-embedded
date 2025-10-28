#include <avr/io.h>
#include <util/delay.h>

int main() {    
    DDRB = DDRB | (1 << DDB0); 
    DDRD = DDRD & ~(1 << PD2);
    int status = 0;

    while(1){
        if (!(PIND & (1 << PD2))) { //!! si j'appuie dans ce cas je change de status
            status = !status; //? switch de status
            if (status)
                PORTB = PORTB | (1 << PORTB0);
            else 
                PORTB = PORTB & ~(1 << PORTB0);
            _delay_ms(200);
        }
    }
}
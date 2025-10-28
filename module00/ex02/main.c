#include <avr/io.h>
#include <util/delay.h>

int main() {    
    DDRB = DDRB | (1 << DDB0); // sortie (1)
    DDRD = DDRD & ~(1 << PD2); // bouton en entree (0) -> attend une action
    while(1){
        if (PIND & (1 << PD2)) { // si PD2 est en entree *?????*
            PORTB = PORTB & ~(1 << PORTB0); // on laisse la led eteinte
        }
        else
            PORTB = PORTB | (1 << PORTB0); // sinon on allume
    }
}

//  *?????* -> PIN inverse la logique donc si PD est en sortie(1) PIN est a 0 sinon il est a 1
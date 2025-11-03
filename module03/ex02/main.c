#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void init_rgb() {
    //? Timer0 controle vert et rouge
    TCCR0A |= ((1 << WGM01) | (1 << WGM00) | (1 << COM0A1) | (1 << COM0B1));
    TCCR0B |= (1 << CS00);
    //! datasheet p.108/113-117

    //? Timer2 controle la partie bleu
    TCCR2A |= ((1 << COM2B1) | (1 << WGM21) | (1 << WGM20)); //? fast PWM + toggle OC2B 
    TCCR2B |= (1 << CS20); //? pas de prescaler car pas besoin
    //! datasheet p.151/156/162-166
}
//? initialise les timers
//? PD3 -> OC2B / INT1 -> Timer2B(bleu)
//? PD5 -> OC0B / T1 -> Timer0B(rouge)
//? PD6 -> OC0A / AIN0 -> Timer0A(vert)

void set_rgb(uint8_t r, uint8_t g, uint8_t b) {
    OCR0A = g; // green
    OCR0B = r; // red
    OCR2B = b; // blue
}
//? set la couleur de la led

void wheel(uint8_t pos) {
    pos = 255 - pos;
    if (pos < 85)
        set_rgb(255 - pos * 3, 0, pos * 3);
    else if (pos < 170) {
        pos = pos - 85;
        set_rgb(0, pos * 3, 255 - pos * 3);
    }
    else {
        pos = pos - 170;
        set_rgb(pos * 3, 255 - pos * 3, 0);
    }
}

int main() {
    DDRD |= ((1 << PD3) | (1 << PD5) | (1 << PD6));
    init_rgb();

    while(1) {
        for (uint8_t i = 0; i < 255; i++) {
            wheel(i);
            _delay_ms(25);
        }
    }
}
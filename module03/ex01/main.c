#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void led_color_change(uint8_t mask) {
    PORTD |= mask;
    _delay_ms(1000);
    PORTD &= ~mask;
}

int main() {
    DDRD |= ((1 << PD3) | (1 << PD5) | (1 << PD6));

    while(1) {
        led_color_change(1 << PD5); // rouge
        led_color_change(1 << PD6); // vert
        led_color_change(1 << PD3); // bleu
        led_color_change((1 << PD5) | (1 << PD6)); // jaune
        led_color_change((1 << PD6) | (1 << PD3)); // cyan
        led_color_change((1 << PD5) | (1 << PD3)); // magenta
        led_color_change((1 << PD5) | (1 << PD6) |  (1 << PD3)); // blanc
    }
}
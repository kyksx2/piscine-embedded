#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

uint8_t uart_index = 0;
char uart_buffer[8];

void uart_init(unsigned int ubrr) {
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;

    UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0); //? activation de l'interuption a la reception
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void uart_tx(char c) {
    while ( !( UCSR0A & (1 << UDRE0)) )
        ;
    UDR0 = c;
}

char uart_rx(void) {
    while (!( UCSR0A & (1 << RXC0))) 
        ;
    return (UDR0);
}

void init_rgb() {
    TCCR0A |= ((1 << WGM01) | (1 << WGM00) | (1 << COM0A1) | (1 << COM0B1));
    TCCR0B |= (1 << CS00);

    TCCR2A |= ((1 << COM2B1) | (1 << WGM21) | (1 << WGM20)); 
    TCCR2B |= (1 << CS20);
}

void set_rgb(uint8_t r, uint8_t g, uint8_t b) {
    OCR0A = g; // green
    OCR0B = r; // red
    OCR2B = b; // blue
}

void uart_print(char *str) {
    for(uint8_t i = 0; str[i]; i++)
        uart_tx(str[i]);
}

int8_t hex_to_num(char c) { // renvoi la valeur hexa en decimal -> ex : a = 10 / f = 15 / 0 = 0
    if (c >= '0' && c <= '9')
        return c - '0';
    if (c >= 'A' && c <= 'F')
        return 10 + (c - 'A');
    if (c >= 'a' && c <= 'f')
        return 10 + (c - 'a');
    return -1;
}

uint8_t hex_rgb(char a, char b) {
    int8_t hi = hex_to_num(a);
    int8_t lo = hex_to_num(b);
    
    if (hi < 0 || lo < 0) 
        return 0;
    return (uint8_t)((hi << 4) | lo); 
    //? ici on shift les bits high (a) de 4 a gauche
    //? puis on rajoute les bits low (b) pour faire un octet complet
}


int check_rgb(char *buffer) {
    if (buffer[0] != '#')
        return (0);
    for (uint8_t i = 1; i <= 6; i++) {
        char c = buffer[i];
        if (!((c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f' ) || (c >= '0' && c <= '9')))
            return (0);
    }
    if (buffer[7] != '\0')
        return (0);
    return (1);
}
    
ISR(USART_RX_vect)
{
	char c = UDR0; // on va lire le caractere recu

	uart_tx(c);


	if (c == '\n' || c == '\r')
	{
		uart_buffer[uart_index] = '\0';

		// on parse le buffer ici :
		if (check_rgb(uart_buffer) && uart_buffer[0] == '#')
		{
			uint8_t r = hex_rgb(uart_buffer[1], uart_buffer[2]);
			uint8_t g = hex_rgb(uart_buffer[3], uart_buffer[4]);
			uint8_t b = hex_rgb(uart_buffer[5], uart_buffer[6]);
			set_rgb(r, g, b);
            uart_tx('\n');
            uart_tx('\r');
		}
        else
            uart_print("\r\nbad rgb code\r\n");
		uart_index = 0;
        return ;
	}
    if (uart_index >= 7) {
        uart_print("\r\ntoo long rgb code\r\n");
        uart_index = 0;
        return;
    }
	uart_buffer[uart_index++] = c;
}

int main() {
    DDRD |= ((1 << PD3) | (1 << PD5) | (1 << PD6));
    
    uart_init(8);
    init_rgb();
    sei();
    uart_print("wait for rgb code:\r\n");
    while(1) {
    }
}

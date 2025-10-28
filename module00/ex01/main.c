#include <avr/io.h>

int main() {
    DDRB = DDRB | (1 << DDB0); // defini si la broche du port est en entree(0) ou sortie(1)
    PORTB = PORTB | (1 << PORTB0); // defini la valeur a apliquer sur les broches en sortie ou active le pull up sur les entrees
    // ici en mettant les 2 bits a 1 on est stable et PB0 est tirer vers le haut
    while(1){
    }
}

//? DDRX(data direction) = registre de direction du port x
//? PORTX(port data register) = registre pour ecrire sur le port x
//? PINX(port input register) = registre pour lire le port x
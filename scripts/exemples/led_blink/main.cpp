#include <stdlib.h>
#include <stdint-gcc.h>

void main() {
    // Initialisation du pin 13 en mode sortie
    *(volatile uint8_t*)24 |= (1 << 5);

    // Allumage de la LED interne
    *(volatile uint8_t*)25 |= (1 << 5);
}
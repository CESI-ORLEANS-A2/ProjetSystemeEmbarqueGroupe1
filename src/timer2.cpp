#include "timer2.hpp"
#include "peripherals/led.hpp"

int counter2 = 0;
void (*callback2)() = NULL;
unsigned long remains2 = 0;

/**
 * @brief Fonction exécutée à chaque interruption du timer
 * 
 * Références : 
 * @ref createTimer()
 * @ref stopTimer()
 * @ref counter
 * @ref callback
 * @ref remains
 */
ISR(TIMER2_COMPA_vect) {
    if (counter2 == 0) {
        if (remains2 > 0) {
            // Création d'un nouveau timer avec le délais restant
            // Ce timer écrase le timer actuel
            createTimer2(remains2, callback2);
        }
        else { // Si le délais est écoulé, on exécute la fonction callback
            if (callback2 != NULL) {
                (*callback2)();
                stopTimer2();
                LEDLoopTimer(color, fact);
            }
        }
    }
    else counter2--;
}

void initTimer2() {};

void createTimer2(long delay, void (*handler)()) {
    noInterrupts(); // Désactivation des interruptions
    unsigned long ticks = (delay * 16) / 1024;  // 16 MHz / 1024 = 15625 Hz; cela correspond à une interruption toutes les 64 µs
    if (ticks > 255) { // Si le délais est trop long, il est découpé en plusieurs interruptions
        remains2 = ticks % 255; // Calcul du nombre de microsecondes restantes après les counter premières interruptions
        counter2 = (ticks - remains2) / 255; // Calcul de nombre d'interruptions à effectuer
        ticks = 255; // Le délais est fixé à 255 coups d'horloge 
    }
    else {             // Sinon, on fixe le nombre d'interruptions à 0 et le nombre de microsecondes restantes à 0 afin d'arrêter
        remains2 = 0;   // le timer après le délais de ticks coups d'horloge
        counter2 = 0;
    }

    callback2 = handler; // Enregistrement la fonction à exécuter à la fin du délais

    TCCR2A = 0; // Réinitialisation de la configuration du timer
    TCCR2B = 0; // Réinitialisation de la configuration du timer
    TCNT2 = 0; // La valeur du compteur est fixée à 0
    OCR2A = ticks - 1; // La valeur de comparaison est fixée à ticks - 1 (le compteur commence à 0 d'où le -1)
    TCCR2B |= (1 << CS20) | (1 << CS21) | (1 << CS22); // Activation du prédiviseur à 1024
    TIMSK2 |= (1 << OCIE2A); // Activation de l'interruption du timer
    interrupts(); // Réactivation des interruptions
}
void stopTimer2() {
    TIMSK2 &= (0 << OCIE2A); // Désactivation de l'interruption du timer
}
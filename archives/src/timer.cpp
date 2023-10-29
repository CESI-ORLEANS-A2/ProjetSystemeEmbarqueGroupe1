#include "timer.hpp"

int counter = 0;
void (*callback)() = NULL;
unsigned long remains = 0;

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
ISR(TIMER1_COMPA_vect) {
    if (counter == 0) {
        if (remains > 0) {
            // Création d'un nouveau timer avec le délais restant
            // Ce timer écrase le timer actuel
            createTimer(remains, callback);
        }
        else { // Si le délais est écoulé, on exécute la fonction callback
            if (callback != NULL) {
                (*callback)();
                stopTimer();
            }
        }
    }
    else counter--;
}

void initTimer() {};

void createTimer(long delay, void (*handler)()) {
    noInterrupts(); // Désactivation des interruptions
    unsigned long ticks = (delay * 16) / 1024;  // 16 MHz / 1024 = 15625 Hz; cela correspond à une interruption toutes les 64 µs
    if (ticks > 65535) { // Si le délais est trop long, il est découpé en plusieurs interruptions
        remains = ticks % 65535; // Calcul du nombre de microsecondes restantes après les counter premières interruptions
        counter = (ticks - remains) / 65535; // Calcul de nombre d'interruptions à effectuer
        ticks = 65535; // Le délais est fixé à 65535 coups d'horloge (à 16MHz, cela correspond à 4,19424 secondes)
    }
    else {             // Sinon, on fixe le nombre d'interruptions à 0 et le nombre de microsecondes restantes à 0 afin d'arrêter
        remains = 0;   // le timer après le délais de ticks coups d'horloge
        counter = 0;
    }

    callback = handler; // Enregistrement la fonction à exécuter à la fin du délais

    TCCR1A = 0; // Réinitialisation de la configuration du timer
    TCCR1B = 0; // Réinitialisation de la configuration du timer
    TCNT1 = 0; // La valeur du compteur est fixée à 0
    OCR1A = ticks - 1; // La valeur de comparaison est fixée à ticks - 1 (le compteur commence à 0 d'où le -1)
    TCCR1B |= (1 << CS12) | (1 << CS10); // Activation du prédiviseur à 1024
    TIMSK1 |= (1 << OCIE1A); // Activation de l'interruption du timer
    interrupts(); // Réactivation des interruptions
}
void stopTimer() {
    TIMSK1 &= (0 << OCIE1A); // Désactivation de l'interruption du timer
}
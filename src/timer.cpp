#include "timer.hpp"

int counter1 = 0;
void (*callback1)() = NULL;
unsigned long remains1 = 0;

int counter2 = 0;
void (*callback2)() = NULL;
unsigned long remains2 = 0;

/**
 * @brief Fonction exécutée à chaque interruption du timer
 * 
 * Références : 
 * @ref createTimer1()
 * @ref stopTimer1()
 * @ref counter1
 * @ref callback1
 * @ref remains1
 */
ISR(TIMER1_COMPA_vect) {
    if (counter1 == 0) {
        if (remains1 > 0) {
            // Création d'un nouveau timer avec le délais restant
            // Ce timer écrase le timer actuel
            createTimer1(remains1, callback1);
        }
        else { // Si le délais est écoulé, on exécute la fonction callback1
            if (callback1 != NULL) {
                stopTimer1();
                (*callback1)();
            }
        }
    }
    else counter1--;
}

void initTimer1() {};

void createTimer1(long delay, void (*handler)()) {
    noInterrupts(); // Désactivation des interruptions
    unsigned long ticks = (delay * 16) / 1024;  // 16 MHz / 1024 = 15625 Hz; cela correspond à une interruption toutes les 64 µs
    if (ticks > MAX_TIMER_VALUE) { // Si le délais est trop long, il est découpé en plusieurs interruptions
        remains1 = ticks % MAX_TIMER_VALUE; // Calcul du nombre de microsecondes restantes après les counter1 premières interruptions
        counter1 = (ticks - remains1) / MAX_TIMER_VALUE - 1; // Calcul de nombre d'interruptions à effectuer
        ticks = MAX_TIMER_VALUE; // Le délais est fixé au maximum à 65535 coups d'horloge (à 16MHz, cela correspond à 4,19424 secondes)
    }
    else {             // Sinon, on fixe le nombre d'interruptions à 0 et le nombre de microsecondes restantes à 0 afin d'arrêter
        remains1 = 0;   // le timer après le délais de ticks coups d'horloge
        counter1 = 0;
    }

    callback1 = handler; // Enregistrement la fonction à exécuter à la fin du délais

    TCCR1A = 0; // Réinitialisation de la configuration du timer
    TCCR1B = 0; // Réinitialisation de la configuration du timer
    TCNT1 = 0; // La valeur du compteur est fixée à 0
    OCR1A = ticks - 1; // La valeur de comparaison est fixée à ticks - 1 (le compteur commence à 0 d'où le -1)
    TCCR1B |= (1 << CS12) | (1 << CS10); // Activation du prédiviseur à 1024
    TIMSK1 |= (1 << OCIE1A); // Activation de l'interruption du timer
    interrupts(); // Réactivation des interruptions
}

void stopTimer1() {
    TIMSK1 &= (0 << OCIE1A); // Désactivation de l'interruption du timer
}

/**
 * @brief Fonction exécutée à chaque interruption du timer
 * 
 * Références : 
 * @ref createTimer1()
 * @ref stopTimer1()
 * @ref counter1
 * @ref callback1
 * @ref remains1
 */
ISR(TIMER2_COMPA_vect) {
    if (counter2 == 0) {
        if (remains2 > 0) {
            // Création d'un nouveau timer avec le délais restant
            // Ce timer écrase le timer actuel
            createTimer2(remains2, callback2);
        }
        else { // Si le délais est écoulé, on exécute la fonction callback1
            if (callback2 != NULL) {
                stopTimer2();
                (*callback2)();
            }
        }
    }
    else counter2--;
}

void initTimer2() {};

void createTimer2(long delay, void (*handler)()) {
    noInterrupts(); // Désactivation des interruptions
    unsigned long ticks = (delay * 16) / 1024;  // 16 MHz / 1024 = 15625 Hz; cela correspond à une interruption toutes les 64 µs
    if (ticks > MAX_TIMER_2_VALUE) { // Si le délais est trop long, il est découpé en plusieurs interruptions
        remains2 = ticks % MAX_TIMER_2_VALUE; // Calcul du nombre de microsecondes restantes après les counter1 premières interruptions
        counter2 = (ticks - remains2) / MAX_TIMER_2_VALUE - 1; // Calcul de nombre d'interruptions à effectuer
        ticks = MAX_TIMER_2_VALUE; // Le délais est fixé au maximum à 65535 coups d'horloge (à 16MHz, cela correspond à 4,19424 secondes) // TODO modifier le commentaire
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
    TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20); // Activation du prédiviseur à 1024
    TIMSK2 |= (1 << OCIE2A); // Activation de l'interruption du timer
    interrupts(); // Réactivation des interruptions
}

void stopTimer2() {
    TIMSK2 &= (0 << OCIE2A); // Désactivation de l'interruption du timer
}
#include "peripherals/buttons.hpp"

void initButtons() {
    // On définit les boutons en entrée avec une résistance de pull-up
    // pour limiter les problèmes de rebond
    pinMode(RED_BUTTON_PIN, INPUT_PULLUP);
    pinMode(GREEN_BUTTON_PIN, INPUT_PULLUP);
}
void initButtonsInterrupt() {
    // Initialisation des interruptions sur le bouton rouge ainsi que son timer pour le délai
    attachInterrupt(digitalPinToInterrupt(RED_BUTTON_PIN), &buttonPressed, CHANGE); 
    // Initialisation des interruptions sur le bouton vert ainsi que son timer pour le délai
    attachInterrupt(digitalPinToInterrupt(GREEN_BUTTON_PIN), &buttonPressed, CHANGE); 
}

void buttonPressed() {
    // digitalRead renvoi 1 si le bouton est relaché et 0 si le bouton est appuyé
    // On fait un OU binaire entre les deux boutons pour avoir un seul switch
    // 0b10 => Bouton rouge appuyé
    // 0b01 => Bouton vert appuyé
    // 0b00 => Bouton vert et rouge appuyé
    // 0b11 => Boutons relachés
    switch (0 | (digitalRead(GREEN_BUTTON_PIN) << 1) | (digitalRead(RED_BUTTON_PIN) << 0)) {
    case 0b10:
        createTimer1(BUTTON_DELAY, &redButtonPressed);
        break;
    case 0b01:
        createTimer1(BUTTON_DELAY, &greenButtonPressed);
        break;
    default:
        stopTimer1();
        break;
    }
}
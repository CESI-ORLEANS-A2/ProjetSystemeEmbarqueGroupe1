#include "includes/peripherals/buttons.hpp"

void initButtons() {
    pinMode(RED_BUTTON_PIN, INPUT_PULLUP);
    pinMode(GREEN_BUTTON_PIN, INPUT_PULLUP);
}
void initButtonsInterrupt() {
    attachInterrupt(digitalPinToInterrupt(RED_BUTTON_PIN), &buttonPressed, CHANGE); // Initialisation des interruptions sur le bouton rouge ainsi que son timer pour le délai
    attachInterrupt(digitalPinToInterrupt(GREEN_BUTTON_PIN), &buttonPressed, CHANGE); // Initialisation des interruptions sur le bouton vert ainsi que son timer pour le délai
}

void buttonPressed() {
    switch (0 | (digitalRead(GREEN_BUTTON_PIN) << 1) | (digitalRead(RED_BUTTON_PIN) << 0)) {
    case 0b10:
        createTimer(BUTTON_DELAY, &redButtonPressed);
        break;
    case 0b01:
        createTimer(BUTTON_DELAY, &greenButtonPressed);
        break;
    default:
        stopTimer();
        break;
    }
}
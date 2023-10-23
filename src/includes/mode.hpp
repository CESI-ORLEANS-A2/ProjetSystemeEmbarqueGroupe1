#include "main.hpp"

// Déclenché lorsqu'on appuie sur le bouton rouge pendant BUTTON_DELAY
// Permet de changer de mode
void redButtonPressed();
// Déclenché lorsqu'on appuie sur le bouton vert pendant BUTTON_DELAY
// Permet de changer de mode
void greenButtonPressed();

void stopLiveMode();

void switchToMode(int newMode);

void printMode();
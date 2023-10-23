#include "includes/mode.hpp"

// Déclenché lorsqu'on appuie sur le bouton rouge pendant BUTTON_DELAY
// Permet de changer de mode
void redButtonPressed() {
    switch (mode) {
    case STANDARD_MODE:
        liveMode = true;

        Serial.println();
        switchToMode(MAINTENANCE_MODE);
#if INTERPRETER
        printLiveMode();
        printPrompt();
        printBuffer();
#endif
        break;
    case ECONOMY_MODE:
        liveMode = true;

        Serial.println();
        switchToMode(MAINTENANCE_MODE);
#if INTERPRETER
        printLiveMode();
        printPrompt();
        printBuffer();
#endif
        break;
    case MAINTENANCE_MODE:
        switch (previousMode) {
        case ECONOMY_MODE:
            stopLiveMode();

            Serial.println();
            switchToMode(ECONOMY_MODE);
#if INTERPRETER
            printPrompt();
            printBuffer();
#endif
            break;
        case STANDARD_MODE:
            stopLiveMode();

            Serial.println();
            switchToMode(STANDARD_MODE);
#if INTERPRETER
            printPrompt();
            printBuffer();
#endif
            break;
        }
    }
}

// Déclenché lorsqu'on appuie sur le bouton vert pendant BUTTON_DELAY
// Permet de changer de mode
void greenButtonPressed() {
    switch (mode) {
    case STANDARD_MODE:

        Serial.println();
        switchToMode(ECONOMY_MODE);
#if INTERPRETER
        printPrompt();
        printBuffer();
#endif
        break;
    case ECONOMY_MODE:

        Serial.println();
        switchToMode(STANDARD_MODE);
#if INTERPRETER
        printPrompt();
        printBuffer();
#endif
        break;
    }
}

void stopLiveMode() {
    if (!liveMode) return;
    liveMode = false;
    Serial.println(F("Fin du mode live"));
}

void switchToMode(int newMode) {
    if (previousMode == MAINTENANCE_MODE) stopLiveMode();
    switch (newMode) {
    case STANDARD_MODE:
        switchToStandardMode();
        break;
    case ECONOMY_MODE:
        switchToEconomyMode();
        break;
    case CONFIGURATION_MODE:
        switchToConfigurationMode();
        break;
    case MAINTENANCE_MODE:
        switchToMaintenanceMode();
        break;
    }
#if INTERPRETER
    Serial.print(F("Passage en mode "));
    printMode();
#endif
};

void printMode() {
    Serial.println(
        mode == CONFIGURATION_MODE ? F("configuration") :
        mode == MAINTENANCE_MODE ? F("maintenance") :
        mode == ECONOMY_MODE ? F("économie") : F("standard")
    );
}
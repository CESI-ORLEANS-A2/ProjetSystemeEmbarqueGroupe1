#include "mode.hpp"

// Déclenché lorsqu'on appuie sur le bouton rouge pendant BUTTON_DELAY
// Permet de changer de mode
void redButtonPressed() {
    switch (mode) {
    case STANDARD_MODE:
        // On active le mode live puisqu'on utilise les boutons pour changer de mode
        liveMode = true;

        Serial.println();
        switchToMode(MAINTENANCE_MODE);
#if INTERPRETER // Permet de réafficher les informations affichées sur la console série 
        printLiveMode();
        printPrompt();
        printBuffer();
#endif
        break;
    case ECONOMY_MODE:
        // On active le mode live puisqu'on utilise les boutons pour changer de mode
        liveMode = true;

        Serial.println();
        switchToMode(MAINTENANCE_MODE);
#if INTERPRETER // Permet de réafficher les informations affichées sur la console série 
        printLiveMode();
        printPrompt();
        printBuffer();
#endif
        break;
    case MAINTENANCE_MODE:
        switch (previousMode) {
        case ECONOMY_MODE:
            stopLiveMode(); // Met fin au mode live

            Serial.println();
            switchToMode(ECONOMY_MODE);
#if INTERPRETER // Permet de réafficher les informations affichées sur la console série 
            printPrompt();
            printBuffer();
#endif
            break;
        case STANDARD_MODE:
            stopLiveMode(); // Met fin au mode live

            Serial.println();
            switchToMode(STANDARD_MODE);
#if INTERPRETER // Permet de réafficher les informations affichées sur la console série 
            printPrompt();
            printBuffer();
#endif
            break;
        case CONFIGURATION_MODE:
            switchToMode(previousMode);
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
#if INTERPRETER // Permet de réafficher les informations affichées sur la console série
        printPrompt();
        printBuffer();
#endif
        break;
    case ECONOMY_MODE:

        Serial.println();
        switchToMode(STANDARD_MODE);
#if INTERPRETER // Permet de réafficher les informations affichées sur la console série
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
    case ERROR_MODE:
        switchToErrorMode(UNKNOWN_ERROR);
        break;
    }
    Serial.print(F("Passage en mode "));
    printMode();
};

void printMode() {
    Serial.println(
        mode == CONFIGURATION_MODE ? F("configuration") :
        mode == MAINTENANCE_MODE ? F("maintenance") :
        mode == ECONOMY_MODE ? F("économie") : F("standard")
    );
}
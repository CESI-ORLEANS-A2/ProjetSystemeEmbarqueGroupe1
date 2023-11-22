#include "mode.hpp"

// Déclenché lorsqu'on appuie sur le bouton rouge pendant BUTTON_DELAY
// Permet de changer de mode
void redButtonPressed() {
    switch (mode) {
    case STANDARD_MODE:
    case ECONOMY_MODE:

#if INTERPRETER
        // On active le mode live puisqu'on utilise les boutons pour changer de mode
        liveMode = true;
#endif // INTERPRETER

        Serial.println();
        switchToMode(MAINTENANCE_MODE);

#if INTERPRETER 
        // Permet de réafficher les informations affichées sur la console série 
        printLiveMode();
        printPrompt();
        printBuffer();
#endif // INTERPRETER

        break;
    case MAINTENANCE_MODE:
        if (previousMode == STANDARD_MODE || previousMode == ECONOMY_MODE) {

#if INTERPRETER
            // Met fin au mode live
            stopLiveMode();
#endif // INTERPRETER

            Serial.println();
            switchToMode(previousMode);

#if INTERPRETER 
            // Permet de réafficher les informations affichées sur la console série 
            printPrompt();
            printBuffer();
#endif // INTERPRETER

        }
        break;
    case CONFIGURATION_MODE:
        switchToMode(previousMode);
        break;
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
        // Permet de réafficher les informations affichées sur la console série
        printPrompt();
        printBuffer();
#endif // INTERPRETER

        break;
    case ECONOMY_MODE:
        Serial.println();
        switchToMode(STANDARD_MODE);

#if INTERPRETER 
        // Permet de réafficher les informations affichées sur la console série
        printPrompt();
        printBuffer();
#endif // INTERPRETER

        break;
    }
}

#if INTERPRETER
void stopLiveMode() {
    if (!liveMode) return;
    liveMode = false;
    Serial.println(F("Fin du mode live"));
}
#endif // INTERPRETER

void switchToMode(int newMode) {
#if INTERPRETER
    if (previousMode == MAINTENANCE_MODE) stopLiveMode();
#endif // INTERPRETER

    switch (mode) {
    case STANDARD_MODE:
        quitStandardMode();
        break;
    case ECONOMY_MODE:
        quitEconomyMode();
        break;
    case CONFIGURATION_MODE:
        quitConfigurationMode();
        break;
    case MAINTENANCE_MODE:
        quitMaintenanceMode();
        break;
    }

    switch (newMode) {
    case STANDARD_MODE:
        Serial.println(F("Passage en mode standard"));
        switchToStandardMode();
        break;
    case ECONOMY_MODE:
        Serial.println(F("Passage en mode economique"));
        switchToEconomyMode();
        break;
    case CONFIGURATION_MODE:
        Serial.println(F("Passage en mode configuration"));
        switchToConfigurationMode();
        break;
    case MAINTENANCE_MODE:
        Serial.println(F("Passage en mode maintenance"));
        switchToMaintenanceMode();
        break;
    case ERROR_MODE:
        switchToErrorMode(UNKNOWN_ERROR);
        break;
    }
};

void printMode() {
    Serial.println(
        mode == CONFIGURATION_MODE ? F("configuration") :
        mode == MAINTENANCE_MODE ? F("maintenance") :
        mode == ECONOMY_MODE ? F("économie") : F("standard")
    );
}

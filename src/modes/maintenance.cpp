#include "modes/maintenance.hpp"

void switchToMaintenanceMode() {
    previousMode = mode;
    mode = MAINTENANCE_MODE;
    
    switchLEDToOrange();

    unmount();

    // On affiche l'en-tête CSV si besoin
#if !INTERPRETER
    printCSVHeader();
#endif // !NTERPRETER
}
void quitMaintenanceMode() {
    mount();
}
void runMaintenanceModeStep() {
#if INTERPRETER
    // Si le mode live est activé, on vérifie si des données sont disponibles sur le port série
    if (liveMode) {
        if (Serial.available()) {
            int data = Serial.read();
            // Si la donnée est un retour à la ligne, on quitte le mode live
            if (data == '\n') {
                stopLiveMode();
                Serial.print(F("\n\r> "));
                return;
            }
        }
        // Si le mode live est activé, on réalise l'acquisition des données
        // et on les affiche sur le port série si l'acquisition est terminée
        if (acquisition()) printData();
    }
#else // INTERPRETER
    // On réalise l'acquisition des données
    // et on les affiche sur le port série si l'acquisition est terminée
    if (acquisition()) printData();
#endif // INTERPRETER
};

#if INTERPRETER
void printLiveMode() {
    Serial.println(F("Mode live activé"));

    // On affiche l'en-tête CSV si besoin
#if LIVE_MODE_SERIAL_OUTPUT==OUTPUT_CSV
    printCSVHeader();
#endif // LIVE_MODE_SERIAL_OUTPUT==OUTPUT_CSV
}

#endif // INTERPRETER

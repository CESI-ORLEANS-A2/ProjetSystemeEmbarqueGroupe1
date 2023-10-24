#include "includes/acquisition.hpp"

unsigned long previousAcquisition = NULL;
bool errors[NUMBER_OF_SENSORS];
bool underAcquisition = false;
int numberOfErrors = NUMBER_OF_SENSORS;

void acquisition(void (*callback)()) {
    if (!underAcquisition) {
        if (
            previousAcquisition &&
            millis() - previousAcquisition < (mode == MAINTENANCE_MODE ? ACQUISITION_DELAY_MANTENANCE : SETTING_DEFAULT_ACQUISITION_DELAY)
            ) return; // On attend le délai d'acquisition
        else {
            // Démarrage d'une nouvelle acquisition
            underAcquisition = true;
            previousAcquisition = millis();
        }
    }

    // Réinitialisation du tableau erreurs
    for (int i = 0; i < NUMBER_OF_SENSORS; i++) {
        errors[i] = true;
    }

    // Acquisition des données
    for (int i = 0; i < NUMBER_OF_SENSORS; i++) {
        if (!getSetting(sensors[i]->enabled)) continue;
        if (mode == ECONOMY_MODE && !sensors[i]->economy) continue;
        if (!errors[i]) continue;

        // Acquisition d'un capteur
        lastMeasurements[i] = sensors[i]->acquisition();
        Serial.print("Acquisition de ");
        Serial.print(i);
        Serial.print(" : ");
        Serial.print(lastMeasurements[i]);
        Serial.print(" | ");
        if (lastMeasurements[i] != NULL) {
            errors[i] = false;
            numberOfErrors--;
        }

    }
    Serial.print("\nNombre d'erreurs : ");
    Serial.println(numberOfErrors);

    // Appel du callback car toutes les données ont été acquises sans erreur
    if (numberOfErrors == 0) {
        underAcquisition = false;
        numberOfErrors = NUMBER_OF_SENSORS;
        (*callback)();
    }
    else
        if (previousAcquisition - millis() > getSetting(SETTING_ACQUISITION_TIMEOUT))
            switchToErrorMode(ERROR_ACQUISITION_TIMEOUT);
}


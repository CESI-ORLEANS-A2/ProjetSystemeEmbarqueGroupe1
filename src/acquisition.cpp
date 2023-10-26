#include "acquisition.hpp"

unsigned long previousAcquisition = NULL;
bool errors[NUMBER_OF_SENSORS];
bool underAcquisition = false;
int numberOfErrors = NUMBER_OF_SENSORS;

void acquisition(void (*callback)()) {
    if (!underAcquisition) {
        if (
            previousAcquisition && // Si la variable previousAcquisition n'est pas initialisée, on peut commencer une acquisition.
            millis() - previousAcquisition < ( // Si le délai entre la dernière acquisition et maintenant est inférieur au délai d'acquisition
                mode == MAINTENANCE_MODE ? ACQUISITION_DELAY_MANTENANCE :             //  -| 
                mode == ECONOMY_MODE ? getSetting(SETTING_ACQUISITION_DELAY) * 2 :    //   | => Sélection du bon délais en fonction du mode
                getSetting(SETTING_ACQUISITION_DELAY)                                 //  -|
                )
            ) return; // On attend le délai d'acquisition
        else {
            // Démarrage d'une nouvelle acquisition
            underAcquisition = true;
            previousAcquisition = millis();
            // Réinitialisation du tableau erreurs
            for (int i = 0; i < NUMBER_OF_SENSORS; i++) {
                errors[i] = true;
            }
        }
    }

    // Acquisition des données
    for (int i = 0; i < NUMBER_OF_SENSORS; i++) {
        if (!getSetting(sensors[i]->enabled)) continue; // Si le capteur n'est pas activé, on passe au suivant
        if (mode == ECONOMY_MODE && !getSetting(sensors[i]->economy)) continue; // Si le capteur n'est pas activé en mode économique, on passe au suivant
        if (!errors[i]) continue; // Si le capteur n'est pas en erreur, on passe au suivant

        // Acquisition d'un capteur
        lastMeasurements[i] = sensors[i]->acquisition();
        if (lastMeasurements[i] != ACQUISITION_ERROR_VALUE) {
            errors[i] = false;
            numberOfErrors--;
        }
    }

    // Appel du callback car toutes les données ont été acquise sans erreur
    if (mode == STANDARD_MODE) { // TODO retirer
        Serial.print("Nombre d'erreurs : ");
        Serial.print(numberOfErrors);
        Serial.print(" | underAcquisition : ");
        Serial.print(underAcquisition);
        Serial.print(" | lastMeasurements[0] : ");
        Serial.print(lastMeasurements[0]);
        Serial.print(" | lastMeasurements[1] : ");
        Serial.println(lastMeasurements[1]);

        Serial.print("Max temp : ");
        Serial.print(getSetting(SETTING_TEMPERATURE_MAX));
        Serial.print(" | Min temp : ");
        Serial.print(getSetting(SETTING_TEMPERATURE_MIN));
        Serial.print(" | Max hum : ");
        Serial.print(getSetting(SETTING_HUMIDITY_MAX));
        Serial.print(" | Min hum : ");
        Serial.println(getSetting(SETTING_HUMIDITY_MIN));
    }
    // Si il n'y a plus d'erreur, on arrête l'acquisition et on appelle le callback
    if (numberOfErrors == 0) {
        underAcquisition = false;
        numberOfErrors = NUMBER_OF_SENSORS;
        if (callback != NULL)
            (*callback)();
    }
    else // Si il reste des erreurs, on vérifie si l'acquisition n'a pas dépassé le délais d'acquisition
        if (previousAcquisition - millis() > getSetting(SETTING_ACQUISITION_TIMEOUT))
            switchToErrorMode(ERROR_ACQUISITION_TIMEOUT);
}


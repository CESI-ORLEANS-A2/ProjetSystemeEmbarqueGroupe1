#include "acquisition.hpp"

unsigned long previousAcquisition = NULL;
bool errors[NUMBER_OF_SENSORS];
bool underAcquisition = false;
int numberOfErrors;
#if GPS_ENABLED
bool GPSError = true;
int GPSCounter;
#endif

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
            numberOfErrors = 0;
            // Réinitialisation du tableau erreurs
            for (int i = 0; i < NUMBER_OF_SENSORS; i++) {
                errors[i] = true;
                if (getSetting(sensors[i].enabled)) numberOfErrors++; // Si le capteur n'est pas activé, on passe au suivant
            }
        }
    }

    // Acquisition des données
    for (int i = 0; i < NUMBER_OF_SENSORS; i++) {
        if (!getSetting(sensors[i].enabled)) continue; // Si le capteur n'est pas activé, on passe au suivant
#if INTERPRETER
        if (mode == ECONOMY_MODE && !getSetting(sensors[i].economy)) continue; // Si le capteur n'est pas activé en mode économique, on passe au suivant
#endif
        if (!errors[i]) continue; // Si le capteur n'est pas en erreur, on passe au suivant

        // Acquisition d'un capteur
        lastMeasurements[i] = sensors[i].measure();
        if (lastMeasurements[i] != ACQUISITION_ERROR_VALUE) {
            errors[i] = false;
            numberOfErrors--;
        }
    }

#if GPS_ENABLED
    //Acquisition du GPS
    if (mode == ECONOMY_MODE ? GPSCounter == 0 : true) {
        if (readGPS()) {
            GPSError = false;
            GPSCounter = 1;
        }
    }
    else
        GPSCounter--;
#endif

    readClock();

    Serial.print(F("Acquisition : "));Serial.print(millis() - previousAcquisition);Serial.println(F("ms"));
    Serial.print(F("Erreurs : "));Serial.println(numberOfErrors);
    // Si il n'y a plus d'erreur, on arrête l'acquisition et on appelle le callback
    if (numberOfErrors == 0
#if GPS_ENABLED
        && !GPSError
#endif
        ) {
        underAcquisition = false;
#if GPS_ENABLED
        GPSError = true;
#endif
        // Appel du callback car toutes les données ont été acquise sans erreur
        if (callback != NULL)
            (*callback)();
    }
    else // Si il reste des erreurs, on vérifie si l'acquisition n'a pas dépassé le délais d'acquisition
        if (previousAcquisition - millis() > getSetting(SETTING_ACQUISITION_TIMEOUT))
            switchToErrorMode(ERROR_ACQUISITION_TIMEOUT);
}


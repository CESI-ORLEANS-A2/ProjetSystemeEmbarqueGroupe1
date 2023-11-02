#include "acquisition.hpp"

unsigned long previousAcquisition = NULL;
bool errors[NUMBER_OF_SENSORS];
bool underAcquisition = false;
int numberOfErrors = NUMBER_OF_SENSORS;
#if GPS_ENABLED
bool GPSError = true;
#endif
bool clockError = true;

#if GPS_ENABLED
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
    
    if (readClock()) {
        clockError = false;
    }
    // Serial.print("E : ");
    // Serial.print(numberOfErrors);
    // Serial.print(" C : ");
    // Serial.print(clockError);
    // Serial.print(" U : ");
    // Serial.println(underAcquisition);
    // Si il n'y a plus d'erreur, on arrête l'acquisition et on appelle le callback
    if (numberOfErrors == 0 &&
#if GPS_ENABLED
        !GPSError &&
#endif
        !clockError
        ) {
        underAcquisition = false;
        numberOfErrors = NUMBER_OF_SENSORS;
#if GPS_ENABLED
        GPSError = true;
#endif
        clockError = true;
        // Appel du callback car toutes les données ont été acquise sans erreur
        if (callback != NULL)
            (*callback)();
    }
    else // Si il reste des erreurs, on vérifie si l'acquisition n'a pas dépassé le délais d'acquisition
        if (previousAcquisition - millis() > getSetting(SETTING_ACQUISITION_TIMEOUT))
            switchToErrorMode(ERROR_ACQUISITION_TIMEOUT);
}


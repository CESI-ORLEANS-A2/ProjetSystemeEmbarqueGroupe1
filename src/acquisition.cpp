#include "acquisition.hpp"

unsigned long previousAcquisition = NULL;
bool errors[NUMBER_OF_SENSORS];
bool underAcquisition = false;
int numberOfErrors;
int sensorsTimeout = 0;
#if GPS_ENABLED
bool GPSError = true;
int GPSCounter;
#endif

bool acquisition() {
    if (!underAcquisition) {
        if (
            previousAcquisition && // Si la variable previousAcquisition n'est pas initialisée, on peut commencer une acquisition.
            millis() - previousAcquisition < ( // Si le délai entre la dernière acquisition et maintenant est inférieur au délai d'acquisition
                mode == MAINTENANCE_MODE ? ACQUISITION_DELAY_MANTENANCE :             //  -| 
                mode == ECONOMY_MODE ? getSetting(SETTING_ACQUISITION_DELAY) * 2 :    //   | => Sélection du bon délais en fonction du mode
                getSetting(SETTING_ACQUISITION_DELAY)                                 //  -|
                )
            ) return false; // On attend le délai d'acquisition
        else {
            // Démarrage d'une nouvelle acquisition

#if LED_BLINK_ACQUISITION
            // On initialise le timer de clignotement de la LED indiquant l'acquisition
            // Si un clignotement des LED n'est pas déja en cours
            if (!LEDTimerIsRunning())
                initLEDTimer(&switchLEDToBlue, &switchLEDToWhite, 1, 30, LED_ACQUISITION_BLINK_FREQUENCY);
#endif // LED_BLINK_ACQUISITION

#if LED_STATIC_ACQUISITION
            switchLEDToPurple();
#endif // LED_STATIC_ACQUISITION

            underAcquisition = true;
            previousAcquisition = millis();
            numberOfErrors = 0;
            // Réinitialisation du tableau erreurs
            for (int i = 0; i < NUMBER_OF_SENSORS; i++) {
                if (!getSetting(sensors[i].enabled)) continue; // Si le capteur n'est pas activé, on passe au suivant
#if INTERPRETER
                if (mode == ECONOMY_MODE && !getSetting(sensors[i].economy)) continue;
#endif // INTERPRETER
                errors[i] = true;
                numberOfErrors++;
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

//     Serial.print("Acquisition ");Serial.print(numberOfErrors);
// #if GPS_ENABLED
//     Serial.print(" ");Serial.print(GPSError);
// #endif 
//     Serial.print(" ");Serial.println(millis() - previousAcquisition);
//     Serial.println(freeRam());

    // Si il n'y a plus d'erreur, on arrête l'acquisition et on appelle le callback
    if (numberOfErrors == 0
#if GPS_ENABLED
        && !GPSError
#endif
        ) {
        underAcquisition = false;
        sensorsTimeout = 0;
#if GPS_ENABLED
        GPSError = true;
#endif
        // Toutes les données ont été acquise sans erreur donc la fonction renvoie true pour indiquer que l'acquisition est terminée

#if LED_BLINK_ACQUISITION
        // On arrête le timer de clignotement de la LED indiquant l'acquisition
        if (LEDfrequency == LED_ACQUISITION_BLINK_FREQUENCY) stopLEDTimer();
#endif // LED_BLINK_ACQUISITION
#if LED_STATIC_ACQUISITION
        mode == MAINTENANCE_MODE ? switchLEDToOrange() :
            mode == STANDARD_MODE ? switchLEDToGreen() :
            mode == ECONOMY_MODE ? switchLEDToBlue() :
            switchLEDToYellow();
#endif // LED_STATIC_ACQUISITION

        return true;
    }
    else // Si il reste des erreurs, on vérifie si l'acquisition n'a pas dépassé le délais d'acquisition
        if (millis() - previousAcquisition > getSetting(SETTING_ACQUISITION_TIMEOUT)) {
            if (sensorsTimeout > 1) {
                switchToErrorMode(ERROR_SENSOR_ACCESS);
            }
            else {
                // switchToErrorMode(ERROR_ACQUISITION_TIMEOUT);
                sensorsTimeout++;
                underAcquisition = false;
#if LED_STATIC_ACQUISITION
                mode == MAINTENANCE_MODE ? switchLEDToOrange() :
                    mode == STANDARD_MODE ? switchLEDToGreen() :
                    mode == ECONOMY_MODE ? switchLEDToBlue() :
                    switchLEDToYellow();
#endif // LED_STATIC_ACQUISITION

                return true;
            }
        }

    return false;
}


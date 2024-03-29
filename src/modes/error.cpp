#include "modes/error.hpp"

int currentError = NULL;

void switchToErrorMode(int error) {
    currentError = error;
    switch (error) {
    case ERROR_RTC_ACCESS:
        switchLEDToRedBlue();
        break;
    case ERROR_GPS_ACCESS:
        switchLEDToRedYellow();
        break;
    case ERROR_SENSOR_ACCESS:
        switchLEDToRedGreen();
        break;
    case ERROR_INCONSISTENT_DATA:
        switchLEDToRed2Green();
        break;
    case ERROR_SD_FULL:
        Serial.println(F("La carte SD est pleine"));
        switchLEDToRedWhite();
        break;
    case ERROR_SD_ACCESS:
        Serial.println(F("Erreur lors de l'ouverture du fichier"));
        switchLEDToRed2White();
        break;
    }
}
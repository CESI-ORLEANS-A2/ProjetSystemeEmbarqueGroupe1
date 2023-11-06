#include "libs/bme.hpp"

BME280 bme;
bool isInit = false;

void initBME() {
    // Si le capteur est déjà initialisé, on ne fait rien
    if (isInit) return;
    isInit = true;

    // Initialise le capteur BME280
    // Si il y a une erreur lors de l'initialisation, on passe en mode erreur
    if (!bme.init())
        switchToErrorMode(ERROR_SENSOR_ACCESS);
}

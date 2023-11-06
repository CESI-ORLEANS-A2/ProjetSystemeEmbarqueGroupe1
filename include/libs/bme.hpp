#include "consts.hpp"
#include "modes/error.hpp"

#include <Seeed_BME280.h>

/**
 * @brief Instance du capteur BME280 représentant le capteur de température, d'humidité et de pression.
*/
extern BME280 bme;
/**
 * @brief Booléen indiquant si le capteur BME280 est initialisé.
*/
extern bool isInit;

/**
 * @brief Initialise le capteur BME280.
 * 
 * Si le capteur n'est pas initialisé, initialise le capteur BME280.
 * 
 * Si il y a une erreur lors de l'initialisation, on passe en mode erreur.
 * 
 * Références :
 * @ref ERROR_SENSOR_ACCESS
 * @ref isInit
 * @ref bme
 * @ref switchToErrorMode()
*/
void initBME();

/**
 * @brief Mesure la pression.
*/
#define readPressure() bme.getPressure()
/**
 * @brief Mesure l'humidité.
*/
#define readHumidity() bme.getHumidity()
/**
 * @brief Mesure la température.
*/
#define readTemperature() bme.getTemperature()

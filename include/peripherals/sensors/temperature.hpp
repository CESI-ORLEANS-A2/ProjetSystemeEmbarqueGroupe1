#include "main.hpp"
#include "libs/bme.hpp"

/**
 * @brief Initialise le capteur de température.
 * 
 * Le capteur est initialiser sous la forme d'une structure Sensor ajoutée au tableau sensors[].
 * Cette structure contient :
 * - L'adresse mémoire Flash du nom du capteur
 * - L'identifiant associé au paramètre réprésentant l'état du capteur
 * - L'identifiant associé au paramètre réprésentant l'état du capteur en mode économie
 * - Un pointeur vers la fonction de mesure du capteur
 * 
 * Références :
 * @ref TEMPERATURE_SENSOR
 * @ref TEMPERATURE_SENSOR_NAME 
 * @ref SETTING_TEMPERATURE_ENABLED
 * @ref SETTING_TEMPERATURE_ECONOMY_ENABLED
 * @ref sensors
 * @ref measureTemperature()
*/
void initTemperatureSensor();

/**
 * @brief Mesure la température.
 * 
 * Récupère la valeur de la température en utilisant la fonction readTemperature() et
 * vérifie que la valeur est comprise entre les valeurs définies dans les paramètres.
 * 
 * @return La température mesurée.
 * 
 * Références :
 * @ref SETTING_TEMPERATURE_MIN
 * @ref SETTING_TEMPERATURE_MAX
 * @ref ACQUISITION_ERROR_VALUE
 * @ref readTemperature()
 * @ref getSetting()
*/
float measureTemperature();
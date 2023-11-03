#include "main.hpp"
#include "libs/bme.hpp"

/**
 * @brief Initialise le capteur de pression.
 * 
 * Le capteur est initialiser sous la forme d'une structure Sensor ajoutée au tableau sensors[].
 * Cette structure contient :
 * - L'adresse mémoire Flash du nom du capteur
 * - L'identifiant associé au paramètre réprésentant l'état du capteur
 * - L'identifiant associé au paramètre réprésentant l'état du capteur en mode économie
 * - Un pointeur vers la fonction de mesure du capteur
 * 
 * Références :
 * @ref PRESSURE_SENSOR
 * @ref PRESSURE_SENSOR_NAME
 * @ref SETTING_PRESSURE_ENABLED
 * @ref SETTING_PRESSURE_ECONOMY_ENABLED
 * @ref sensors
 * @ref measurePressure()
*/
void initPressureSensor();

/**
 * @brief Mesure la pression.
 * 
 * Récupère la valeur de la pression en utilisant la fonction readPressure() et
 * vérifie que la valeur est comprise entre les valeurs définies dans les paramètres.
 * 
 * @return La pression mesurée.
 * 
 * Références :
 * @ref SETTING_PRESSURE_MIN
 * @ref SETTING_PRESSURE_MAX
 * @ref ACQUISITION_ERROR_VALUE
 * @ref readPressure()
*/
float measurePressure();
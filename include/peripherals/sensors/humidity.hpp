#include "main.hpp"
#include "libs/bme.hpp"

/**
 * @brief Initialise le capteur d'humidité.
 * 
 * Le capteur est initialiser sous la forme d'une structure Sensor ajoutée au tableau sensors[].
 * Cette structure contient :
 * - L'adresse mémoire Flash du nom du capteur
 * - L'identifiant associé au paramètre réprésentant l'état du capteur
 * - L'identifiant associé au paramètre réprésentant l'état du capteur en mode économie
 * - Un pointeur vers la fonction de mesure du capteur
 * 
 * Références :
 * @ref HUMIDITY_SENSOR
 * @ref HUMIDITY_SENSOR_NAME
 * @ref SETTING_HUMIDITY_ENABLED
 * @ref SETTING_HUMIDITY_ECONOMY_ENABLED
 * @ref sensors
 * @ref measureHumidity()
*/
void initHumiditySensor();

/**
 * @brief Mesure l'humidité.
 * 
 * Récupère la valeur de l'humidité en utilisant la fonction readHumidity() et
 * vérifie que la valeur est comprise entre les valeurs définies dans les paramètres.
 * 
 * @return L'humidité mesurée.
 * 
 * Références :
 * @ref TEMPERATURE_SENSOR
 * @ref SETTING_HUMIDITY_MIN
 * @ref SETTING_HUMIDITY_MAX
 * @ref ACQUISITION_ERROR_VALUE
 * @ref readHumidity()
 * @ref getSetting()
*/
float measureHumidity();
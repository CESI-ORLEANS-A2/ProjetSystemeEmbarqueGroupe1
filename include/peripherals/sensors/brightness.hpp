#include "main.hpp"

/**
 * @brief Initialise le capteur de luminosité.
 * 
 * Le capteur est initialiser sous la forme d'une structure Sensor ajoutée au tableau sensors[].
 * Cette structure contient : 
 *  - L'adresse mémoire Flash du nom du capteur
 *  - L'identifiant associé au paramètre réprésentant l'état du capteur
 *  - L'identifiant associé au paramètre réprésentant l'état du capteur en mode économie
 *  - Un pointeur vers la fonction de mesure du capteur
 * 
 * Références :
 * @ref BRIGHTNESS_SENSOR
 * @ref BRIGHTNESS_SENSOR_NAME
 * @ref SETTING_BRIGHTNESS_ENABLED
 * @ref SETTING_BRIGHTNESS_ECONOMY_ENABLED
 * @ref sensors
 * @ref measureBrightness()
*/
void initBrightnessSensor();

/**
 * @brief Mesure la luminosité.
 * 
 * Récupère la valeur de la luminosité en utilisant la fonction analogRead() et 
 * vérifie que la valeur est comprise entre les valeurs définies dans les paramètres.
 * 
 * @return La luminosité mesurée.
 * 
 * Références :
 * @ref BRIGHTNESS_SENSOR_DEVICE
 * @ref SETTING_BRIGHTNESS_LOW
 * @ref SETTING_BRIGHTNESS_HIGH
 * @ref ACQUISITION_ERROR_VALUE
 * @ref getSetting()
*/
float measureBrightness();
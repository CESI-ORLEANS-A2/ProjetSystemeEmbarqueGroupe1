#ifndef Settings_h
#define Settings_h

#include "consts.hpp"
#include <EEPROM.h>

/**
 * @brief Structure représentant un paramètre de la station météo.
 * 
 * Ce paramètre possède une valeur par défaut définit dans le fichier consts.hpp et 
 * est modifiable grâce à la commande set.
 * Exemple: set LOG_INTERVALL 10
*/
struct Setting
{
    /**
     * @brief Nom du paramètre
     * 
     * Le nom est stocké dans la mémoire Flash.
    */
    char* name;
    /**
     * @brief Valeur par défaut du paramètre
    */
    long defaultValue;
    /**
     * @brief Valeur actuelle du paramètre
    */
    long value; 
};

/**
 * @brief Paramètres de la station météo
 * 
 * Ces paramètres sont stockés dans l'EEPROM de l'Arduino et mis à jour au démarrage
 * du programme ou sur demande. Les paramètres par défaut sont définis dans consts.hpp .
*/
extern Setting settings[NUMBER_OF_SETTINGS];

/**
 * @brief Initialise les paramètres de la station météo.
 * 
 * Les paramètres par défaut sont définis dans consts.hpp .
 * 
 * Références : 
 * @ref settings
 * @ref Setting
 * @ref SETTING_ACQUISITION_DELAY
 * @ref SETTING_NAME_ACQUISITION_DELAY
 * @ref SETTING_DEFAULT_ACQUISITION_DELAY
 * @ref SETTING_FILE_MAX_SIZE
 * @ref SETTING_NAME_FILE_MAX_SIZE
 * @ref SETTING_DEFAULT_FILE_MAX_SIZE
 * @ref SETTING_ACQUISITION_TIMEOUT
 * @ref SETTING_NAME_ACQUISITION_TIMEOUT
 * @ref SETTING_DEFAULT_ACQUISITION_TIMEOUT
 * @ref SETTING_BRIGHTNESS_ENABLED
 * @ref SETTING_NAME_BRIGHTNESS_ENABLED
 * @ref SETTING_DEFAULT_BRIGHTNESS_ENABLED
 * @ref SETTING_BRIGHTNESS_LOW
 * @ref SETTING_NAME_BRIGHTNESS_LOW
 * @ref SETTING_DEFAULT_BRIGHTNESS_LOW
 * @ref SETTING_BRIGHTNESS_HIGH
 * @ref SETTING_NAME_BRIGHTNESS_HIGH
 * @ref SETTING_DEFAULT_BRIGHTNESS_HIGH
 * @ref SETTING_TEMPERATURE_ENABLED
 * @ref SETTING_NAME_TEMPERATURE_ENABLED
 * @ref SETTING_DEFAULT_TEMPERATURE_ENABLED
 * @ref SETTING_TEMPERATURE_MIN
 * @ref SETTING_NAME_TEMPERATURE_MIN
 * @ref SETTING_DEFAULT_TEMPERATURE_MIN
 * @ref SETTING_TEMPERATURE_MAX
 * @ref SETTING_NAME_TEMPERATURE_MAX
 * @ref SETTING_DEFAULT_TEMPERATURE_MAX
 * @ref SETTING_HUMIDITY_ENABLED
 * @ref SETTING_NAME_HUMIDITY_ENABLED
 * @ref SETTING_DEFAULT_HUMIDITY_ENABLED
 * @ref SETTING_HUMIDITY_MIN
 * @ref SETTING_NAME_HUMIDITY_MIN
 * @ref SETTING_DEFAULT_HUMIDITY_MIN
 * @ref SETTING_HUMIDITY_MAX
 * @ref SETTING_NAME_HUMIDITY_MAX
 * @ref SETTING_DEFAULT_HUMIDITY_MAX
 * @ref SETTING_PRESSURE_ENABLED
 * @ref SETTING_NAME_PRESSURE_ENABLED
 * @ref SETTING_DEFAULT_PRESSURE_ENABLED
 * @ref SETTING_PRESSURE_MIN
 * @ref SETTING_NAME_PRESSURE_MIN
 * @ref SETTING_DEFAULT_PRESSURE_MIN
 * @ref SETTING_PRESSURE_MAX
 * @ref SETTING_NAME_PRESSURE_MAX
 * @ref SETTING_DEFAULT_PRESSURE_MAX
*/
void initSettings();
/**
 * @brief Met à jour les paramètres de la station météo à partir de l'EEPROM.
 * 
 * Si le paramètre en question n'est pas définit dans l'EEPROM, la valeur par défaut
 * est utilisée.
 * 
 * Références : 
 * @ref settings
 * @ref EEPROM
 * @ref NUMBER_OF_SETTINGS
 * @ref DEFAULT_SETTINGS
*/
void updateSettingsFromEEPROM();
/**
 * @brief Réinitialise les paramètres de la station météo à leurs valeurs par défaut.
 * 
 * Les paramètres par défaut sont définis dans consts.hpp .
 * Les paramètres sont ensuite sauvegardés dans l'EEPROM.
 * 
 * Références : 
 * @ref settings
 * @ref EEPROM
 * @ref DEFAULT_SETTINGS
 * @ref NUMBER_OF_SETTINGS
*/
void resetSettings();
/**
 * @brief Récupère la valeur d'un paramètre depuis le tableau settings.
 * 
 * Cette fonction ne met pas à jour les paramètres depuis l'EEPROM.
 * 
 * @return La valeur du paramètre
 * 
 * Références : 
 * @ref settings
*/
long getSetting(int id);
/**
 * @brief Sauvegarde la valeur d'un paramètre dans l'EEPROM.
 * 
 * Le tableau settings est également mis à jour.
 * 
 * Références : 
 * @ref EEPROM
*/
void setSetting(int id, long value);

#endif
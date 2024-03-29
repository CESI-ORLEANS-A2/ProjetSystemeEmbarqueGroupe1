#ifndef Settings_h
#define Settings_h

#include "consts.hpp"
#if SETTINGS_IN_EEPROM
#include <EEPROM.h>
#endif // SETTINGS_IN_EEPROM

/**
 * @brief Structure représentant un paramètre de la station météo.
 *
 * Ce paramètre possède une valeur par défaut définit dans le fichier consts.hpp et
 * est modifiable grâce à la commande set.
 * Exemple: set LOG_INTERVALL 10
*/
struct Setting {
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
    /**
     * @brief Valeur minimale du paramètre
    */
    long min;
    /**
     * @brief Valeur maximale du paramètre
    */
    long max;
    /**
     * @brief Somme des caractères du nom du paramètre pour une comparaison plus rapide
    */
    int sum;
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
 * Pour chaque paramètre, cette fonction calcule la somme des caractères du nom du
 * paramètre pour une comparaison plus rapide.
 *
 * Références :
 * @ref SETTING_ACQUISITION_DELAY
 * @ref SETTING_NAME_ACQUISITION_DELAY
 * @ref SETTING_DEFAULT_ACQUISITION_DELAY
 * @ref SETTING_ACQUISITION_DELAY_MIN
 * @ref SETTING_ACQUISITION_DELAY_MAX
 * @ref SETTING_FILE_MAX_SIZE
 * @ref SETTING_NAME_FILE_MAX_SIZE
 * @ref SETTING_DEFAULT_FILE_MAX_SIZE
 * @ref SETTING_FILE_MAX_SIZE_MIN
 * @ref SETTING_FILE_MAX_SIZE_MAX
 * @ref SETTING_ACQUISITION_TIMEOUT
 * @ref SETTING_NAME_ACQUISITION_TIMEOUT
 * @ref SETTING_DEFAULT_ACQUISITION_TIMEOUT
 * @ref SETTING_ACQUISITION_TIMEOUT_MIN
 * @ref SETTING_ACQUISITION_TIMEOUT_MAX
 * @ref SETTING_BRIGHTNESS_ENABLED
 * @ref SETTING_NAME_BRIGHTNESS_ENABLED
 * @ref SETTING_DEFAULT_BRIGHTNESS_ENABLED
 * @ref SETTING_BRIGHTNESS_ENABLED_MIN
 * @ref SETTING_BRIGHTNESS_ENABLED_MAX
 * @ref SETTING_BRIGHTNESS_LOW
 * @ref SETTING_NAME_BRIGHTNESS_LOW
 * @ref SETTING_DEFAULT_BRIGHTNESS_LOW
 * @ref SETTING_BRIGHTNESS_LOW_MIN
 * @ref SETTING_BRIGHTNESS_LOW_MAX
 * @ref SETTING_BRIGHTNESS_HIGH
 * @ref SETTING_NAME_BRIGHTNESS_HIGH
 * @ref SETTING_DEFAULT_BRIGHTNESS_HIGH
 * @ref SETTING_BRIGHTNESS_HIGH_MIN
 * @ref SETTING_BRIGHTNESS_HIGH_MAX
 * @ref SETTING_TEMPERATURE_ENABLED
 * @ref SETTING_NAME_TEMPERATURE_ENABLED
 * @ref SETTING_DEFAULT_TEMPERATURE_ENABLED
 * @ref SETTING_TEMPERATURE_ENABLED_MIN
 * @ref SETTING_TEMPERATURE_ENABLED_MAX
 * @ref SETTING_TEMPERATURE_MIN
 * @ref SETTING_NAME_TEMPERATURE_MIN
 * @ref SETTING_DEFAULT_TEMPERATURE_MIN
 * @ref SETTING_TEMPERATURE_MIN_MIN
 * @ref SETTING_TEMPERATURE_MIN_MAX
 * @ref SETTING_TEMPERATURE_MAX
 * @ref SETTING_NAME_TEMPERATURE_MAX
 * @ref SETTING_DEFAULT_TEMPERATURE_MAX
 * @ref SETTING_TEMPERATURE_MAX_MIN
 * @ref SETTING_TEMPERATURE_MAX_MAX
 * @ref SETTING_HUMIDITY_ENABLED
 * @ref SETTING_NAME_HUMIDITY_ENABLED
 * @ref SETTING_DEFAULT_HUMIDITY_ENABLED
 * @ref SETTING_HUMIDITY_ENABLED_MIN
 * @ref SETTING_HUMIDITY_ENABLED_MAX
 * @ref SETTING_HUMIDITY_MIN
 * @ref SETTING_NAME_HUMIDITY_MIN
 * @ref SETTING_DEFAULT_HUMIDITY_MIN
 * @ref SETTING_HUMIDITY_MIN_MIN
 * @ref SETTING_HUMIDITY_MIN_MAX
 * @ref SETTING_HUMIDITY_MAX
 * @ref SETTING_NAME_HUMIDITY_MAX
 * @ref SETTING_DEFAULT_HUMIDITY_MAX
 * @ref SETTING_HUMIDITY_MAX_MIN
 * @ref SETTING_HUMIDITY_MAX_MAX
 * @ref SETTING_PRESSURE_ENABLED
 * @ref SETTING_NAME_PRESSURE_ENABLED
 * @ref SETTING_DEFAULT_PRESSURE_ENABLED
 * @ref SETTING_PRESSURE_ENABLED_MIN
 * @ref SETTING_PRESSURE_ENABLED_MAX
 * @ref SETTING_PRESSURE_MIN
 * @ref SETTING_NAME_PRESSURE_MIN
 * @ref SETTING_DEFAULT_PRESSURE_MIN
 * @ref SETTING_PRESSURE_MIN_MIN
 * @ref SETTING_PRESSURE_MIN_MAX
 * @ref SETTING_PRESSURE_MAX
 * @ref SETTING_NAME_PRESSURE_MAX
 * @ref SETTING_DEFAULT_PRESSURE_MAX
 * @ref SETTING_PRESSURE_MAX_MIN
 * @ref SETTING_PRESSURE_MAX_MAX
 * @ref SETTING_BRIGHTNESS_ECONOMY_ENABLED
 * @ref SETTING_NAME_BRIGHTNESS_ECONOMY_ENABLED
 * @ref SETTING_DEFAULT_BRIGHTNESS_ECONOMY_ENABLED
 * @ref SETTING_BRIGHTNESS_ECONOMY_ENABLED_MIN
 * @ref SETTING_BRIGHTNESS_ECONOMY_ENABLED_MAX
 * @ref SETTING_TEMPERATURE_ECONOMY_ENABLED
 * @ref SETTING_NAME_TEMPERATURE_ECONOMY_ENABLED
 * @ref SETTING_DEFAULT_TEMPERATURE_ECONOMY_ENABLED
 * @ref SETTING_TEMPERATURE_ECONOMY_ENABLED_MIN
 * @ref SETTING_TEMPERATURE_ECONOMY_ENABLED_MAX
 * @ref SETTING_HUMIDITY_ECONOMY_ENABLED
 * @ref SETTING_NAME_HUMIDITY_ECONOMY_ENABLED
 * @ref SETTING_DEFAULT_HUMIDITY_ECONOMY_ENABLED
 * @ref SETTING_HUMIDITY_ECONOMY_ENABLED_MIN
 * @ref SETTING_HUMIDITY_ECONOMY_ENABLED_MAX
 * @ref SETTING_PRESSURE_ECONOMY_ENABLED
 * @ref SETTING_NAME_PRESSURE_ECONOMY_ENABLED
 * @ref SETTING_DEFAULT_PRESSURE_ECONOMY_ENABLED
 * @ref SETTING_PRESSURE_ECONOMY_ENABLED_MIN
 * @ref SETTING_PRESSURE_ECONOMY_ENABLED_MAX
 * @ref NUMBER_OF_SETTINGS
 * @ref MAX_SETTING_LENGTH
 * @ref settings
 * @ref Setting
*/
void initSettings();

#if SETTINGS_IN_EEPROM
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
#endif // SETTINGS_IN_EEPROM

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
 * Références :
 * @ref settings
*/
#define getSetting(id) settings[id].value
/**
 * @brief Sauvegarde la valeur d'un paramètre dans l'EEPROM.
 *
 * Le tableau settings est également mis à jour.
 *
 * Références :
 * @ref EEPROM
 * @ref settings
*/
void setSetting(int id, long value);

#endif // Settings_h
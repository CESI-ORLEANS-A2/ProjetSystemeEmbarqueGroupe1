#ifndef Mode_h
#define Mode_h

#include "main.hpp"

/**
 * @brief Réalise le changement de mode lorsqu'on appuie sur le bouton rouge pendant BUTTON_DELAY.
 *
 * Références : 
 * @ref mode
 * @ref liveMode
 * @ref previousMode
 * @ref stopLiveMode()
 * @ref switchToMode()
 * @ref MAINTENANCE_MODE
 * @ref STANDARD_MODE
 * @ref ECONOMY_MODE
 * @ref CONFIGURATION_MODE
 * Avec L'interpréteur :
 * @ref printLiveMode()
 * @ref printPrompt()
 * @ref printBuffer()
*/
void redButtonPressed();
/**
 * @brief Réalise le changement de mode lorsqu'on appuie sur le bouton vert pendant BUTTON_DELAY.
 *
 * Références : 
 * @ref mode
 * @ref switchToMode()
 * @ref STANDARD_MODE
 * @ref ECONOMY_MODE
 *
 * Avec l'interpréteur :
 * @ref printMode()
 * @ref printBuffer()
*/
void greenButtonPressed();
/**
 * @brief Met fin au mode live.
 *
 * Références : 
 * @ref liveMode
*/
void stopLiveMode();
/**
 * @brief Change le mode actuel.
 * 
 * Les modes sont :
 * - STANDARD_MODE
 * - ECONOMY_MODE
 * - MAINTENANCE_MODE
 * - CONFIGURATION_MODE
 * 
 * Références : 
 * @ref previousMode
 * @ref stopLiveMode()
 * @ref switchToStandardMode()
 * @ref switchToEconomyMode()
 * @ref switchToMaintenanceMode()
 * @ref switchToConfigurationMode()
 * @ref MAINTEANCE_MODE
 * @ref ECONOMY_MODE
 * @ref CONFIGURATION_MODE
 * @ref STANDARD_MODE
 * @ref ERROR_MODE
 * @ref UNKNOWN_MODE
 * Avec l'interpréteur :
 * @ref printMode()
*/
void switchToMode(int newMode);
/**
 * @brief Affiche le mode actuel dans le moniteur série.
 * 
 * Références : 
 * @ref mode
 * @ref CONFIGURATION_MODE
 * @ref MAINTENANCE_MODE
 * @ref CONFIGURATION_MODE
*/
void printMode();

#endif
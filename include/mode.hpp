#ifndef Mode_h
#define Mode_h

#include "main.hpp"

/**
 * @brief Réalise le changement de mode lorsqu'on appuie sur le bouton rouge pendant BUTTON_DELAY.
 *
 * Références : 
 * @ref MAINTENANCE_MODE
 * @ref STANDARD_MODE
 * @ref ECONOMY_MODE
 * @ref CONFIGURATION_MODE
 * @ref mode
 * @ref previousMode
 * @ref switchToMode()
 * 
 * Avec L'interpréteur avancé :
 * @ref liveMode
 * @ref printLiveMode()
 * @ref stopLiveMode()
 * @ref printPrompt()
 * @ref printBuffer()
*/
void redButtonPressed();
/**
 * @brief Réalise le changement de mode lorsqu'on appuie sur le bouton vert pendant BUTTON_DELAY.
 *
 * Références : 
 * @ref STANDARD_MODE
 * @ref ECONOMY_MODE
 * @ref mode
 * @ref switchToMode()
 *
 * Avec l'interpréteur avancé :
 * @ref printMode()
 * @ref printBuffer()
*/
void greenButtonPressed();

#if INTERPRETER
/**
 * @brief Met fin au mode live.
 *
 * Références : 
 * @ref liveMode
*/
void stopLiveMode();
#endif // INTERPRETER

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
 * @ref MAINTEANCE_MODE
 * @ref ECONOMY_MODE
 * @ref CONFIGURATION_MODE
 * @ref STANDARD_MODE
 * @ref ERROR_MODE
 * @ref UNKNOWN_MODE
 * @ref switchToStandardMode()
 * @ref switchToEconomyMode()
 * @ref switchToMaintenanceMode()
 * @ref switchToConfigurationMode()
 * 
 * Avec l'interpréteur avancé :
 * @ref previousMode
 * @ref printMode()
 * @ref stopLiveMode()
*/
void switchToMode(int newMode);
/**
 * @brief Affiche le mode actuel dans le moniteur série.
 * 
 * Références : 
 * @ref CONFIGURATION_MODE
 * @ref MAINTENANCE_MODE
 * @ref CONFIGURATION_MODE
 * @ref mode
*/
void printMode();

#endif // Mode_h
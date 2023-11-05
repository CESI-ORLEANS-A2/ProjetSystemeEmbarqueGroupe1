#include "main.hpp"

/**
 * @brief Passe en mode économique.
 * 
 * Références : 
 * @ref ECONOMY_MODE
 * @ref previousMode
 * @ref mode
 * @ref switchLEDToBlue()
*/
void switchToEconomyMode();
/**
 * @brief Quitte le mode économique.
*/
void quitEconomyMode();
/**
 * @brief Exécute une étape de la boucle principale du mode économique.
 * 
 * Cette fonction est appelée à chaque itération de la boucle principale du programme.
 * Elle permet de gérer le mode économique.
 * 
 * Elle réalise deux actions :
 *  - Réaliser l'acquisition des données.
 *  - Si l'acquisition est terminée, on sauvegarde les données dans un fichier. 
 * 
 * Références :
 * @ref acquisition()
 * @ref saveData()
*/
void runEconomyModeStep();
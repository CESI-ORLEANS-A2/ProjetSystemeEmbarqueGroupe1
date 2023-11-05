#include "main.hpp"
#include "acquisition.hpp"
#include "modes/error.hpp"

/**
 * @brief Passe au mode standard
 * 
 * Références :
 * @ref STANDARD_MODE
 * @ref previousMode
 * @ref mode
 * @ref switchLEDToGreen()
*/
void switchToStandardMode();
/**
 * @brief Quitte le mode standard
*/
void quitStandardMode();
/**
 * @brief Exécute une étape de la boucle principale du mode standard.
 * 
 * Cette fonction est appelée à chaque itération de la boucle principale du programme.
 * Elle permet de gérer le mode standard.
 * 
 * Elle réalise deux actions :
 *  - Réaliser l'acquisition des données.
 *  - Si l'acquisition est terminée, on sauvegarde les données dans un fichier.
*/
void runStandardModeStep();

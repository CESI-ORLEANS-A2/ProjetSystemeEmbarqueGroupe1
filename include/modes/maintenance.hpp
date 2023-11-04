#include "main.hpp"
#include "acquisition.hpp"
#include "peripherals/sd.hpp"
#include "peripherals/serial.hpp"

/**
 * @brief Passe en mode maintenance.
 * 
 * Références :
 * @ref MAINTENANCE_MODE
 * @ref previousMode
 * @ref mode
 * @ref switchLEDToOrange()
 * @ref unmount()
 * @ref printCSVHeader()
*/
void switchToMaintenanceMode();
/**
 * @brief Quitte le mode maintenance.
 * 
 * Références :
 * @ref mount()
*/
void quitMaintenanceMode();
/**
 * @brief Exécute une étape de la boucle principale du mode maintenance.
 * 
 * Cette fonction est appelée à chaque itération de la boucle principale du programme.
 * Elle permet de gérer le mode maintenance.
 * 
 * Elle réalise trois actions :
 *  - Si l'interpréteur avancé est activé, vérifie si le mode live est activé.
 *    Si c'est le cas, on vérifie si des données sont disponibles sur le port série.
 *    Si c'est le cas et que l'utilisateur a entré un retour à la ligne, on quitte le mode live.
 *  - Réaliser l'acquisition des données. 
 *  - Si l'acquisition est terminée, on affiche les données sur le port série.
 *
 * Références :
 * @ref liveMode
 * @ref stopLiveMode()
 * @ref acquisition()
 * @ref printData()
*/
void runMaintenanceModeStep();

/**
 * @brief Affiche un message indiquant que le mode live est activé.
 * 
 * Si besoin, affiche également l'en-tête CSV.
 * 
 * Références :
 * @ref printCSVHeader()
*/
void printLiveMode();
#ifndef ConfigurationMode_h
#define ConfigurationMode_h

#include "main.hpp"

/**
 * @brief Date de la dernière activité de l'utilisateur en millisecondes depuis le démarrage du programme.
 * 
 * Si l'utilisateur n'entre aucune commande pendant un certain temps, le programme quitte le mode de configuration.
 * Par défaut, cette durée est de 30 minutes (
 * @ref CONFIGURATION_MODE_TIMEOUT
 * ).
*/
extern unsigned long lastActivity;

#if !INTERPRETER
/**
 * @brief Variable servant de buffer pour l'entrée de l'utilisateur.
 * 
 * Elle permet de stocker temporairement les caractères entrés par l'utilisateur.
 * 
 * Si l'interpréteur avancé n'est pas activé, cette variable est utilisée à la place de celle
 * définie dans interpreter.hpp (
 * @ref inputBuffer
 * ).
*/
extern char configurationInputBuffer[INPUT_BUFFER_SIZE];
/**
 * @brief Représente la longueur de l'entrée de l'utilisateur.
 * 
 * Si l'interpréteur avancé n'est pas activé, cette variable est utilisée à la place de celle
 * définie dans interpreter.hpp (
 * @ref inputLength
 * ).
*/
extern int configurationInputLength;

/**
 * @brief Traite et exécute une commande entrée par l'utilisateur.
 * 
 * Elle se découpe en plusieurs étapes :
 *  - Calcul de la somme des caractères de la commande (pour des comparaisons plus rapides).
 *  - Switch-Case avec les commandes simples ne nécéssitant pas d'arguments: RESET, VERSION
 *  - Si la commande n'est pas reconnue, on continue.
 *  - Itération dans la liste des paramètres pour vérifié si la commande n'est pas un paramètre 
 *    sans valeur (ex: LOG_INTERVALL au lieu de LOG_INTERVALL=1000). Si c'est le cas, on revoie la 
 *    valeur enrégistrée.
 *  - Si la commande n'est pas reconnue, on continue.
 *  - Séparation de la commande et de la valeur (ex: LOG_INTERVALL=1000 -> LOG_INTERVALL et 1000).
 *  - Recalcul de la somme, mais uniquement sur le nom de paramètre.
 *  - Switch-Case avec les commandes nécéssitant des arguments complexes (nécéssitant un 
 *    prétraitement): CLOCK, DATE, DAY
 *  - Si la commande n'est pas reconnue, on continue.
 *  - Itération dans la liste des paramètres pour vérifié si la commande n'est pas un paramètre. Si
 *    c'est le cas, la valeur est vérifiée et le paramètre est mis à jour.
 *  - Si la commande n'est pas reconnue, on revoie "inconnu". 
 * 
 * @param command La commande à exécuter.
 * 
 * Références : 
 * @ref NUMBER_OF_SETTINGS
 * @ref MONDAY
 * @ref TUESDAY
 * @ref WEDNESDAY
 * @ref THURSDAY
 * @ref FRIDAY
 * @ref SATURDAY
 * @ref SUNDAY
 * @ref settings
 * @ref configurationInputBuffer
 * @ref configurationInputLength
 * @ref resetSettings()
 * @ref printVersion()
 * @ref printInvalidValue()
 * @ref setHour()
 * @ref setMinute()
 * @ref setSecond()
 * @ref setDay()
 * @ref setMonth()
 * @ref setYear()
 * @ref setDayOfWeek()
 * @ref setSetting()
*/
void configurationRunCommand(char* command);

#endif // !INTERPRETER

/**
 * @brief Passe le programme en mode de configuration.
 * 
 * Ce changement ce traduit par le démontage de la carte SD et la mise à jour de la 
 * dernière activité de l'utilisateur.
 * 
 * Références :
 * @ref CONFIGURATION_MODE 
 * @ref previousMode
 * @ref mode
 * @ref lastActivity
 * @ref switchLEDToYellow()
 * @ref unmount()
*/
void switchToConfigurationMode();
/**
 * @brief Quitte le mode de configuration.
 * 
 * Références : 
 * @ref mount()
*/
void quitConfigurationMode();

/**
 * @brief Exécute une étape de la boucle principale du mode de configuration.
 * 
 * Cette fonction est appelée à chaque itération de la boucle principale du programme.
 * Elle permet de gérer le mode de configuration.
 * 
 * Elle réalise une action : 
 *  - Si l'interpréteur avancé n'est pas activé, elle lit les caractères entrés par l'utilisateur
 *    et exécute la commande correspondante.
 * 
 * Références :
 * @ref CONFIGURATION_MODE_TIMEOUT
 * @ref MAINTENANCE_MODE
 * @ref ECONOMY_MODE
 * @ref STANDARD_MODE
 * @ref INPUT_BUFFER_SIZE
 * @ref previousMode
 * @ref lastActivity
 * @ref configurationInputBuffer
 * @ref configurationInputLength
 * @ref switchToMaintenanceMode()
 * @ref switchToEconomyMode()
 * @ref switchToStandardMode()
 * @ref updateLastActivity()
 * @ref configurationRunCommand()
*/
void runConfigurationModeStep();

/**
 * @brief Met à jour la date de la dernière activité de l'utilisateur.
 * 
 * Référence : 
 * @ref lastActivity
*/
#define updateLastActivity() lastActivity = millis()

/**
 * @brief Affiche dans le moniteur série 'Valeur invalide'.
*/
void printInvalidValue();

#endif
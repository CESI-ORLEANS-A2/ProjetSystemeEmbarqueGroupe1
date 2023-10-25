#ifndef Interpreter_h
#define Interpreter_h

#include "consts.hpp"
#include "main.hpp"
#include "settings.hpp"

/**
 * @brief Variable accueillant la commande entrée par l'utilisateur.
*/
extern char inputBuffer[INPUT_BUFFER_SIZE];
/**
 * @brief Taille le ligne de commandé entrée par l'utilisateur.
*/
extern int inputLength;

/**
 * @brief Initialise l'interpréteur de commandes.
 *
 * @ref printMode()
 * @ref printPrompt()
*/
void initInterpreter();
/**
 * @brief Exécute une étape de l'interpréteur de commandes.
 *
 * Cette fonction est appelée à chaque itération de la boucle principale.
 * Elle permet de lire les commandes entrées par l'utilisateur et d'exécuter
 * les commandes en conséquence.
 *
 * @ref liveMode
 * @ref inputBuffer
 * @ref inputLength
 * @ref printPrompt()
 * @ref runCommand()
 * @ref INPUT_BUFFER_SIZE
*/
void runInterpreterStep();

/**
 * @brief Exécute une commande.
 *
 * Cette fonction est appelée par runInterpreterStep() lorsqu'une commande
 * est entrée par l'utilisateur.
 *
 * @ref mode
 * @ref commandHelp()
 * @ref commandList()
 * @ref commandLive()
 * @ref commandMode()
 * @ref commandEnable()
 * @ref commandDisable()
 * @ref commandSet()
 * @ref commandGet()
 * @ref commandReset()
 * @ref commandLast()
 * @ref commandClock()
 * @ref commandDate()
 * @ref commandDay()
 * @ref printUnknownCommand()
 * @ref MAINTENANCE_MODE
*/
void runCommand(char* command);

/**
 * @brief Affiche le prompt de l'interpréteur de commandes.
 *
 * @ref liveMode
*/
void printPrompt();
/**
 * @brief Affiche "Commande : "
*/
void printHelpCommand();
/**
 * @brief Affiche "Mode nécessaire : "
*/
void printHelpNeededMode();
/**
 * @brief Affiche "Description : "
*/
void printHelpDesciption();
/**
 * @brief Affiche "Syntaxe : "
*/
void printHelpSyntax();
/**
 * @brief Affiche "Arguments : "
*/
void printHelpArguments();
/**
 * @brief Affiche "   - "
 *
 * @ref printSpaces()
*/
void printHelpListDash();
/**
 * @brief Affiche "Commandes inconnues.\n\r"
*/
void printUnknownCommand();
/**
 * @brief Affiche la commande que l'utilisateur est en train d'entrer.
 *
 * Cela permet d'afficher à nouveau la commande entrée par l'utilisateur
 * si un message vient à être affiché.
 *
 * @ref inputBuffer()
*/
void printBuffer();
/**
 * @brief Affiche "Ce mode est déja activé.\n\r"
*/
void printModeAlreadyEnabled();
/**
 * @brief Affiche " " n fois.
*/
void printSpaces(int n);
/**
 * @brief Affiche "Le capteur {{capteur}} a été activé."
*/
void printSensorEnabled(int id);
/**
 * @brief Affiche "Le capteur {{capteur}} a été désactivé."
*/
void printSensorDisabled(int id);

/**
 * @brief Affiche "Cette commande n'est pas disponible dans ce mode.\n\r"
*/
void printCommandUnavailableInThisMode();

/**
 * @brief Affiche la liste des commandes disponibles.
 *
 * Si le détail des commandes est activé, affiche également les descriptions
 * et les syntaxes des commandes sur demande.
 *
 * @ref printHelpCommand()
 * @ref printHelpNeededMode()
 * @ref printHelpDesciption()
 * @ref printHelpSyntax()
 * @ref printHelpArguments()
 * @ref printHelpListDash()
 * @ref printSpaces()
 * @ref printUnknownCommand()
*/
void commandHelp(char* command);
/**
 * @brief Affiche la liste des capteurs disponibles.
 *
 * Affiche également l'état de chaque capteur.
 *
 * @ref sensors
 * @ref NUMBER_OF_SENSORS
*/
void commandList();
/**
 * @brief Active ou désactive le mode live.
 *
 * @ref liveMode
*/
void commandLive();
/**
 * @brief Change le mode en cours d'exécution.
 *
 * @ref mode
 * @ref printMode()
 * @ref printModeAlreadyEnabled()
 * @ref switchToMode()
 * @ref CONFIGURATION_MODE
 * @ref MAINTENANCE_MODE
 * @ref STANDARD_MODE
 * @ref ECONOMY_MODE
*/
void commandMode(char* mode);
/**
 * @brief Active un capteur ou tous.
 *
 * @ref sensors
 * @ref setSetting()
 * @ref getSetting()
 * @ref NUMBER_OF_SENSORS
*/
void commandEnable(int id = NULL);
/**
 * @brief Désactive un capteur ou tous.
 *
 * @ref sensors
 * @ref setSetting()
 * @ref getSetting()
 * @ref NUMBER_OF_SENSORS
*/
void commandDisable(int id = NULL);
/**
 * @brief Change la valeur d'un paramètre.
 * 
 * @ref settings
 * @ref setSetting()
 * @ref NUMBER_OF_SETTINGS
*/
void commandSet(char* variable, int value);
/*
 * @brief Affiche la valeur d'un paramètre.

 * @ref settings
 * @ref getSetting()
 * @ref NUMBER_OF_SETTINGS
*/
void commandGet(char* variable);
/**
 * @brief Réinitialise les paramètres de la station météo.
 *
 * @ref resetSettings()
*/
void commandReset();
/**
 * @brief Affiche les dernières données enregistrées.
 * 
 * @ref printData()
*/
void commandLast();
void commandClock(int hours, int minutes, int seconds);
void commandDate(int day, int month, int year);
void commandDay(char* day);

#endif
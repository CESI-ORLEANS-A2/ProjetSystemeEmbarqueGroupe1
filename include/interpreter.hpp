#ifndef Interpreter_h
#define Interpreter_h

#include "consts.hpp"
#include "main.hpp"
#include "settings.hpp"

#if INTERPRETER
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
void runCommand();

/**
 * @brief Affiche le prompt de l'interpréteur de commandes.
 *
 * @ref liveMode
*/
void printPrompt();
/**
 * @brief Affiche la commande que l'utilisateur est en train d'entrer.
 *
 * Cela permet d'afficher à nouveau la commande entrée par l'utilisateur
 * si un message vient à être affiché.
 *
 * @ref inputBuffer()
*/
void printBuffer();

#if COMMAND_HELP
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
#endif // COMMAND_HELP
/**
 * @brief Affiche "Commandes inconnues.\n\r"
*/
void printUnknownCommand();
/**
 * @brief Affiche "Ce mode est déja activé.\n\r"
*/
void printModeAlreadyEnabled();
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
#if INTERPRETER
/**
 * @brief Affiche l'heure enregistrée sous le format "hh:mm:ss".
 *
 * Cette heure peut être modifiée grâce à la commande "clock hh mm ss".
*/
void printClock();
#else // NOT INTERPRETER
/**
 * @brief Affiche l'heure enregistrée sous le format "hh:mm:ss".
 *
 * Cette heure peut être modifiée grâce à la commande "CLOCK=hh:mm:ss".
*/
void printClock();
#endif // INTERPRETER
#if INTERPRETER
/**
 * @brief Affiche la date enregistrée sous le format "jj/mm/aaaa".
 *
 * Cette date peut être modifiée grâce à la commande "date jj mm aaaa".
*/
void printDate();
#else // NOT INTERPRETER
/**
 * @brief Affiche la date enregistrée sous le format "jj/mm/aaaa".
 *
 * Cette date peut être modifiée grâce à la commande "DATE=jj/mm/aaaa".
*/
void printDate();
#endif // INTERPRETER
#if INTERPRETER
/**
 * @brief Affiche le jour de la semaine enregistré.
 *
 * Ce jour peut être modifié grâce à la commande "day [lundi|mardi|mercredi|jeudi|vendredi|samedi|dimanche]".
*/
void printDayOfWeek();
#else // NOT INTERPRETER
/**
 * @brief Affiche le jour de la semaine enregistré.
 *
 * Ce jour peut être modifié grâce à la commande "DAY=[MON|TUE|WED|THU|FRI|SAT|SUN]".
*/
void printDayOfWeek();
#endif // INTERPRETER
#if INTERPRETER
/**
 * @brief Affiche "Jour modifié.".
 *
 * Ce jour peut être modifié grâce à la commande "day [lundi|mardi|mercredi|jeudi|vendredi|samedi|dimanche]".
*/
void printDayModified();
#else // NOT INTERPRETER
/**
 * @brief Affiche "Jour modifié.".
 *
 * Ce jour peut être modifié grâce à la commande "DAY=[MON|TUE|WED|THU|FRI|SAT|SUN]".
*/
void printDayModified();
#endif // INTERPRETER

#if COMMAND_HELP
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
#endif // COMMAND_HELP
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
#if COMMAND_ENABLE
void commandEnable(int id = -1);
/**
 * @brief Désactive un capteur ou tous.
 *
 * @ref sensors
 * @ref setSetting()
 * @ref getSetting()
 * @ref NUMBER_OF_SENSORS
*/
void commandDisable(int id = -1);
/**
 * @brief Change la valeur d'un paramètre.
 *
 * @ref settings
 * @ref setSetting()
 * @ref NUMBER_OF_SETTINGS
*/
#endif // COMMAND_ENABLE
void commandSet(char* variable, int value);
#if COMMAND_GET
/*
 * @brief Affiche la valeur d'un paramètre.

 * @ref settings
 * @ref getSetting()
 * @ref NUMBER_OF_SETTINGS
*/
void commandGet(char* variable);
#endif // COMMAND_GET
/**
 * @brief Réinitialise les paramètres de la station météo.
 *
 * Références :
 * @ref resetSettings()
*/
void commandReset();
#if COMMAND_LAST
/**
 * @brief Affiche les dernières données enregistrées.
 *
 * Références :
 * @ref printData()
*/
void commandLast();
#endif // COMMAND_LAST
/**
 * @brief Afficher ou change l'heure enregistrée.
 *
 * Syntaxe : clock [hh?] [mm?] [ss?]
 * Si au moins un des trois arguments n'est fourni, affiche l'heure enregistrée.
 * Sinon, change l'heure enregistrée.
 *
 * Références :
 * @ref readClock()
 * @ref printClock()
 * @ref setHour()
 * @ref setMinute()
 * @ref setSecond()
*/
void commandClock(int hours, int minutes, int seconds);
/**
 * @brief Afficher ou change la date enregistrée.
 *
 * Syntaxe : date [jj?] [mm?] [aaaa?]
 * Si au moins un des trois arguments n'est fourni, affiche la date enregistrée.
 * Sinon, change la date enregistrée.
 *
 * Références :
 * @ref readClock()
 * @ref printDate()
 * @ref setDay()
 * @ref setMonth()
 * @ref setYear()
*/
void commandDate(int day, int month, int year);
/**
 * @brief Afficher ou change le jour de la semaine enregistré.
 *
 * Syntaxe : day [lundi|mardi|mercredi|jeudi|vendredi|samedi|dimanche]
 * Si aucun argument n'est fourni, affiche le jour de la semaine enregistré.
 * Sinon, change le jour de la semaine enregistré.
 *
 * Références :
 * @ref readClock()
 * @ref printDayOfWeek()
 * @ref setDayOfWeek()
 * @ref printDayModified()
*/
void commandDay(char* day);
#endif // INTERPRETER

#endif // Interpreter_h
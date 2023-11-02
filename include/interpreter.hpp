#ifndef Interpreter_h
#define Interpreter_h

#include "consts.hpp"
#include "main.hpp"
#include "settings.hpp"

enum DayOfWeek {
    NOT_A_DAY,
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY,
    SUNDAY
};

/**
 * @brief Variable accueillant la commande entrée par l'utilisateur.
*/
extern char inputBuffer[INPUT_BUFFER_SIZE];
/**
 * @brief Taille le ligne de commandé entrée par l'utilisateur.
*/
extern int inputLength;
/**
 * @brief Un charactère espace en mémoire Flash.
*/
static const char* spaceChar;

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
#if INTERPRETER
/**
 * @brief Affiche l'heure enregistrée sous le format "hh:mm:ss".
 *
 * Cette heure peut être modifiée grâce à la commande "clock hh mm ss".
*/
void printClock();
#else 
/**
 * @brief Affiche l'heure enregistrée sous le format "hh:mm:ss".
 *
 * Cette heure peut être modifiée grâce à la commande "CLOCK=hh:mm:ss".
*/
void printClock();
#endif
#if INTERPRETER
/**
 * @brief Affiche la date enregistrée sous le format "jj/mm/aaaa".
 *
 * Cette date peut être modifiée grâce à la commande "date jj mm aaaa".
*/
void printDate();
#else
/**
 * @brief Affiche la date enregistrée sous le format "jj/mm/aaaa".
 *
 * Cette date peut être modifiée grâce à la commande "DATE=jj/mm/aaaa".
*/
void printDate();
#endif
#if INTERPRETER
/**
 * @brief Affiche le jour de la semaine enregistré.
 *
 * Ce jour peut être modifié grâce à la commande "day [lundi|mardi|mercredi|jeudi|vendredi|samedi|dimanche]".
*/
void printDayOfWeek();
#else
/**
 * @brief Affiche le jour de la semaine enregistré.
 *
 * Ce jour peut être modifié grâce à la commande "DAY=[MON|TUE|WED|THU|FRI|SAT|SUN]".
*/
void printDayOfWeek();
#endif
#if INTERPRETER
/**
 * @brief Affiche "Jour modifié.".
 *
 * Ce jour peut être modifié grâce à la commande "day [lundi|mardi|mercredi|jeudi|vendredi|samedi|dimanche]".
*/
void printDayModified();
#else
/**
 * @brief Affiche "Jour modifié.".
 *
 * Ce jour peut être modifié grâce à la commande "DAY=[MON|TUE|WED|THU|FRI|SAT|SUN]".
*/
void printDayModified();
#endif

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

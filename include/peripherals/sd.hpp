#ifndef SD_h
#define SD_h

#include <SdFat.h>
#include "consts.hpp"
#include "sensor.hpp"
#include "acquisition.hpp"
#include "main.hpp"

/**
 * @brief Instance de la classe SdFat représentant la carte SD
*/
extern SdFat SD;

/**
 * @brief Numéro de révision, permet de créer plusieurs fichiers par jour
*/
extern unsigned int revisionNumber;
/**
 * @brief Dernier jour de sauvegarde, permet de réinitialiser le numéro de révision si besoin
*/
extern int lastDay;

/**
 * @brief Montage de la carte SD
 * 
 * En cas d'erreur, on passe en mode erreur.
 * 
 * Références : 
 * @ref SD_PIN
 * @ref ERROR_SD_ACCESS
 * @ref switchToErrorMode()
*/
void mount();
/**
 * @brief Démontage de la carte SD
*/
void unmount();
/**
 * @brief Génération du nom de fichier
 * 
 * Le nom est au format : AAMMJJ_NNN.LOG (AAMMJJ : date, NNN : numéro de révision)
 * 
 * @param fileName Buffer contenant le nom de fichier
 * 
 * Références :
 * @ref MAX_NAME_LENGTH
 * @ref revisionNumber
 * @ref getYear()
 * @ref getMonth()
 * @ref getDay()
*/
void getFileName(char* fileName);
/**
 * @brief Sauvegarde des données sur la carte SD
 * 
 * Si la carte SD est pleine, on passe en mode erreur.
 * 
 * Références :
 * @ref SETTING_FILE_MAX_SIZE
 * @ref ERROR_SD_ACCESS
 * @ref revisionNumber
 * @ref lastDay
 * @ref getFileName()
 * @ref getSetting()
 * @ref printHeaderLine()
 * @ref printLine()
 * @ref switchToErrorMode()
 * @ref getDay()
*/
void saveData();
/**
 * @brief Affichage d'une ligne de données sur le port série ou dans un fichier de la carte SD
 *
 * Les instances Serial et SD étendent la classe Stream, on peut donc utiliser la même fonction pour les deux.
 * Cette classe Stream fournit les méthodes print() et println() qui permettent d'afficher des données de différents types.
 * 
 * @param s Port série ou fichier de la carte SD 
 * 
 * Références :
 * @ref NUMBER_OF_SENSORS
 * @ref lastNorth
 * @ref lastWest
 * @ref sensors
 * @ref lastMeasurements
 * @ref getDay()
 * @ref getMonth()
 * @ref getYear()
 * @ref getHour()
 * @ref getMinute()
 * @ref getSecond()
*/
void printLine(Stream &s);

#if LIVE_MODE_SERIAL_OUTPUT==OUTPUT_CSV

/**
 * @brief Affichage de l'en-tête CSV sur le port série ou dans un fichier de la carte SD
 * 
 * Les instances Serial et SD étendent la classe Stream, on peut donc utiliser la même fonction pour les deux.
 * Cette classe Stream fournit les méthodes print() et println() qui permettent d'afficher des données de différents types.
 * 
 * @param s Port série ou fichier de la carte SD
 * 
 * Références :
 * @ref NUMBER_OF_SENSORS
 * @ref MAX_NAME_LENGTH
 * @ref sensors
*/
void printHeaderLine(Stream &s);

/**
 * @brief Ajout de l'en-tête CSV à une ligne de données
*/
#define printCSVHeader() printHeaderLine(Serial)

#endif // LIVE_MODE_SERIAL_OUTPUT==OUTPUT_CSV

#endif // SD_h
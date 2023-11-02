#ifndef SD_h
#define SD_h

#include <SdFat.h>
#include <string.h>
#include "consts.hpp"
#include "sensor.hpp"
#include "acquisition.hpp"
#include "main.hpp"

extern SdFat SD;

/**
 * @brief Montage de la carte SD
*/
void mount();
/**
 * @brief Démontage de la carte SD
*/
void unmount();
/**
 * @brief Sauvegarde des données sur la carte SD
*/
void saveData();
/**
 * @brief Formatage d'une ligne de données
 *
 * @param line Ligne de données
*/
void formatLine(char* line);

#if LIVE_MODE_SERIAL_OUTPUT==OUTPUT_CSV
/**
 * @brief Ajout de l'en-tête CSV à une ligne de données
*/
void CSVHeader(char* line);
#endif

#endif
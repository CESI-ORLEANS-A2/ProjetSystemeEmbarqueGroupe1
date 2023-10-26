#ifndef SD_h
#define SD_h

#include <SD.h>
#include <string.h>
#include "consts.hpp"
#include "sensor.hpp"
#include "main.hpp"

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

#endif
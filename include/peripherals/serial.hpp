#ifndef Serial_h
#define Serial_h

#include <Arduino.h>
#include <ArduinoUniqueID.h>
#include "main.hpp"
#include "interpreter.hpp"

/**
 * @brief Initialise le port série et affiche la version du logiciel.
 * 
 * Références : 
 * @ref SERIAL_BAUD_RATE
 * @ref printVersion()
*/
void initSerial();
/**
 * @brief Affiche les données sur le port série.
 * 
 * Références :
 * @ref printLine()
*/
#define printData() printLine(Serial)
/**
 * @brief Affiche la version du logiciel sur le port série.
 * 
 * La version de la carte est récupérable grâce à une librairie : ArduinoUniqueID.
 * 
 * Références :
 * @ref VERSION
*/
void printVersion();

#endif // Serial_h
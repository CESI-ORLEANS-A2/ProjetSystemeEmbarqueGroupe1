#ifndef Serial_h
#define Serial_h

#include <Arduino.h>
#include <ArduinoUniqueID.h>
#include "main.hpp"
#include "interpreter.hpp"

/**
 * @brief Initialise le port série.
 * 
 * Références : 
 * @ref SERIAL_BAUD_RATE
*/
void initSerial();
/**
 * @brief Affiche les données sur le port série.
 * 
 * Références :
 * @ref formatLine()
 * @ref MAX_LINE_SIZE
*/
void printData();
/**
 * @brief Affiche la version du logiciel sur le port série.
*/
void printVersion();

#endif
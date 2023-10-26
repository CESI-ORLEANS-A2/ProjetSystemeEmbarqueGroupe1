#ifndef Serial_h
#define Serial_h

#include <Arduino.h>
#include "main.hpp"

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

#endif
#include "consts.hpp"
#include "peripherals/serial.hpp"
#include "peripherals/led.hpp"

/**
 * @brief Mode en cours
*/
extern int currentError;

/**
 * @brief Passe en mode erreur
*/
void switchToErrorMode(int error);
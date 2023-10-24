#ifndef Main_h
#define Main_h

#include <Arduino.h>

#include "consts.hpp"

#include "includes/timer.hpp"
#include "includes/mode.hpp"
#include "includes/sensor.hpp"
#include "includes/settings.hpp"
#include "includes/peripherals/sd.hpp"
#include "includes/peripherals/buttons.hpp"
#if INTERPRETER
#include "includes/interpreter.hpp"
#endif
#include "includes/peripherals/led.hpp"
#include "includes/peripherals/sd.hpp"
#include "includes/peripherals/clock.hpp"
#include "includes/peripherals/gps.hpp"

#include "includes/modes/standard.hpp"
#include "includes/modes/economy.hpp"
#include "includes/modes/configuration.hpp"
#include "includes/modes/maintenance.hpp"

#include "includes/peripherals/sensors/temperature.hpp"
#include "includes/peripherals/sensors/humidity.hpp"
#include "includes/peripherals/sensors/pressure.hpp"
#include "includes/peripherals/sensors/brightness.hpp"

void restart();

/*!
 * @brief Mode en cours 
 *
 * Cette variable contient le mode en cours d'exécution.
 * Les modes disponibles sont (voir consts.hpp):
 * - STANDARD_MODE
 * - ECONOMY_MODE
 * - CONFIGURATION_MODE
 * - MAINTENANCE_MODE
 */
extern int mode;
/*!
 * @brief Dernier mode; pour revenir au mode précédent
 *
 * Cette variable contient le mode en cours d'exécution.
 * Les modes disponibles sont (voir consts.hpp):
 * - STANDARD_MODE
 * - ECONOMY_MODE
 * - CONFIGURATION_MODE
 * - MAINTENANCE_MODE
 */
extern int previousMode;
/*!
 * @brief Contient une représentation (class) de chaque capteur
 */
extern Sensor* sensors[NUMBER_OF_SENSORS];
/*!
 * @brief Si le port série est utilisé pour afficher les données en temps réel
 */
extern bool liveMode;
/*!
 * @brief 
 */
extern float lastMeasurements[NUMBER_OF_SENSORS];

#endif
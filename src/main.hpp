#ifndef Main_h
#define Main_h

#include <Arduino.h>

#include "consts.hpp"

#include "includes/timer.hpp"
#include "includes/mode.hpp"
#include "includes/sensor.hpp"
#include "includes/acquisition.hpp"
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

// Mode en cours
extern int mode;
// Dernier mode; pour revenir au mode précédent
extern int previousMode;
// Contient une représentation (structure) de chaque capteur
extern Sensor* sensors[NUMBER_OF_SENSORS];
// Si le port série est utilisé pour afficher les données en temps réel
extern bool liveMode;

#endif
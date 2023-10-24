#ifndef Settings_h
#define Settings_h

#include "consts.hpp"
#include <EEPROM.h>

extern int settings[NUMBER_OF_SETTINGS];

void updateSettingsFromEEPROM();
void resetSettings();
int getSetting(int id);
void saveSetting(int id, int value);

#endif
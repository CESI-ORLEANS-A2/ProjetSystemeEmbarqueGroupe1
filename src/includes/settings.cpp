#include "includes/settings.hpp"

int settings[NUMBER_OF_SETTINGS];

void updateSettingsFromEEPROM() {
    int value;
    for (int i = 0; i < NUMBER_OF_SETTINGS; i++) {
        value = EEPROM[i];
        if (!value) settings[i] = DEFAULT_SETTINGS[i];
        else settings[i] = value;
    }
}
void resetSettings() {
    int value;
    for (int i = 0; i < NUMBER_OF_SETTINGS; i++) {
        value = DEFAULT_SETTINGS[i];
        EEPROM[i] = value;
        settings[i] = value;
    }
}
int getSetting(int id) {
    return settings[id];
}
void saveSetting(int id, int value) {
    EEPROM[id] = value;
}
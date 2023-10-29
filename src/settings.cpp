#include "settings.hpp"

Setting settings[NUMBER_OF_SETTINGS] = {};

void initSettings() {
    settings[SETTING_ACQUISITION_DELAY] = {
        SETTING_NAME_ACQUISITION_DELAY,
        SETTING_DEFAULT_ACQUISITION_DELAY,
        SETTING_DEFAULT_ACQUISITION_DELAY
    };
    settings[SETTING_FILE_MAX_SIZE] = {
        SETTING_NAME_FILE_MAX_SIZE,
        SETTING_DEFAULT_FILE_MAX_SIZE,
        SETTING_DEFAULT_FILE_MAX_SIZE
    };
    settings[SETTING_ACQUISITION_TIMEOUT] = {
        SETTING_NAME_ACQUISITION_TIMEOUT,
        SETTING_DEFAULT_ACQUISITION_TIMEOUT,
        SETTING_DEFAULT_ACQUISITION_TIMEOUT
    };
    settings[SETTING_BRIGHTNESS_ENABLED] = {
        SETTING_NAME_BRIGHTNESS_ENABLED,
        SETTING_DEFAULT_BRIGHTNESS_ENABLED,
        SETTING_DEFAULT_BRIGHTNESS_ENABLED
    };
    settings[SETTING_BRIGHTNESS_LOW] = {
        SETTING_NAME_BRIGHTNESS_LOW,
        SETTING_DEFAULT_BRIGHTNESS_LOW,
        SETTING_DEFAULT_BRIGHTNESS_LOW
    };
    settings[SETTING_BRIGHTNESS_HIGH] = {
        SETTING_NAME_BRIGHTNESS_HIGH,
        SETTING_DEFAULT_BRIGHTNESS_HIGH,
        SETTING_DEFAULT_BRIGHTNESS_HIGH
    };
    settings[SETTING_TEMPERATURE_ENABLED] = {
        SETTING_NAME_TEMPERATURE_ENABLED,
        SETTING_DEFAULT_TEMPERATURE_ENABLED,
        SETTING_DEFAULT_TEMPERATURE_ENABLED
    };
    settings[SETTING_TEMPERATURE_MIN] = {
        SETTING_NAME_TEMPERATURE_MIN,
        SETTING_DEFAULT_TEMPERATURE_MIN,
        SETTING_DEFAULT_TEMPERATURE_MIN
    };
    settings[SETTING_TEMPERATURE_MAX] = {
        SETTING_NAME_TEMPERATURE_MAX,
        SETTING_DEFAULT_TEMPERATURE_MAX,
        SETTING_DEFAULT_TEMPERATURE_MAX
    };
    settings[SETTING_HUMIDITY_ENABLED] = {
        SETTING_NAME_HUMIDITY_ENABLED,
        SETTING_DEFAULT_HUMIDITY_ENABLED,
        SETTING_DEFAULT_HUMIDITY_ENABLED
    };
    settings[SETTING_HUMIDITY_MIN] = {
        SETTING_NAME_HUMIDITY_MIN,
        SETTING_DEFAULT_HUMIDITY_MIN,
        SETTING_DEFAULT_HUMIDITY_MIN
    };
    settings[SETTING_HUMIDITY_MAX] = {
        SETTING_NAME_HUMIDITY_MAX,
        SETTING_DEFAULT_HUMIDITY_MAX,
        SETTING_DEFAULT_HUMIDITY_MAX
    };
    settings[SETTING_PRESSURE_ENABLED] = {
        SETTING_NAME_PRESSURE_ENABLED,
        SETTING_DEFAULT_PRESSURE_ENABLED,
        SETTING_DEFAULT_PRESSURE_ENABLED
    };
    settings[SETTING_PRESSURE_MIN] = {
        SETTING_NAME_PRESSURE_MIN,
        SETTING_DEFAULT_PRESSURE_MIN,
        SETTING_DEFAULT_PRESSURE_MIN
    };
    settings[SETTING_PRESSURE_MAX] = {
        SETTING_NAME_PRESSURE_MAX,
        SETTING_DEFAULT_PRESSURE_MAX,
        SETTING_DEFAULT_PRESSURE_MAX
    };
}
    #if SETTINGS_IN_EEPROM
void updateSettingsFromEEPROM() {
    int value;
    for (int i = 0; i < NUMBER_OF_SETTINGS; i++) {
        EEPROM.get(i, value);
        if (!value) {
            EEPROM.put(i, settings[i].defaultValue);
            settings[i].value = settings[i].defaultValue;
        }
        else settings[i].value = value;
    }
}
#endif
void resetSettings() {
    for (int i = 0; i < NUMBER_OF_SETTINGS; i++) {
#if SETTINGS_IN_EEPROM
        EEPROM.put(i, settings[i].defaultValue);
#endif
        settings[i].value = settings[i].defaultValue;
    }
}
long getSetting(int id) {
    return settings[id].value;
}
void setSetting(int id, long value) {
#if SETTINGS_IN_EEPROM
    EEPROM.put(id, value);
#endif
    settings[id].value = value;
}
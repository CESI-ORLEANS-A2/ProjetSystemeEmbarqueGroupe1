#include "settings.hpp"

Setting settings[NUMBER_OF_SETTINGS];

void initSettings() {
    Setting settings[NUMBER_OF_SETTINGS] = {
        {
            .name = SETTING_NAME_ACQUISITION_DELAY,
            .defaultValue = SETTING_DEFAULT_ACQUISITION_DELAY,
            .value = SETTING_DEFAULT_ACQUISITION_DELAY,
            .min = SETTING_ACQUISITION_DELAY_MIN,
            .max = SETTING_ACQUISITION_DELAY_MAX
        },
        {
            .name = SETTING_NAME_FILE_MAX_SIZE,
            .defaultValue = SETTING_DEFAULT_FILE_MAX_SIZE,
            .value = SETTING_DEFAULT_FILE_MAX_SIZE,
            .min = SETTING_FILE_MAX_SIZE_MIN,
            .max = SETTING_FILE_MAX_SIZE_MAX},
        {
            .name = SETTING_NAME_ACQUISITION_TIMEOUT,
            .defaultValue = SETTING_DEFAULT_ACQUISITION_TIMEOUT,
            .value = SETTING_DEFAULT_ACQUISITION_TIMEOUT,
            .min = SETTING_ACQUISITION_TIMEOUT_MIN,
            .max = SETTING_ACQUISITION_TIMEOUT_MAX
        },
        {
            .name = SETTING_NAME_BRIGHTNESS_ENABLED,
            .defaultValue = SETTING_DEFAULT_BRIGHTNESS_ENABLED,
            .value = SETTING_DEFAULT_BRIGHTNESS_ENABLED,
            .min = SETTING_BRIGHTNESS_ENABLED_MIN,
            .max = SETTING_BRIGHTNESS_ENABLED_MAX
        },
        {
            .name = SETTING_NAME_BRIGHTNESS_LOW,
            .defaultValue = SETTING_DEFAULT_BRIGHTNESS_LOW,
            .value = SETTING_DEFAULT_BRIGHTNESS_LOW,
            .min = SETTING_BRIGHTNESS_LOW_MIN,
            .max = SETTING_BRIGHTNESS_LOW_MAX
        },
        {
            .name = SETTING_NAME_BRIGHTNESS_HIGH,
            .defaultValue = SETTING_DEFAULT_BRIGHTNESS_HIGH,
            .value = SETTING_DEFAULT_BRIGHTNESS_HIGH,
            .min = SETTING_BRIGHTNESS_HIGH_MIN,
            .max = SETTING_BRIGHTNESS_HIGH_MAX
        },
        {
            .name = SETTING_NAME_TEMPERATURE_ENABLED,
            .defaultValue = SETTING_DEFAULT_TEMPERATURE_ENABLED,
            .value = SETTING_DEFAULT_TEMPERATURE_ENABLED,
            .min = SETTING_TEMPERATURE_ENABLED_MIN,
            .max = SETTING_TEMPERATURE_ENABLED_MAX
        },
        {
            .name = SETTING_NAME_TEMPERATURE_MIN,
            .defaultValue = SETTING_DEFAULT_TEMPERATURE_MIN,
            .value = SETTING_DEFAULT_TEMPERATURE_MIN,
            .min = SETTING_TEMPERATURE_MIN_MIN,
            .max = SETTING_TEMPERATURE_MIN_MAX
        },
        {
            .name = SETTING_NAME_TEMPERATURE_MAX,
            .defaultValue = SETTING_DEFAULT_TEMPERATURE_MAX,
            .value = SETTING_DEFAULT_TEMPERATURE_MAX,
            .min = SETTING_TEMPERATURE_MAX_MIN,
            .max = SETTING_TEMPERATURE_MAX_MAX
        },
        {
            .name = SETTING_NAME_HUMIDITY_ENABLED,
            .defaultValue = SETTING_DEFAULT_HUMIDITY_ENABLED,
            .value = SETTING_DEFAULT_HUMIDITY_ENABLED,
            .min = SETTING_HUMIDITY_ENABLED_MIN,
            .max = SETTING_HUMIDITY_ENABLED_MAX
        },
        {
            .name = SETTING_NAME_HUMIDITY_MIN,
            .defaultValue = SETTING_DEFAULT_HUMIDITY_MIN,
            .value = SETTING_DEFAULT_HUMIDITY_MIN,
            .min = SETTING_HUMIDITY_MIN_MIN,
            .max = SETTING_HUMIDITY_MIN_MAX
        },
        {
            .name = SETTING_NAME_HUMIDITY_MAX,
            .defaultValue = SETTING_DEFAULT_HUMIDITY_MAX,
            .value = SETTING_DEFAULT_HUMIDITY_MAX,
            .min = SETTING_HUMIDITY_MAX_MIN,
            .max = SETTING_HUMIDITY_MAX_MAX
        },
        {
            .name = SETTING_NAME_PRESSURE_ENABLED,
            .defaultValue = SETTING_DEFAULT_PRESSURE_ENABLED,
            .value = SETTING_DEFAULT_PRESSURE_ENABLED,
            .min = SETTING_PRESSURE_ENABLED_MIN,
            .max = SETTING_PRESSURE_ENABLED_MAX
        },
        {
            .name = SETTING_NAME_PRESSURE_MIN,
            .defaultValue = SETTING_DEFAULT_PRESSURE_MIN,
            .value = SETTING_DEFAULT_PRESSURE_MIN,
            .min = SETTING_PRESSURE_MIN_MIN,
            .max = SETTING_PRESSURE_MIN_MAX
        },
        {
            .name = SETTING_NAME_PRESSURE_MAX,
            .defaultValue = SETTING_DEFAULT_PRESSURE_MAX,
            .value = SETTING_DEFAULT_PRESSURE_MAX,
            .min = SETTING_PRESSURE_MAX_MIN,
            .max = SETTING_PRESSURE_MAX_MAX
        }
#if INTERPRETER
        ,{
            .name = SETTING_NAME_BRIGHTNESS_ECONOMY_ENABLED,
            .defaultValue = SETTING_DEFAULT_BRIGHTNESS_ECONOMY_ENABLED,
            .value = SETTING_DEFAULT_BRIGHTNESS_ECONOMY_ENABLED,
            .min = SETTING_BRIGHTNESS_ECONOMY_ENABLED_MIN,
            .max = SETTING_BRIGHTNESS_ECONOMY_ENABLED_MAX
        },
        {
            .name = SETTING_NAME_TEMPERATURE_ECONOMY_ENABLED,
            .defaultValue = SETTING_DEFAULT_TEMPERATURE_ECONOMY_ENABLED,
            .value = SETTING_DEFAULT_TEMPERATURE_ECONOMY_ENABLED,
            .min = SETTING_TEMPERATURE_ECONOMY_ENABLED_MIN,
            .max = SETTING_TEMPERATURE_ECONOMY_ENABLED_MAX
        },
        {
            .name = SETTING_NAME_HUMIDITY_ECONOMY_ENABLED,
            .defaultValue = SETTING_DEFAULT_HUMIDITY_ECONOMY_ENABLED,
            .value = SETTING_DEFAULT_HUMIDITY_ECONOMY_ENABLED,
            .min = SETTING_HUMIDITY_ECONOMY_ENABLED_MIN,
            .max = SETTING_HUMIDITY_ECONOMY_ENABLED_MAX
        },
        {
            .name = SETTING_NAME_PRESSURE_ECONOMY_ENABLED,
            .defaultValue = SETTING_DEFAULT_PRESSURE_ECONOMY_ENABLED,
            .value = SETTING_DEFAULT_PRESSURE_ECONOMY_ENABLED,
            .min = SETTING_PRESSURE_ECONOMY_ENABLED_MIN,
            .max = SETTING_PRESSURE_ECONOMY_ENABLED_MAX
        }
#endif
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

void setSetting(int id, long value) {
#if SETTINGS_IN_EEPROM
    EEPROM.put(id, value);
#endif
    settings[id].value = value;
}
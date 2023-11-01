#include "peripherals/sensors/temperature.hpp"

void initTemperatureSensor() {
    initBME();
    sensors[TEMPERATURE_SENSOR] = {
        .name = TEMPERATURE_SENSOR_NAME,
        .enabled = SETTING_TEMPERATURE_ENABLED,
#if INTERPRETER
        .economy = SETTING_TEMPERATURE_ECONOMY_ENABLED,
#endif
        .measure = &measureTemperature
    };
}

float measureTemperature() {
    const float temperature = readTemperature();
    if (temperature < getSetting(SETTING_TEMPERATURE_MIN) || temperature > getSetting(SETTING_TEMPERATURE_MAX))
        return ACQUISITION_ERROR_VALUE;
    return temperature;
}
#include "peripherals/sensors/temperature.hpp"

extern int mode;
extern int previousMode;
extern Sensor* sensors[NUMBER_OF_SENSORS];

void initTemperatureSensor() {
    initBME();
    sensors[TEMPERATURE_SENSOR] = new Sensor(
        TEMPERATURE_SENSOR_NAME,
        TEMPERATURE_SENSOR_PROTOCOL,
        TEMPERATURE_SENSOR_DEVICE,
        SETTING_TEMPERATURE_ENABLED,
        TEMPERATURE_SENSOR_ECONOMY,
        NULL,
        &measureTemperature
    );
}

float measureTemperature() {
    const float temperature = readTemperature();
    if (temperature < getSetting(SETTING_TEMPERATURE_MIN) || temperature > getSetting(SETTING_TEMPERATURE_MAX))
        return NULL;
    return temperature;
}
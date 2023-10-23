#include "includes/peripherals/sensors/temperature.hpp"

extern int mode;
extern int previousMode;
extern Sensor* sensors[NUMBER_OF_SENSORS];

void initTemperatureSensor() {
    initBME();
    sensors[TEMPERATURE_SENSOR] = new Sensor(
        TEMPERATURE_SENSOR_NAME,
        TEMPERATURE_SENSOR_PROTOCOL,
        TEMPERATURE_SENSOR_DEVICE,
        TEMPERATURE_SENSOR_ENABLED,
        TEMPERATURE_SENSOR_ECONOMY,
        NULL,
        &measureTemperature
    );
}

long measureTemperature() {
    return readTemperature();
}
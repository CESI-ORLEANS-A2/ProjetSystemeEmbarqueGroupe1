#include "peripherals/sensors/pressure.hpp"

extern int mode;
extern int previousMode;
extern Sensor* sensors[NUMBER_OF_SENSORS];

void initPressureSensor() {
    initBME();
    sensors[PRESSURE_SENSOR] = new Sensor(
        PRESSURE_SENSOR_NAME,
        PRESSURE_SENSOR_PROTOCOL,
        PRESSURE_SENSOR_DEVICE,
        PRESSURE_SENSOR_ENABLED,
        PRESSURE_SENSOR_ECONOMY,
        NULL,
        &measurePressure
    );
}

long measurePressure() {
    return readPressure();
}
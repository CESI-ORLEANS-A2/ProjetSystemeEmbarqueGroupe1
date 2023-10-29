#include "peripherals/sensors/pressure.hpp"

void initPressureSensor() {
    initBME();
    sensors[PRESSURE_SENSOR] = new Sensor(
        PRESSURE_SENSOR_NAME,
        PRESSURE_SENSOR_DEVICE,
        SETTING_PRESSURE_ENABLED,
        SETTING_PRESSURE_ECONOMY_ENABLED,
        NULL,
        &measurePressure
    );
}

float measurePressure() {
    const float pressure = readPressure();
    if (pressure < getSetting(SETTING_PRESSURE_MIN) || pressure > getSetting(SETTING_PRESSURE_MAX))
        return ACQUISITION_ERROR_VALUE;
    return pressure;
}
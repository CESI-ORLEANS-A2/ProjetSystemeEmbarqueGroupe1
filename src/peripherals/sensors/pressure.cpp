#include "peripherals/sensors/pressure.hpp"

void initPressureSensor() {
    initBME();
    sensors[PRESSURE_SENSOR] = {
        .name = PRESSURE_SENSOR_NAME,
        .enabled = SETTING_PRESSURE_ENABLED,
#if INTERPRETER
        .economy = SETTING_PRESSURE_ECONOMY_ENABLED,
#endif
        .measure = &measurePressure
    };
}

float measurePressure() {
    const float pressure = readPressure() / 100; // conversion de Pa en hPa
    Serial.println(pressure);
    // Serial.print("min="); Serial.print(getSetting(SETTING_PRESSURE_MIN)); Serial.print(" max="); Serial.println(getSetting(SETTING_PRESSURE_MAX));
    if (pressure < getSetting(SETTING_PRESSURE_MIN) || pressure > getSetting(SETTING_PRESSURE_MAX))
        return ACQUISITION_ERROR_VALUE;
    return pressure;
}
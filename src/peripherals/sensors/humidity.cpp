#include "peripherals/sensors/humidity.hpp"

void initHumiditySensor() {
    initBME();
    sensors[HUMIDITY_SENSOR] = {
        .name = HUMIDITY_SENSOR_NAME,
        .enabled = SETTING_HUMIDITY_ENABLED,
#if INTERPRETER
        .economy = SETTING_HUMIDITY_ECONOMY_ENABLED,
#endif
        .measure = &measureHumidity
    };
}

float measureHumidity() {
    const float humidity = readHumidity();
    // Serial.println(humidity);
    // Serial.print("min="); Serial.print(getSetting(SETTING_HUMIDITY_MIN)); Serial.print(" max="); Serial.println(getSetting(SETTING_HUMIDITY_MAX));
    if (lastMeasurements[TEMPERATURE_SENSOR] < getSetting(SETTING_HUMIDITY_MIN) || lastMeasurements[TEMPERATURE_SENSOR] > getSetting(SETTING_HUMIDITY_MAX))
        return ACQUISITION_ERROR_VALUE;
    return humidity;
}
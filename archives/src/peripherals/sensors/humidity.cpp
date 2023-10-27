#include "peripherals/sensors/humidity.hpp"

extern int mode;
extern int previousMode;
extern Sensor* sensors[NUMBER_OF_SENSORS];

void initHumiditySensor() {
    initBME();
    sensors[HUMIDITY_SENSOR] = new Sensor(
        HUMIDITY_SENSOR_NAME,
        HUMIDITY_SENSOR_DEVICE,
        SETTING_HUMIDITY_ENABLED,
        SETTING_HUMIDITY_ECONOMY_ENABLED,
        NULL,
        &measureHumidity
    );
}

float measureHumidity() {
    const float humidity = readHumidity();
    if (lastMeasurements[TEMPERATURE_SENSOR] < getSetting(SETTING_HUMIDITY_MIN) || lastMeasurements[TEMPERATURE_SENSOR] > getSetting(SETTING_HUMIDITY_MAX))
        return ACQUISITION_ERROR_VALUE;
    return humidity;
}
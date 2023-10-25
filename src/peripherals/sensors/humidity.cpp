#include "peripherals/sensors/humidity.hpp"

extern int mode;
extern int previousMode;
extern Sensor* sensors[NUMBER_OF_SENSORS];

void initHumiditySensor() {
    initBME();
    sensors[HUMIDITY_SENSOR] = new Sensor(
        HUMIDITY_SENSOR_NAME,
        HUMIDITY_SENSOR_PROTOCOL,
        HUMIDITY_SENSOR_DEVICE,
        SETTING_HUMIDITY_ENABLED,
        HUMIDITY_SENSOR_ECONOMY,
        NULL,
        &measureHumidity
    );
}

float measureHumidity() {
    const float humidity = readHumidity();
    if (humidity < getSetting(SETTING_HUMIDITY_MIN) || humidity > getSetting(SETTING_HUMIDITY_MAX))
        return NULL;
    return humidity;
}
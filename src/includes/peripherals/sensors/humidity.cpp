#include "includes/peripherals/sensors/humidity.hpp"

extern int mode;
extern int previousMode;
extern Sensor* sensors[NUMBER_OF_SENSORS];

void initHumiditySensor() {
    initBME();
    sensors[HUMIDITY_SENSOR] = new Sensor(
        HUMIDITY_SENSOR_NAME,
        HUMIDITY_SENSOR_PROTOCOL,
        HUMIDITY_SENSOR_DEVICE,
        HUMIDITY_SENSOR_ENABLED,
        HUMIDITY_SENSOR_ECONOMY,
        NULL,
        &measureHumidity
    );
}

long measureHumidity() {
    return readHumidity();
}
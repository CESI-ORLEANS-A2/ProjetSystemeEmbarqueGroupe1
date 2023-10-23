#include "includes/peripherals/sensors/brightness.hpp"

extern int mode;
extern int previousMode;
extern Sensor* sensors[NUMBER_OF_SENSORS];

void initBrightnessSensor() {
    sensors[BRIGHTNESS_SENSOR] = new Sensor(
        BRIGHTNESS_SENSOR_NAME,
        BRIGHTNESS_SENSOR_PROTOCOL,
        BRIGHTNESS_SENSOR_DEVICE,
        BRIGHTNESS_SENSOR_ENABLED,
        BRIGHTNESS_SENSOR_ECONOMY,
        &initBrightness,
        NULL
    );
}

// void measureBrightness() {
// }

void initBrightness() {
    
}
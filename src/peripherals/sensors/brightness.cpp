#include "peripherals/sensors/brightness.hpp"

void initBrightnessSensor() {
    sensors[BRIGHTNESS_SENSOR] = new Sensor(
        BRIGHTNESS_SENSOR_NAME,
        BRIGHTNESS_SENSOR_DEVICE,
        SETTING_BRIGHTNESS_ENABLED,
        SETTING_BRIGHTNESS_ECONOMY_ENABLED,
        &initBrightness,
        NULL
    );
}

// void measureBrightness() {
// }

void initBrightness() {
    
}

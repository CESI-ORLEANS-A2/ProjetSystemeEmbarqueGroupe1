#include "peripherals/sensors/brightness.hpp"

void initBrightnessSensor() {
    sensors[BRIGHTNESS_SENSOR] = {
        .name = BRIGHTNESS_SENSOR_NAME,
        .enabled = SETTING_BRIGHTNESS_ENABLED,
#if INTERPRETER
        .economy = SETTING_BRIGHTNESS_ECONOMY_ENABLED,
#endif
        .measure = &measureBrightness
    };
}

float measureBrightness() {
    const int brightness = analogRead(BRIGHTNESS_SENSOR_DEVICE);
    // Serial.println(brightness);
    // Serial.print("min="); Serial.print(getSetting(SETTING_BRIGHTNESS_LOW)); Serial.print(" max="); Serial.println(getSetting(SETTING_BRIGHTNESS_HIGH));
    if (brightness < getSetting(SETTING_BRIGHTNESS_LOW) || brightness > getSetting(SETTING_BRIGHTNESS_HIGH))
        return ACQUISITION_ERROR_VALUE;
    return brightness;
}

#include "includes/peripherals/libs/bme.hpp"

Adafruit_BME280 bme;

bool isInit = false;

void initBME() {
    if (isInit) return;

    // Wire.begin();
    bme.begin();
}

float readTemperature() {
    return bme.readTemperature();
}
float readHumidity() {
    return bme.readHumidity();
}
float readPressure() {
    return bme.readPressure();
}

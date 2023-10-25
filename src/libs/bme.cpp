#include "libs/bme.hpp"

BME280 bme;

bool isInit = false;

void initBME() {
    if (isInit) return;
    isInit = true;

    bool status = bme.init();

    if (!status) 
        switchToErrorMode(ERROR_SENSOR_ACCESS);
    
}

float readTemperature() {
    return bme.getTemperature();
}
float readHumidity() {
    return bme.getHumidity();
}
float readPressure() {
    return bme.getTemperature();
}

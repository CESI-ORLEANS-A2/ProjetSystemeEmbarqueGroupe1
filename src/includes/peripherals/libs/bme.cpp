#include "includes/peripherals/libs/bme.hpp"

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
    Serial.print(" (Temperature : ");
    Serial.print(bme.getTemperature());
    Serial.print(") ");
    return NULL;
}
float readHumidity() {
    Serial.print(" (Humidity : ");
    Serial.print(bme.getHumidity());
    Serial.print(") ");
    return bme.getHumidity();
}
float readPressure() {
    return bme.getTemperature();
}

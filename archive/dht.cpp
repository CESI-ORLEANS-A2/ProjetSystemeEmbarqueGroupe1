#include "includes/peripherals/libs/dht.hpp"

DHTNEW dht(TEMPERATURE_SENSOR_DEVICE);
bool readThisStep = false;

void readDHT() {
    if (readThisStep) return;
    readThisStep = true;
    dht.read();
}

float readTemperature() {
    readDHT();
    return dht.getTemperature();
}
float readHumidity() {
    readDHT();
    return dht.getHumidity();
}
float readPressure() {
    return 0;
}
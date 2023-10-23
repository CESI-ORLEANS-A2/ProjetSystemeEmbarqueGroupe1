#include "includes/peripherals/serial.hpp"

bool isSerialInit = false;

void initSerial() {
    if (isSerialInit) return;
    Serial.begin(SERIAL_BAUD_RATE);
    isSerialInit = true;

    if (Serial) Serial.println(F("Station Météo v3"));
}
void print(String message) {
    if (!isSerialInit) return;
    Serial.print(message);
}
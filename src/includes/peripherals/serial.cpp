#include "includes/peripherals/serial.hpp"

void initSerial() {
    Serial.begin(SERIAL_BAUD_RATE);

    if (Serial) Serial.println(F("Station Météo v3"));
}
void print(String message) {
    Serial.print(message);
}

void printData() {
#if LIVE_MODE_SERIAL_OUTPUT==OUTPUT_JSON
    Serial.print(F("{"));
    for (int i = 0; i < NUMBER_OF_SENSORS; i++) {
        char name[MAX_NAME_LENGTH];
        strcpy_P(name, sensors[i]->name);
        Serial.print(F("\""));
        Serial.print(name);
        Serial.print(F("\":"));
        Serial.print(lastMeasurements[i]);
        if (i < NUMBER_OF_SENSORS - 1) Serial.print(F(","));
    }
    Serial.println(F("}"));
#else
    for (int i = 0; i < NUMBER_OF_SENSORS; i++) {
        char name[MAX_NAME_LENGTH];
        strcpy_P(name, sensors[i]->name);
        Serial.println(lastMeasurements[i]);
        if (i < NUMBER_OF_SENSORS - 1) Serial.print(F(";"));
    }
#endif
}

#include "peripherals/serial.hpp"

void initSerial() {
    Serial.begin(SERIAL_BAUD_RATE);

    if (Serial) Serial.println(F("Station Météo v3"));
}
void printData() {
    char* line;
    line = (char*)malloc(MAX_LINE_SIZE * sizeof(char));
    formatLine(line);
    Serial.println(line);
}

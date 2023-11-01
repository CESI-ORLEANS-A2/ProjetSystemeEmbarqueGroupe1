#include "peripherals/serial.hpp"

void initSerial() {
    Serial.begin(SERIAL_BAUD_RATE);

    Serial.print(F("\r\nStation Météo "));
    printVersion();
    Serial.println();
    Serial.println();
}
void printData() {
    char line[MAX_LINE_SIZE] = "";
    formatLine(line);
    Serial.println(line);
}

void printVersion()  {
    Serial.print('v');
    Serial.print(VERSION);
    Serial.print('-');
    for (int i = 0; i < UniqueIDsize; i++) {
        Serial.print(UniqueID[i], HEX);
    }
}
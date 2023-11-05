#include "peripherals/serial.hpp"

void initSerial() {
    // Initialisation du port série
    Serial.begin(SERIAL_BAUD_RATE);

    // Affichage de 'Station Météo vX.X.X-XXXXXXXXXXXX' sur le port série
    Serial.print(F("\r\nStation Météo "));
    printVersion();
    Serial.println();
    Serial.println();
}

void printVersion()  {
    Serial.print('v');
    Serial.print(VERSION);
    Serial.print('-');
    // Affichage de chaque partie de l'ID unique de la carte
    for (int i = 0; i < UniqueIDsize; i++) {
        Serial.print(UniqueID[i], HEX);
    }
}
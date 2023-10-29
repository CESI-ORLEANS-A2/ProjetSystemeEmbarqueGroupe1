#include "peripherals/gps.hpp"

SoftwareSerial GPSSerial(GPS_RX_PIN, GPS_TX_PIN);

float lastNorth;
float lastWest;

void initGPS() {
    GPSSerial.begin(9600);
}
bool readGPS() {
    char* line = (char*)malloc(50 * sizeof(char));
    while (GPSSerial.available()) {
        GPSSerial.readBytesUntil('\n', line, 50);
        Serial.println(line);
        if (strncmp(line, "$GPRMC", 6) != 0)
            line = NULL;
    }
    if (line) {
        char* token = strsep(&line, ",");
        for (int i = 0; i < 3; i++) {
            token = strsep(&line, ",");
        }
        lastNorth = atof(token);
        for (int i = 0; i < 2; i++) {
            token = strsep(&line, ",");
        }
        lastWest = atof(token);

        free(line);
        return true;
    }
    free(line);
    return false;
}
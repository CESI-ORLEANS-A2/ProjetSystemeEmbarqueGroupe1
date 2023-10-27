#include "peripherals/sd.hpp"

SdFat SD;

void mount() {
    if (!SD.begin(SD_PIN))
        switchToErrorMode(ERROR_SD_ACCESS);
}
void unmount() {
    SD.end();
}
void saveData() {
    char* line;
    line = (char*)malloc(sizeof(char) * MAX_LINE_SIZE);
    formatLine(line);

    File32 dataFile = SD.open("data.txt", FILE_WRITE);
    if (dataFile) {
        dataFile.println(line);
        dataFile.close();
    }
    else {
        free(line);
        switchToErrorMode(ERROR_SD_ACCESS);
    }
}
void formatLine(char* line) {
    char* buf;
    buf = (char*)malloc(sizeof(char) * 10);

#if LIVE_MODE_SERIAL_OUTPUT==OUTPUT_JSON
    strcat_P(line, PSTR("{"));
    strcat_P(line, PSTR("\"north\":"));
    strcat(line, dtostrf(lastNorth, 0, 4, buf));
    strcat_P(line, PSTR(",\"west\":"));
    strcat(line, dtostrf(lastWest, 0, 4, buf));
    strcat_P(line, PSTR(","));
    for (int i = 0; i < NUMBER_OF_SENSORS; i++) {

        strcat_P(line, PSTR("\""));
        strcat_P(line, sensors[i]->name);
        strcat_P(line, PSTR("\":"));
        strcat(line, itoa(lastMeasurements[i], buf, 10));

        if (i < NUMBER_OF_SENSORS - 1) strcat_P(line, PSTR(","));
    }
    Serial.println(F("}"));
#else
    strcat(line, dtostrf(lastNorth, 0, 4, buf));
    strcat_P(line, PSTR(";"));
    strcat(line, dtostrf(lastWest, 0, 4, buf));
    for (int i = 0; i < NUMBER_OF_SENSORS; i++) {
        strcat(line, itoa(lastMeasurements[i], buf, 10));
        if (i < NUMBER_OF_SENSORS - 1) strcat_P(line, PSTR(";"));
    }
#endif

    free(buf);
}

#if LIVE_MODE_SERIAL_OUTPUT==OUTPUT_CSV
void CSVHeader(char* line) {
    strcat_P(line, PSTR("north;west;"));
    for (int i = 0; i < NUMBER_OF_SENSORS; i++) {
        strcat_P(line, sensors[i]->name);
        if (i < NUMBER_OF_SENSORS - 1) strcat_P(line, PSTR(";"));
    }
}
#endif
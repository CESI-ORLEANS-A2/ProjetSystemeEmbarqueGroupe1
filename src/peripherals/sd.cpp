#include "peripherals/sd.hpp"

SdFat SD;

unsigned int revisionNumber = 0;

void mount() {
    if (!SD.begin(SD_PIN))
        switchToErrorMode(ERROR_SD_ACCESS);
}
void unmount() {
    SD.end();
}
void getFileName(char* fileName) {
    char* buf = (char*)malloc(sizeof(char) * 10);

    fileName = "";

    strcat(fileName, itoa(lastYear, buf, 10));
    strcat(fileName, itoa(lastMonth, buf, 10));
    strcat(fileName, itoa(lastDay, buf, 10));
    strcat_P(fileName, PSTR("_"));
    strcat(fileName, itoa(revisionNumber, buf, 10));
    strcat_P(fileName, PSTR(".LOG"));

    free(buf);
}

void saveData() {
    char* line = (char*)malloc(sizeof(char) * MAX_LINE_SIZE);
    char* fileName = (char*)malloc(sizeof(char) * 20);
    formatLine(line);
    // getFileName(fileName);
    fileName = "test.log"

    File32* dataFile = (File32*) malloc(sizeof(File32)); 

    dataFile = &SD.open(fileName, FILE_WRITE);
    if (dataFile) {
        if (dataFile->size() + strlen(line) + 1 > getSetting(SETTING_FILE_MAX_SIZE)) {
            dataFile->close();

            revisionNumber++;
            getFileName(fileName);
            dataFile = &SD.open(fileName, FILE_WRITE);

            if (!dataFile) switchToErrorMode(ERROR_SD_ACCESS);
        }
        else {
            dataFile->println(line);
            dataFile->close();
        }
    }
    else
        switchToErrorMode(ERROR_SD_ACCESS);

    free(dataFile);
    free(line);
    free(fileName);
}
void formatLine(char* line) {
    char* buf;
    buf = (char*)malloc(sizeof(char) * 10);

#if LIVE_MODE_SERIAL_OUTPUT==OUTPUT_JSON
    strcat_P(line, PSTR("{"));

#if GPS_ENABLED
    strcat_P(line, PSTR("\"north\":"));
    strcat(line, dtostrf(lastNorth, 0, 4, buf));
    strcat_P(line, PSTR(",\"west\":"));
    strcat(line, dtostrf(lastWest, 0, 4, buf));
    strcat_P(line, PSTR(","));
#endif

    for (int i = 0; i < NUMBER_OF_SENSORS; i++) {

        strcat_P(line, PSTR("\""));
        strcat_P(line, sensors[i]->name);
        strcat_P(line, PSTR("\":"));
        strcat(line, itoa(lastMeasurements[i], buf, 10));

        if (i < NUMBER_OF_SENSORS - 1) strcat_P(line, PSTR(","));
    }
    strcat_P(line, PSTR("}"));
#else

#if GPS_ENABLED
    strcat(line, dtostrf(lastNorth, 0, 4, buf));
    strcat_P(line, PSTR(";"));
    strcat(line, dtostrf(lastWest, 0, 4, buf));
#endif

    for (int i = 0; i < NUMBER_OF_SENSORS; i++) {
        strcat(line, itoa(lastMeasurements[i], buf, 10));
        if (i < NUMBER_OF_SENSORS - 1) strcat_P(line, PSTR(";"));
    }
#endif

    free(buf);
}

#if LIVE_MODE_SERIAL_OUTPUT==OUTPUT_CSV
void printCSVHeader() {
    char* buf = (char*)malloc(sizeof(char) * 10);

#if GPS_ENABLED
    Serial.print(F("north;west;"));
#endif

    for (int i = 0; i < NUMBER_OF_SENSORS; i++) {
        strcat_P(buf, sensors[i]->name);
        Serial.print(buf);
        if (i < NUMBER_OF_SENSORS - 1) Serial.print(F(";"));
    }

    Serial.println();
}
#endif
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
    char buf[20];

    strcat(fileName, itoa(getYear(), buf, 10));
    strcat(fileName, itoa(getMonth(), buf, 10));
    strcat(fileName, itoa(getDay(), buf, 10));
    strcat_P(fileName, PSTR("_"));
    strcat(fileName, itoa(revisionNumber, buf, 10));
    strcat_P(fileName, PSTR(".LOG"));
}

void saveData() {
    if (SD.bytesPerCluster() * SD.freeClusterCount() < MIN_SD_FREE_BYTES) {
        switchToErrorMode(ERROR_SD_FULL);
        return;
    }

    char line[MAX_LINE_SIZE];
    char fileName[20];
    formatLine(line);
    getFileName(fileName);

    File32 dataFile = SD.open(fileName, FILE_WRITE);
    while (dataFile && dataFile.size() > getSetting(SETTING_FILE_MAX_SIZE)) { //  + strlen(line) + 1
        Serial.print(F("Révision ")); Serial.println(revisionNumber);
        Serial.print(F("Taille du fichier ")); Serial.println(dataFile.size());
        Serial.print(F("Taille max ")); Serial.println(getSetting(SETTING_FILE_MAX_SIZE));
        dataFile.close();

        revisionNumber++;
        for (int i = 0; i < strlen(fileName); i++) fileName[i] = '\0';
        getFileName(fileName);
        dataFile = SD.open(fileName, FILE_WRITE);
    }
    if (dataFile) {
#if LIVE_MODE_SERIAL_OUTPUT==OUTPUT_CSV
        if (dataFile.size() == 0) {
            char headerLine[MAX_LINE_SIZE];
            formatHeaderLine(headerLine);
            dataFile.println(headerLine);
        }
#endif
        dataFile.println(line);
        dataFile.close();
    }
    else
        switchToErrorMode(ERROR_SD_ACCESS);
}
void formatLine(char* line) {
    char buf[10];

#if LIVE_MODE_SERIAL_OUTPUT==OUTPUT_JSON
    strcat_P(line, PSTR("{"));

    strcat_P(line, PSTR("\"date\":\""));
    strcat(line, itoa(getDay(), buf, 10));
    strcat_P(line, PSTR("/"));
    strcat(line, itoa(getMonth(), buf, 10));
    strcat_P(line, PSTR("/"));
    strcat(line, itoa(getYear(), buf, 10));
    strcat_P(line, PSTR("\","));
    strcat_P(line, PSTR("\"time\":\""));
    strcat(line, itoa(getHour(), buf, 10));
    strcat_P(line, PSTR(":"));
    strcat(line, itoa(getMinute(), buf, 10));
    strcat_P(line, PSTR(":"));
    strcat(line, itoa(getSecond(), buf, 10));
    strcat_P(line, PSTR("\","));

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

    strcat(line, itoa(getDay(), buf, 10));
    strcat_P(line, PSTR("/"));
    strcat(line, itoa(getMonth(), buf, 10));
    strcat_P(line, PSTR("/"));
    strcat(line, itoa(getYear(), buf, 10));
    strcat_P(line, PSTR(";"));
    strcat(line, itoa(getHour(), buf, 10));
    strcat_P(line, PSTR(":"));
    strcat(line, itoa(getMinute(), buf, 10));
    strcat_P(line, PSTR(":"));
    strcat(line, itoa(getSecond(), buf, 10));
    strcat_P(line, PSTR(";"));

#if GPS_ENABLED
    strcat(line, dtostrf(lastNorth, 0, 4, buf));
    strcat_P(line, PSTR(";"));
    strcat(line, dtostrf(lastWest, 0, 4, buf));
    strcat_P(line, PSTR(";"));
#endif

    for (int i = 0; i < NUMBER_OF_SENSORS; i++) {
        strcat(line, itoa(lastMeasurements[i], buf, 10));
        if (i < NUMBER_OF_SENSORS - 1) strcat_P(line, PSTR(";"));
    }
#endif
}

#if LIVE_MODE_SERIAL_OUTPUT==OUTPUT_CSV
void formatHeaderLine(char* line) {
    strcat_P(line, PSTR("date;time;"));
#if GPS_ENABLED
    strcat_P(line, PSTR("north;west;"));
#endif
    for (int i = 0; i < NUMBER_OF_SENSORS; i++) {
        strcat_P(line, sensors[i].name);
        if (i < NUMBER_OF_SENSORS - 1) strcat_P(line, PSTR(";"));
    }
}

void printCSVHeader() {
    char line[MAX_LINE_SIZE] = "";

    formatHeaderLine(line);

    Serial.println(line);
}
#endif
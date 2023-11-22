#include "peripherals/sd.hpp"

SdFat SD; // Taille SRAM : 600

unsigned int revisionNumber = 0;

int lastDay;

void mount() {
    // Montage de la carte SD
    // En cas d'erreur, on passe en mode erreur
    if (!SD.begin(SD_PIN))
        switchToErrorMode(ERROR_SD_ACCESS);
}
void unmount() {
    // Démontage de la carte SD
    SD.end();
}

void getFileName(char* fileName) {
    // Buffer pour la conversion des nombres en chaîne de caractères
    char buf[MAX_NAME_LENGTH];

    // On ajoute un 0 devant les nombres inférieurs à 10 pour que les noms de fichiers soient triés correctement
    // et que les noms soit tous de la même taille.

    if (getYear() < 10) strcat_P(fileName, PSTR("0"));
    strcat(fileName, itoa(getYear(), buf, 10));

    if (getMonth() < 10) strcat_P(fileName, PSTR("0"));
    strcat(fileName, itoa(getMonth(), buf, 10));

    if (getDay() < 10) strcat_P(fileName, PSTR("0"));
    strcat(fileName, itoa(getDay(), buf, 10));

    strcat_P(fileName, PSTR("_"));

    if (revisionNumber < 10) strcat_P(fileName, PSTR("00"));
    else if (revisionNumber < 100) strcat_P(fileName, PSTR("0"));
    strcat(fileName, itoa(revisionNumber, buf, 10));

    strcat_P(fileName, FILE_EXTENSION);
}

void saveData() {
    // if (SD.bytesPerCluster() * SD.freeClusterCount() < MIN_SD_FREE_BYTES) {
    //     switchToErrorMode(ERROR_SD_FULL);
    //     return;
    // }

    // Réinitialisation du numéro de révision si on change de jour
    if (lastDay != getDay()) {
        lastDay = getDay();
        revisionNumber = 0;
    }

    char fileName[20] = "";
    getFileName(fileName);

    noInterrupts();

    // Ouverture du fichier
    File32 dataFile = SD.open(fileName, FILE_WRITE);
    // Tant que le fichier est trop gros, on incrémente le numéro de révision
    while (dataFile && dataFile.size() + MAX_LINE_SIZE > getSetting(SETTING_FILE_MAX_SIZE)) {
        // Fermeture du fichier
        dataFile.close();

        revisionNumber++;

        // Réinitialisation de nom de fichier
        for (int i = 0; i < strlen(fileName); i++) fileName[i] = '\0';
        getFileName(fileName);

        // Ouverture du fichier
        dataFile = SD.open(fileName, FILE_WRITE);
    }

    interrupts();

    // Si on n'a pas pu ouvrir le fichier, on passe en mode erreur
    // Sinon on écrit les données
    if (dataFile) {
#if LIVE_MODE_SERIAL_OUTPUT==OUTPUT_CSV
        // Si le fichier est vide, on écrit l'en-tête
        if (dataFile.size() == 0) {
            printHeaderLine(dataFile);
        }
#endif
        printLine(dataFile);
        dataFile.close();
    }
    else
        switchToErrorMode(ERROR_SD_ACCESS);
}

void printLine(Stream& s) {
    char buf[10];

#if LIVE_MODE_SERIAL_OUTPUT==OUTPUT_JSON
    s.print(F("{"));

    s.print(F("\"date\":\""));
    s.print(itoa(getDay(), buf, 10));
    s.print(F("/"));
    s.print(itoa(getMonth(), buf, 10));
    s.print(F("/"));
    s.print(itoa(getYear(), buf, 10));
    s.print(F("\","));
    s.print(F("\"time\":\""));
    s.print(itoa(getHour(), buf, 10));
    s.print(F(":"));
    s.print(itoa(getMinute(), buf, 10));
    s.print(F(":"));
    s.print(itoa(getSecond(), buf, 10));
    s.print(F("\","));

#if GPS_ENABLED
    s.print(F("\"north\":"));
    s.print(dtostrf(lastNorth, 0, 4, buf));
    s.print(F(",\"west\":"));
    s.print(dtostrf(lastWest, 0, 4, buf));
    s.print(F(","));
#endif

    for (int i = 0; i < NUMBER_OF_SENSORS; i++) {

        s.print(F("\""));
        s.print(sensors[i]->name);
        s.print(F("\":"));
        s.print(itoa(lastMeasurements[i], buf, 10));

        if (i < NUMBER_OF_SENSORS - 1) s.print(F(","));
    }
    s.print(F("}"));
#else

    // Si le nombre est inférieur à 10, on ajoute un 0 devant pour que les nombres soient tous de la même taille
    // Cela permet une meilleure lisibilité des données

    // Écriture de la date et de l'heure
    if (getDay() < 10) s.print(F("0"));
    s.print(itoa(getDay(), buf, 10));

    s.print(F("/"));

    if (getMonth() < 10) s.print(F("0"));
    s.print(itoa(getMonth(), buf, 10));

    s.print(F("/"));

    s.print(itoa(getYear(), buf, 10));

    s.print(F(";"));

    if (getHour() < 10) s.print(F("0"));
    s.print(itoa(getHour(), buf, 10));

    s.print(F(":"));

    if (getMinute() < 10) s.print(F("0"));
    s.print(itoa(getMinute(), buf, 10));

    s.print(F(":"));

    if (getSecond() < 10) s.print(F("0"));
    s.print(itoa(getSecond(), buf, 10));

    s.print(F(";"));

    // Écriture des coordonnées GPS
#if GPS_ENABLED
    s.print(lastLatitude);
    s.print(F(";"));
    s.print(lastLongitude);
    s.print(F(";"));
#endif

    // Écriture des données des capteurs
    for (int i = 0; i < NUMBER_OF_SENSORS; i++) {
        float value = lastMeasurements[i];
        if (value == ACQUISITION_ERROR_VALUE) value = NAN;
        s.print(dtostrf(value, 0, DECIMAL, buf));
        if (i < NUMBER_OF_SENSORS - 1) s.print(F(";"));
    }
#endif
    s.println();
}

#if LIVE_MODE_SERIAL_OUTPUT==OUTPUT_CSV
void printHeaderLine(Stream& s) {
    // Écriture de l'en-tête CSV
    // Date et heure
    s.print(F("date;time;"));
#if GPS_ENABLED
    // Coordonnées GPS
    s.print(F("latitude;longitude;"));
#endif
    // Nom des capteurs
    for (int i = 0; i < NUMBER_OF_SENSORS; i++) {
        char buf[MAX_NAME_LENGTH];
        strcpy_P(buf, sensors[i].name);
        s.print(buf);
        if (i < NUMBER_OF_SENSORS - 1) s.print(F(";"));
    }
    s.println();
}

#endif
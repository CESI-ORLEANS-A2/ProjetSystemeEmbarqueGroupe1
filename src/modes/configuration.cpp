#include "modes/configuration.hpp"

unsigned long* lastActivity;

#if !INTERPRETER
char configurationInputBuffer[INPUT_BUFFER_SIZE];
int configurationInputLength = 0;
#endif

void switchToConfigurationMode() {
    previousMode = mode;
    mode = CONFIGURATION_MODE;

    switchLEDToYellow();

    unmount();

    lastActivity = (unsigned long*)malloc(sizeof(long));
    *lastActivity = millis();
};
void quitConfigurationMode() {
    free(lastActivity);
    mount();
}
void runConfigurationModeStep() {
    if ((unsigned long)millis() - *lastActivity >= CONFIGURATION_MODE_TIMEOUT)
        switch (previousMode) {
        case MAINTENANCE_MODE:
            switchToMaintenanceMode();
            break;
        case ECONOMY_MODE:
            switchToEconomyMode();
            break;
        case STANDARD_MODE:
            switchToStandardMode();
            break;
        }

    // TODO Interpréteur de commande spécifique
#if !INTERPRETER
    if (Serial.available()) updateLastActivity();
    while (Serial.available()) {
        int data = Serial.read();
        if (data == '\r')
            continue;
        else if (data == '\b' || data == '\177') {
            if (configurationInputLength) {
                configurationInputLength--;
#if INPUT_DO_ECHO
                Serial.write("\b \b");
#endif
            }
        }
        else if (data == '\n') {
#if INPUT_DO_ECHO
            Serial.write("\r\n");
#endif
            configurationInputBuffer[configurationInputLength] = '\0';
            if (configurationInputLength)
                configurationRunCommand(configurationInputBuffer);
            Serial.println();
            for (int i = 0; i < configurationInputLength; i++)
                configurationInputBuffer[i] = '\0';
            configurationInputLength = 0;
        }
        else if (configurationInputLength < INPUT_BUFFER_SIZE - 1) {
            configurationInputBuffer[configurationInputLength++] = data;
#if INPUT_DO_ECHO
            Serial.write(data);
#endif
        }
    }
#endif
};

#if !INTERPRETER
void configurationRunCommand(char* command) {
    int sum = 0;
    for (int i = 0; i < configurationInputLength; i++)
        sum += configurationInputBuffer[i];

    switch (sum) {
    case 387: // RESET
        resetSettings();
        Serial.println(F("Paramètres réinitialisés"));
        return;
    case 550: // VERSION
        printVersion();
        return;
    }

    char* commandName = strsep(&command, (const char*)'=');
    sum = 0;
    for (int i = 0; i < strlen(commandName); i++)
        sum += commandName[i];
    switch (sum) {
    case 364: // CLOCK
        int hour = atoi(strsep(&command, (const char*)':'));
        int minute = atoi(strsep(&command, (const char*)':'));
        int second = atoi(command);

        if (!hour || !minute || !second || hour > 23 || hour < 0 || minute > 59 || minute < 0 || second > 59 || second < 0) {
            printInvalidValue();
            return;
        }
        setHour(hour);
        setMinute(minute);
        setSecond(second);
        break;
    case 286: // DATE
        int day = atoi(strsep(&command, (const char*)'/'));
        int month = atoi(strsep(&command, (const char*)'/'));
        int year = atoi(command);

        if (!day || !month || !year || day > 31 || day < 0 || month > 12 || month < 0 || year > 99 || year < 0) {
            printInvalidValue();
            return;
        }
        setDay(day);
        setMonth(month);
        setYear(year);
        break;
    case 222: // DAY
        int dayOfWeek = atoi(command);
        sum = 0;
        for (int i = 0; i < 3; i++) {
            sum += command[i];
        }
        switch (sum) {
        case 291: // MON
            setDayOfWeek(MONDAY);
            break;
        case 292: // TUE
            setDayOfWeek(TUESDAY);
            break;
        case 293: // WED
            setDayOfWeek(WEDNESDAY);
            break;
        case 294: // THU
            setDayOfWeek(THURSDAY);
            break;
        case 295: // FRI
            setDayOfWeek(FRIDAY);
            break;
        case 296: // SAT
            setDayOfWeek(SATURDAY);
            break;
        case 297: // SUN
            setDayOfWeek(SUNDAY);
            break;
        default:
            printInvalidValue();
            return;
        }
        break;
    }
    for (int i = 0; i < NUMBER_OF_SETTINGS; i++) {
        int settingNameSum = 0;
        for (int j = 0; j < strlen(settings[i].name); j++)
            settingNameSum += settings[i].name[j];
        if (sum == settingNameSum) {
            int value = atoi(command);
            if (value > settings[i].max || value < settings[i].min) {
                printInvalidValue();
            }
            else { 
                setSetting(i, value);
                Serial.println(F("Enregistré"));
            }
        }
    }
}
#endif

void updateLastActivity() {
    *lastActivity = millis();
}

void printInvalidValue() {
    Serial.println(F("Valeur invalide"));
}
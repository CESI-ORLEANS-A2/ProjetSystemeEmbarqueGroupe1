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

    lastActivity = (unsigned long*)malloc(sizeof(long));
    *lastActivity = millis();
};
void quitConfigurationMode() {
    free(lastActivity);
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
            Serial.print(F("\n\r> "));
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
    if (strcmp_P(command, PSTR("RESET")) == 0) {
        resetSettings();
        Serial.println(F("Paramètres réinitialisés"));
    }
    else if (strcmp_P(command, PSTR("VERSION")) == 0) {

    }
}
#endif

void printSwitchToConfiguration() {
    Serial.println(F("Passage en mode configuration"));
}

void updateLastActivity() {
    *lastActivity = millis();
}
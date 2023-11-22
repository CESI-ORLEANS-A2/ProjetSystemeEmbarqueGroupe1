#include "modes/configuration.hpp"

unsigned long lastActivity;

#if !INTERPRETER
char configurationInputBuffer[INPUT_BUFFER_SIZE];
int configurationInputLength = 0;
#endif // !INTERPRETER

void switchToConfigurationMode() {
    previousMode = mode;
    mode = CONFIGURATION_MODE;

    switchLEDToYellow();

    // Démontage de la carte SD
    unmount();
  
    // Mise à jour de la dernière activité de l'utilisateur
    lastActivity = millis();
};
void quitConfigurationMode() {
    // Remontage de la carte SD
    mount();
}
void runConfigurationModeStep() {
    // Vérification de temps d'inactivité (durée entre maintenant et la dernière activité)
    if ((unsigned long)millis() - lastActivity >= CONFIGURATION_MODE_TIMEOUT)
        // Si le temps d'inactivité est trop long, on quitte le mode de configuration
        // en revenant au mode précédent.
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

    // Si des caractères sont disponibles sur le port série, on met à jour la dernière activité
    if (Serial.available()) updateLastActivity();

    // Interpréteur de commande simple
#if !INTERPRETER
    // Lecture des caractères entrés par l'utilisateur
    while (Serial.available()) {
        int data = Serial.read();
        // Si le caractère est un retour chariot, on l'ignore
        if (data == '\r')
            continue;
        // Si le caractère est un retour, on efface le dernier caractère entré
        else if (data == '\b' || data == '\177') {
            if (configurationInputLength) {
                configurationInputLength--;
                Serial.write("\b \b");
            }
        }
        // Si le caractère est un saut de ligne, on exécute la commande
        else if (data == '\n') {
            Serial.write("\r\n");
            // On ajoute un caractère de fin de chaîne
            configurationInputBuffer[configurationInputLength] = '\0';
            // On exécute la commande entrée si elle n'est pas vide
            if (configurationInputLength)
                configurationRunCommand(configurationInputBuffer);

            Serial.println();

            // On réinitialise le buffer d'entrée ainsi que sa longueur
            for (int i = 0; i < configurationInputLength; i++)
                configurationInputBuffer[i] = '\0';
            configurationInputLength = 0;
        }
        // Sinon, on ajoute le caractère au buffer d'entrée et on l'affiche
        else if (configurationInputLength < INPUT_BUFFER_SIZE - 1) {
            configurationInputBuffer[configurationInputLength++] = data;
            Serial.write(data);
        }
    }
#endif
};

#if !INTERPRETER
void configurationRunCommand(char* command) {
    // Calcul de la somme des caractères de la commande
    int sum = 0;
    for (int i = 0; i < configurationInputLength; i++)
        sum += configurationInputBuffer[i];

    // Switch-Case pour les commandes sans arguments : RESET, VERSION
    switch (sum) {
    case 387: // RESET
        resetSettings();
        Serial.println(F("Paramètres réinitialisés"));
        return;
    case 550: // VERSION
        printVersion();
        Serial.println();
        return;
    }

    // Itération dans la liste des paramètres pour vérifié si la commande n'est pas un paramètre sans valeur
    for (int i = 0; i < NUMBER_OF_SETTINGS; i++) {
        if (sum == settings[i].sum) {
            Serial.println(settings[i].value);
            return;
        }
    }

    // Séparation de la commande et de la valeur
    char* commandName = strsep_P(&command, PSTR("="));
    // Recalcul de la somme, mais uniquement sur le nom de paramètre
    sum = 0;
    for (int i = 0; i < strlen(commandName); i++)
        sum += commandName[i];

    // Switch-Case pour les commandes avec arguments complexes : CLOCK, DATE, DAY
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
        return;
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
        return;
    case 222: // DAY
        int dayOfWeek = atoi(command);
        sum = 0;
        for (int i = 0; i < 3; i++) {
            sum += command[i];
        }
        switch (sum) { // TODO Vérifier les valeurs
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
            break;
        }
        return;
    }

    // Itération dans la liste des paramètres pour vérifié si la commande n'est pas un paramètre avec valeur
    for (int i = 0; i < NUMBER_OF_SETTINGS; i++) {
        if (sum == settings[i].sum) {
            int value = atoi(command);
            // Vérification de la valeur
            if (value > settings[i].max || value < settings[i].min) {
                printInvalidValue();
                return;
            }
            else {
                setSetting(i, value);
                Serial.println(F("Enregistré"));
                return;
            }

        }
    }

    // Si la commande n'est pas reconnue, on revoie "Inconnu"
    Serial.println(F("Inconnu"));
}
#endif

void printInvalidValue() {
    Serial.println(F("Valeur invalide"));
}
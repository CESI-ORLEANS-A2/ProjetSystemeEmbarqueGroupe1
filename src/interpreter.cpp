#include "interpreter.hpp"

char inputBuffer[INPUT_BUFFER_SIZE];
int inputLength = 0;

void initInterpreter() {

    Serial.print(F("\n\r"
        "Bienvenue dans l'invite de commande de la station météo !\n\r"
        "Pour afficher toutes les commandes disponibles: taper 'help'.\n\r"
        "Mode actuel : "));
    printMode();

    printPrompt();
}

void runInterpreterStep() {
    if (liveMode) return;

    while (Serial.available()) {
        int data = Serial.read();
        if (data == '\r')
            continue;
        else if (data == '\b' || data == '\177') {
            if (inputLength) {
                inputLength--;
#if INPUT_DO_ECHO
                Serial.write("\b \b");
#endif
            }
        }
        else if (data == '\n') {
#if INPUT_DO_ECHO
            Serial.write("\r\n");
#endif
            inputBuffer[inputLength] = '\0';
            if (inputLength)
                runCommand();
            printPrompt();
            for (int i = 0; i < inputLength; i++)
                inputBuffer[i] = '\0';
            inputLength = 0;
        }
        else if (inputLength < INPUT_BUFFER_SIZE - 1) {
            inputBuffer[inputLength++] = data;
#if INPUT_DO_ECHO
            Serial.write(data);
#endif
        }
    }
}

void runCommand() {
    char* commandLine = (char*)malloc(INPUT_BUFFER_SIZE * sizeof(char));
    char* command = (char*)malloc(10 * sizeof(char));
    commandLine = inputBuffer;
    command = strsep_P(&commandLine, PSTR(" "));

    if (strcmp_P(command, PSTR("help")) == 0) {
        commandHelp(strsep_P(&commandLine, PSTR(" ")));
    }
    else if (strcmp_P(command, PSTR("list")) == 0) {
        commandList();
    }
    else if (strcmp_P(command, PSTR("live")) == 0) {
        if (mode != MAINTENANCE_MODE) {
            printCommandUnavailableInThisMode();
        }
        else
            commandLive();
    }
    else if (strcmp_P(command, PSTR("mode")) == 0) {
        commandMode(strsep_P(&commandLine, PSTR(" ")));
    }
    else if (strcmp_P(command, PSTR("enable")) == 0) {
        if (mode != CONFIGURATION_MODE) {
            printCommandUnavailableInThisMode();
        }
        else
            commandEnable(atoi(strsep_P(&commandLine, PSTR(" "))));
    }
    else if (strcmp_P(command, PSTR("disable")) == 0) {
        if (mode != CONFIGURATION_MODE) {
            printCommandUnavailableInThisMode();
        }
        else
            commandDisable(atoi(strsep_P(&commandLine, PSTR(" "))));
    }
    else if (strcmp_P(command, PSTR("set")) == 0) {
        if (mode != CONFIGURATION_MODE) {
            printCommandUnavailableInThisMode();
        }
        else {
            char* name, * value;
            name = (char*)malloc(20 * sizeof(char));
            value = (char*)malloc(10 * sizeof(char));

            name = strsep_P(&commandLine, PSTR(" "));
            value = strsep_P(&commandLine, PSTR(" "));

            commandSet(name, atoi(value));

            free(name);
            free(value);
        }
    }
    else if (strcmp_P(command, PSTR("get")) == 0) {
        if (mode != CONFIGURATION_MODE) {
            printCommandUnavailableInThisMode();
        }
        else
            commandGet(strsep_P(&commandLine, PSTR(" ")));
    }
    else if (strcmp_P(command, PSTR("reset")) == 0) {
        if (mode != CONFIGURATION_MODE) {
            printCommandUnavailableInThisMode();
        }
        else
            commandReset();
    }
    else if (strcmp_P(command, PSTR("last")) == 0) {
        commandLast();
    }
    else if (strcmp_P(command, PSTR("clock")) == 0) {
        if (mode != CONFIGURATION_MODE) {
            printCommandUnavailableInThisMode();
        }
        else {
            char* hours, * minutes, * seconds;
            hours = (char*)malloc(3 * sizeof(char));
            minutes = (char*)malloc(3 * sizeof(char));
            seconds = (char*)malloc(3 * sizeof(char));

            hours = strsep_P(&commandLine, PSTR(" "));
            minutes = strsep_P(&commandLine, PSTR(" "));
            seconds = strsep_P(&commandLine, PSTR(" "));

            commandClock(atoi(hours), atoi(minutes), atoi(seconds));

            free(hours);
            free(minutes);
            free(seconds);
        }
    }
    else if (strcmp_P(command, PSTR("date")) == 0) {
        if (mode != CONFIGURATION_MODE) {
            printCommandUnavailableInThisMode();
        }
        else {
            char* day, * month, * year;
            day = (char*)malloc(3 * sizeof(char));
            month = (char*)malloc(3 * sizeof(char));
            year = (char*)malloc(5 * sizeof(char));

            day = strsep_P(&commandLine, PSTR(" "));
            month = strsep_P(&commandLine, PSTR(" "));
            year = strsep_P(&commandLine, PSTR(" "));

            commandDate(atoi(day), atoi(month), atoi(year));

            free(day);
            free(month);
            free(year);
        }
    }
    else if (strcmp_P(command, PSTR("day")) == 0) {
        if (mode != CONFIGURATION_MODE) {
            printCommandUnavailableInThisMode();
        }
        else
            commandDay(strsep_P(&commandLine, PSTR(" ")));
    }
#if SETTINGS_IN_EEPROM
    else if (strcmp_P(command, PSTR("eeprom")) == 0) {
        long value;
        for (int i = 0; i < EEPROM.length(); i++) {
            Serial.print(i);
            Serial.print(" : ");
            Serial.print(EEPROM.get(i, value));
            Serial.print("\n");
        }
        Serial.println();
    }
#endif
    else {
        printUnknownCommand();
    }

    free(commandLine);
    free(command);
}

void printPrompt() {
    if (!liveMode)
        Serial.print(F("\n\r> "));
}
void printHelpCommand() {
    Serial.print(F("Commande : "));
}
void printHelpNeededMode() {
    Serial.print(F("Mode nécessaire : "));
}
void printHelpDesciption() {
    Serial.print(F("Description : "));
}
void printHelpSyntax() {
    Serial.print(F("Syntaxe : "));
}
void printHelpArguments() {
    Serial.print(F("Arguments :"));
}
void printHelpListDash() {
    printSpaces(3);
    Serial.print(F("-"));
    printSpaces(1);
}
void printUnknownCommand() {
    Serial.print(F("Commande inconnue.\n\r"));
}
void printBuffer() {
    Serial.print(inputBuffer);
}
void printModeAlreadyEnabled() {
    Serial.print(F("Ce mode est déjà activé.\n\r"));
}
void printSpaces(int n) {
    for (int i = 0; i < n; i++)
        Serial.print(F(" "));
}
void printSensorEnabled(int id) {
    char* name;
    strcpy_P(name, sensors[id]->name);
    Serial.print(F("Le capteur "));
    Serial.print(name);
    Serial.println(F("a été activé."));
}
void printSensorDisabled(int id) {
    char* name;
    strcpy_P(name, sensors[id]->name);
    Serial.print(F("Le capteur "));
    Serial.print(name);
    Serial.println(F("a été désactivé."));
}
void printCommandUnavailableInThisMode() {
    Serial.println(F("Cette commande n'est pas disponible dans ce mode.\n\r"));
}
void printClock() {
    Serial.print(F("Heure actuelle : "));
    Serial.print(getHour());
    Serial.print(F(":"));
    Serial.print(getMinute());
    Serial.print(F(":"));
    Serial.println(getSecond());
}
void printDate() {
    Serial.print(F("Date actuelle : "));
    Serial.print(getDay());
    Serial.print(F("/"));
    Serial.print(getMonth());
    Serial.print(F("/"));
    Serial.println(getYearFull());
}
void printDayOfWeek() {
    Serial.print(F("Jour actuel : "));
    switch (getDayOfWeek()) {
    case 1:
        Serial.println(F("Lundi"));
        break;
    case 2:
        Serial.println(F("Mardi"));
        break;
    case 3:
        Serial.println(F("Mercredi"));
        break;
    case 4:
        Serial.println(F("Jeudi"));
        break;
    case 5:
        Serial.println(F("Vendredi"));
        break;
    case 6:
        Serial.println(F("Samedi"));
        break;
    case 7:
        Serial.println(F("Dimanche"));
        break;
    }
}
void printDayModified() {
    Serial.println(F("Jour modifié."));
}

void commandHelp(char* command) {
    if (!command) {
        Serial.print(F("Liste des commandes disponibles :\n\r"
#if DETAILED_HELP_COMMAND
            " - help [command?] : Affiche ce menu.\n\r"
#else
            " - help : Affiche ce menu.\n\r"
#endif
            " - list : Affiche la liste des capteurs disponibles.\n\r"
            " - live : Affiche les dernières données récoltées en temps réel.\n\r" // NOTE seconde ?
            " - last : Affiche une fois les dernières données récoltées.\n\r"
            " - enable [id?] : Active un ou plusieurs capteurs.\n\r"
            " - disable [id?] : Désactive un ou plusieurs capteurs.\n\r"
            " - set [name] [value] : Modifie les paramètres.\n\r"
            " - get [name] : Affiche la valeur d'un paramètre.\n\r"
            " - mode [mode?] : Change le mode de la station météo.\n\r"
            " - reset : Réinitialise les paramètres.\n\r"
            " - clock [hours?] [minutes?] [seconds?] : Affiche ou change l'heure.\n\r"
            " - date [day?] [month?] [year?] : Affiche ou change la date.\n\r"
            " - day [day?] : Affiche ou change le jour actuel.\n\r"
        ));
    }
#if DETAILED_HELP_COMMAND
    else if (strcmp_P(command, PSTR("help")) == 0) {
        // "Commande : HELP\n\r"
        // "Mode nécessaire : /\n\r"
        // "Description : Affiche ce menu.\n\r"
        // "Syntaxe : help [command?]\n\r"
        // "Arguments :\n\r"
        // "    - command (optionnel) : Permet d'obtenir l'aide pour une commande particulière.\n\r"
        printHelpCommand();Serial.println(F("HELP"));
        printHelpNeededMode();Serial.println(F("/"));
        printHelpDesciption();Serial.println(F("Affiche le menu d'aide."));
        printHelpSyntax();Serial.println(F("help [command?]"));
        printHelpArguments();
        printHelpListDash();Serial.println(F("command (optionnel) : Permet d'obtenir l'aide pour une commande particulière."));
    }
    else if (strcmp_P(command, PSTR("list")) == 0) {
        // "Commande : LIST\n\r"
        // "Mode nécessaire : /\n\r"
        // "Description : Affiche la liste des capteurs disponibles et quelques informations.\n\r"
        // "Syntaxe : list\n\r"
        printHelpCommand();Serial.println(F("LIST"));
        printHelpNeededMode();Serial.println(F("/"));
        printHelpDesciption();Serial.println(F("Affiche la liste des capteurs disponibles et quelques informations."));
        printHelpSyntax();Serial.println(F("list"));
    }
    else if (strcmp_P(command, PSTR("live")) == 0) {
        // "Commande : LIVE\n\r"
        // "Mode nécessaire : maintenance\n\r"
        // "Description : Affiche les dernières données récoltées en temps réel.\n\r"
        // "Syntaxe : live\n\r"
        printHelpCommand();Serial.println(F("LIVE"));
        printHelpNeededMode();Serial.println(F("maintenance"));
        printHelpDesciption();Serial.println(F("Affiche ou arrête d'afficher les données récoltées toutes les secondes."));
        printHelpSyntax();Serial.println(F("live"));
    }
    // else if (strcmp(command, PSTR("last")) == 0)
    //     Serial.print(F("Commande : LAST\n\r"
    //         "Mode nécessaire : maintenance\n\r"
    //         "Description : Affiche une fois les dernières données récoltées.\n\r"
    //         "Syntaxe : last\n\r"));
    else if (strcmp_P(command, PSTR("enable")) == 0) {
        printHelpCommand();Serial.println(F("ENABLE"));
        printHelpNeededMode();Serial.println(F("configuration"));
        printHelpDesciption();Serial.println(F("Active un ou tous capteurs."));
        printHelpSyntax();Serial.println(F("enable [id?]"));
        printHelpArguments();
        printHelpListDash();Serial.println(F("id (optionnel) : Le nom du capteur particulier."));
    }
    else if (strcmp_P(command, PSTR("disable")) == 0) {
        printHelpCommand();Serial.println(F("DISABLE"));
        printHelpNeededMode();Serial.println(F("configuration"));
        printHelpDesciption();Serial.println(F("Désactive un ou tous capteurs."));
        printHelpSyntax();Serial.println(F("disable [id?]"));
        printHelpArguments();
        printHelpListDash();Serial.println(F("id (optionnel) : Le nom du capteur particulier."));
    }
    else if (strcmp_P(command, PSTR("mode")) == 0) {
        // "Commande : MODE\n\r"
        // "Mode nécessaire : /\n\r"
        // "Description : Affiche le mode actuel de la station météo ou le change.\n\r"
        // "              Dans le cas de mode standard et économique, cela met fin à la connexion.\n\r"
        // "              Les modes :\n\r"
        // "                  - configuration : Permet de configurer les différents paramètres, la récupération des données est désactivé.\n\r"
        // "                  - maintenance : Permet d'accéder aux données et de changer la carte SD.\n\r"
        // "                                  L'enregistrement des données est désactivé.\n\r"
        // "                  - economy : Désactive certains capteurs.\n\r"
        // "                  - standard : Mode de récupération des données par défaut.\n\r"
        // "Syntaxe : mode ['configuration' | 'maintenance' | 'economy' | 'standard'?]\n\r"
        // "Arguments :\n\r"
        // "    - 'configuration' | 'maintenance' | 'economy' | 'standard' (optionnel) :\n\r"
        // "      Le mode de configuration.\n\r"
        printHelpCommand();Serial.println(F("MODE"));
        printHelpNeededMode();Serial.println(F("/"));
        printHelpDesciption();Serial.println(F("Affiche le mode actuel de la station météo ou le change."));
        printHelpSyntax();Serial.println(F("mode ['configuration' | 'maintenance' | 'economy' | 'standard'?]"));
        printSpaces(14);Serial.println(F("Dans le cas de mode standard et économique, cela met fin à la connexion."));
        printSpaces(14);Serial.println(F("Les modes :"));
        printSpaces(14);printHelpListDash();Serial.println(F("configuration : Permet de configurer les différents paramètres, la récupération des données est désactivé."));
        printSpaces(14);printHelpListDash();Serial.println(F("maintenance : Permet d'accéder aux données et de changer la carte SD."));
        printSpaces(34);Serial.println(F("L'enregistrement des données est désactivé."));
        printSpaces(14);printHelpListDash();Serial.println(F("economy : Désactive certains capteurs."));
        printSpaces(14);printHelpListDash();Serial.println(F("standard : Mode de récupération des données par défaut."));
        printHelpArguments();
        printHelpListDash();Serial.println(F("'configuration' | 'maintenance' | 'economy' | 'standard' (optionnel) : Le mode de configuration."));
    }
    // else if (strcmp(command, PSTR("erase")) == 0)
    //     Serial.print(F("Commande : ERASE\n\r"
    //         "Mode nécessaire : maintenance\n\r"
    //         "Description : Efface les données d'un ou tous capteurs.\n\r"
    //         "Syntaxe : erase [id?]\n\r"
    //         "Arguments :\n\r"
    //         "    - id (optionnel) : Le nom du capteur particulier.\n\r"));
    // else if (strcmp(command, PSTR("reset")) == 0)
    //     Serial.print(F("Commande : RESET\n\r"
    //         "Mode nécessaire : configuration\n\r"
    //         "Description : Réinitialise les paramètres d'un ou tous capteurs.\n\r"
    //         "Syntaxe : reset [id?]\n\r"
    //         "Arguments :\n\r"
    //         "    - id (optionnel) : Le nom du capteur particulier.\n\r"));
    else if (strcmp_P(command, PSTR("set")) == 0) {
        printHelpCommand();Serial.println(F("SET"));
        printHelpNeededMode();Serial.println(F("configuration"));
        printHelpDesciption();Serial.println(F("Affiche tous les paramètres ou modifie un paramètre"));
        printHelpSyntax();Serial.println(F("set [nom] [valeur]"));
        printHelpArguments();
        printHelpListDash();Serial.println(F("nom (optionnel): Le nom du paramètre à modifier."));
        printHelpListDash();Serial.println(F("id (optionnel) : Le nom du capteur particulier."));
    }
    else if (strcmp_P(command, PSTR("get")) == 0) {
        printHelpCommand();Serial.println(F("GET"));
        printHelpNeededMode();Serial.println(F("configuration"));
        printHelpDesciption();Serial.println(F("Affiche la valeur d'un paramètre"));
        printHelpSyntax();Serial.println(F("get {nom}"));
        printHelpArguments();
        printHelpListDash();Serial.println(F("nom: Le nom du paramètre à modifier."));
    }

    else
        printUnknownCommand();
#endif
}
void commandList() {
#if NUMBER_OF_SENSORS == 0
    Serial.print(F("| Nom (id)                 | Activé ? | Économie ? |\n\r"
        "|--------------------------|----------|------------|\n\r"
        "| Pas de capteurs                                  |\n\r"));
#else
    Serial.print(F("| Nom (id)                 | Activé ? | Économie ? |\n\r"
        "|--------------------------|----------|------------|\n\r"));

    char* name, * enabled, * economy, * line;
    name = (char*)malloc(20 * sizeof(char));
    enabled = (char*)malloc(3 * sizeof(char));
    economy = (char*)malloc(3 * sizeof(char));
    line = (char*)malloc(52 * sizeof(char));

    for (int i = 0; i < NUMBER_OF_SENSORS; i++) {

        strcpy_P(name, sensors[i]->name);
        strcpy_P(enabled, sensors[i]->enabled ? PSTR("Oui") : PSTR("Non"));
        strcpy_P(economy, sensors[i]->economy ? PSTR("Oui") : PSTR("Non"));

        strcat_P(line, PSTR("| "));

        strcat_P(line, name);
        for (int j = 0; j < (24 - (int)strlen_P(name)); j++)
            strcat_P(line, PSTR(" "));
        strcat(line, PSTR(" | "));
        strcat(line, enabled);
        strcat(line, PSTR("      | "));
        strcat(line, economy);
        strcat(line, PSTR("        |\n\r"));
        Serial.write(line);
    };

    free(name);
    free(enabled);
    free(economy);
    free(line);
#endif
}
void commandLive() {
    liveMode = true;
    Serial.print(F("Mode live\n\r"));
}
void commandMode(char* modeArg) {
    if (!modeArg) {
        Serial.print(F("Mode actuel : "));
        printMode();
    }
    else if (strcmp_P(modeArg, PSTR("configuration")) == 0) {
        if (mode == CONFIGURATION_MODE)
            printModeAlreadyEnabled();
        else
            switchToMode(CONFIGURATION_MODE);
    }
    else if (strcmp_P(modeArg, PSTR("maintenance")) == 0) {
        if (mode == MAINTENANCE_MODE)
            printModeAlreadyEnabled();
        else
            switchToMode(MAINTENANCE_MODE);
    }
    else if (strcmp_P(modeArg, PSTR("economy")) == 0) {
        if (mode == ECONOMY_MODE)
            printModeAlreadyEnabled();
        else
            switchToMode(ECONOMY_MODE);
    }
    else if (strcmp_P(modeArg, PSTR("standard")) == 0) {
        if (mode == STANDARD_MODE)
            printModeAlreadyEnabled();
        else
            switchToMode(STANDARD_MODE);
    }
    else {
        Serial.print(F("Mode inconnu."));
    }
}
void commandEnable(int id = NULL) {
    if (id == NULL) {
        for (int i = 0; i < NUMBER_OF_SENSORS; i++)
            setSetting(sensors[i]->enabled, true);
    }
    else {
        if (getSetting(sensors[id]->enabled))
            Serial.print(F("Ce capteur est déjà activé.\n\r"));
        else {
            setSetting(sensors[id]->enabled, true);
            printSensorEnabled(id);
        }
    }
}
void commandDisable(int id = NULL) {
    if (id == NULL) {
        for (int i = 0; i < NUMBER_OF_SENSORS; i++)
            setSetting(sensors[i]->enabled, false);
    }
    else {
        if (!getSetting(sensors[id]->enabled))
            Serial.print(F("Ce capteur est déjà désactivé.\n\r"));
        else {
            setSetting(sensors[id]->enabled, false);
            printSensorDisabled(id);
        }
    }
}
void commandSet(char* variable, int value) {
    Serial.print(variable);
    Serial.println(value);
    if (variable == NULL) {
        char* name;
        name = (char*)malloc(20 * sizeof(char));
        for (int i = 0; i < NUMBER_OF_SETTINGS; i++) {
            strcpy_P(name, settings[i].name);

            Serial.print(name);
            printSpaces(20 - strlen(name));
            Serial.print(F("= "));
            Serial.print(getSetting(i));
            Serial.print(F("\n\r"));
        }
        free(name);
        return;
    }
    for (int i = 0; i < NUMBER_OF_SETTINGS; i++) {
        if (strcmp_P(variable, settings[i].name) == 0) {
            setSetting(i, value);
            Serial.print(F("Paramètre modifié.\n\r"));
            return;
        }
    }
    Serial.print(F("Paramètre inconnu.\n\r"));
}
void commandGet(char* variable) {
    for (int i = 0; i < NUMBER_OF_SETTINGS; i++) {
        if (strcmp_P(variable, settings[i].name) == 0) {
            Serial.print(getSetting(i));
            return;
        }
    }
    Serial.print(F("Paramètre inconnu.\n\r"));
}
void commandReset() {
    resetSettings();
    Serial.println(F("Paramètres réinitialisés."));
}
void commandLast() {
    printData();
}
void commandClock(int hours, int minutes, int seconds) {
    if (!hours || !minutes || !seconds) {
        readClock();
        printClock();
    }
    else {
        if (hours < 0 || hours > 23 || minutes < 0 || minutes > 59 || seconds < 0 || seconds > 59) {
            Serial.print(F("Heure invalide.\n\r"));
            return;
        }
        setHour(hours);
        setMinute(minutes);
        setSecond(seconds);
        Serial.print(F("Heure modifiée.\n\r"));
    }
}
void commandDate(int day, int month, int year) {
    if (!day || !month || !year) {
        readClock();
        printDate();
    }
    else {
        if (day < 1 || day > 31 || month < 1 || month > 12 || year < 0) {
            Serial.print(F("Date invalide.\n\r"));
            return;
        }
        setDay(day);
        setMonth(month);
        setYearFull(year);
        Serial.println(F("Date modifiée.\n\r"));
    }
}
void commandDay(char* day) {
    if (!day) {
        readClock();
        printDayOfWeek();
    }
    else {
        int sum = 0;
        for (int i = 0; i < strlen(day); i++)
            sum += day[i];
        switch (sum) {
            case 540:
                setDayOfWeek(MONDAY);
                printDayModified();
                break;
            case 525:
                setDayOfWeek(TUESDAY);
                printDayModified();
                break;
            case 843:
                setDayOfWeek(WEDNESDAY);
                printDayModified();
                break;
            case 529:
                setDayOfWeek(THURSDAY);
                printDayModified();
                break;
            case 849:
                setDayOfWeek(FRIDAY);
                printDayModified();
                break;
            case 627:
                setDayOfWeek(SATURDAY);
                printDayModified();
                break;
            case 825:
                setDayOfWeek(SUNDAY);
                printDayModified();
                break;
            default:
                Serial.println(F("Jour invalide.\n\r"));
                return;
        }
    }
}

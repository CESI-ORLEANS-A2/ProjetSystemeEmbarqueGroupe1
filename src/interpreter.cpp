#include "interpreter.hpp"

#if INTERPRETER
char inputBuffer[INPUT_BUFFER_SIZE];
int inputLength = 0;

void initInterpreter() {
    Serial.println(F("Bienvenue dans l'invite de commande de la station météo !"));
#if COMMAND_HELP
    Serial.println(F("Commandes disponibles: taper 'help'"));
#endif
    Serial.print(F("Mode actuel : "));
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
                Serial.write("\b \b");
            }
        }
        else if (data == '\n') {
            Serial.write("\r\n");
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
            Serial.write(data);
        }
    }
}

void runCommand() {
    char buf1[INPUT_BUFFER_SIZE], buf2[10];
    char* commandLine = buf1;
    char* command = buf2;
    strcpy(commandLine, inputBuffer);
    strcpy(command, strsep_P(&commandLine, PSTR(" ")));

    int sum = 0; // Calcul de la somme des caractères de la commande pour un switch plus rapide
    for (int i = 0; i < (int)strlen(command); i++)
        sum += command[i];

    switch (sum) {
#if COMMAND_HELP
    case 425: // help
        commandHelp(strsep_P(&commandLine, PSTR(" ")));
        break;
#endif
    case 444: // list
        commandList();
        break;
    case 432: // live
        if (mode != MAINTENANCE_MODE)
            printCommandUnavailableInThisMode();
        else
            commandLive();
        break;
    case 421: // mode
        commandMode(strsep_P(&commandLine, PSTR(" ")));
        break;
#if COMMAND_ENABLE
    case 615: // enable
        if (mode != CONFIGURATION_MODE)
            printCommandUnavailableInThisMode();
        else
            commandEnable(atoi(strsep_P(&commandLine, PSTR(" "))));
        break;
    case 724: // disable
        if (mode != CONFIGURATION_MODE)
            printCommandUnavailableInThisMode();
        else
            commandDisable(atoi(strsep_P(&commandLine, PSTR(" "))));
        break;
#endif
    case 332: // set
        if (mode != CONFIGURATION_MODE)
            printCommandUnavailableInThisMode();
        else {
            char buf1[MAX_NAME_LENGTH], buf2[10];
            char* name = buf1, * value = buf2;

            name = strsep_P(&commandLine, PSTR(" "));
            value = strsep_P(&commandLine, PSTR(" "));

            commandSet(name, atoi(value));
        }
        break;
#if COMMAND_GET
    case 320: // get
        if (mode != CONFIGURATION_MODE)
            printCommandUnavailableInThisMode();
        else
            commandGet(strsep_P(&commandLine, PSTR(" ")));
        break;
#endif
    case 547: // reset
        if (mode != CONFIGURATION_MODE)
            printCommandUnavailableInThisMode();
        else
            commandReset();
        break;
#if COMMAND_LAST
    case 436: // last
        commandLast();
        break;
#endif
    case 524: // clock
        if (mode != CONFIGURATION_MODE)
            printCommandUnavailableInThisMode();
        else {
            char buf1[3], buf2[3], buf3[3];
            char* hours = buf1, * minutes = buf2, * seconds = buf3;

            hours = strsep_P(&commandLine, PSTR(" "));
            minutes = strsep_P(&commandLine, PSTR(" "));
            seconds = strsep_P(&commandLine, PSTR(" "));

            commandClock(atoi(hours), atoi(minutes), atoi(seconds));
        }
        break;
    case 414: // date
        if (mode != CONFIGURATION_MODE)
            printCommandUnavailableInThisMode();

        else {
            char buf1[3], buf2[3], buf3[5];
            char* day = buf1, * month = buf2, * year = buf3;
            

            day = strsep_P(&commandLine, PSTR(" "));
            month = strsep_P(&commandLine, PSTR(" "));
            year = strsep_P(&commandLine, PSTR(" "));

            commandDate(atoi(day), atoi(month), atoi(year));
        }
        break;
    case 318: // day
        if (mode != CONFIGURATION_MODE)
            printCommandUnavailableInThisMode();
        else
            commandDay(strsep_P(&commandLine, PSTR(" ")));
    case 774: // version
        printVersion();
        Serial.println();
        break;
    default:
        printUnknownCommand();
        break;
    }
}

void printPrompt() {
    if (!liveMode)
        Serial.print(F("\n\r> "));
}
void printBuffer() {
    Serial.print(inputBuffer);
}
#if COMMAND_HELP
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
    Serial.print(F("   - "));
}
#endif
void printUnknownCommand() {
    Serial.println(F("Inconnue"));
}
void printModeAlreadyEnabled() {
    Serial.println(F("Déjà en cours"));
}
void printSensorEnabled(int id) {
    char name[MAX_NAME_LENGTH];
    strcpy_P(name, sensors[id].name);
    Serial.print(F("Capteur "));
    Serial.print(name);
    Serial.println(F(" activé"));
}
void printSensorDisabled(int id) {
    char name[MAX_NAME_LENGTH];
    strcpy_P(name, sensors[id].name);
    Serial.print(F("Capteur "));
    Serial.print(name);
    Serial.println(F(" désactivé"));
}
void printCommandUnavailableInThisMode() {
    Serial.println(F("Indisponible dans ce mode"));
}
void printClock() {
    Serial.print(getHour());
    Serial.print(':');
    Serial.print(getMinute());
    Serial.print(':');
    Serial.println(getSecond());
}
void printDate() {
    Serial.print(getDay());
    Serial.print('/');
    Serial.print(getMonth());
    Serial.print('/');
    Serial.println(getYearFull());
}
void printDayOfWeek() {
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
    Serial.println(F("Jour modifié"));
}

#if COMMAND_HELP
void commandHelp(char* command) {
    if (!command) {
        Serial.println(F("Liste des commandes disponibles :"));
#if DETAILED_HELP_COMMAND
        printHelpListDash();Serial.println(F("help [command?]"));
        printHelpListDash();Serial.println(F("list"));
        printHelpListDash();Serial.println(F("live"));
#if COMMAND_LAST
        printHelpListDash();Serial.println(F("last"));
#endif
#if COMMAND_ENABLE
        printHelpListDash();Serial.println(F("enable [id?]"));
        printHelpListDash();Serial.println(F("disable [id?]"));
#endif
        printHelpListDash();Serial.println(F("set [name] [value]"));
#if COMMAND_GET
        printHelpListDash();Serial.println(F("get [name]"));
#endif
        printHelpListDash();Serial.println(F("mode [mode?]"));
        printHelpListDash();Serial.println(F("reset"));
        printHelpListDash();Serial.println(F("clock [hours?] [minutes?] [seconds?]"));
        printHelpListDash();Serial.println(F("date [day?] [month?] [year?]"));
        printHelpListDash();Serial.println(F("day [day?]"));
        printHelpListDash();Serial.println(F("version"))
#else 
        Serial.println(F(" - help : Affiche ce menu"));
        Serial.println(F(" - list : Affiche la liste des capteurs disponibles"));
        Serial.println(F(" - live : Affiche les dernières données récoltées en temps réel"));
#if COMMAND_LAST
        Serial.println(F(" - last : Affiche une fois les dernières données récoltées"));
#endif
#if COMMAND_ENABLE
        Serial.println(F(" - enable [id?] : Active un ou plusieurs capteurs"));
        Serial.println(F(" - disable [id?] : Désactive un ou plusieurs capteurs"));
#endif 
        Serial.println(F(" - set [name] [value] : Modifie les paramètres"));
#if COMMAND_GET
        Serial.println(F(" - get [name] : Affiche la valeur d'un paramètre"));
#endif
        Serial.println(F(" - mode [mode?] : Change le mode de la station météo"));
        Serial.println(F(" - reset : Réinitialise les paramètres"));
        Serial.println(F(" - clock [hours?] [minutes?] [seconds?] : Affiche ou change l'heure"));
        Serial.println(F(" - date [day?] [month?] [year?] : Affiche ou change la date"));
        Serial.println(F(" - day [day?] : Affiche ou change le jour actuel"));
        Serial.println(F(" - version : Affiche la version du logiciel"));
#endif
    }
#if DETAILED_HELP_COMMAND
    else {
        int sum = 0; // Calcul de la somme des caractères de la commande pour un switch plus rapide
        for (int i = 0; i < strlen(command); i++)
            sum += command[i];

        switch (sum) {
        case 425: // help
            printHelpCommand();Serial.println(F("HELP"));
            printHelpNeededMode();Serial.println(F("/"));
            printHelpDesciption();Serial.println(F("Affiche ce menu"));
            printHelpSyntax();Serial.println(F("help [command?]"));
            printHelpArguments();
            printHelpListDash();Serial.println(F("command (optionnel) : Permet d'obtenir l'aide pour une commande particulière"));
            break;
        case 444: // list
            printHelpCommand();Serial.println(F("LIST"));
            printHelpNeededMode();Serial.println(F("/"));
            printHelpDesciption();Serial.println(F("Affiche la liste des capteurs disponibles et quelques informations"));
            printHelpSyntax();Serial.println(F("list"));
            break;
        case 432: // live
            printHelpCommand();Serial.println(F("LIVE"));
            printHelpNeededMode();Serial.println(F("maintenance"));
            printHelpDesciption();Serial.println(F("Affiche ou arrête d'afficher les données récoltées toutes les secondes"));
            printHelpSyntax();Serial.println(F("live"));
            break;
        case 421: // mode
            printHelpCommand();Serial.println(F("MODE"));
            printHelpNeededMode();Serial.println(F("/"));
            printHelpDesciption();Serial.println(F("Affiche le mode actuel de la station météo ou le change"));
            printHelpSyntax();Serial.println(F("mode ['configuration' | 'maintenance' | 'economy' | 'standard'?]"));
            printSpaces(14);Serial.println(F("Dans le cas de mode standard et économique, cela met fin à la connexion"));
            printSpaces(14);Serial.println(F("Les modes :"));
            printSpaces(14);printHelpListDash();Serial.println(F("configuration : Permet de configurer les différents paramètres, la récupération des données est désactivé"));
            printSpaces(14);printHelpListDash();Serial.println(F("maintenance : Permet d'accéder aux données et de changer la carte SD"));
            printSpaces(34);Serial.println(F("L'enregistrement des données est désactivé"));
            printSpaces(14);printHelpListDash();Serial.println(F("economy : Désactive certains capteurs"));
            printSpaces(14);printHelpListDash();Serial.println(F("standard : Mode de récupération des données par défaut"));
            printHelpArguments();
            printHelpListDash();Serial.println(F("'configuration' | 'maintenance' | 'economy' | 'standard' (optionnel) : Le mode de configuration"));
            break;
#if COMMAND_ENABLE
        case 615: // enable
            printHelpCommand();Serial.println(F("ENABLE"));
            printHelpNeededMode();Serial.println(F("configuration"));
            printHelpDesciption();Serial.println(F("Active un ou tous capteurs"));
            printHelpSyntax();Serial.println(F("enable [id?]"));
            printHelpArguments();
            printHelpListDash();Serial.println(F("id (optionnel) : Le nom du capteur particulier"));
            break;
        case 724: // disable
            printHelpCommand();Serial.println(F("DISABLE"));
            printHelpNeededMode();Serial.println(F("configuration"));
            printHelpDesciption();Serial.println(F("Désactive un ou tous capteurs"));
            printHelpSyntax();Serial.println(F("disable [id?]"));
            printHelpArguments();
            printHelpListDash();Serial.println(F("id (optionnel) : Le nom du capteur particulier"));
            break;
#endif
        case 332: // set
            printHelpCommand();Serial.println(F("SET"));
            printHelpNeededMode();Serial.println(F("configuration"));
            printHelpDesciption();Serial.println(F("Affiche tous les paramètres ou modifie un paramètre"));
            printHelpSyntax();Serial.println(F("set [nom] [valeur]"));
            printHelpArguments();
            printHelpListDash();Serial.println(F("nom (optionnel): Le nom du paramètre à modifier"));
            printHelpListDash();Serial.println(F("id (optionnel) : Le nom du capteur particulier"));
            break;
#if COMMAND_GET
        case 320: // get
            printHelpCommand();Serial.println(F("GET"));
            printHelpNeededMode();Serial.println(F("configuration"));
            printHelpDesciption();Serial.println(F("Affiche la valeur d'un paramètre"));
            printHelpSyntax();Serial.println(F("get {nom}"));
            printHelpArguments();
            printHelpListDash();Serial.println(F("nom: Le nom du paramètre à modifier"));
            break;
#endif
        case 547: // reset
            printHelpCommand();Serial.println(F("RESET"));
            printHelpNeededMode();Serial.println(F("configuration"));
            printHelpDesciption();Serial.println(F("Réinitialise les paramètres de la station météo"));
            printHelpSyntax();Serial.println(F("reset [id?]"));
            printHelpArguments();
            printHelpListDash();Serial.println(F("id (optionnel) : Le nom du capteur particulier"));
            break;
#if COMMAND_LAST
        case 436: // last
            printHelpCommand();Serial.println(F("LAST"));
            printHelpNeededMode();Serial.println(F("/"));
            printHelpDesciption();Serial.println(F("Affiche une fois les dernières données récoltées"));
            printHelpSyntax();Serial.println(F("last"));
            break;
#endif
        case 524: // clock
            printHelpCommand();Serial.println(F("CLOCK"));
            printHelpNeededMode();Serial.println(F("configuration"));
            printHelpDesciption();Serial.println(F("Affiche ou change l'heure"));
            printHelpSyntax();Serial.println(F("clock [hours?] [minutes?] [seconds?]"));
            printHelpArguments();
            printHelpListDash();Serial.println(F("hours (optionnel) : L'heure"));
            printHelpListDash();Serial.println(F("minutes (optionnel) : Les minutes"));
            printHelpListDash();Serial.println(F("seconds (optionnel) : Les secondes"));
            break;
        case 414: // date
            printHelpCommand();Serial.println(F("DATE"));
            printHelpNeededMode();Serial.println(F("configuration"));
            printHelpDesciption();Serial.println(F("Affiche ou change la date"));
            printHelpSyntax();Serial.println(F("date [day?] [month?] [year?]"));
            printHelpArguments();
            printHelpListDash();Serial.println(F("day (optionnel) : Le jour"));
            printHelpListDash();Serial.println(F("month (optionnel) : Le mois"));
            printHelpListDash();Serial.println(F("year (optionnel) : L'année"));
            break;
        case 318: // day
            printHelpCommand();Serial.println(F("DAY"));
            printHelpNeededMode();Serial.println(F("configuration"));
            printHelpDesciption();Serial.println(F("Affiche ou change le jour actuel"));
            printHelpSyntax();Serial.println(F("day [day?]"));
            printHelpArguments();
            printHelpListDash();Serial.println(F("day (optionnel) : Le jour"));
            break;
        case 774: // version
            printHelpCommand();Serial.println(F("VERSION"));
            printHelpNeededMode();Serial.println(F("/"));
            printHelpDesciption();Serial.println(F("Affiche la version du logiciel"));
            printHelpSyntax();Serial.println(F("version"));
            break;
        default:
            printUnknownCommand();
            break;
        }
    }
#endif
}
#endif

void commandList() {
#if NUMBER_OF_SENSORS == 0
    Serial.println(F("| Nom (id)        | Activé ? | Économie ? |"));
    Serial.println(F("|-----------------|----------|------------|"));
    Serial.println(F("| Pas de capteurs...                      |"))
#else

    Serial.println(F("| Nom (id)        | Activé ? | Économie ? |"));
    Serial.println(F("|-----------------|----------|------------|"));

    char name[MAX_NAME_LENGTH];

    for (int i = 0; i < NUMBER_OF_SENSORS; i++) {
        strcpy_P(name, sensors[i].name);

        Serial.print(F("| "));
        Serial.print(name);
        for (int j = 0; j < 16 - (int)strlen_P(sensors[i].name); j++)
            Serial.print(' ');
        Serial.print(F("| "));
        Serial.print(getSetting(sensors[i].enabled) ? F("Oui") : F("Non"));
        Serial.print(F("     | "));
        Serial.print(getSetting(sensors[i].economy) ? F("Oui") : F("Non"));
        Serial.println(F("       |"));
    };

#endif
}
void commandLive() {
    liveMode = true;
    Serial.println(F("Mode live"));
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
        Serial.print(F("Inconnu"));
    }
}

#if COMMAND_ENABLE
void commandEnable(int id = -1) {
    if (id == -1) {
        for (int i = 0; i < NUMBER_OF_SENSORS; i++)
            if (!getSetting(sensors[i].enabled)) {
                setSetting(sensors[i].enabled, true);
                printSensorEnabled(i);
            }
    }
    else {
        if (getSetting(sensors[id].enabled))
            Serial.println(F("Déjà activé"));
        else {
            setSetting(sensors[id].enabled, true);
            printSensorEnabled(id);
        }
    }
}
void commandDisable(int id = -1) {
    if (id == -1) {
        for (int i = 0; i < NUMBER_OF_SENSORS; i++)
            if (getSetting(sensors[i].enabled)) {
                setSetting(sensors[i].enabled, false);
                printSensorDisabled(i);
            }

    }
    else {
        if (!getSetting(sensors[id].enabled))
            Serial.println(F("Déjà désactivé"));
        else {
            setSetting(sensors[id].enabled, false);
            printSensorDisabled(id);
        }
    }
}
#endif

void commandSet(char* setting, int value) {
    if (setting == NULL) {
        for (int i = 0; i < NUMBER_OF_SETTINGS; i++) {
            char name[MAX_SETTING_LENGTH];
            strcpy_P(name, settings[i]->name);

            Serial.print(name);
            for (int j = 0; j < MAX_SETTING_LENGTH - (int)strlen(name); j++)
                Serial.print(' ');
            Serial.print(F("= "));
            Serial.println(getSetting(i));
        }
        return;
    }

    int sum = 0;
    for (int i = 0; i < (int)strlen(setting); i++)
        sum += setting[i];

    for (int i = 0; i < NUMBER_OF_SETTINGS; i++) {

        char name[MAX_SETTING_LENGTH];
        strcpy_P(name, settings[i]->name);
        int settingNameSum = 0;
        for (int j = 0; j < (int)strlen(name); j++)
            settingNameSum += name[j];

        Serial.print(settingNameSum);Serial.print(F(" "));Serial.print(sum);Serial.print(F(" "));Serial.print(name);Serial.print(" ");Serial.print(setting);Serial.println();
        if (sum == settingNameSum) {
            setSetting(i, value);
            Serial.println(F("Modifié"));
            return;
        }
    }
    Serial.println(F("Inconnu"));
}

#if COMMAND_GET
void commandGet(char* setting) {
    for (int i = 0; i < NUMBER_OF_SETTINGS; i++) {
        if (strcmp_P(setting, settings[i]->name) == 0) {
            Serial.println(getSetting(i));
            return;
        }
    }
    Serial.println(F("Inconnu"));
}
#endif

void commandReset() {
    resetSettings();
    Serial.println(F("Paramètres réinitialisés"));
}

#if COMMAND_LAST
void commandLast() {
#if LIVE_MODE_SERIAL_OUTPUT == OUTPUT_CSV
    printCSVHeader();
#endif
    printData();
}
#endif

void commandClock(int hours, int minutes, int seconds) {
    if (!hours || !minutes || !seconds) {
        readClock();
        printClock();
    }
    else {
        if (hours < 0 || hours > 23 || minutes < 0 || minutes > 59 || seconds < 0 || seconds > 59) {
            Serial.println(F("Heure invalide"));
            return;
        }
        setHour(hours);
        setMinute(minutes);
        setSecond(seconds);
        Serial.println(F("Heure modifiée"));
    }
}
void commandDate(int day, int month, int year) {
    if (!day || !month || !year) {
        readClock();
        printDate();
    }
    else {
        if (day < 1 || day > 31 || month < 1 || month > 12 || year < 0) {
            Serial.println(F("Date invalide"));
            return;
        }
        setDay(day);
        setMonth(month);
        setYearFull(year);
        Serial.println(F("Date modifiée"));
    }
}
void commandDay(char* day) {
    if (!day) {
        readClock();
        printDayOfWeek();
    }
    else {
        int sum = 0;
        for (int i = 0; i < (int)strlen(day); i++)
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
            Serial.println(F("Jour invalide"));
            return;
        }
    }
}
#endif
#include "includes/interpreter.hpp"

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
                runCommand(inputBuffer);
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

void runCommand(char* commandLine) {
    char* command = strsep(&commandLine, " ");

    if (strcmp_P(command, PSTR("help")) == 0) {
        commandHelp(strsep(&commandLine, " "));
    }
    else if (strcmp_P(command, PSTR("list")) == 0) {
        commandList();
    }
    else if (strcmp_P(command, PSTR("live")) == 0) {
        commandLive();
    }
    else if (strcmp_P(command, PSTR("mode")) == 0) {
        commandMode(strsep(&commandLine, " "));
    }
    else {
        printUnknownCommand();
    }
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
            // " - last : Affiche une fois les dernières données récoltées.\n\r"
            " - enable [id?] : Active un ou plusieurs capteurs.\n\r"
            " - disable [id?] : Désactive un ou plusieurs capteurs.\n\r"
            // " - set [name] [value] [id?] : Modifie les paramètres d'un ou plusieurs capteurs.\n\r"
            " - mode [mode?] : Change le mode de la station météo.\n\r"
            // " - erase [id?] : Efface les données d'un ou tous les capteurs.\n\r"
            // " - reset [id?] : Réinitialise les paramètres d'un ou tous les capteurs.\n\r"
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
    else if (strcmp_P(command, PSTR("enabled")) == 0) {
        printHelpCommand();Serial.println(F("ENABLED"));
        printHelpNeededMode();Serial.println(F("configuration"));
        printHelpDesciption();Serial.println(F("Active un ou tous capteurs."));
        printHelpSyntax();Serial.println(F("enabled [enabled] [id?]"));
        printHelpArguments();
        printHelpListDash();Serial.println(F("enabled : true ou false"));
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

    for (int i = 0; i < NUMBER_OF_SENSORS; i++) {

        const char* name = sensors[i]->name;
        const char* enabled = sensors[i]->enabled ? "Oui" : "Non";
        const char* economy = sensors[i]->economy ? "Oui" : "Non";

        char line[52] = "| ";

        strcat_P(line, name);
        for (int j = 0; j < (24 - (int)strlen_P(name)); j++)
            strcat(line, " ");
        strcat(line, " | ");
        strcat(line, enabled);
        strcat(line, "      | ");
        strcat(line, economy);
        strcat(line, "        |\n\r");
        Serial.write(line);
    };
#endif
}
void commandLive() {
    if (mode != MAINTENANCE_MODE) {
        Serial.print(F("Cette commande n'est disponible que dans le mode maintenance.\n\r"));
        return;
    }
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
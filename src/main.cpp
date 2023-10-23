#include "main.hpp"

int mode = STANDARD_MODE;
int previousMode = STANDARD_MODE;
bool liveMode = false;

// Contient une représentation (structure) de chaque capteur
Sensor* sensors[NUMBER_OF_SENSORS];

void setup() {
    initLED();
    switchLEDToGreen();
    initTimer(); // Initialisation des compteurs

    Serial.begin(SERIAL_BAUD_RATE); // Initialisation du port série (communication avec l'ordinateur)
    // TODO Initialisation carte SD
    // TODO Initialisation GPS => SoftwareSerial

    // TODO mettre dans un fichier boutons.cpp, fonction initButtons
    pinMode(RED_BUTTON_PIN, INPUT_PULLUP); 
    pinMode(GREEN_BUTTON_PIN, INPUT_PULLUP);

    // TODO bouttons.cpp, fonction initButtonsInterrupts
    attachButtonInterrupt(RED_BUTTON_PIN, BUTTON_DELAY, redButtonPressed); // Initialisation des interruptions sur le bouton rouge ainsi que son timer pour le délai
    attachButtonInterrupt(GREEN_BUTTON_PIN, BUTTON_DELAY, greenButtonPressed); // Initialisation des interruptions sur le bouton vert ainsi que son timer pour le délai

    // Initialisation des capteurs
    initTemperatureSensor();
    initHumiditySensor();
    // initPressureSensor();
    // initBrightnessSensor();
    
    if (Serial) Serial.println(F("Station Météo v3"));

#if INTERPRETER // Initialisation de l'interpréteur si activé
    initInterpreter();
#endif

    if (digitalRead(RED_BUTTON_PIN) == LOW) // Si le bouton rouge est appuyé au démarrage, on passe en mode configuration
        switchToConfigurationMode();
}

void loop() {
#if INTERPRETER
    runInterpreterStep(); // On exécute une étape de l'interpréteur
#endif

    // On exécute une étape du mode actuel
    switch (mode) {
    case STANDARD_MODE:
        runStandardModeStep();
        break;
    case ECONOMY_MODE:
        runEconomyModeStep();
        break;
    case CONFIGURATION_MODE:
        runConfigurationModeStep();
        break;
    case MAINTENANCE_MODE:
        runMaintenanceModeStep();
        break;
    }
}

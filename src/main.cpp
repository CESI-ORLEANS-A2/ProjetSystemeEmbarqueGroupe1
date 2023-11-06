/**
 * @file main.cpp
 *
 * @mainpage Station Météo
 *
 * @section intro Introduction
 *
 * Ce projet est le programme pour une station météo réalisée dans
 * le cadre d'un bloc d'apprentissage au CESI.
 *
 * @section author Auteurs
 *
 * Réalisé par :
 * - Alban ([@0xybo](https://github.com/0xybo))
 * - Hugo ([@HuHel](https://github.com/HuHel))
 * - Adam ([@aaben40](https://github.com/aaben40))
 * - Romain ([@RomainHemart](https://github.com/RomainHemart))
 * - Matthieu ([@Aureste-o](https://github.com/Aureste-o))
 *
 * @section license License
 *
 * MIT License
 *
 * Copyright (c) 2023 Alban G. (@0xybo), Hugo H. (@HuHel), Adam B. (@aaben40), Romain H. (@RomainHemart), Matthieu M. (@Aureste-o)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
*/

#include "main.hpp"

Mode mode = STANDARD_MODE;
Mode previousMode = STANDARD_MODE;
#if INTERPRETER
bool liveMode = false;
#endif
float lastMeasurements[NUMBER_OF_SENSORS];

void setup() {
    initSettings();
#if SETTINGS_IN_EEPROM
    updateSettingsFromEEPROM();
#endif
    initLED(); // Initialisation de la LED
    initTimer1(); // Initialisation du compteur

    initSerial(); // Initialisation du port série
    initButtons(); // Initialisation des boutons (sans les interruptions)

    // Initialisation des capteurs
    initTemperatureSensor();
    initHumiditySensor();
    initPressureSensor();
    initBrightnessSensor();

    initClock(); // Initialisation de l'horloge
#if GPS_ENABLED
    initGPS(); // Initialisation du GPS
#endif

    if (digitalRead(RED_BUTTON_PIN) == LOW) // Si le bouton rouge est appuyé au démarrage, on passe en mode configuration
        switchToConfigurationMode();
    else if (digitalRead(GREEN_BUTTON_PIN) == LOW)
        switchToMaintenanceMode();
    else { // Sinon, on monte la carte SD et on passe la LED en vert
        mount();
        switchLEDToGreen();
    }

#if INTERPRETER // Initialisation de l'interpréteur si activé
    initInterpreter();
#endif

    initButtonsInterrupt(); // Initialisation des interruptions des boutons
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
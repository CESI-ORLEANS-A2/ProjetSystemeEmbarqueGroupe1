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
 * - Hugo ()
 * - Adam ()
 * - Romain ()
 * - Matthieu ()
 *
 * @section license License
 *
 * MIT License
 *
 * Copyright (c) 2023 Alban G. (@0xybo), Hugo H. (), Adam B. (), Romain H. (), Matthieu M. ()
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

int mode = STANDARD_MODE;
int previousMode = STANDARD_MODE;
bool liveMode = false;
float lastMeasurements[NUMBER_OF_SENSORS];

Sensor* sensors[NUMBER_OF_SENSORS];

void setup() {
    initSettings();
    updateSettingsFromEEPROM();
    initLED();
    initTimer(); // Initialisation des compteurs

    initSerial();
    initButtons();

    // Initialisation des capteurs
    initTemperatureSensor();
    initHumiditySensor();
    // initPressureSensor();
    // initBrightnessSensor();

    initClock();
    initGPS();

    if (digitalRead(RED_BUTTON_PIN) == LOW) // Si le bouton rouge est appuyé au démarrage, on passe en mode configuration
        switchToConfigurationMode();
    else {
        mount();
        switchLEDToGreen();
    }

#if INTERPRETER // Initialisation de l'interpréteur si activé
    initInterpreter();
#endif

    initButtonsInterrupt();
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

void restart() {
    // TODO Activé le pin reset
}
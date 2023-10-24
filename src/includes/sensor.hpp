#ifndef Sensor_h
#define Sensor_h

#include <Arduino.h>
#include <Wire.h>

#include "consts.hpp"
#include "settings.hpp"

/*!
 * @brief Classe représentant un capteur
 *
 * Cette classe contient les informations relatives à un capteur. 
 * 
 * Elle permet de faciliter la récupération des données des capteurs en fournissant
 * une interface commune pour tous les capteurs. Elle fourni notamment une méthode d'initialisation
 * et une méthode de mesure.
 */
class Sensor {
public:
    Sensor(
        const char* name,
        int protocol,
        int device,
        int enabled,
        bool economy,
        void (*init)() = NULL,
        float (*measure)() = NULL
    );

    const char* name;
    const int protocol;
    const int device;
    int enabled;
    bool economy;
    void (*init)();
    float (*measure)();

    float acquisition();

    void initI2C();
    void initAnalog();

    long measureAnalog();
};

#endif
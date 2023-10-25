#ifndef Sensor_h
#define Sensor_h

#include <Arduino.h>
#include <Wire.h>

#include "consts.hpp"
#include "settings.hpp"

/**
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
    /**
     * @brief Constructeur de la classe Sensor
     *
     * @param name Nom du capteur
     * @param protocol Protocole utilisé par le capteur
     * @param device Adresse ou pin du capteur
     * @param enabled Si le capteur est activé
     * @param economy Si le capteur est activé en mode économique
     * @param init Fonction d'initialisation du capteur
     * @param measure Fonction de mesure du capteur
     * 
     * @ref Sensor::init()
     * @ref Sensor::protocol
     * @ref Sensor::initI2C()
     * @ref Sensor::initAnalog()
     * @ref I2C_PROTOCOL
     * @ref ANALOG_PROTOCOL
     */
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

    /**
     * @brief Fonction d'acquisition des données du capteur
     *
     * @return Valeur (nombre réel) mesurée par le capteur
     * 
     * @ref Sensor::measure()
     * @ref Sensor::measureAnalog()
     * @ref Sensor::enabled
     * @ref getSetting()
     * @ref ANALOG_PROTOCOL
     */
    float acquisition();

    /**
     * @brief Fonction d'initialisation du capteur en I2C
     */
    void initI2C();
    /**
     * @brief Fonction d'initialisation du capteur en analogique
     * 
     * @ref Sensor::device
     */
    void initAnalog();
    /**
     * @brief Fonction de mesure du capteur en analogique
     *
     * @return Valeur (nombre réel) mesurée par le capteur
     * 
     * @ref Sensor::device
     */
    long measureAnalog();
};

#endif
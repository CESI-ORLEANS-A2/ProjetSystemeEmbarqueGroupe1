#ifndef Sensor_h
#define Sensor_h

#include <Arduino.h>
#include <Wire.h>

#include "consts.hpp"
#include "settings.hpp"
/**
 * @brief Structure représentant un capteur
 *
 * Cette classe contient les informations relatives à un capteur.
 *
 * Elle permet de faciliter la récupération des données des capteurs en fournissant
 * une interface commune pour tous les capteurs. Elle fourni notamment une méthode d'initialisation
 * et une méthode de mesure.
 */
struct Sensor {
    char* name;
    int enabled;
#if INTERPRETER
    int economy;
#endif
    float (*measure)();
};

// /**
//  * @brief Classe représentant un capteur
//  *
//  * Cette classe contient les informations relatives à un capteur.
//  *
//  * Elle permet de faciliter la récupération des données des capteurs en fournissant
//  * une interface commune pour tous les capteurs. Elle fourni notamment une méthode d'initialisation
//  * et une méthode de mesure.
//  */
//     class Sensor {
//     public:
//         /**
//          * @brief Constructeur de la classe Sensor
//          *
//          * @param name Nom du capteur
//          * @param enabled Si le capteur est activé
//          * @param economy Si le capteur est activé en mode économique
//          * @param measure Fonction de mesure du capteur
//          */
//         Sensor(
//             const char* name,
//             int enabled,
//             int economy,
//             float (*measure)() = NULL
//         );

//         const char* name;
//         int enabled;
//         int economy;
//         float (*measure)();

//         /**
//          * @brief Fonction d'acquisition des données du capteur
//          *
//          * @return Valeur (nombre réel) mesurée par le capteur
//          *
//          * Références :
//          * @ref Sensor::measure()
//          * @ref Sensor::enabled
//          * @ref getSetting()
//          */
//         float acquisition();
// };

#endif
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
 * 
 * Cette structure contient : 
 *  - L'adresse mémoire Flash du nom du capteur
 *  - L'identifiant associé au paramètre réprésentant l'état du capteur
 *  - L'identifiant associé au paramètre réprésentant l'état du capteur en mode économie
 *  - Un pointeur vers la fonction de mesure du capteur
 */
struct Sensor {
    /**
     * @brief Adresse mémoire Flash du nom du capteur
    */
    char* name;
    /**
     * @brief Identifiant associé au paramètre réprésentant l'état du capteur
    */
    int enabled;
#if INTERPRETER
    /**
     * @brief Identifiant associé au paramètre réprésentant l'état du capteur en mode économie
    */
    int economy;
#endif
    /**
     * @brief Pointeur vers la fonction de mesure du capteur
    */
    float (*measure)();
};

/**
 * @brief Contient une représentation (structure) de chaque capteur
 */
extern Sensor sensors[NUMBER_OF_SENSORS];

#endif
#include "sensor.hpp"

// Sensor::Sensor(
//     const char* name,
//     int enabled,
// #if INTERPRETER
//     int economy,
// #endif
//     float (*measure)()
// ) :
//     name(name), // Initialisation des attributs
//     enabled(enabled),
// #if INTERPRETER
//     economy(economy),
// #endif
//     measure(measure) {
// }

// float Sensor::acquisition() {
//     if (!getSetting(this->enabled)) return NULL; // Si le capteur n'est pas activé, on retourne NULL

//     if (this->measure != NULL)
//         return this->measure(); // Mesure du capteur si une fonction de mesure est définie

//     return ACQUISITION_ERROR_VALUE; // Sinon, on retourne une valeur d'erreur
// }
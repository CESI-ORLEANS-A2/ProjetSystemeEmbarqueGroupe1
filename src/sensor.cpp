#include "sensor.hpp"

Sensor::Sensor(
    const char* name, 
    const int device,
    int enabled,
    int economy,
    void (*init)(),
    float (*measure)()
) :
    name(name), // Initialisation des attributs
    device(device),
    enabled(enabled),
    economy(economy),
    init(init),
    measure(measure) {
    if (this->init != NULL)
        this->init(); // Initialisation du capteur si une fonction d'initialisation est définie
}

float Sensor::acquisition() {
    if (!getSetting(this->enabled)) return NULL; // Si le capteur n'est pas activé, on retourne NULL

    if (this->measure != NULL)
        return this->measure(); // Mesure du capteur si une fonction de mesure est définie
}

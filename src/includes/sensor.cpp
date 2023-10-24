#include "includes/sensor.hpp"

/*!
 * @brief Constructeur de la classe Sensor
 *
 * @param name Nom du capteur
 * @param protocol Protocole utilisé par le capteur
 * @param device Adresse ou pin du capteur
 * @param enabled Si le capteur est activé
 * @param economy Si le capteur est activé en mode économique
 * @param init Fonction d'initialisation du capteur
 * @param measure Fonction de mesure du capteur
 */
Sensor::Sensor(
    const char* name,
    const int protocol,
    const int device,
    int enabled,
    bool economy,
    void (*init)(),
    float (*measure)()
) :
    name(name),
    protocol(protocol),
    device(device),
    enabled(enabled),
    economy(economy),
    init(init),
    measure(measure) {
    if (this->init != NULL)
        this->init();

    else switch (this->protocol) {
    case I2C_PROTOCOL:
        this->initI2C();
        break;
    case ANALOG_PROTOCOL:
        this->initAnalog();
        break;
    }
}

/*!
 * @brief Fonction d'acquisition des données du capteur
 *
 * @return Valeur (nombre réel) mesurée par le capteur
 */
float Sensor::acquisition() {
    if (!getSetting(this->enabled)) return NULL;

    if (this->measure != NULL)
        return this->measure();

    switch (this->protocol) {
    case ANALOG_PROTOCOL:
        return this->measureAnalog();
        break;

    default:
        return NULL;
        break;
    }
}

/*!
 * @brief Fonction d'initialisation du capteur en I2C
 */
void Sensor::initI2C() {

};
/*!
 * @brief Fonction d'initialisation du capteur en analogique
 */
void Sensor::initAnalog() {
    pinMode(this->device, INPUT);
};

/*!
 * @brief Fonction de mesure du capteur en analogique
 *
 * @return Valeur (nombre réel) mesurée par le capteur
 */
long Sensor::measureAnalog() {
    return analogRead(this->device);
};
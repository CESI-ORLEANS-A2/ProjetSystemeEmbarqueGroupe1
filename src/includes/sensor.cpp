#include "includes/sensor.hpp"

// Représente un capteur
Sensor::Sensor(
    const char* name,
    const int protocol,
    const int device,
    bool enabled,
    bool economy,
    void (*init)(),
    long (*measure)()
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

long Sensor::acquisition() {
    if (!this->enabled) return NULL;

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

void Sensor::initI2C() {

};
void Sensor::initAnalog() {
    pinMode(this->device, INPUT);
};

long Sensor::measureAnalog() {
    return analogRead(this->device);
};
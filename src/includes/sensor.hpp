#ifndef Sensor_h
#define Sensor_h

#include <Arduino.h>
#include <Wire.h>

#include "consts.hpp"

extern bool wireInitialized;

class Sensor {
public:
    Sensor(
        const char* name,
        int protocol,
        int device,
        bool enabled,
        bool economy,
        void (*init)() = NULL,
        long (*measure)() = NULL
    );

    const char* name;
    const int protocol;
    const int device;
    bool enabled;
    bool economy;
    void (*init)();
    long (*measure)();

    long acquisition();

    void initI2C();
    void initAnalog();

    long measureAnalog();
};

#endif